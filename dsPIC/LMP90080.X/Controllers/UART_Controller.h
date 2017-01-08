/* 
 * File:   UART_Controller.h
 * Author: wouter
 *
 * Created on January 1, 2017, 2:03 PM
 */

#ifndef UART_CONTROLLER_H
#define	UART_CONTROLLER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
#include <stdbool.h>
    
    // Defines
    
#define MESSAGE_TYPE    0
#define BLOCK_TYPE      1
    
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
    
    // Variables

    /**
     * Boolean indicating data can be read.
     */
    extern bool C_UART_ReadFlag;
    
    // Typedefs
    
    /**
     * Data struct for reading data.
     */
    typedef struct {
        char command[2];   // Command buffer
        uint8_t commandCnt;   // Count of the command buffer
        char message[50];  // Message buffer
        uint8_t messageCnt;   // Count of the message buffer
    } ReadData_t;

    
    // Functions
    
    /**
    * Initializes all the parameters to the default setting, as well as writing the
    * tri-state registers. Initializes the UART to the default data rate and settings.
    * @param name The name of the device.
    * @param baud The baud rate.
    */
    void C_UART_Init(const char * name, uint16_t baud);
    
    /**
    * Write data to the TX pin of UART module. 
    * @param command: Command
    * @param data: Data string to write
    */
   void C_UART_Write(const char* command, const char* data);

    /**
     * Write data to the TX pin of UART module. 
     * @param command: Command
     * @param data: Data integer to write
     */
    void C_UART_WriteInt(const char* command, int16_t data);

    /**
     * Read data from the RX pin of UART module.
     * @return data: returns the data struct.
     */
    ReadData_t C_UART_ReadMessage(void);
    
    /**
     * 
     * @param c
     */
    void C_UART_AppendMessage(char c);


    /**
     * 
     * @return 
     */
    ReadData_t C_UART_ReadBlockMessage(uint8_t cnt);
    uint8_t C_UART_BlockLength(void);
    uint8_t C_UART_MessageType(void);

    /**
     * Get the device name.
     * @return const char* device name
     */
    const char* C_UART_GetDeviceName();
    
    /**
     * 
     * @param msg
     */
    void C_UART_HandleMessage(ReadData_t msg);


#ifdef	__cplusplus
}
#endif

#endif	/* UART_CONTROLLER_H */

