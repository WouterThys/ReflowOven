#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>

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
 *          BASIC FUNCTIONS
 ******************************************************************************/


/*******************************************************************************
 *          DRIVER FUNCTIONS
 ******************************************************************************/
void D_PORT_Init() {
    TRISA = 0x00;   PORTA = 0x00;
    TRISB = 0x00;   PORTB = 0x00;
    TRISC = 0x00;   PORTC = 0x00;
    ADCON1 = 0x0F;
    
    LED1_Dir = 0; LED1 = 0;   
    LED2_Dir = 0; LED2 = 0;     
    LED3_Dir = 0; LED3 = 0;       
    LED4_Dir = 0; LED4 = 0;
    
    DOOR_LID_Dir = 1;             
}