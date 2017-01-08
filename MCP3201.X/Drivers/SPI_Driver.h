#ifndef SPI_DRIVER_H
#define	SPI_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
#include <stdint.h>
    // Defines
    
    // Variables
//typedef struct {
//    uint8_t start;
//    uint8_t command;
//    uint8_t data;
//    uint8_t stop;
//    uint8_t counter;
//} READ_Data;
/**
* Variable flag to indicate a read action is ready
*/
extern bool readSpiReady;
    
    // Functions
/**
* Initializes all the parameters to the default setting, as well as writing the
* tri-state registers. Initializes the SPI to the default data rate and settings.
*/
void D_SPI_Init();
/**
 * Write 8-bit of data to the output pin of SPI module. 
 * @param data: Data to write.
 * @return the SSPBUF
 */
uint8_t D_SPI_Write(uint8_t data);
/**
 * Read 8-bit of data from the input pin of SPI module.
 * @return data: returns the data.
 */
uint8_t D_SPI_Read();
/**
 * Enable the SPI module
 * @param enable: Enable or disable module
 */
void D_SPI_Enable(bool enable);

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_DRIVER */