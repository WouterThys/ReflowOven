#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>

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
 *          BASIC FUNCTIONS
 ******************************************************************************/


/*******************************************************************************
 *          DRIVER FUNCTIONS
 ******************************************************************************/
void D_SPI_Init() {
    // Port settings master
    SPI_SCK_Dir = 0; 
    SPI_SDI_Dir = 1;
    
    // Clear the buffer
    SSPBUF = 0x00;
    
    // Disable SPI while initializing
    D_SPI_Enable(false);
    
    // SSPSTAT register settings
    SSPSTATbits.SMP = 0; // Input data sampled at middle of data output time.
    SSPSTATbits.CKE = 0; // Transmit occurs on transition from Idle to active clock state
    
    // SSPCON1 register settings
    SSPCON1bits.CKP = 1; // Idle state for clock is a high level
    SSPCON1bits.SSPM = 0b0010; // SPI Master mode, clock = Fosc/64
    
    // Clear interrupt flag
    PIR1bits.SSPIF = 0;
}

uint8_t D_SPI_Write(uint8_t data) {
     SSPBUF = data;
     while(!PIR1bits.SSPIF){};       // Wait until data is fetched
     PIR1bits.SSPIF = 0;
     return SSPBUF;
}

uint8_t D_SPI_Read() {
    uint8_t read;
    read = SSPBUF;
    SSPBUF = 0x55;
    return read;
}

void D_SPI_Enable(bool enable) {
    if (enable) {
        SPI_SCK_Dir = 0;
        SPI_SDI_Dir = 1;
        SSPCON1bits.SSPEN = 1; // Enable serial port 
    } else {
        SSPCON1bits.SSPEN = 0; // Disable serial port
    }
}