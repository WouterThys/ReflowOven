/* 
 * File:   ADC_Driver.h
 * Author: wouter
 *
 * Created on December 30, 2016, 6:26 PM
 */

#ifndef ADC_DRIVER_H
#define	ADC_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    // Defines
    
#define WRITE_ADDRESS   0x10
#define READ_ADDRESS    0x90
    
#define WRITE_DATA      0x00    
#define READ_DATA       0x01
#define SZ_1_BYTE       0x00
#define SZ_2_BYTES      0x01
#define SZ_3_BYTES      0x02
#define SZ_STREAM       0x03
    
#define UAB_MASK        0x07
#define LRA_MASK        0x0F
#define RWB_MASK        0x80
#define SZ_MASK         0x60
    
#define REG_AND_CNV_RST 0xC3

    
    // Typedefs
    
    typedef struct {
        uint8_t INST1; // Instruction byte 1 - RA/WAB
        uint8_t UAB; // Upper Address Byte - User with UAB_MASK
    } transaction1_t;
    
    typedef struct {
        uint8_t R_WB; // Read/Write data - W=0, 1=R
        uint8_t SZ; // Size - 1 byte = 0x0, 2 bytes = 0x1, 3 bytes = 0x2, Streaming = 0x3
        uint8_t LRA; // Lower Register Address
    } INST2_t;
    
    typedef struct {
        INST2_t INST2; // Instruction byte 2
        uint8_t DataByte; // 
    } transaction2_t;
    
    typedef struct {
        transaction1_t transaction1;
        transaction2_t transaction2;
    } transaction_t;
    
    
    // Functions

/**
 * 
 */
void D_ADC_Init();

/**
 * 
 */
void D_ADC_Reset();

/**
 * 
 * @param addr
 * @return 
 */
uint8_t D_ADC_ReadRegister(uint8_t addr);

/**
 * 
 * @param addr
 * @param data
 */
void D_ADC_WriteRegister(uint8_t addr, uint8_t data);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_DRIVER_H */

