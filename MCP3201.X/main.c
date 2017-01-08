/*
 * File:   main.c
 * Author: wouter
 *
 * Created on October 22, 2016, 5:17 PM
 */
#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "Drivers/TIMER0_Driver.h"
#include "Drivers/PORT_Driver.h"
#include "Drivers/UART_Driver.h"
#include "Drivers/MCP3201_Driver.h"

#define _XTAL_FREQ 16000000

#define COMMAND_Reset       "RE"
#define COMMAND_Initialize  "IN"
#define COMMAND_AnalogRead  "AR"
#define COMMAND_GetName     "GN"
#define COMMAND_DoorLid     "DL"
#define COMMAND_Heater      "HE"
#define COMMAND_Fan         "FA"
#define COMMAND_CloseDown   "CD"

#define MESSAGE_On          "ON"
#define MESSAGE_Off         "OFF"

READ_Data read;
uint16_t value;
bool isDoorOpen;

void initialize();
void handle_message(READ_Data msg);
void read_inputs();
void handle_inputs();

void initialize() {
    D_PORT_Init();
    // Initialize the UART module with a baud rate of 9600, with the use 
    // of interrupts.
    D_UART_Init("Panda", 9600, true);
    D_UART_Enable(true);
    
    // Initialize MCP3201
    D_MCP3201_Init();
    D_MCP3201_Enable(true);
    
    // Initialize TIMER0
    D_TIMRER0_Init(256);
    D_TIMER0_Enable(true);
    
    D_UART_Write(COMMAND_Initialize, "Initialized");
}

void main(void) {
    
    initialize();
    
    while(1) {
        
        if (D_TIMER0_Flag) {
            D_TIMER0_Flag = false;
            read_inputs();
            handle_inputs();
        }
        
        if (D_UART_ReadFlag) {
            D_UART_ReadFlag = false;
            uint8_t length = D_UART_BlockLength();
            if (length == 1) {
                handle_message(D_UART_Read());
            } else if (length > 1) {
                uint8_t i;
                for (i=0; i < length; i++) {
                    handle_message(D_UART_ReadBlock(i));
                }
            }
        }    
    }
    return;
}


void handle_message(READ_Data msg) {
    if (strcmp(msg.command, COMMAND_Initialize) == 0) {
        initialize();
        D_UART_Write(COMMAND_Initialize, "OK");
    } 
    
    if (strcmp(msg.command, COMMAND_AnalogRead) == 0) {
        value = D_MCP3201_Read();
        D_UART_WriteInt(COMMAND_AnalogRead, value);     
    } 
    
    else if (strcmp(msg.command, COMMAND_GetName) == 0) {
        D_UART_Write(COMMAND_GetName, D_UART_GetDeviceName());
    } 
    
    else if (strcmp(msg.command, COMMAND_Heater) == 0) {
        if (strcmp(msg.message, MESSAGE_On)) {
            LED1 = 1;
        } else {
            LED1 = 0;
        }
    } 
    
    else if (strcmp(msg.command, COMMAND_Fan) == 0) {
        if (strcmp(msg.message, MESSAGE_On)) {
            LED2 = 1;
        } else {
            LED2 = 0;
        }
    } 
    
    else if (strcmp(msg.command, COMMAND_CloseDown) == 0) {
        LED2 = LED1 = 0;
        D_TIMER0_Enable(false);
        D_MCP3201_Enable(false);
        D_UART_Enable(false);
    }
    
    else {
        D_UART_Write("Oops", "Did not understand that command");
    }
}

void read_inputs() {
    DOOR_LID_Dir = 1;  
    if (DOOR_LID == 0) {
        if (!isDoorOpen)
            D_UART_Write(COMMAND_DoorLid, "O");
        isDoorOpen = true;
    }
    else {
        if (isDoorOpen)
            D_UART_Write(COMMAND_DoorLid, "C");
        isDoorOpen = false;
    }
}

void handle_inputs() {
    if (isDoorOpen) {
        LED4 = 1;
    } else {
        LED4 = 0;
    }
}