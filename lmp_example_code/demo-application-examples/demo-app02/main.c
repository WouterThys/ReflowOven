//******************************************************************************
//  Demo Application02 for MSP430/LMP90100 Interface Code Library v1.0
//  Normal Stream Read/Write LMP90100 Registers
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

#define BUF_SIZE 9
//******************************************************************************
void main(void)
{
 
  uint8_t prev_URA;                                                            // Previous Upper Register Address (URA)
  uint8_t count, i, addr;
  uint8_t write_buf[BUF_SIZE], read_buf[BUF_SIZE];                             // write and read buffer for normal streaming
  uint8_t error_flag = 0;

  WDTCTL = WDTPW+WDTHOLD;                                                      // Stop WDT
  
  TI_LMP90100_LED_PxOUT |= TI_LMP90100_LED_PIN;                                // Set LED ON
  TI_LMP90100_LED_PxDIR |= TI_LMP90100_LED_PIN;                                // Set pin direction is output
  
  TI_LMP90100_SPISetup();                                                      // Initilaize MSP430 SPI Block
  prev_URA = LMP90100_URA_END;                                                 // IInitialize prev_URA to invalid segment   
  
  // Initialize write_buf with register values for stream write to channel registers
  write_buf[0] = TI_LMP90100_CH_SCAN_REG_VALUE;                                
  write_buf[1] = TI_LMP90100_CH0_INPUTCN_REG_VALUE;
  write_buf[2] = TI_LMP90100_CH0_CONFIG_REG_VALUE;
  write_buf[3] = TI_LMP90100_CH1_INPUTCN_REG_VALUE;
  write_buf[4] = TI_LMP90100_CH1_CONFIG_REG_VALUE;
  write_buf[5] = TI_LMP90100_CH2_INPUTCN_REG_VALUE;
  write_buf[6] = TI_LMP90100_CH2_CONFIG_REG_VALUE;
  write_buf[7] = TI_LMP90100_CH3_INPUTCN_REG_VALUE;
  write_buf[8] = TI_LMP90100_CH3_CONFIG_REG_VALUE;
      
  addr = TI_LMP90100_CH_SCAN_REG;                                              // Initialize to stream write start address
  count = BUF_SIZE;                                                            // Number of bytes to write
  
  
  TI_LMP90100_SPIWriteReg(TI_LMP90100_SPI_STREAMCN_REG, TI_LMP90100_SPI_STREAMCN_REG_VALUE, 
                          &prev_URA);                                          // Ensure device is in normal streaming mode    
  
  TI_LMP90100_SPINormalStreamWriteReg(addr, write_buf, count, &prev_URA);      // Stream write to channel registers
  TI_LMP90100_SPINormalStreamReadReg(addr, read_buf, count, &prev_URA);        // Stream Read back for test

  // test if stream write/read values match 
  for (i=0; i < count; i++)
  {
    if (write_buf[i] != read_buf[i])
    {
      error_flag = 1;
      TI_LMP90100_LED_PxOUT &= ~TI_LMP90100_LED_PIN;                           // error: Set LED OFF   
    }
  }
  while (!error_flag)                                                          // no error: blink LED continuously
  {
    __delay_cycles(250000);
    __delay_cycles(250000);
    TI_LMP90100_LED_PxOUT ^= TI_LMP90100_LED_PIN;        
  }   
  __bis_SR_register(LPM0_bits + GIE);                                          // Enter LPM0, enable interrupts
  __no_operation();                                                            // For debugger 

}
//******************************************************************************
