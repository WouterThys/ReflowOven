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

#include "Drivers/LMP90080.h"
#include "Drivers/UART_Driver.h"
#include "Drivers/SYSTEM_Driver.h"
#include "Drivers/INT_Driver.h"
#include "Drivers/PORT_Driver.h"

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
    
    D_UART_Init(UART_MODULE_1, 9600);
    D_UART_Enable(UART_MODULE_1, true);
    //D_INT_EnableUartInterrupts(true);
    
    // Initialize Models
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
    printf("ini");
    
    if (C_LMP_TestWrite(SPI_DRDYBCN, 0x83)) LED1 = 1;
    
    while(1) {
        
    }
    return 0;
}
