/*
 * File:   main.c
 * Author: Wouter
 */
#if defined(__XC16__)
#include <xc.h>
#elif defined(__C30__)
#if defined(__dsPIC33E__)
#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "Drivers/SYSTEM_Driver.h"
#include "Drivers/INT_Driver.h"
#include "Drivers/PORT_Driver.h"

#include "Controllers/UART_Controller.h"
#include "Controllers/LMP_Controller.h"

/*******************************************************************************
 *          DEFINES
 ******************************************************************************/

/*******************************************************************************
 *          MACRO FUNCTIONS
 ******************************************************************************/

/*******************************************************************************
 *          LOCAL FUNCTIONS
 ******************************************************************************/
static void initialize();

void initialize() {
    // Disable interrupts before startup
    D_INT_EnableInterrupts(false);
    
    // Initializes system 
    D_SYS_InitPll();
    D_SYS_InitOscillator();
    D_SYS_InitPorts();
    D_INT_Init();
    D_INT_EnableInterrupts(true);
    
    // Initialize Models
    C_UART_Init("pic", 9600);
    C_LMP_Init();
    
    // Initialize controllers
    
}

/*******************************************************************************
 *          VARIABLES
 ******************************************************************************/

/*******************************************************************************
 *          MAIN PROGRAM
 ******************************************************************************/

int main(void) {
    
    initialize();
    
    // Test
    C_UART_Write(COMMAND_Initialize, "Initialized");
    
    C_LMP_ConfigureChannel(CHANNEL_0, ODR_7, GAIN_1, BUFFER_DIS, 
            BURNOUT_DIS, VREF_SEL_1, VINP_0, VINN_1, BG_CAL_MODE_2);
    
    while(1) {
        
        DelayMs(1000);
        C_LMP_ReadAdc();
        
        if (C_UART_ReadFlag) {
            C_UART_ReadFlag = false;
            
//            C_UART_HandleMessage(C_UART_ReadMessage());
        }
        
//        C_LMP_FlashLED();
        
    }
    return 0;
}


