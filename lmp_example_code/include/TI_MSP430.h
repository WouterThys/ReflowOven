//******************************************************************************
//  Description:  This file contains definitions specific to the specific MSP430
//  chosen for this implementation.  MSP430 has multiple interfaces capable
//  of interfacing to the SPI port; each of these is defined in this file.
//
//  The source labels for the definitions (i.e., "P3SEL") can be found in
//  msp430xxxx.h.
//
//  MSP430/LMP90100 Interface Code Library v1.0
//
//   Vishy Natarajan
//   Texas Instruments Inc.
//   October 2011
//   Built with CCE Version: 4.2 and IAR Embedded Workbench Version:  5.3x
//******************************************************************************
// Change Log:
//******************************************************************************
// Version:  1.00
// Comments: Initial Release Version
//******************************************************************************
#ifndef HEADER_TI_LMP90100_MSP430_H

#define HEADER_FILE_TI_LMP90100_MSP430_H

#include "msp430.h"

//******************************************************************************
// SPI port definitions
// Adjust the values for the chosen interfaces, according to the pin
// assignments indicated in the chosen MSP430 device datasheet.
//******************************************************************************
// SPI port definitions 

// USCIA0 for F552x
#define TI_LMP90100_SPI_USCIA0_PxSEL1  P3SEL
#define TI_LMP90100_SPI_USCIA0_PxDIR1  P3DIR
#define TI_LMP90100_SPI_USCIA0_PxSEL2  P2SEL
#define TI_LMP90100_SPI_USCIA0_PxDIR2  P2DIR
#define TI_LMP90100_SPI_USCIA0_PxIN    P3IN
#define TI_LMP90100_SPI_USCIA0_SIMO    BIT3
#define TI_LMP90100_SPI_USCIA0_SOMI    BIT4
#define TI_LMP90100_SPI_USCIA0_UCLK    BIT7

// USCIA1 for F552x
#define TI_LMP90100_SPI_USCIA1_PxSEL1  P4SEL
#define TI_LMP90100_SPI_USCIA1_PxDIR1  P4DIR
#define TI_LMP90100_SPI_USCIA1_PxSEL2  P4SEL
#define TI_LMP90100_SPI_USCIA1_PxDIR2  P4DIR
#define TI_LMP90100_SPI_USCIA1_PxIN    P4IN
#define TI_LMP90100_SPI_USCIA1_SIMO    BIT4
#define TI_LMP90100_SPI_USCIA1_SOMI    BIT5
#define TI_LMP90100_SPI_USCIA1_UCLK    BIT0

// USCIA2 for F543x
#define TI_LMP90100_SPI_USCIA2_PxSEL1  P9SEL
#define TI_LMP90100_SPI_USCIA2_PxDIR1  P9DIR
#define TI_LMP90100_SPI_USCIA2_PxSEL2  P9SEL
#define TI_LMP90100_SPI_USCIA2_PxDIR2  P9DIR
#define TI_LMP90100_SPI_USCIA2_PxIN    P9IN
#define TI_LMP90100_SPI_USCIA2_SIMO    BIT4
#define TI_LMP90100_SPI_USCIA2_SOMI    BIT5
#define TI_LMP90100_SPI_USCIA2_UCLK    BIT0

// USCIA3 for F543x
#define TI_LMP90100_SPI_USCIA3_PxSEL1  P10SEL
#define TI_LMP90100_SPI_USCIA3_PxDIR1  P10DIR
#define TI_LMP90100_SPI_USCIA3_PxSEL2  P10SEL
#define TI_LMP90100_SPI_USCIA3_PxDIR2  P10DIR
#define TI_LMP90100_SPI_USCIA3_PxIN    P10IN
#define TI_LMP90100_SPI_USCIA3_SIMO    BIT4
#define TI_LMP90100_SPI_USCIA3_SOMI    BIT5
#define TI_LMP90100_SPI_USCIA3_UCLK    BIT0

// USCIB0 for F552x
#define TI_LMP90100_SPI_USCIB0_PxSEL1  P3SEL
#define TI_LMP90100_SPI_USCIB0_PxDIR1  P3DIR
#define TI_LMP90100_SPI_USCIB0_PxSEL2  P3SEL
#define TI_LMP90100_SPI_USCIB0_PxDIR2  P3DIR
#define TI_LMP90100_SPI_USCIB0_PxIN    P3IN
#define TI_LMP90100_SPI_USCIB0_SIMO    BIT0
#define TI_LMP90100_SPI_USCIB0_SOMI    BIT1
#define TI_LMP90100_SPI_USCIB0_UCLK    BIT2

// USCIB1 for F552x
#define TI_LMP90100_SPI_USCIB1_PxSEL1  P4SEL
#define TI_LMP90100_SPI_USCIB1_PxDIR1  P4DIR
#define TI_LMP90100_SPI_USCIB1_PxSEL2  P4SEL
#define TI_LMP90100_SPI_USCIB1_PxDIR2  P4DIR
#define TI_LMP90100_SPI_USCIB1_PxIN    P4IN
#define TI_LMP90100_SPI_USCIB1_SIMO    BIT1
#define TI_LMP90100_SPI_USCIB1_SOMI    BIT2
#define TI_LMP90100_SPI_USCIB1_UCLK    BIT3

// USCIB2 for F543x
#define TI_LMP90100_SPI_USCIB2_PxSEL1  P9SEL
#define TI_LMP90100_SPI_USCIB2_PxDIR1  P9DIR
#define TI_LMP90100_SPI_USCIB2_PxSEL2  P9SEL
#define TI_LMP90100_SPI_USCIB2_PxDIR2  P9DIR
#define TI_LMP90100_SPI_USCIB2_PxIN    P9IN
#define TI_LMP90100_SPI_USCIB2_SIMO    BIT1
#define TI_LMP90100_SPI_USCIB2_SOMI    BIT2
#define TI_LMP90100_SPI_USCIB2_UCLK    BIT3

// USCIB3 for F543x
#define TI_LMP90100_SPI_USCIB3_PxSEL1  P10SEL
#define TI_LMP90100_SPI_USCIB3_PxDIR1  P10DIR
#define TI_LMP90100_SPI_USCIB3_PxSEL2  P10SEL
#define TI_LMP90100_SPI_USCIB3_PxDIR2  P10DIR
#define TI_LMP90100_SPI_USCIB3_PxIN    P10IN
#define TI_LMP90100_SPI_USCIB3_SIMO    BIT1
#define TI_LMP90100_SPI_USCIB3_SOMI    BIT2
#define TI_LMP90100_SPI_USCIB3_UCLK    BIT3

// USART0 for F449
#define TI_LMP90100_SPI_USART0_PxSEL         P3SEL        
#define TI_LMP90100_SPI_USART0_PxDIR         P3DIR        
#define TI_LMP90100_SPI_USART0_PxIN          P3IN        
#define TI_LMP90100_SPI_USART0_SIMO          BIT1
#define TI_LMP90100_SPI_USART0_SOMI          BIT2
#define TI_LMP90100_SPI_USART0_UCLK          BIT3

// USART1 for F449
#define TI_LMP90100_SPI_USART1_PxSEL         P4SEL        
#define TI_LMP90100_SPI_USART1_PxDIR         P4DIR        
#define TI_LMP90100_SPI_USART1_PxIN          P4IN        
#define TI_LMP90100_SPI_USART1_SIMO          BIT3
#define TI_LMP90100_SPI_USART1_SOMI          BIT4
#define TI_LMP90100_SPI_USART1_UCLK          BIT5

// USCI_A0 for F261x
#define TI_LMP90100_SPI_UCA0_PxSEL1    P3SEL
#define TI_LMP90100_SPI_UCA0_PxDIR1    P3DIR
#define TI_LMP90100_SPI_UCA0_PxSEL2    P3SEL
#define TI_LMP90100_SPI_UCA0_PxDIR2    P3DIR
#define TI_LMP90100_SPI_UCA0_PxIN      P3IN
#define TI_LMP90100_SPI_UCA0_SIMO      BIT4
#define TI_LMP90100_SPI_UCA0_SOMI      BIT5
#define TI_LMP90100_SPI_UCA0_UCLK      BIT0

// USCI_A1 for F261x
#define TI_LMP90100_SPI_UCA1_PxSEL1    P3SEL
#define TI_LMP90100_SPI_UCA1_PxDIR1    P3DIR
#define TI_LMP90100_SPI_UCA1_PxSEL2    P5SEL
#define TI_LMP90100_SPI_UCA1_PxDIR2    P5DIR
#define TI_LMP90100_SPI_UCA1_PxIN      P3IN
#define TI_LMP90100_SPI_UCA1_SIMO      BIT6
#define TI_LMP90100_SPI_UCA1_SOMI      BIT7
#define TI_LMP90100_SPI_UCA1_UCLK      BIT0

// USCI_B0 for F261x
#define TI_LMP90100_SPI_UCB0_PxSEL1    P3SEL
#define TI_LMP90100_SPI_UCB0_PxDIR1    P3DIR
#define TI_LMP90100_SPI_UCB0_PxSEL2    P3SEL
#define TI_LMP90100_SPI_UCB0_PxDIR2    P3DIR
#define TI_LMP90100_SPI_UCB0_PxIN      P3IN
#define TI_LMP90100_SPI_UCB0_SIMO      BIT1
#define TI_LMP90100_SPI_UCB0_SOMI      BIT2
#define TI_LMP90100_SPI_UCB0_UCLK      BIT3

// USCI_B1 for F261x
#define TI_LMP90100_SPI_UCB1_PxSEL1    P5SEL
#define TI_LMP90100_SPI_UCB1_PxDIR1    P5DIR
#define TI_LMP90100_SPI_UCB1_PxSEL2    P5SEL
#define TI_LMP90100_SPI_UCB1_PxDIR2    P5DIR
#define TI_LMP90100_SPI_UCB1_PxIN      P5IN
#define TI_LMP90100_SPI_UCB1_SIMO      BIT1
#define TI_LMP90100_SPI_UCB1_SOMI      BIT2
#define TI_LMP90100_SPI_UCB1_UCLK      BIT3

// USI for G2x31 value series
#define TI_LMP90100_SPI_USI_PxDIR     P1DIR
#define TI_LMP90100_SPI_USI_PxIN      P1IN
#define TI_LMP90100_SPI_USI_SIMO      BIT6
#define TI_LMP90100_SPI_USI_SOMI      BIT7
#define TI_LMP90100_SPI_USI_UCLK      BIT5



//******************************************************************************
//  These constants are used to identify the chosen SPI and USART interfaces.
//******************************************************************************
#define TI_LMP90100_SER_INTF_NULL         0
#define TI_LMP90100_SER_INTF_USCIA0_5xx   1
#define TI_LMP90100_SER_INTF_USCIA1_5xx   2
#define TI_LMP90100_SER_INTF_USCIA2_5xx   3
#define TI_LMP90100_SER_INTF_USCIA3_5xx   4
#define TI_LMP90100_SER_INTF_USCIB0_5xx   5
#define TI_LMP90100_SER_INTF_USCIB1_5xx   6
#define TI_LMP90100_SER_INTF_USCIB2_5xx   7
#define TI_LMP90100_SER_INTF_USCIB3_5xx   8
#define TI_LMP90100_SER_INTF_USART0       9
#define TI_LMP90100_SER_INTF_USART1       10
#define TI_LMP90100_SER_INTF_USCIA0       11
#define TI_LMP90100_SER_INTF_USCIA1       12
#define TI_LMP90100_SER_INTF_USCIB0       13
#define TI_LMP90100_SER_INTF_USCIB1       14
#define TI_LMP90100_SER_INTF_USI          15

#endif                                                                         // HEADER_FILE_TI_LMP90100_MSP430_H
