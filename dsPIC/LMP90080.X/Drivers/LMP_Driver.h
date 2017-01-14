/* 
 * File:   LMP_Driver.h
 * Author: wouter
 *
 * Created on January 2, 2017, 7:30 PM
 */

#ifndef LMP_DRIVER_H
#define	LMP_DRIVER_H

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
#define STATUS_MASK     0x80
    
#define REG_AND_CNV_RST 0xC3
    
#define STRM_TYPE_NORMAL     0x00
#define STRM_TYPE_CONTROLLED 0x80
    
    // CRC-8: x8 + x5 + x4 + 1
#define CRC8_POLY          0x31
#define CRC8_INIT_REM      0x00
#define CRC8_FINAL_XOR     0xFF
    
#define DATA_FIRST_ENABLE   0xFA
#define DATA_FIRST_DISABLE  0xFB
#define DATA_FIRST_STATUS   0x9F
    
#define CH_SCAN_NRDY        0x02    /* Channel Scan Not Ready Bit */
    

    
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
    
    enum crc_check {
        CRC_PASS, 
        CRC_FAIL, 
        CRC_NOT_USED
    } ;
    
    
    
    // Functions

/**
 * 
 */
void D_LMP_Init();

/**
 * 
 */
void D_LMP_Reset();

/**
 * 
 * @param addr
 * @return 
 */
uint8_t D_LMP_ReadRegister(uint8_t addr);

/**
 * Writes "data" to a single configuration register at address "addr". 
 * @param addr: Address of the register (use LMP90080.h file)
 * @param data: Data to write
 */
void D_LMP_WriteRegister(uint8_t addr, uint8_t data);

/**
 * Writes the values in the buffer to multiple configuration registers, the
 * first register at address "addr". The transactions writes "count" times, as 
 * such, count is the length of the buffer.
 * @param addr: First address to write to.
 * @param buffer: Values to write.
 * @param count: Number of bytes in the write buffer.
 */
void D_LMP_NormalStreamWriteRegister(uint8_t addr, uint8_t *buffer, uint8_t count);

/**
 * Reads multiple configuration registers, the first register being at address
 * "addr". Values read are deposited sequentially starting at address "buffer", 
 * until "count" registers have been read.
 * @param addr: Starting address of the LMP
 * @param buffer: Values will be loaded in this buffer.
 * @param count: Number of bytes to load in the buffer.
 */
void D_LMP_NormalStreamReadRegister(uint8_t addr, uint8_t *buffer, uint8_t count);

/**
 * Checks if CRC read from the device matches computed result. CRC computed
 * for "count" bytes at address "buffer" and compared against CRC stored in
 * "buffer[count] and returns "CRC_PASS" or CRC_FAIL" accordingly.
 * @param buffer: data.
 * @param count: length of the data.
 * @return: "CRC_PASS" or CRC_FAIL"
 */
uint8_t D_LMP_CRCCheck(uint8_t *buffer, uint8_t count);

/**
 * Special read function for reading ADC data registers. Reads multiple
 * registers, the first register being at address "addr". Values read are 
 * deposited sequentially starting at address "buffer", until "count" registers
 * have been read.
 * @param addr
 * @param buffer
 * @param count
 */
void D_LMP_NormalStreamReadAdc(uint8_t addr, uint8_t *buffer, uint8_t count);

/**
 * Special read function for reading ADC data registers in Controlled Stream Mode.
 * Reads multiple registers, the first register being at address "addr". Values 
 * read are deposited sequentially starting at address "buffer", until "count" 
 * registers have been read.
 * @param addr
 * @param buffer
 * @param count
 */
void D_LMP_ControlledStreamReadAdc(uint8_t addr, uint8_t *buffer, uint8_t count);

/**
 * Special read function for reading ADC data registers in Data Only mode. 
 * Values read are deposited sequentially starting at address "buffer", until 
 * "count" registers have been read. In order to use the Data Only read 
 * transaction capability of the LMP, the data first mode must be enabled by
 * calling D_LMP_EnableDataFirstMode() function.
 * @param buffer
 * @param count
 */
void D_LMP_DataOnlyReadAdc(uint8_t *buffer, uint8_t count);

/**
 * Compute 8 bit CRC of data "*pmsg" of size "msg_size" bytes, using polynomal
 * "poly" and initial value "crc".
 * @param crc
 * @param poly
 * @param pmsg
 * @param msg_size
 * @return
 */
uint8_t D_LMP_CRC8MakeBitwise2(uint8_t crc, uint8_t poly, uint8_t *pmsg, uint8_t msg_size);

/**
 * Enables data first mode of LMP. DATA_ONLY_1 and DATA_ONLY_2 registers are
 * initialized to "addr" and "count-1" and the LMP is placed in the data first
 * mode. In order to use the data only read transaction capability of the LMP, 
 * the data first mode must be enabled.
 * @param addr
 * @param count
 * @return 1 if ok, 0 if not.
 */
uint8_t D_LMP_EnableDataFirstMode(uint8_t addr, uint8_t count);

/**
 * Disables the data first mode of the LMP. Reads dta bytes of the data only
 * transaction then disables the data first mode of LMP. The data only transaction
 * bytes are deposited sequentially starting at address "buffer", until "count"
 * registers have been read.
 * @param buffer
 * @param count
 * @return 1 if ok, 0 if not.
 */
uint8_t D_LMP_DisableDataFirstMode(uint8_t *buffer, uint8_t count);

#ifdef	__cplusplus
}
#endif

#endif	/* LMP_DRIVER_H */

