//******************************************************************************
//  Description:  This file contains functions that allow the MSP430 device to
//  access the SPI interface of the LMP90100.  There are multiple
//  instances of each function; the one to be compiled is selected by the
//  system variable TI_LMP90100_SER_INTF, defined in "TI_LMP90100_hardware_board.h".
//
//  MSP430/LMP90100 Interface Code Library v1.0
// 
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
/*  Copyright 2011-2012 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user who
  downloaded the software, his/her employer (which must be your employer) and
  Texas Instruments Incorporated (the "License"). You may not use this Software
  unless you agree to abide by the terms of the License. The License limits your
  use, and you acknowledge, that the Software may not be modified, copied or
  distributed unless embedded on a Texas Instruments microcontroller which is 
  integrated into your product. Other than for the foregoing purpose, you may 
  not use, reproduce, copy, prepare derivative works of, modify, distribute, 
  perform, display or sell this Software and/or its documentation for any 
  purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL TEXAS
  INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL
  EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT
  LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL
  DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS,
  TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT
  LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
*******************************************************************************/

#include <stdint.h>
#include "TI_LMP90100.h"
#include "TI_MSP430.h"
#include "TI_MSP430_hardware_board.h"
#include "TI_MSP430_spi.h"


//******************************************************************************
// Support for 552x USART0
//******************************************************************************
#if TI_LMP90100_SER_INTF == TI_LMP90100_SER_INTF_USART0

//------------------------------------------------------------------------------
//  void TI_LMP90100_SPISetup(void)
//
//  DESCRIPTION:
//  Configures the assigned interface to function as a SPI port and
//  initializes it.
//------------------------------------------------------------------------------
void TI_LMP90100_SPISetup(void)
{
  TI_LMP90100_CSn_PxOUT |= TI_LMP90100_CSn_PIN;
  TI_LMP90100_CSn_PxDIR |= TI_LMP90100_CSn_PIN;                                // /CS disable

  ME1 |= USPIE0;                                                               // Enable USART0 SPI mode
  UCTL0 = SWRST;                                                               // Disable USART state machine
  UCTL0 |= CHAR + SYNC + MM;                                                   // 8-bit SPI Master **SWRST**
  UTCTL0 |= CKPH + SSEL1 + SSEL0 + STC;                                        // SMCLK, 3-pin mode
  UBR00 = 0x02;                                                                // UCLK/2
  UBR10 = 0x00;                                                                // 0
  UMCTL0 = 0x00;                                                               // No modulation
  TI_LMP90100_SPI_USART0_PxSEL |= TI_LMP90100_SPI_USART0_SIMO
                          | TI_LMP90100_SPI_USART0_SOMI
                          | TI_LMP90100_SPI_USART0_UCLK;
                                                                               // SPI option select
  TI_LMP90100_SPI_USART0_PxDIR |= TI_LMP90100_SPI_USART0_SIMO 
                                  + TI_LMP90100_SPI_USART0_UCLK;               // SPI TX out direction
  UCTL0 &= ~SWRST;                                                             // Initialize USART state machine
}

//------------------------------------------------------------------------------
//  void TI_LMP90100_SPIWriteReg(uint8_t addr, uint8_t value, uint8_t *pURA)
//
//  DESCRIPTION:
//  Writes "value" to a single configuration register at address "addr". If 
//  "addr" lies within the same segment as "*pURA", it takes 1 less transaction 
//  to write the value.
//------------------------------------------------------------------------------
void TI_LMP90100_SPIWriteReg(uint8_t addr, uint8_t value, uint8_t *pURA)
{
  uint8_t new_URA, inst;
  
  new_URA = (addr & LMP90100_URA_MASK)>>4;                                     // extract upper register address

  TI_LMP90100_CSn_PxOUT &= ~TI_LMP90100_CSn_PIN;                               // /CS enable
  while (TI_LMP90100_SPI_USART0_PxIN&TI_LMP90100_SPI_USART0_SOMI);             // wait for LMP90100 ready
  
  if (*pURA != new_URA)                                                        // if new and previous URA not same, add transaction 1
  {    
    inst = LMP90100_INSTRUCTION_BYTE1_WRITE;                                   // Transaction-1
    
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag
    U0TXBUF = inst;                                                            // Send instruction
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
 
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag
    U0TXBUF = new_URA;                                                         // Send upper register address 
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
    
    *pURA = new_URA;                                                           // save new URA
    
  }
  
  inst = LMP90100_WRITE_BIT | LMP90100_SIZE_1B |(addr & LMP90100_LRA_MASK);    // lower register address
  
  while (!(IFG1 & UTXIFG0));                                                   // Wait for TXBUF ready
  IFG1 &= ~URXIFG0;                                                            // clear flag
  U0TXBUF = inst;                                                              // Send lower register address
  while (!(IFG1 & URXIFG0));                                                   // wait for tx to finish  
  
  while (!(IFG1 & UTXIFG0));                                                   // Wait for TXBUF ready
  IFG1 &= ~URXIFG0;                                                            // clear flag
  U0TXBUF = value;                                                             // Send data value
  while (!(IFG1 & URXIFG0));                                                   // wait for tx to finish  
  
  TI_LMP90100_CSn_PxOUT |= TI_LMP90100_CSn_PIN;                                // /CS disable
  
}
//------------------------------------------------------------------------------
//  uint8_t TI_LMP90100_SPIReadReg(uint8_t addr, unit8_t *pURA)
//
//  DESCRIPTION:
//  Reads a single configuration register at address "addr" and returns the
//  value read. If "addr" lies within the same segment as "*pURA", it takes 1 
//  less transaction to read the value.
//------------------------------------------------------------------------------
uint8_t TI_LMP90100_SPIReadReg(uint8_t addr, uint8_t *pURA)
{
  uint8_t x, new_URA, inst;

  new_URA = (addr & LMP90100_URA_MASK)>>4;                                     // extract upper register address 
  TI_LMP90100_CSn_PxOUT &= ~TI_LMP90100_CSn_PIN;                               // /CS enable
  while (TI_LMP90100_SPI_USART0_PxIN&TI_LMP90100_SPI_USART0_SOMI);             // wait for LMP90100 ready  
  
  if (*pURA != new_URA)                                                        // if new and previous URA not same, add transaction 1
  {    
    inst = LMP90100_INSTRUCTION_BYTE1_WRITE;                                   // Transaction-1
    
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag    
    U0TXBUF = inst;                                                            // Send instruction
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
  
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag    
    U0TXBUF = new_URA;                                                         // Send upper register address
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
    
    *pURA = new_URA;                                                           // save new URA
    
  }
  
  inst = LMP90100_READ_BIT | LMP90100_SIZE_1B | (addr & LMP90100_LRA_MASK);    // Transaction-2
  
  while (!(IFG1 & UTXIFG0));                                                   // Wait for TXBUF ready
  IFG1 &= ~URXIFG0;                                                            // clear flag  
  U0TXBUF = inst;                                                              // Send lower register address
  while (!(IFG1 & URXIFG0));                                                   // wait for tx to finish  
  
  while (!(IFG1 & UTXIFG0));                                                   // Wait for TXBUF ready
  IFG1 &= ~URXIFG0;                                                            // clear flag
  U0TXBUF = 0;                                                                 // Dummy write so we can read data
  while (!(IFG1 & URXIFG0));                                                   // wait for tx to finish
  
  x = U0RXBUF;                                                                 // Read data
  
  TI_LMP90100_CSn_PxOUT |= TI_LMP90100_CSn_PIN;                                // /CS disable

  return x;
}
//------------------------------------------------------------------------------
//  void TI_LMP90100_SPINormalStreamWriteReg(uint8_t addr, uint8_t *buffer, uint8_t count, uint8_t *pURA)
//
//  DESCRIPTION:
//  Writes values to multiple configuration registers, the first register being
//  at address "addr".  First data byte is at "buffer", and both addr and
//  buffer are incremented sequentially (within the LMP90100 and MSP430,
//  respectively) until "count" writes have been performed. If "addr" lies within
//  the same segment as "*pURA", it takes 1 less transaction to write the value.
//------------------------------------------------------------------------------
void TI_LMP90100_SPINormalStreamWriteReg(uint8_t addr, uint8_t *buffer, 
                                         uint8_t count, uint8_t *pURA)
{
  uint8_t new_URA, inst, i;
  
  new_URA = (addr & LMP90100_URA_MASK)>>4;                                     // extract upper register address

  TI_LMP90100_CSn_PxOUT &= ~TI_LMP90100_CSn_PIN;                               // /CS enable
  while (TI_LMP90100_SPI_USART0_PxIN&TI_LMP90100_SPI_USART0_SOMI);             // wait for LMP90100 ready
  
  if (*pURA != new_URA)                                                        // if new and previous URA not same, add transaction 1
  {    
    inst = LMP90100_INSTRUCTION_BYTE1_WRITE;                                   // Transaction-1
    
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag    
    U0TXBUF = inst;                                                            // Send instruction
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
    
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag    
    U0TXBUF = new_URA;                                                         // Send upper register address 
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
    
    *pURA = new_URA;                                                           // save new URA
  }
  
  inst = LMP90100_WRITE_BIT | LMP90100_SIZE_STREAM 
                            | (addr & LMP90100_LRA_MASK);                      // lower register address
  while (!(IFG1 & UTXIFG0));                                                   // Wait for TXBUF ready
  IFG1 &= ~URXIFG0;                                                            // clear flag  
  U0TXBUF = inst;                                                              // Send lower register address
  while (!(IFG1 & URXIFG0));                                                   // wait for tx to finish
  
  for(i= 0; i < count; i++)
  {
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag    
    U0TXBUF = *(buffer+i);                                                     // Send data value
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
  }

   TI_LMP90100_CSn_PxOUT |= TI_LMP90100_CSn_PIN;                               // /CS disable
  
}
//------------------------------------------------------------------------------
//  void TI_LMP90100_SPIReadNormalStreamReg(uint8_t addr, unit8_t *buffer, uint8_t count, uint8_t *pURA)
//
//  DESCRIPTION:
//  Reads multiple configuration registers, the first register being at address
//  "addr".  Values read are deposited sequentially starting at address
//  "buffer", until "count" registers have been read. If "addr" lies within
//  the same segment as "*pURA", it takes 1 less transaction to read the value.
//------------------------------------------------------------------------------
void TI_LMP90100_SPINormalStreamReadReg(uint8_t addr, uint8_t *buffer, 
                                        uint8_t count, uint8_t *pURA)
{
  uint8_t i, new_URA, inst;

  new_URA = (addr & LMP90100_URA_MASK)>>4;                                     // extract upper register address
  
  TI_LMP90100_CSn_PxOUT &= ~TI_LMP90100_CSn_PIN;                               // /CS enable
  while (TI_LMP90100_SPI_USART0_PxIN&TI_LMP90100_SPI_USART0_SOMI);             // wait for LMP90100 ready
  
  if (*pURA != new_URA)                                                        // if new and previous URA not same, add transaction 1
  {    
    inst = LMP90100_INSTRUCTION_BYTE1_WRITE;                                   // Transaction-1
    
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag    
    U0TXBUF = inst;                                                            // Send instruction
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
  
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag    
    U0TXBUF = new_URA;                                                         // Send upper register address 
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
    
    *pURA = new_URA;                                                           // save new URA
    
  }
 
  inst = LMP90100_READ_BIT | LMP90100_SIZE_STREAM 
                           | (addr & LMP90100_LRA_MASK);                       // Transaction-2
  
  while (!(IFG1 & UTXIFG0));                                                   // Wait for TXBUF ready
  IFG1 &= ~URXIFG0;                                                            // clear flag  
  U0TXBUF = inst;                                                              // Send lower register address  
  while (!(IFG1 & URXIFG0));                                                   // wait for tx to finish  
  
  for(i=0; i < count; i++)
  {
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag    
    U0TXBUF = 0;                                                               // Dummy write so we can read data
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish

    *(buffer+i) = U0RXBUF;                                                     // Read data
  }
  TI_LMP90100_CSn_PxOUT |= TI_LMP90100_CSn_PIN;                                // /CS disable

}
//------------------------------------------------------------------------------
//  void TI_LMP90100_SPICRCCheck(uint8_t *buffer, uint8_t count)
//
//  DESCRIPTION: Checks if CRC read from the device matches computed result. 
//  CRC is computed for "count" bytes at address "buffer" and compared against CRC 
//  stored in "buffer[count]" and returns "CRC_PASS" or "CRC_FAIL" accordingly.
//
//------------------------------------------------------------------------------
uint8_t TI_LMP90100_SPICRCCheck (uint8_t *buffer, uint8_t count)
{
  uint8_t crc_data, crc_calc;
  
  crc_data = buffer[count];                                                    // extract CRC data
  crc_calc = TI_LMP90100_crc8MakeBitwise2(CRC8_INIT_REM, CRC8_POLY, 
                                           buffer, count);                     // calculate CRC for the adc output (size 3 bytes)  
  if (crc_data == crc_calc)
    return CRC_PASS;
  else
    return CRC_FAIL;
}

//------------------------------------------------------------------------------
//  void TI_LMP90100_SPINormalStreamReadADC(uint8_t addr, uint8_t *buffer, uint8_t count, uint8_t *pURA)
//
//  DESCRIPTION:
//  Special read function for reading ADC data registers. Reads multiple registers, 
//  the first register being at address"addr".  Values read are deposited sequentially 
//  starting at address "buffer", until "count" registers have been read. If "addr" lies 
//  within the same segment as "*pURA", it takes 1 less transaction to read the value.
//------------------------------------------------------------------------------
void TI_LMP90100_SPINormalStreamReadADC(uint8_t addr, uint8_t *buffer, 
                                        uint8_t count, uint8_t *pURA)
{
  uint8_t i, new_URA, inst;
  
  new_URA = (addr & LMP90100_URA_MASK)>>4;                                     // extract upper register address
  
  TI_LMP90100_CSn_PxOUT &= ~TI_LMP90100_CSn_PIN;                               // /CS enable
  while (TI_LMP90100_SPI_USART0_PxIN&TI_LMP90100_SPI_USART0_SOMI);             // wait for LMP90100 ready
  
  if (*pURA != new_URA)                                                        // if new and previous URA not same, add transaction 1
  {    
    inst = LMP90100_INSTRUCTION_BYTE1_WRITE;                                   // Transaction-1
    
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag    
    U0TXBUF = inst;                                                            // Send instruction
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
  
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag    
    U0TXBUF = new_URA;                                                         // Send upper register address 
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
    
    *pURA = new_URA;                                                           // save new URA
    
  }
 
  inst = LMP90100_READ_BIT | LMP90100_SIZE_STREAM 
         | (addr & LMP90100_LRA_MASK);                                         // Transaction-2
  
  while (!(IFG1 & UTXIFG0));                                                   // Wait for TXBUF ready
  IFG1 &= ~URXIFG0;                                                            // clear flag  
  U0TXBUF = inst;                                                              // Send lower register address  
  while (!(IFG1 & URXIFG0));                                                   // wait for tx to finish
  
  for(i=0; i<count; i++)
  {
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag    
    U0TXBUF = 0;                                                               // Dummy write so we can read data
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
 
    *(buffer+i) = U0RXBUF;                                                     // Read register data    
  }
    
  TI_LMP90100_CSn_PxOUT |= TI_LMP90100_CSn_PIN;                                // /CS disable   
}
//------------------------------------------------------------------------------
//  void TI_LMP90100_SPIControlledStreamReadADC(uint8_t addr, uint8_t *buffer, uint8_t count, uint8_t *pURA)
//
//  DESCRIPTION:
//  Special read function for reading ADC data registers in Controlled Stream Mode.  
//  Reads multiple registers, the first register being at address"addr".  Values read  
//  are deposited sequentiallystarting at address "buffer", until "count" registers 
//  have been read. If "addr" lies within the same segment as "*pURA", it takes 1 less 
//  transaction to read the value.
//------------------------------------------------------------------------------
void TI_LMP90100_SPIControlledStreamReadADC(uint8_t addr, uint8_t *buffer, 
                                            uint8_t count, uint8_t *pURA)
{
  uint8_t i, new_URA, inst;
  static uint8_t repeat_controlled = 0;                                        // if set, LRA transaction is skipped
  

  new_URA = (addr & LMP90100_URA_MASK)>>4;                                     // extract upper register address
//  CS Enable/Disable done outside so it is for entire controlled stream transaction    
  while (TI_LMP90100_SPI_USART0_PxIN&TI_LMP90100_SPI_USART0_SOMI);             // wait for LMP90100 ready
  
  if (*pURA != new_URA)                                                        // if new and previous URA not same, add transaction 1
  {    
    inst = LMP90100_INSTRUCTION_BYTE1_WRITE;                                   // Transaction-1
    
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag    
    U0TXBUF = inst;                                                            // Send instruction
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
    
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag    
    U0TXBUF = new_URA;                                                         // Send upper register address 
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
    
    *pURA = new_URA;                                                           // save new URA
    if (repeat_controlled)
      repeat_controlled = 0;
  }
  if (!repeat_controlled)
  { 
    inst = LMP90100_READ_BIT | LMP90100_SIZE_STREAM 
         | (addr & LMP90100_LRA_MASK);                                         // Transaction-2
  
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag    
    U0TXBUF = inst;                                                            // Send lower register address
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
    repeat_controlled = 1;
  }
  for(i=0; i<count; i++)
  {
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag    
    U0TXBUF = 0;                                                               // Dummy write so we can read data
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
    
    *(buffer+i) = U0RXBUF;                                                     // Read register data    
  } 
}
//------------------------------------------------------------------------------
//  void TI_LMP90100_SPIDataOnlyReadADC(uint8_t addr, uint8_t *buffer, uint8_t count, uint8_t *pURA)
//
//  DESCRIPTION:
//  Special read function for reading ADC data registers in Data only read mode. Values read 
//  deposited sequentialy starting at address "buffer", until "count" registers have been read. 
//  In order to use the data only read transaction capability of the LMP90100, the data first 
//  mode must be enabled by calling TI_LMP90100_SPIEnableDataFirstMode() function.
//------------------------------------------------------------------------------
void TI_LMP90100_SPIDataOnlyReadADC(uint8_t *buffer, uint8_t count)
{
  uint8_t i;
  
  TI_LMP90100_CSn_PxOUT &= ~TI_LMP90100_CSn_PIN;                               // /CS enable
  while (TI_LMP90100_SPI_USART0_PxIN&TI_LMP90100_SPI_USART0_SOMI);             // wait for LMP90100 ready
  for(i=0; i<count; i++)
  {
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag
    U0TXBUF =0;                                                                // Dummy write so we can read data     
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish  
    *(buffer+i) = U0RXBUF;                                                     // Read register data  
  }    
  TI_LMP90100_CSn_PxOUT |= TI_LMP90100_CSn_PIN;                                // /CS disable
      
}
//------------------------------------------------------------------------------
//  void TI_LMP90100_crc8MakeBitwise2(uint8_t crc, uint8_t poly, uint8_t *pmsg, uint8_t msg_size)
//
//  DESCRIPTION: Compute 8bit CRC of data "*pmsg" of size "msg_size" bytes using polynomial "poly" and init value "crc"
//    
//  
//------------------------------------------------------------------------------
uint8_t TI_LMP90100_crc8MakeBitwise2(uint8_t crc, uint8_t poly, uint8_t *pmsg, uint8_t msg_size)
{
  uint8_t i, j;
  uint8_t msg;
    
  for(i = 0 ; i < msg_size ; i ++)
  {
    msg = (*pmsg++ << 0);
    for(j = 0 ; j < 8 ; j++)
    {
      if((msg ^ crc) >> 7) 
        crc = (crc << 1) ^ poly; 
      else crc <<= 1;	
        msg <<= 1;
    }
  } 
  
  return(crc ^ CRC8_FINAL_XOR);
  
}
//------------------------------------------------------------------------------
//  void TI_LMP90100_SPIEnableDataFirstMode(uint8_t addr, uint8_t count, uint8_t *pURA)
//
//  DESCRIPTION:
//  Enables the data first mode of LMP90100. DATA_ONLY_1 and DATA_ONLY_2 registers are initialized 
//  to "addr" and "count-1" and the LMP90100 is placed in the data first mode. In order to use the 
//  data only read transaction capability of the LMP90100, the data first mode must be enabled.
//
//------------------------------------------------------------------------------
void TI_LMP90100_SPIEnableDataFirstMode(uint8_t addr, uint8_t count, uint8_t *pURA)
{
  TI_LMP90100_SPIWriteReg(TI_LMP90100_DATA_ONLY_1_REG, addr, pURA);            // Load DATA_ONLY_1 register with address
  TI_LMP90100_SPIWriteReg(TI_LMP90100_DATA_ONLY_2_REG, count-1, pURA);         // Load DATA_ONLY_2 register with count-1 
  
  TI_LMP90100_CSn_PxOUT &= ~TI_LMP90100_CSn_PIN;                               // /CS enable
  while (TI_LMP90100_SPI_USART0_PxIN&TI_LMP90100_SPI_USART0_SOMI);             // wait for LMP90100 ready
  
  while (!(IFG1 & UTXIFG0));                                                   // Wait for TXBUF ready
  IFG1 &= ~URXIFG0;                                                            // clear flag
  U0TXBUF = LMP90100_DATA_FIRST_MODE_INSTRUCTION_ENABLE;                       // write Data First mode instruction
  while (!(IFG1 & URXIFG0));                                                   // wait for tx to finish
  
  while (!(IFG1 & UTXIFG0));                                                   // Wait for TXBUF ready 
  IFG1 &= ~URXIFG0;                                                            // clear flag
  U0TXBUF = LMP90100_DATA_FIRST_MODE_INSTRUCTION_READ_MODE_STATUS;             // Write read mode status instruction
  while (!(IFG1 & URXIFG0));                                                   // wait for tx to finish
  
  while (!(U0RXBUF & LMP90100_DATA_FIRST_MODE_STATUS_FLAG))                    // wait for device to enter data first mode
  {
    IFG1 &= ~URXIFG0;                                                          // clear flag
    U0TXBUF = LMP90100_DATA_FIRST_MODE_INSTRUCTION_READ_MODE_STATUS;           // Write device read mode status instruction
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
  }
  
  TI_LMP90100_CSn_PxOUT |= TI_LMP90100_CSn_PIN;                                // /CS disable  
}
//------------------------------------------------------------------------------
//  void TI_LMP90100_SPIDisableDataFirstMode(uint8_t *buffer, uint8_t count)
//
//  DESCRIPTION:
//  Disables the data first mode of LMP90100. Reads data bytes of the data only transaction 
//  and then disables the data first mode of LMP90100. The data only transaction bytes are 
//  deposited sequentially starting at address "buffer", until "count" registers have been read.
//   
//------------------------------------------------------------------------------
void TI_LMP90100_SPIDisableDataFirstMode(uint8_t *buffer, uint8_t count)
{
  uint8_t i;
  
  TI_LMP90100_CSn_PxOUT &= ~TI_LMP90100_CSn_PIN;                               // /CS enable
  while (TI_LMP90100_SPI_USART0_PxIN&TI_LMP90100_SPI_USART0_SOMI);             // wait for LMP90100 ready
  
  // Method to disable data first mode: First read the data & then disable
  for(i=0; i<count; i++)
  {
    while (!(IFG1 & UTXIFG0));                                                 // Wait for TXBUF ready
    IFG1 &= ~URXIFG0;                                                          // clear flag
    U0TXBUF =0;                                                                // Dummy write so we can read data     
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish  
    *(buffer+i) = U0RXBUF;                                                     // Read register data    
  }
  
  while (!(IFG1 & UTXIFG0));                                                   // Wait for TXBUF ready
  IFG1 &= ~URXIFG0;                                                            // clear flag
  U0TXBUF = LMP90100_DATA_FIRST_MODE_INSTRUCTION_DISABLE;                      // Disable Data First Mode
  while (!(IFG1 & URXIFG0));                                                   // wait for tx to finish 
  
  while (!(IFG1 & UTXIFG0));                                                   // Wait for TXBUF ready 
  IFG1 &= ~URXIFG0;                                                            // clear flag  
  U0TXBUF = LMP90100_DATA_FIRST_MODE_INSTRUCTION_READ_MODE_STATUS;             // Write device read mode status instruction
  while (!(IFG1 & URXIFG0));                                                   // wait for tx to finish 
  
  while (U0RXBUF & LMP90100_DATA_FIRST_MODE_STATUS_FLAG)                       // wait for device to exit data first mode
  {
    IFG1 &= ~URXIFG0;                                                          // clear flag
    U0TXBUF = LMP90100_DATA_FIRST_MODE_INSTRUCTION_READ_MODE_STATUS;           // Write device read mode status instruction
    while (!(IFG1 & URXIFG0));                                                 // wait for tx to finish
  }
  
  TI_LMP90100_CSn_PxOUT |= TI_LMP90100_CSn_PIN;                                // /CS disable  
}
//------------------------------------------------------------------------------
#endif

