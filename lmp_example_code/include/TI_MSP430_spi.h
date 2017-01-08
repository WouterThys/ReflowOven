//------------------------------------------------------------------------------
//  Description:  Header file for TI_MSP430_spi_*.c
//
//  MSP430/LMP90100 Interface Code Library v1.1
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

#ifndef HEADER_FILE_TI_MSP430_SPI_H
#define HEADER_FILE_TI_MSP430_SPI_H

// CRC-8: x8 + x5 + x4 + 1
#define CRC8_POLY          0x31
#define CRC8_INIT_REM      0x0
#define CRC8_FINAL_XOR     0xFF

void TI_LMP90100_SPISetup(void);
void TI_LMP90100_SPIWriteReg(uint8_t, uint8_t, uint8_t *);
uint8_t TI_LMP90100_SPIReadReg(uint8_t, uint8_t *);
void TI_LMP90100_SPINormalStreamWriteReg(uint8_t, uint8_t *, uint8_t, uint8_t *);
void TI_LMP90100_SPINormalStreamReadReg(uint8_t, uint8_t *, uint8_t, uint8_t *);
void TI_LMP90100_SPINormalStreamReadADC(uint8_t, uint8_t *, uint8_t, uint8_t *);
void TI_LMP90100_SPIControlledStreamReadADC(uint8_t, uint8_t *, uint8_t, uint8_t *);
void TI_LMP90100_SPIDataOnlyReadADC(uint8_t *, uint8_t);
uint8_t TI_LMP90100_SPICRCCheck (uint8_t *, uint8_t);
void TI_LMP90100_SPIEnableDataFirstMode(uint8_t, uint8_t, uint8_t *);
void TI_LMP90100_SPIDisableDataFirstMode(uint8_t *, uint8_t);

// Following function used by TI_LMP90100_SPICRCCheck 
uint8_t TI_LMP90100_crc8MakeBitwise2(uint8_t, uint8_t, uint8_t *, uint8_t);


#endif                                                                         // HEADER_FILE_TI_MSP430_SPI_H