#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>

#include "MCP3201_Driver.h"
#include "PORT_Driver.h"
#include "SPI_Driver.h"

#define _XTAL_FREQ 16000000

/*******************************************************************************
 *          DEFINES
 ******************************************************************************/

/*******************************************************************************
 *          MACRO FUNCTIONS
 ******************************************************************************/

/*******************************************************************************
 *          VARIABLES
 ******************************************************************************/
    uint8_t msbBits = 0x00;
    uint8_t lsbBits = 0x00;
    uint16_t analogValue = 0x0000;
    
/*******************************************************************************
 *          BASIC FUNCTIONS
 ******************************************************************************/
uint16_t convertData(uint8_t high, uint8_t low);

uint16_t convertData(uint8_t high, uint8_t low) {
    high = (uint16_t)high;
    low = (uint16_t)low;
    // Mask it
    high = (high & MASK_HIGH);
    low = (low & MASK_LOW);
    
    // Shift second value to get rid of B1 bit
    low = (low >> 1);
    
    // Add the last bit of the first byte
    if ((high & 0x0001) == 0x0001) {
        low = (low | 0x0080);
    }
    
    // Shift first value, add it to the second value
    high = (high >> 1);
    return (low + (high << 8));
}

/*******************************************************************************
 *          DRIVER FUNCTIONS
 ******************************************************************************/

void D_MCP3201_Init() {
    // Set Chip select port
    MCP_nCS_Dir = 0; // Output
    MCP_nCS = 1; // Not selected
    
    // Clear all values
    msbBits = 0x00;
    lsbBits = 0x00;
    analogValue = 0x0000;
    
    // Initialize SPI module
    D_SPI_Init();
}

void D_MCP3201_Enable(bool enable) {
    if (enable) {
        D_SPI_Enable(true);
    } else {
        D_SPI_Enable(false);
    }
}

uint16_t D_MCP3201_Read() {
    MCP_nCS = 0; // Select the chip
    __delay_us(1);
    msbBits = D_SPI_Write(0x00);
    lsbBits = D_SPI_Write(0x00);
    __delay_us(1);
    MCP_nCS = 1; // Deselect the chip
    
    analogValue = convertData(msbBits, lsbBits);
    
    return analogValue;
}

uint8_t D_MCP3201_GetLSB() {
    return lsbBits;
}

uint8_t D_MCP3201_GetMSB() {
    return msbBits;
}
