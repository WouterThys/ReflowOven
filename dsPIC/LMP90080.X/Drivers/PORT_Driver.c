#include <xc.h>
#include <stdio.h>
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "SPI_Driver.h"
#include "UART_Driver.h"
#include "PORT_Driver.h"

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
 *          LOCAL FUNCTIONS
*******************************************************************************/
static void initSpiPorts_1(uint16_t MS);
static void initSpiPorts_2(uint16_t MS);

static void initUartPorts_1(void);
static void initUartPorts_2(void);

void initSpiPorts_1(uint16_t MS) {
        // Tri-sates
    if(MS == SPI_MASTER) {
        SPI1_SCK_Dir = 0;
    } else if(MS == SPI_SLAVE) {
        SPI1_SCK_Dir = 1;
    } else {
        return;
    }
    SPI1_SDI_Dir = 1;
    SPI1_SDO_Dir = 0;
}

void initSpiPorts_2(uint16_t MS) {
//    // Tri-sates
//    if(MS == SPI_MASTER) {
//        SPI2_SCK_Dir = 0;
//    } else if(MS == SPI_SLAVE) {
//        SPI2_SCK_Dir = 1;
//    } else {
//        return;
//    }
//    SPI2_SDI_Dir = 1;
//    SPI2_SDO_Dir = 0;
//    
//    // Mapping
//    if(MS == SPI_MASTER) {
//        RPOR4bits.RP42R = SPI2_SCK_O;
//    } else if(MS == SPI_SLAVE) {
//        RPINR22bits.SCK2R = SPI2_SCK_I;
//    } else {
//        return;
//    }
//    RPINR22bits.SDI2R = SPI2_SDI;
//    RPOR4bits.RP43R = SPI2_SDO;
}

void initUartPorts_1() {
    // Tri-states
    UART1_RX_Dir = 1;
    UART1_TX_Dir = 0;
    
    // Mapping
    RPINR18bits.U1RXR = UART1_RX;
    RPOR2bits.RP38R = UART1_TX;
}

void initUartPorts_2() {
    
}

/*******************************************************************************
 *          DRIVER FUNCTIONS
*******************************************************************************/
void D_PORT_SetSpiPorts(uint16_t which, uint16_t MS) {
    if(which == SPI_MODULE_1) {
        initSpiPorts_1(MS);
    } else if (which == SPI_MODULE_2) {
        initSpiPorts_2(MS);
    } else {
        return;
    }
}

void D_PORT_SetUartPorts(uint16_t which) {
    if(which == UART_MODULE_1) {
        initUartPorts_1();
    } else if(which == UART_MODULE_2) {
        initUartPorts_2();
    } else {
        return;
    }
}

void D_PORT_SetLmpInterruptPort(void) {
    DRDYB_Dir = 1; // Input for interrupts
    RPINR0bits.INT1R = RP36; // RP36 (RB4) tied to INT1 interrupt pin
}