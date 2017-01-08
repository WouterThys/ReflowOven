/* 
 * File:   MCP3201_Driver.h
 * Author: wouter
 *
 * Created on December 1, 2016, 7:36 PM
 */

#ifndef MCP3201_DRIVER_H
#define	MCP3201_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
#include <stdint.h>
    
    /**
     * First byte:  ?  | ?  | 0  | B11| B10| B9 | B8 | B7
     * Second byte: B6 | B5 | B4 | B3 | B2 | B1 | B0 | B1
     */
    
#define MASK_HIGH  0x1F
#define MASK_LOW   0xFE

/**
 * Initialize SPI module to work with MCP3201.
 */
void D_MCP3201_Init();

/**
 * Enables MCP3201 module.
 * @param enable: Enable or disable.
 */
void D_MCP3201_Enable(bool enable);

/**
 * Read a 16-bit value from the MCP3201.
 * @return AD-Converted data
 */
uint16_t D_MCP3201_Read();

uint8_t D_MCP3201_GetLSB();
uint8_t D_MCP3201_GetMSB();

#ifdef	__cplusplus
}
#endif

#endif	/* MCP3201_DRIVER_H */

