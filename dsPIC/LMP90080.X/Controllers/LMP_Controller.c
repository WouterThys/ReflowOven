#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#include "LMP_Controller.h"
#include "../Drivers/INT_Driver.h"
#include "../Drivers/PORT_Driver.h"
#include "../Drivers/LMP90080.h"
#include "../Drivers/SYSTEM_Driver.h"
#include "../Drivers/LMP_Driver.h"

/*******************************************************************************
 *          DEFINES
 ******************************************************************************/


/*******************************************************************************
 *          MACRO FUNCTIONS
 ******************************************************************************/

/*******************************************************************************
 *          VARIABLES
 ******************************************************************************/
static bool ledState;
static bool inReadOnlyState; 
bool adcDataReadyFlag;

/*******************************************************************************
 *          BASIC FUNCTIONS
 ******************************************************************************/
static void configureLmp(void);

void configureLmp() {
    
    D_LMP_WriteRegister(RESETCN, 0xC3); // Register and Conversion reset
    D_LMP_WriteRegister(SPI_HANDSHAKECN, 0x01); // SPI SDO High Z Delayed
    D_LMP_WriteRegister(SPI_STREAMCN, 0x00); // SPI Normal Streaming mode
    D_LMP_WriteRegister(PWRCN, 0x00); // Active mode
    D_LMP_WriteRegister(ADC_RESTART, 0x00); // Disable restart conversion
    D_LMP_WriteRegister(GPIO_DIRCN, 0x41); // D6 & D0 output, D1-D5 inputs
    D_LMP_WriteRegister(GPIO_DAT, 0x40); // Set D6 high, D0 low, ignore others
    D_LMP_WriteRegister(BGCALCN, 0x02); // Background calibration mode 2
    D_LMP_WriteRegister(SPI_DRDYBCN, 0x83); // Enable DRDYB on D6, bits 0 & 1 must be 1, others default
    D_LMP_WriteRegister(ADC_AUXCN, 0x28); // Bypass external clock detection, internal clock, select 1000 µA RTD current
    D_LMP_WriteRegister(SPI_CRC_CN, 0x00); // Disable, bit 3 must be 0, DRDYB is de-asserted DOUTL is read
    D_LMP_WriteRegister(SENDIAG_THLD, 0x00); // Sensor diagnostics threshold low
    D_LMP_WriteRegister(SCALCN, 0x00); // System calibration normal mode
    D_LMP_WriteRegister(ADC_DONE, 0xFF); // ADC Data unavailable
    
    while(D_LMP_ReadRegister(CH_STS & CH_SCAN_NRDY)); // Wait while channel scan not ready
    
    D_LMP_WriteRegister(CH_SCAN, 0x00); // Single channel Continuous scan: channel 0
    D_LMP_WriteRegister(CH0_INPUTCN, 0x41); // Disable sensor diagnostics, VREFP2 & VREFN2, Vinp0 and Vinn1
    D_LMP_WriteRegister(CH0_CONFIG, 0x47); // Channel 0 configuration: 26.83SPS, FGA x4, buffer in signal path
    D_LMP_WriteRegister(CH1_INPUTCN, 0x13); // Disable sensor diagnostics, default ref, Vinp2 and Vinn3
    D_LMP_WriteRegister(CH1_CONFIG, 0x40); // Channel 1 configuration: 26.83SPS, FGA off, no buffer in signal path
    D_LMP_WriteRegister(CH2_INPUTCN, 0x25); // Disable sensor diagnostics, default ref, Vinp4 and Vinn5
    D_LMP_WriteRegister(CH2_CONFIG, 0x70); // Channel 2 configuration: 214.655SPS, FGA off, no buffer in signal path
    D_LMP_WriteRegister(CH3_INPUTCN, 0x37); // Disable sensor diagnostics, default ref, Vinp6 and Vinn7
    D_LMP_WriteRegister(CH3_CONFIG, 0x70); // Channel 3 configuration: 214.655SPS, FGA off, no buffer in signal path
    D_LMP_WriteRegister(CH4_INPUTCN, 0x01); // Disable sensor diagnostics, default ref, vinp2 and vinn3
    D_LMP_WriteRegister(CH4_CONFIG, 0x70); // Channel 4 configuration: 214.655SPS, FGA off, no buffer in signal path
    D_LMP_WriteRegister(CH5_INPUTCN, 0x13); // Disable sensor diagnostics, default ref, vinp4 and vinn5
    D_LMP_WriteRegister(CH5_CONFIG, 0x70); // Channel 5 configuration: 214.655SPS, FGA off, no buffer in signal path
    D_LMP_WriteRegister(CH6_INPUTCN, 0x25); // Disable sensor diagnostics, default ref, vinp6 and vinn7
    D_LMP_WriteRegister(CH6_CONFIG, 0x70); // Channel 6 configuration: 214.655SPS, FGA off, no buffer in signal path
    
}

/*******************************************************************************
 *          DRIVER FUNCTIONS
 ******************************************************************************/
void C_LMP_Init() {
    
    // Initialize the driver
    D_LMP_Init();
    
    // Configure LMP
    configureLmp();
    
    // Variables
    ledState = false;
    adcDataReadyFlag = false;
}

void C_LMP_ConfigureChannel(uint8_t which, 
                            uint8_t odr, 
                            uint8_t gain, 
                            uint8_t buf_en,
                            uint8_t burn_en, 
                            uint8_t vref_sel, 
                            uint8_t vinp, 
                            uint8_t vinn, 
                            uint8_t bgcal) {
    
    switch (which) {
        case CHANNEL_0:
            D_LMP_WriteRegister(CH0_CONFIG, (odr | gain | buf_en));
            D_LMP_WriteRegister(CH0_INPUTCN, (burn_en | vref_sel | vinp | vinn));
            D_LMP_WriteRegister(BGCALCN, bgcal);
            break;
        case CHANNEL_1:
            D_LMP_WriteRegister(CH1_CONFIG, (odr | gain | buf_en));
            D_LMP_WriteRegister(CH1_INPUTCN, (burn_en | vref_sel | vinp | vinn));
            D_LMP_WriteRegister(BGCALCN, bgcal);
            break;
        case CHANNEL_2:
            D_LMP_WriteRegister(CH2_CONFIG, (odr | gain | buf_en));
            D_LMP_WriteRegister(CH2_INPUTCN, (burn_en | vref_sel | vinp | vinn));
            D_LMP_WriteRegister(BGCALCN, bgcal);
            break;
        case CHANNEL_3:
            D_LMP_WriteRegister(CH3_CONFIG, (odr | gain | buf_en));
            D_LMP_WriteRegister(CH3_INPUTCN, (burn_en | vref_sel | vinp | vinn));
            D_LMP_WriteRegister(BGCALCN, bgcal);
            break;
        case CHANNEL_4:
            D_LMP_WriteRegister(CH4_CONFIG, (odr | gain | buf_en));
            D_LMP_WriteRegister(CH4_INPUTCN, (burn_en | vref_sel | vinp | vinn));
            D_LMP_WriteRegister(BGCALCN, bgcal);
            break;
        case CHANNEL_5:
            D_LMP_WriteRegister(CH5_CONFIG, (odr | gain | buf_en));
            D_LMP_WriteRegister(CH5_INPUTCN, (burn_en | vref_sel | vinp | vinn));
            D_LMP_WriteRegister(BGCALCN, bgcal);
            break;
        case CHANNEL_6:
            D_LMP_WriteRegister(CH6_CONFIG, (odr | gain | buf_en));
            D_LMP_WriteRegister(CH6_INPUTCN, (burn_en | vref_sel | vinp | vinn));
            D_LMP_WriteRegister(BGCALCN, bgcal);
            break;
    }
}

uint16_t C_LMP_ReadAdc() {
    
    uint8_t read_buffer[2];
    //D_LMP_NormalStreamReadAdc(ADC_DOUTH, read_buffer, 2);
    //D_LMP_NormalStreamReadRegister(ADC_DOUTH, read_buffer, 2);
    read_buffer[0] = D_LMP_ReadRegister(ADC_DOUTH);
    read_buffer[1] = D_LMP_ReadRegister(ADC_DOUTL);
    
    return ((read_buffer[0]<<8) + read_buffer[1]);
}

void C_LMP_SetErrorLed(bool set) {
    uint8_t current_state = D_LMP_ReadRegister(GPIO_DAT);
    if (set) {
        D_LMP_WriteRegister(GPIO_DAT, (current_state | 0x01));
    } else {
        D_LMP_WriteRegister(GPIO_DAT, (current_state & 0xFE));
    }
}

void C_LMP_DiagnoseSensor(SensorDiagnostics_t *sd){
    uint8_t read;
    read = D_LMP_ReadRegister(SENDIAG_FLAGS);
    sd->channel = (read & 0x07);
    sd->overflow = ((read >> 3) & 0x03);
    sd->power_on_reset = ((read >> 5) & 0x01);
    sd->rails = ((read >> 6) & 0x01);
    sd->short_circuit = ((read >> 7) & 0x01);
}

bool C_LMP_Test_SimpleRW(uint8_t addr, uint8_t value) {
    uint8_t returned;
    
    D_LMP_WriteRegister(addr, value);
    DelayUs(10);
    returned = D_LMP_ReadRegister(addr);
    
    if (returned == value) {
        return true;
    } else {
        return false;
    }
}

bool C_LMP_Test_NormalStreamRW() {
    uint8_t write_buffer[9];
    uint8_t read_buffer[9];
    LED2 = 0;
    
    write_buffer[0] = 0x00; // Channel scan register value
    write_buffer[1] = 0x01; // CH0 configuration
    write_buffer[2] = 0x40; // CH0 input configuration
    write_buffer[3] = 0x13; // CH1 configuration
    write_buffer[4] = 0x40; // CH1 input configuration
    write_buffer[5] = 0x25; // CH2 configuration
    write_buffer[6] = 0x70; // CH2 input configuration
    write_buffer[7] = 0x37; // CH3 configuration
    write_buffer[8] = 0x70; // CH3 input configuration
    
    // Put device in normal stream mode
    D_LMP_WriteRegister(SPI_STREAMCN, 0x00);
    
    // Stream write and read
    D_LMP_NormalStreamWriteRegister(CH_SCAN, write_buffer, 9);
    DelayUs(10);
    D_LMP_NormalStreamReadRegister(CH_SCAN, read_buffer, 9);
    
    // Check
    uint8_t i;
    uint8_t errors = 0;
    for (i=0; i<9; i++) {
        if (write_buffer[i] != read_buffer[i]) {
            errors++;
        }
    }
    
    if (errors == 0) return true;
    return false;
}

bool C_LMP_Test_NormalStreamReadADC(uint16_t *adc_sample_array, uint16_t samples) {
    // Configure port pin to handle Data Ready Bar Output (DRDYB)
    D_PORT_SetLmpInterruptPort();
    D_INT_EnableDRDYBInterrupts(true);
    
    uint8_t i = 0, count = 2; // Data bytes to read for one conversion
    
    uint8_t read_buffer[count]; // Buffer with one sample
    uint16_t adc_data; // Read data
    bool ready = false;
    
    while(!ready) {
        if (adcDataReadyFlag) {
            adcDataReadyFlag = false;
            // Read data into buffer
            D_LMP_NormalStreamReadAdc(ADC_DOUTH, read_buffer, count);
            // Convert data
            adc_data = (((uint16_t)read_buffer[0] << 8) | (read_buffer[1]));
            adc_sample_array[i] = adc_data;
            
            if (++i == samples) {
                ready = true;
            }
        }
    }
    return true;   
}

bool C_LMP_Test_NormalStreamReadADCwithCRC(uint16_t *adc_sample_array, uint16_t samples) {
    // Configure port pin to handle Data Ready Bar Output (DRDYB)
    D_PORT_SetLmpInterruptPort();
    D_INT_EnableDRDYBInterrupts(true);
    
    uint8_t i = 0, count = 3; // Data bytes to read for one conversion + CRC test
    
    uint8_t crc_test, read_buffer[count]; // CRC test value and buffer with one sample
    uint16_t adc_data; // Read data
    bool ready = false;
    
    while(!ready) {
        if (adcDataReadyFlag) {
            adcDataReadyFlag = false;
            // Read data into buffer
            D_LMP_NormalStreamReadAdc(ADC_DOUTH, read_buffer, count);
            // Convert data
            adc_data = (((uint16_t)read_buffer[0] << 8) | (read_buffer[1]));
            crc_test = D_LMP_CRCCheck(read_buffer, count-1);
            
            if (crc_test == CRC_PASS) {
                adc_sample_array[i] = adc_data;
            } else {
                adc_sample_array[i] = 0x0000;
            }
            
            if (++i == samples) {
                ready = true;
            }
        }
    }
    
    return true;
}

