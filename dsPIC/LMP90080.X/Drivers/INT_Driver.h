/* 
 * File:   interrupts.h
 * Author: wouter
 *
 * Created on 3 maart 2015, 13:06
 */

#ifndef INT_DRIVER_H
#define	INT_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * Interrupt priorities
 */

#define INT2_IP     6
#define INT1_IP     3
#define U1RX_IP     5
#define TMR2_IP     4   
#define TMR4_IP     1

/**
 * Initializes the interrupts to the default settings.
 */
void D_INT_Init(void);
/**
 * Enable interrupts.
 */
void D_INT_EnableInterrupts(bool enable);

/**
 * 
 * @param enable
 */
void D_INT_EnableUartInterrupts(bool enable);

#ifdef	__cplusplus
}
#endif

#endif	