/* 
 * File:   SPI functions
 * Author: wouter
 */

#ifndef PORT_DRIVER_H
#define	PORT_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
// SPI    
#define SPI1_SCK_Dir    TRISBbits.TRISB7
#define SPI1_SDO_Dir    TRISBbits.TRISB8
#define SPI1_SDI_Dir    TRISBbits.TRISB9
    
// UART
#define UART1_RX_Dir    TRISBbits.TRISB5
#define UART1_TX_Dir    TRISBbits.TRISB6    
    
#define UART1_RX        0b0100101
#define UART1_TX        0b000001
    
// LMP90080
#define LMP_CSB         PORTBbits.RB10
#define LMP_CSB_Dir     TRISBbits.TRISB10
    
/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/
/**
 * Sets the port directions and mapping for the SPI module. Select the module
 * to use.
 * @param which: SPI_MODULE_1 or SPI_MODULE_2
 * @param MS: SPI_MASTER or SPI_SLAVE
 */
void D_PORT_SetSpiPorts(uint16_t which, uint16_t MS);
/**
 * Sets the port directions and mapping for the UART module. Select the module
 * to use.
 * @param which: UART_MODULE_1 or UART_MODULE_2
 */
void D_PORT_SetUartPorts(uint16_t which);


#endif