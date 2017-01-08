#include <xc.h>
#include <stdio.h>
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <string.h>

#include "../Drivers/SYSTEM_Driver.h"
#include "../Drivers/INT_Driver.h"
#include "../Drivers/UART_Driver.h"
#include "Utils.h"
#include "UART_Controller.h"

/*******************************************************************************
 *          DEFINES
 ******************************************************************************/
// &
#define START_CHAR 0x26 
// $
#define STOP_CHAR  0x24 
// :
#define SEP_CHAR   0x3A 

#define READ_STATE_START   0x00
#define READ_STATE_TYPE    0x01
#define READ_STATE_SENDER  0x02
#define READ_STATE_BLOCK   0x03
#define READ_STATE_COMMAND 0x04
#define READ_STATE_MESSAGE 0x05
#define READ_STATE_END     0x06

/*******************************************************************************
 *          MACRO FUNCTIONS
 ******************************************************************************/

/*******************************************************************************
 *          VARIABLES
 ******************************************************************************/
static const char* startCharacter = "&";
static const char* stopCharacter = "$";
static const char* deviceName;
static const char* messageCharacter =     "[M]";
static const char* ackCharacter =         "[A]";

typedef struct {
    char type[5];      // Type of the message buffer  
    uint8_t typeCnt;      // Count of the type buffer
    uint8_t blockLength;  // One block = <Command>:<Message>:
    
    char sender[10];   // Sender name buffer
    uint8_t senderCnt;    // Count of the sender buffer
    
    ReadData_t data[10];  // Array with commands and messages
    uint8_t dataCnt;       // Count of the data packages
    
    uint8_t readId;       // Id send from the sender, to acknowledge
    uint8_t state;        // State of the read buffer
} ReadBuffer_t;

static ReadBuffer_t readBuffer;
static uint8_t inputBuffer[100];
static uint8_t inputBufferCnt;
static bool isFillingBuffer;
bool C_UART_ReadFlag;

/*******************************************************************************
 *          BASIC FUNCTIONS
 ******************************************************************************/
static void handleInputMessage(uint8_t* data, uint8_t length);
static void fillDataBuffer(uint8_t data);
static void acknowledge();

ReadData_t tmpData;

void handleInputMessage(uint8_t* data, uint8_t length) {
    uint8_t i = 0;
    while(i<length) {
        fillDataBuffer(*data);
        data++;
        i++;
    }
    
    C_UART_ReadFlag = true;
}

void fillDataBuffer(uint8_t data) {
    switch(readBuffer.state) {
        case READ_STATE_START:
            if(data == START_CHAR) {
                readBuffer.typeCnt = 0;
                readBuffer.blockLength = 0;
                readBuffer.senderCnt = 0;
                readBuffer.dataCnt = 0;
                C_UART_ReadFlag = false;
                readBuffer.state = READ_STATE_TYPE;
            } else {
                readBuffer.state = READ_STATE_START;
                return;
            }
            break;
        
        case READ_STATE_TYPE:
            if (data == SEP_CHAR) {
                readBuffer.state = READ_STATE_SENDER;
                readBuffer.type[readBuffer.typeCnt] = '\0';
            } else {
                readBuffer.type[readBuffer.typeCnt] = data;
                readBuffer.typeCnt++;
                if(readBuffer.typeCnt > 5) {
                    readBuffer.typeCnt = 0;
                }
            }
            break;
            
        case READ_STATE_SENDER:
            if (data == SEP_CHAR) {
                readBuffer.state = READ_STATE_BLOCK;
                readBuffer.sender[readBuffer.senderCnt] = '\0';
            } else {
                readBuffer.sender[readBuffer.senderCnt] = data;
                readBuffer.senderCnt++;
                if(readBuffer.senderCnt > 10) {
                    readBuffer.senderCnt = 0;
                }
            }
            break;
            
        case READ_STATE_BLOCK:
            if (data == SEP_CHAR) {
                readBuffer.state = READ_STATE_COMMAND;
                readBuffer.sender[readBuffer.senderCnt] = '\0';
            } else {
                readBuffer.blockLength = (data - 0x30);
                readBuffer.dataCnt = (data - 0x30);
            }
            break;
            
        case READ_STATE_COMMAND:
            if (data == SEP_CHAR) {
                readBuffer.state = READ_STATE_MESSAGE;
                tmpData.command[tmpData.commandCnt] = '\0';
            } else {
                tmpData.command[tmpData.commandCnt] = data;
                tmpData.commandCnt++;
                if(tmpData.commandCnt > 2) {
                    tmpData.commandCnt = 0;
                }
            }
            break;
            
        case READ_STATE_MESSAGE:
            if (data == SEP_CHAR) {
                tmpData.message[tmpData.messageCnt] = '\0';
                
                readBuffer.dataCnt--;
                readBuffer.data[readBuffer.dataCnt] = tmpData;
                
                uint8_t i = 0;
                for (i=0; i < tmpData.commandCnt; i++) {
                    tmpData.command[i] = 0;
                }
                for (i=0; i < tmpData.messageCnt; i++) {
                    tmpData.message[i] = 0;
                }
                
                tmpData.commandCnt = 0;
                tmpData.messageCnt = 0;

                if (readBuffer.dataCnt == 0) {
                    readBuffer.state = READ_STATE_END;
                } else {
                    readBuffer.state = READ_STATE_COMMAND;
                }
            } else {
                tmpData.message[tmpData.messageCnt] = data;
                tmpData.messageCnt++;
                if(tmpData.messageCnt > 50) {
                    tmpData.messageCnt = 0;
                }
            }
            break;
            
        case READ_STATE_END:
            if (data == STOP_CHAR) {
                acknowledge();
                readBuffer.state = READ_STATE_START;
            } else {
                readBuffer.readId = (data - 0x30);
            }
            break;
            
        default: 
            readBuffer.state = READ_STATE_START;
            break;
    }
}

void acknowledge() {
    printf(startCharacter);
    
    printf(ackCharacter);
    // id
    printf("%x",readBuffer.readId);
    
    printf(stopCharacter);
}

/*******************************************************************************
 *          DRIVER FUNCTIONS
 ******************************************************************************/
void C_UART_Init(const char* name, uint16_t baud) {
    // Initialize UART
    D_UART_Init(UART_MODULE_1, baud);
    
    // Clear/set variables
    deviceName = name;
    C_UART_ReadFlag = false;
    inputBufferCnt = 0;
    isFillingBuffer = false;
    readBuffer.state = READ_STATE_START;
    
    // Enable UART
    D_UART_Enable(UART_MODULE_1, true);
    
    // Interrupts for reading
    D_INT_EnableUartInterrupts(true);
}

void C_UART_Write(const char* command, const char* data) {
    printf(startCharacter);
    
    printf(messageCharacter);
    printf(deviceName);
    // Command
    printf(":");printf(command);
    // Message
    printf(":");printf(data);
    
    printf(stopCharacter);
    DelayMs(1);
}

void C_UART_WriteInt(const char* command, int16_t data) {
    printf(startCharacter);
    
    printf(messageCharacter);
    printf(deviceName);
    // Command
    printf(":");printf(command);
    // Message
    printf(":");printf("%d",data);
    
    printf(stopCharacter);
    DelayMs(1);
}

void C_UART_AppendMessage(char c) {
    if ((c == START_CHAR) && (isFillingBuffer == false)) {
        isFillingBuffer = true;
    }
    
    if (c == STOP_CHAR) {
        inputBuffer[inputBufferCnt] = c;
        inputBufferCnt++;
        handleInputMessage(inputBuffer, inputBufferCnt);

        // Clean it up
        isFillingBuffer = false;
        inputBufferCnt = 0;
    }
    
    if(isFillingBuffer) {
        inputBuffer[inputBufferCnt] = c;
        inputBufferCnt++;
    }
}

ReadData_t C_UART_ReadMessage(){
    return readBuffer.data[0];
}

ReadData_t C_UART_ReadBlockMessage(uint8_t cnt) {
    return readBuffer.data[cnt];
}

uint8_t C_UART_BlockLength() {
    return readBuffer.blockLength;
}

const char* C_UART_GetDeviceName() {
    return deviceName;
}

void C_UART_HandleMessage(ReadData_t msg) {

    if (StringEquals(msg.command, COMMAND_Initialize)) {
        //initialize();
        C_UART_Write(COMMAND_Initialize, "OK");
    } 
    
    else if (StringEquals(msg.command, COMMAND_AnalogRead)) {
        //value = D_MCP3201_Read();
        C_UART_WriteInt(COMMAND_AnalogRead, 125);     
    } 
    
    else if (StringEquals(msg.command, COMMAND_GetName)) {
        C_UART_Write(COMMAND_GetName, deviceName);
    } 
    
    else if (StringEquals(msg.command, COMMAND_Heater)) {
        if (StringEquals(msg.message, MESSAGE_On)) {
            //LED1 = 1;
        } else {
            //LED1 = 0;
        }
    } 
    
    else if (StringEquals(msg.command, COMMAND_Fan)) { 
        if (StringEquals(msg.message, MESSAGE_On)) {
            //LED2 = 1;
        } else {
            //LED2 = 0;
        }
    } 
    
    else if (StringEquals(msg.command, COMMAND_CloseDown)) {
        //LED2 = LED1 = 0;
//        D_TIMER0_Enable(false);
//        D_MCP3201_Enable(false);
        //D_UART_Enable(false);
    }
    
    else {
        C_UART_Write("Error", "Command not known");
    }
}


