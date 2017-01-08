/*
 * File:   main.c
 * Author: Wouter
 *
 * Created on October 22, 2016, 5:17 PM
 */
#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "Drivers/ADC_Driver.h"
#include "Drivers/LMP90080.h"
#include "Drivers/PORT_Driver.h"
#include "Drivers/SPI_Driver.h"

#define _XTAL_FREQ 16000000

void initialize();
void delay10ms(uint8_t d);
void delay100ms(uint8_t d);
void delay1000ms(uint8_t d);

void delay10ms(uint8_t d) {
    uint8_t i = 0;
    while(i < d) {
        __delay_ms(10);
        i++;
    }
}

void delay100ms(uint8_t d) {
    uint8_t i = 0;
    while(i < d) {
        delay10ms(10);
        i++;
    }
}

void delay1000ms(uint8_t d) {
    uint8_t i = 0;
    while(i < d) {
        delay100ms(10);
        i++;
    }
}

void initialize() {
    D_PORT_Init();
    D_ADC_Init();
}

void main(void) {
    
    initialize();
    
    delay1000ms(2);
    D_ADC_WriteRegister(DATA_ONLY_1, 0x16);
    uint8_t a = D_ADC_ReadRegister(DATA_ONLY_1);
//    D_ADC_WriteRegister(RESETCN, REG_AND_CNV_RST);
//    __delay_ms(1);
//    D_ADC_WriteRegister(ADC_RESTART, 0x01);
//    __delay_ms(1);
    D_ADC_WriteRegister(GPIO_DIRCN, 0x00);
    D_ADC_WriteRegister(GPIO_DAT, 0x02);
            
    while(1) {
        
        
    }
    return;
}