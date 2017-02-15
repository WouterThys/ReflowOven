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
double calculate_average(double avg, double new_sample, uint16_t samples);

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
    LED1 = 0;
    
    // Initialize controllers
    
}

double calculate_average(double avg, double new_sample, uint16_t samples) {
    avg -= avg / samples;
    avg += new_sample / samples;
    return avg;
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
    printf("ini \n");
    
    uint16_t samples = 16;
    uint16_t buffer[samples];
    SensorDiagnostics_t sd;
    bool error = false;
    double av;
    
    //if (C_LMP_Test_SimpleRW(SPI_DRDYBCN, 0x83)) LED1 = 1;
    //if(C_LMP_Test_NormalStreamRW()) LED1 = 1;
    
    while(1) {
        if(C_LMP_Test_NormalStreamReadADC(buffer, samples)) LED1 = 1;
    
        av = buffer[0];
        uint16_t i;
        for (i=0; i<samples; i++) {
            av = calculate_average(av, buffer[i], samples);
        }

        printf("%d \n", (int16_t)av);
        
        C_LMP_DiagnoseSensor(&sd);
        
        if (sd.overflow > 0) {
            error = true;
        }
        if (sd.power_on_reset) {
            error = true;
        }
        if (sd.rails) {
            error = true;
        }
        if  (sd.short_circuit) {
            error = true;
        }
        if (error) {
            C_LMP_SetErrorLed(true);
        } else {
            C_LMP_SetErrorLed(false);
        }
        error = false;
        DelayMs(1000);
    }
    return 0;
}


