#ifndef PORT_DRIVER_H
#define	PORT_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

    // Ports for UART
#define UART_TX         PORTCbits.RC6
#define UART_RX         PORTCbits.RC7
    
#define UART_TX_Dir     TRISCbits.TRISC6
#define UART_RX_Dir     TRISCbits.TRISC7
    
    // Ports for SPI
#define SPI_SDI         PORTBbits.RB0
#define SPI_SDO         PORTCbits.RC7
#define SPI_SCK         PORTBbits.RB1
    
#define SPI_SDI_Dir     TRISBbits.TRISB0
#define SPI_SDO_Dir     TRISCbits.TRISC7
#define SPI_SCK_Dir     TRISBbits.TRISB1
    
    // Ports for LMP90080
#define LMP_CSB         PORTBbits.RB2
    
#define LMP_CSB_Dir     TRISBbits.TRISB2
    
    // IO Ports
#define LED1            LATBbits.LATB3
#define LED2            LATBbits.LATB4
#define LED3            LATBbits.LATB5
#define LED4            LATBbits.LATB6
    
#define LED1_Dir        TRISBbits.TRISB3
#define LED2_Dir        TRISBbits.TRISB4
#define LED3_Dir        TRISBbits.TRISB5
#define LED4_Dir        TRISBbits.TRISB6   
    
 /**
 * Initializes all the parameters to the default setting, as well as writing the
 * tri-state registers. Sets all ports to zero, and all tri-states to output.
 */
void D_PORT_Init();

#ifdef	__cplusplus
}
#endif

#endif	/* PORT_DRIVER */
