#ifndef SPI_DRIVER_H
#define	SPI_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
#include <stdint.h>
    
    // Defines
#define SPI_MASTER  0
#define SPI_SLAVE   1    
    
#define SPI_MODE_0  0    
#define SPI_MODE_1  1 
#define SPI_MODE_2  2 
#define SPI_MODE_3  3 
    
/**
* Variable flag to indicate a read action is ready
*/
extern bool readSpiReady;
    
    // Functions
/**
* Initializes all the parameters to the default setting, as well as writing the
* tri-state registers. Initializes the SPI to the default data rate and settings.
 * @param MS: SPI_MASTER or SPI_SLAVE
 * @param mode: mode of the SPI:
 *                  Clock polarity      Clock phase     Clock edge
 *      SPI_MODE_0:      0                   0               1
 *      SPI_MODE_1:      0                   1               0
 *      SPI_MODE_2:      1                   0               1
 *      SPI_MODE_3:      1                   1               0      
*/
void D_SPI_Init(uint8_t MS, uint8_t mode);
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