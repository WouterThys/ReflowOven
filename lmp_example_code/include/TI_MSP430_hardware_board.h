//----------------------------------------------------------------------------
//  Description:  This file contains definitions specific to the hardware board.
//  Specifically, the definitions include hardware connections with the
//  LMP90100 connector port, LEDs, and switches.
//
//  MSP430/LMP90100 Interface Code Library v1.0
//
//   Vishy Natarajan
//   Texas Instruments Inc.
//   October 2011
//   Built with CCE Version: 4.2 and IAR Embedded Workbench Version:  5.3x
//------------------------------------------------------------------------------
// Change Log:
//------------------------------------------------------------------------------
// Version:  1.00
// Comments: Initial Release Version
//------------------------------------------------------------------------------
#ifndef HEADER_TI_MSP430_HARDWARE_BOARD_H

#define HEADER_FILE_TI_MSP430_HARDWARE_BOARD_H

#define TI_LMP90100_LED_PxOUT            P1OUT
#define TI_LMP90100_LED_PxDIR            P1DIR
#define TI_LMP90100_LED_PIN              BIT0

#define TI_LMP90100_DRDY_PORTx           PORT_2
#define TI_LMP90100_DRDYB_PxDIR          P2DIR
#define TI_LMP90100_DRDYB_PxIE           P2IE
#define TI_LMP90100_DRDYB_PxIES          P2IES
#define TI_LMP90100_DRDYB_PxIFG          P2IFG
#define TI_LMP90100_DRDYB_PxREN          P2REN
#define TI_LMP90100_DRDYB_PxOUT          P2OUT
#define TI_LMP90100_DRDYB_PIN            BIT4
#define TI_LMP90100_DRDYB_VECTOR         PORT2_VECTOR

#define TI_LMP90100_CSn_PxOUT            P2OUT
#define TI_LMP90100_CSn_PxDIR            P2DIR
#define TI_LMP90100_CSn_PIN              BIT5


//----------------------------------------------------------------------------
// Select which port will be used for interface to LMP90100
//----------------------------------------------------------------------------
#define TI_LMP90100_SER_INTF            TI_LMP90100_SER_INTF_USCIA0_5xx   // 5xx, 6xx family USCIA0 SPI Interface to LMP90100
//#define TI_LMP90100_SER_INTF            TI_LMP90100_SER_INTF_USCIA1_5xx   // 5xx, 6xx family USCIA1 SPI Interface to LMP90100
//#define TI_LMP90100_SER_INTF            TI_LMP90100_SER_INTF_USCIA2_5xx   // 5xx, 6xx family USCIA2 SPI Interface to LMP90100
//#define TI_LMP90100_SER_INTF            TI_LMP90100_SER_INTF_USCIA3_5xx   // 5xx, 6xx family USCIA3 SPI Interface to LMP90100
//#define TI_LMP90100_SER_INTF            TI_LMP90100_SER_INTF_USCIB0_5xx   // 5xx, 6xx family USCIB0 SPI Interface to LMP90100
//#define TI_LMP90100_SER_INTF            TI_LMP90100_SER_INTF_USCIB1_5xx   // 5xx, 6xx family USCIB1 SPI Interface to LMP90100
//#define TI_LMP90100_SER_INTF            TI_LMP90100_SER_INTF_USCIB2_5xx   // 5xx, 6xx family USCIB2 SPI Interface to LMP90100
//#define TI_LMP90100_SER_INTF            TI_LMP90100_SER_INTF_USCIB3_5xx   // 5xx, 6xx family USCIB3 SPI Interface to LMP90100
//#define TI_LMP90100_SER_INTF            TI_LMP90100_SER_INTF_USART0       // USART0 SPI Interface to LMP90100
//#define TI_LMP90100_SER_INTF            TI_LMP90100_SER_INTF_USART1       // USART1 SPI Interface to LMP90100
//#define TI_LMP90100_SER_INTF            TI_LMP90100_SER_INTF_USCIA0       // 2xx, 4xx family USCIA0 SPI Interface to LMP90100
//#define TI_LMP90100_SER_INTF            TI_LMP90100_SER_INTF_USCIA1       // 2xx, 4xx family USCIA1 SPI Interface to LMP90100
//#define TI_LMP90100_SER_INTF            TI_LMP90100_SER_INTF_USCIB0       // 2xx, 4xx family USCIB0 SPI Interface to LMP90100
//#define TI_LMP90100_SER_INTF            TI_LMP90100_SER_INTF_USCIB1       // 2xx, 4xx family USCIB1 SPI Interface to LMP90100
//#define TI_LMP90100_SER_INTF            TI_LMP90100_SER_INTF_USI          // G2xx value seris SPI Interface to LMP90100

#endif                                                                         // HEADER_FILE_TI_MSP430_HARDWARE_BOARD_H