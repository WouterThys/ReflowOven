/* 
 * File:   SPI functions
 * Author: wouter
 */

#ifndef SPI_DRIVER_H
#define	SPI_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define SPI_MASTER      1
#define SPI_SLAVE       0
    
#define SPI_MODULE_1    0
#define SPI_MODULE_2    1
    
/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/
/**
 * Initialize the SPI module. 
 * @param which: select the SPI module: SPI_MODULE_1 or SPI_MODULE_2
 * @param MS: Select if master or slave: SPI_MASTER or SPI_SLAVE
 */    
void D_SPI_Init(uint16_t which, uint16_t MS); 
/**
 * Write one byte (8-bit) with the SPI module.
 * @param data: byte data to write
 * @return: byte shifted in the register while writing the data.
 */
uint8_t D_SPI_WriteByte(uint8_t data);

#endif