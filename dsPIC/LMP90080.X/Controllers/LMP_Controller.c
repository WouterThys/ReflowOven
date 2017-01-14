#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#include "LMP_Controller.h"
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

/*******************************************************************************
 *          BASIC FUNCTIONS
 ******************************************************************************/
static void configureLmp(void);

void configureLmp() {
    
//    // Reset
//    D_LMP_WriteRegister(RESETCN, REG_AND_CNV_RST);
//    
//    // Disable data first mode
//    uint8_t buffer[1];
//    if (!D_LMP_DisableDataFirstMode(buffer, 0)) {
//        D_LMP_DisableDataFirstMode(buffer, 0);
//    } else {
//        inReadOnlyState = false;
//    }
//    
//    // SPI
//    D_LMP_WriteRegister(SPI_HANDSHAKECN, 0x80); // SDO_DRDYB_DRIVER = 0x4, SW_OFF_TRG = 0
//    D_LMP_WriteRegister(SPI_DRDYBCN, 0x83); // D6 = DRDYB signal, CRC_RST = 0, FGA_BGCAL = 0
//    
//    // Auxiliary control
//    D_LMP_WriteRegister(ADC_AUXCN, 0x20); // "External-Clock Detection" is bypassed, rest is default
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
    
    return ((read_buffer[0]<<7) + read_buffer[1]);
}

void C_LMP_FlashLED(void) {
    if(ledState) {
        D_LMP_WriteRegister(GPIO_DAT, 0);
        ledState = false;
    } else {
        D_LMP_WriteRegister(GPIO_DAT, 1);
        ledState = true;
    }
    DelayMs(1000);
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

