//******************************************************************************
//  Demo Application04 for MSP430/LMP90100 Interface Code Library v1.0
//  Normal Stream Read ADC Data (1 channel) with interrupt and CRC Check
//
//                MSP430F5528
//             -----------------
//         /|\|              XIN|-
//          | |                 |  32kHz
//          --|RST          XOUT|-
//            |                 |
//            |    P3.3/UCA0SIMO|--> SDI 
//            |    P3.4/UCA0SOMI|<-- SDO 
//            |     P2.7/UCA0CLK|--> CLK 
//            |             P2.5|--> CSB 
//            |             P2.4|<-- DRDYB 
//            |                 | 
//
//   Vishy Natarajan
//   Texas Instruments Inc.
//   October 2011
//   Built with CCE Version: 4.2 and IAR Embedded Workbench Version:  5.3x
//******************************************************************************
/*  Copyright 2011-2012 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user who
  downloaded the software, his/her employer (which must be your employer) and
  Texas Instruments Incorporated (the "License"). You may not use this Software
  unless you agree to abide by the terms of the License. The License limits your
  use, and you acknowledge, that the Software may not be modified, copied or
  distributed unless embedded on a Texas Instruments microcontroller which is 
  integrated into your product. Other than for the foregoing purpose, you may 
  not use, reproduce, copy, prepare derivative works of, modify, distribute, 
  perform, display or sell this Software and/or its documentation for any 
  purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL TEXAS
  INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL
  EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT
  LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL
  DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS,
  TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT
  LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
*******************************************************************************/

#include <stdint.h>
#include "TI_LMP90100.h"
#include "TI_LMP90100_register_settings.h"
#include "TI_MSP430.h"
#include "TI_MSP430_hardware_board.h"
#include "TI_MSP430_spi.h"

void TI_LMP90100_WriteRegSettings(uint8_t *);                                  // Configure LMP90100 registers
void process_adc_output(uint32_t *);                                           // dummy adc data process function: toggles LED
volatile uint8_t LMP90100_ADCDataReady = 0;                                    // set to 1 in DRDYB interrupt service routine
#define SAMPLE_ARRAY_SIZE 16                                                   // Store last 16 ADC samples for processing
#define CH_DATA_SIZE 4                                                         // 4 bytes: ADC_DOUT2, ADC_DOUT1, ADC_DOUT0, CRC

//******************************************************************************
void main(void)
{
 
  uint8_t prev_URA;                                                            // Previous Upper Register Address (URA)
  uint8_t count, addr, i, crc_test;
  uint8_t read_buf[CH_DATA_SIZE]; 
  uint32_t adc_data, adc_sample_array[SAMPLE_ARRAY_SIZE];
  
  WDTCTL = WDTPW+WDTHOLD;                                                      // Stop WDT
  
  TI_LMP90100_LED_PxOUT |= TI_LMP90100_LED_PIN;                                // Set LED ON
  TI_LMP90100_LED_PxDIR |= TI_LMP90100_LED_PIN;                                // Set pin direction is output
  
  // configure Port Pin to handle Data Ready Bar Output (DRDYB) from LMP90100
  TI_LMP90100_DRDYB_PxDIR &= ~TI_LMP90100_DRDYB_PIN;                           // Set up port pin for DRDYB
  TI_LMP90100_DRDYB_PxIES |= TI_LMP90100_DRDYB_PIN;                            // Interrupt Edge Select
  TI_LMP90100_DRDYB_PxIFG &= ~TI_LMP90100_DRDYB_PIN;                           // Clear Interrupt Flag
  TI_LMP90100_DRDYB_PxIE |= TI_LMP90100_DRDYB_PIN;                             // Enable Port interrupt  
  
  TI_LMP90100_SPISetup();                                                      // Initilaize MSP430 SPI Block
  prev_URA = LMP90100_URA_END;                                                 // Initialize prev_URA to invalid segment 


  TI_LMP90100_WriteRegSettings(&prev_URA);                                     // Set up LMP90100 for Channel 0 Scan

  addr = TI_LMP90100_ADC_DOUT2_REG;                                            // Start Reading from ADC_DOUT2 Register
  count = CH_DATA_SIZE;                                                        // bytes to read: ADC_DOUT2 - ADCDOUT0, CRC
  i = 0;
  while (1)
  {
    if (LMP90100_ADCDataReady)
    {
      LMP90100_ADCDataReady = 0;                                               // clear flag      
      TI_LMP90100_SPINormalStreamReadADC(addr, read_buf, count, &prev_URA);    // read adc output into read_buf
      
      adc_data = ((uint32_t) read_buf[0] << 16) 
                 | ((uint16_t) read_buf[1] << 8) | read_buf[2];                // form raw adc output data 
      
      crc_test = TI_LMP90100_SPICRCCheck(read_buf, CH_DATA_SIZE-1);            // test if CRC read from device matches computed

      if (crc_test == CRC_PASS)
      {
        adc_sample_array[i] = adc_data;
        if (++i == SAMPLE_ARRAY_SIZE)                                          // sample array is full
        {
          process_adc_output(adc_sample_array);                                // dummy app function: no error toggles led
          i = 0;
        }
      }
    } else
    { // CRC mismatch, discard the sample
      TI_LMP90100_LED_PxOUT &= ~TI_LMP90100_LED_PIN;                           // Set LED OFF         
    }
    __bis_SR_register(LPM0_bits + GIE);                                        // Enter LPM0, enable interrupts
    __no_operation();                                                          // For debugger 
  } 
}
//******************************************************************************
//  void TI_LMP90100_WriteRegSettings(uint8_t *)
//
//  DESCRIPTION:
//  LMP90100 registers are configured to the values defined LMP90100_register_settings.h
//  These register settings can easily be obtained from the "Register configuration file"  
//  saved from Sensor AFE Software
//
//  ARGUMENTS:
//      pURA indicating the previous register segment that was accessed
//******************************************************************************

void TI_LMP90100_WriteRegSettings(uint8_t *pURA)
{
 
  TI_LMP90100_SPIWriteReg(TI_LMP90100_RESETCN_REG, 
                          TI_LMP90100_RESETCN_REG_VALUE, pURA);                // register and conversion reset
  TI_LMP90100_SPIWriteReg(TI_LMP90100_SPI_HANDSHAKECN_REG, 
                          TI_LMP90100_SPI_HANDSHAKECN_REG_VALUE, pURA);        // SDO high z delayed 
  TI_LMP90100_SPIWriteReg(TI_LMP90100_SPI_STREAMCN_REG, 
                          TI_LMP90100_SPI_STREAMCN_REG_VALUE, pURA);           // normal streaming
  TI_LMP90100_SPIWriteReg(TI_LMP90100_PWRCN_REG, 
                          TI_LMP90100_PWRCN_REG_VALUE, pURA);                  // active mode
  TI_LMP90100_SPIWriteReg(TI_LMP90100_ADC_RESTART_REG, 
                          TI_LMP90100_ADC_RESTART_REG_VALUE, pURA);            // disable restart conversion
  TI_LMP90100_SPIWriteReg(TI_LMP90100_GPIO_DIRCN_REG, 
                          TI_LMP90100_GPIO_DIRCN_REG_VALUE, pURA);             // D6 is an output, D1-D5 are inputs
  TI_LMP90100_SPIWriteReg(TI_LMP90100_GPIO_DAT_REG, 
                          TI_LMP90100_GPIO_DAT_REG_VALUE, pURA);               // Set D6 high
  TI_LMP90100_SPIWriteReg(TI_LMP90100_BGCALCN_REG, 
                          TI_LMP90100_BGCALCN_REG_VALUE, pURA);                // Background calibration off 
  TI_LMP90100_SPIWriteReg(TI_LMP90100_SPI_DRDYBCN_REG, 
                          TI_LMP90100_SPI_DRDYBCN_REG_VALUE, pURA);            // enable DRDYB on D6 
  TI_LMP90100_SPIWriteReg(TI_LMP90100_ADC_AUXCN_REG, 
                          TI_LMP90100_ADC_AUXCN_REG_VALUE, pURA);              // disable external clock detection, internal clock
  TI_LMP90100_SPIWriteReg(TI_LMP90100_SPI_CRC_CN_REG, 
                          TI_LMP90100_SPI_CRC_CN_REG_VALUE, pURA);             // Enable CRC
  TI_LMP90100_SPIWriteReg(TI_LMP90100_SENDIAG_THLDH_REG, 
                          TI_LMP90100_SENDIAG_THLDH_REG_VALUE, pURA);          // Sensor Diagnostic Threshold High
  TI_LMP90100_SPIWriteReg(TI_LMP90100_SENDIAG_THLDL_REG, 
                          TI_LMP90100_SENDIAG_THLDL_REG_VALUE, pURA);          // Sensor Diagnostic Threshold Low
  TI_LMP90100_SPIWriteReg(TI_LMP90100_SCALCN_REG, 
                          TI_LMP90100_SCALCN_REG_VALUE, pURA);                 // Normal mode
  TI_LMP90100_SPIWriteReg(TI_LMP90100_ADC_DONE_REG, 
                          TI_LMP90100_ADC_DONE_REG_VALUE, pURA);               // ADC Data unavailable
  // Set up scan register for conversion
  while (TI_LMP90100_SPIReadReg((TI_LMP90100_CH_STS_REG 
                                 & TI_LMP90100_CH_SCAN_NRDY), pURA));          // wait if CH_SCAN_NRDY
  TI_LMP90100_SPIWriteReg(TI_LMP90100_CH_SCAN_REG, 
                          TI_LMP90100_CH_SCAN_REG_VALUE, pURA);                // single CH continuous scan, ch# = 0   
  // CH0 in use
  TI_LMP90100_SPIWriteReg(TI_LMP90100_CH0_INPUTCN_REG, 
                          TI_LMP90100_CH0_INPUTCN_REG_VALUE, pURA);            // diable sensor diagnostics, default ref, vinp0 vinn1
  TI_LMP90100_SPIWriteReg(TI_LMP90100_CH0_CONFIG_REG, 
                          TI_LMP90100_CH0_CONFIG_REG_VALUE, pURA);             // 26.83SPS, FGA off, buffer in signal path
  // CH1 not used
  TI_LMP90100_SPIWriteReg(TI_LMP90100_CH1_INPUTCN_REG, 
                          TI_LMP90100_CH1_INPUTCN_REG_VALUE, pURA);            // disable sensor diagnostics, default ref, vinp2 vinn3
  TI_LMP90100_SPIWriteReg(TI_LMP90100_CH1_CONFIG_REG, 
                          TI_LMP90100_CH1_CONFIG_REG_VALUE, pURA);             // 26.83SPS, FGA off, buffer in signal path  
  // CH2 not used
  TI_LMP90100_SPIWriteReg(TI_LMP90100_CH2_INPUTCN_REG, 
                          TI_LMP90100_CH2_INPUTCN_REG_VALUE, pURA);            // disable sensor diagnostics, default ref, vinp4 vinn5
  TI_LMP90100_SPIWriteReg(TI_LMP90100_CH2_CONFIG_REG, 
                          TI_LMP90100_CH2_CONFIG_REG_VALUE, pURA);             // 214.65SPS, FGA off, buffer in signal path
  // CH3 not used
  TI_LMP90100_SPIWriteReg(TI_LMP90100_CH3_INPUTCN_REG, 
                          TI_LMP90100_CH3_INPUTCN_REG_VALUE, pURA);            // disable sensor diagnostics, default ref, vinp6 vinn7
  TI_LMP90100_SPIWriteReg(TI_LMP90100_CH3_CONFIG_REG, 
                          TI_LMP90100_CH3_CONFIG_REG_VALUE, pURA);             // 214.65SPS, FGA off, buffer in signal path
  // CH4 not used
  TI_LMP90100_SPIWriteReg(TI_LMP90100_CH4_INPUTCN_REG, 
                          TI_LMP90100_CH4_INPUTCN_REG_VALUE, pURA);            // diable sensor diagnostics, default ref, vinp0 vinn1
  TI_LMP90100_SPIWriteReg(TI_LMP90100_CH4_CONFIG_REG, 
                          TI_LMP90100_CH4_CONFIG_REG_VALUE, pURA);             // 214.65SPS, FGA off, buffer in signal path
  // CH5 not used
  TI_LMP90100_SPIWriteReg(TI_LMP90100_CH5_INPUTCN_REG, 
                          TI_LMP90100_CH5_INPUTCN_REG_VALUE, pURA);            // disable sensor diagnostics, default ref, vinp2 vinn3
  TI_LMP90100_SPIWriteReg(TI_LMP90100_CH5_CONFIG_REG, 
                          TI_LMP90100_CH5_CONFIG_REG_VALUE, pURA);             // 214.65SPS, FGA off, buffer in signal path
  // CH6 not used 
  TI_LMP90100_SPIWriteReg(TI_LMP90100_CH6_INPUTCN_REG, 
                          TI_LMP90100_CH6_INPUTCN_REG_VALUE, pURA);            // disable sensor diagnostics, default ref, vinp4 vinn5
  TI_LMP90100_SPIWriteReg(TI_LMP90100_CH6_CONFIG_REG, 
                          TI_LMP90100_CH6_CONFIG_REG_VALUE, pURA);	       // 214.65SPS, FGA off, buffer in signal path			
 
}
//******************************************************************************
//  void process_adc_output(uint32_t *)
//
//  DESCRIPTION:
//  Dummy ADC data process function: Toggles LED
//******************************************************************************
void process_adc_output(uint32_t *data)
{ 
    TI_LMP90100_LED_PxOUT ^= TI_LMP90100_LED_PIN;                               // Toggle LED 
}
//******************************************************************************
// TI_LMP90100_SPI_DRDYB_PIN interrupt service routine
#pragma vector=TI_LMP90100_DRDYB_VECTOR
__interrupt void TI_LMP90100_DRDY_PORTx(void)
{
  TI_LMP90100_DRDYB_PxIFG &= ~TI_LMP90100_DRDYB_PIN;                           //  IFG cleared
  LMP90100_ADCDataReady = 1;                                                   // set flag
  __bic_SR_register_on_exit(LPM0_bits);                                        // Exit active CPU  
}
//******************************************************************************