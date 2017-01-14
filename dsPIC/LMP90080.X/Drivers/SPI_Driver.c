#include <xc.h>
#include <stdio.h>
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "SYSTEM_Driver.h"
#include "PORT_Driver.h"
#include "SPI_Driver.h"
/*******************************************************************************
 *          DEFINES
 ******************************************************************************/

/*******************************************************************************
 *          MACRO FUNCTIONS
 ******************************************************************************/

/*******************************************************************************
 *          VARIABLES
 ******************************************************************************/

/*******************************************************************************
 *          LOCAL FUNCTIONS
*******************************************************************************/
static void initSpi_1(uint16_t MS);
static void initSpi_2(uint16_t MS);

void initSpi_1(uint16_t MS) {
    // SPI1STAT Register Settings
    SPI1STATbits.SPIEN = 0; // Disable SPI module
    SPI1STATbits.SPISIDL = 0; // Continue module operation in Idle mode
    SPI1STATbits.SPIROV = 0; // No Receive Overflow has occurred

    // SPI1CON1 Register Settings
    SPI1CON1bits.MSTEN = 1; // Master mode enabled
    SPI1CON1bits.MODE16 = 0; // Communication is byte-wide (8 bits)
    SPI1CON1bits.DISSCK = 0; // SPIx clock on SCKx pin is enabled
    SPI1CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
    //if(MS == SPI_MASTER){
        SPI1CON1bits.SMP = 0; // Input data is sampled at the end of data output time
    //} else {
      //  SPI1CON1bits.SMP = 0; // The SMP bit must be cleared when the SPIx module is used in Slave mode.
    //}
    SPI1CON1bits.CKE = 0; // 
    SPI1CON1bits.SSEN = 0; // SSx pin is not used by the module; pin is controlled by port function
    SPI1CON1bits.CKP = 1; // 
    //if(MS == SPI_MASTER) {
        SPI1CON1bits.SPRE = 0b110; // Secondary pre-scale 1:1
        SPI1CON1bits.PPRE = 0b00; // Primary pre-scale 64:1
    //}
    
    // SPI1CON2 Register Settings
    SPI1CON2bits.FRMEN = 0; // Framed SPIx support is disabled
    SPI1CON2bits.SPIBEN = 0; // Enhanced buffer is disabled (Legacy mode)
    
    // Clear the buffer
    SPI1BUF = 0; 
    
    // Enable SPI module
    SPI1STATbits.SPIEN = 1; // Enable SPI module
}

void initSpi_2(uint16_t MS) {
//    // SPI2STAT register settings
//    SPI2STATbits.SPIEN = 0; // SPI2 module is disabled
//    SPI2STATbits.SPISIDL = 0; // SPIx module operation is continued in Idle mode
//    SPI2STATbits.SPIBEC = 0b00; // Buffer element count to 0
//           
//    // SPI2CON1 register settings
//    SPI2CON1bits.MSTEN = MS;
//    SPI2CON1bits.MODE16 = 0; // Communication is byte-wide (8 bits)
//    SPI2CON1bits.DISSCK = 0; // SPIx clock on SCKx pin is enabled
//    SPI2CON1bits.DISSDO = 0; // SDOx pin is controlled by the module 
//    if(MS == SPI_MASTER){
//        SPI2CON1bits.SMP = 1; // Input data is sampled at the end of data output time
//    } else {
//        SPI2CON1bits.SMP = 0; // The SMP bit must be cleared when the SPIx module is used in Slave mode.
//    }
//    SPI2CON1bits.CKE = 1; // Serial output data changes on transition from active clock state to Idle clock state        
//    SPI2CON1bits.SSEN = 0; // SSx pin is not used by the module; pin is controlled by port function
//    SPI2CON1bits.CKP = 0; // Idle state for clock is a low level; active state is a high level
//    if(MS == SPI_MASTER) {
//        SPI2CON1bits.SPRE = 0b110; // Secondary pre-scale 1:1 
//        SPI2CON1bits.PPRE = 0b00; // Primary pre-scale 64:1
//    }
//            
//    // SPI2CON2 register settings
//    SPI2CON2bits.FRMEN = 0; // Framed SPIx support is disabled
//    SPI2CON2bits.SPIBEN = 0; // Enhanced buffer is disabled (Legacy mode) 
//    
//    // Clear the buffer
//    SPI2BUF = 0x0000;
//    
//    // Enable
//    SPI2STATbits.SPIEN = 1; // SPIx module is enabled and configures the SCKx, SDOx, SDIx and SSx pins as serial port pins
}

/*******************************************************************************
 *          DRIVER FUNCTIONS
 ******************************************************************************/
void D_SPI_Init(uint16_t which, uint16_t MS) {
    // Port initializes
    D_PORT_SetSpiPorts(which, MS);
    
    // Register initializes
    if(which == SPI_MODULE_1) {
        initSpi_1(MS);
    } else if (which == SPI_MODULE_2) {
        initSpi_2(MS);
    } else {
        return;
    }
}

uint8_t D_SPI_WriteByte(uint8_t data) {
        SPI1BUF = data;
        while(!SPI1STATbits.SPIRBF){}
        return SPI1BUF;
}