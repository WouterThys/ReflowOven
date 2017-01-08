#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#include "LMP_Controller.h"
#include "UART_Controller.h"
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
    
    // Disable data first mode
    uint8_t buffer[1];
    if (!D_LMP_DisableDataFirstMode(buffer, 0)) {
        D_LMP_DisableDataFirstMode(buffer, 0);
    } else {
        inReadOnlyState = false;
    }
    
    // SPI
    D_LMP_WriteRegister(SPI_HANDSHAKECN, 0x80); // SDO_DRDYB_DRIVER = 0x4, SW_OFF_TRG = 0
    D_LMP_WriteRegister(SPI_DRDYBCN, 0x83); // D6 = DRDYB signal, CRC_RST = 0, FGA_BGCAL = 0
    
    // Auxiliary control
    D_LMP_WriteRegister(ADC_AUXCN, 0x20); // "External-Clock Detection" is bypassed, rest is default
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
    
    C_UART_WriteInt("A1", read_buffer[0]);
    DelayMs(1);
    C_UART_WriteInt("A2", read_buffer[1]);
    
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

