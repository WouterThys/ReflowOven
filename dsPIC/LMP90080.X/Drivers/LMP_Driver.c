#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#include "PORT_Driver.h"
#include "SPI_Driver.h"
#include "LMP_Driver.h"
#include "LMP90080.h"
#include "SYSTEM_Driver.h"

/*******************************************************************************
 *          DEFINES
 ******************************************************************************/


/*******************************************************************************
 *          MACRO FUNCTIONS
 ******************************************************************************/
#define ConstructURA(addr) ((addr >> 4) & UAB_MASK)
#define ConstructLRA(addr) (addr & LRA_MASK)

/*******************************************************************************
 *          VARIABLES
 ******************************************************************************/


/*******************************************************************************
 *          BASIC FUNCTIONS
 ******************************************************************************/
static uint8_t inst2ToByte(INST2_t inst2);
static INST2_t contructInstruction2Byte(uint8_t rwb, uint8_t sz, uint8_t lra);
static transaction1_t constructTransaction1(uint8_t rw, uint8_t uab);
static transaction2_t constructTransaction2(uint8_t db, uint8_t rwb, uint8_t sz, uint8_t lra);
static uint8_t writeTransaction(transaction_t t);

uint8_t inst2ToByte(INST2_t inst2) {
    return ((inst2.R_WB << 7) & RWB_MASK) + ((inst2.SZ << 5) & SZ_MASK) + ((inst2.LRA) & LRA_MASK);
}

INST2_t contructInstruction2Byte(uint8_t rwb, uint8_t sz, uint8_t lra) {
    INST2_t inst2;
    inst2.R_WB = rwb;
    inst2.SZ = sz;
    inst2.LRA = lra;
    return inst2;
}

transaction1_t constructTransaction1(uint8_t rw, uint8_t uab) {
    transaction1_t transaction1;
    transaction1.INST1 = rw;
    transaction1.UAB = (uab & UAB_MASK);
    return transaction1;
}

transaction2_t constructTransaction2(uint8_t db, uint8_t rwb, uint8_t sz, uint8_t lra) {
    transaction2_t transaction2;
    transaction2.INST2 = contructInstruction2Byte(rwb, sz, lra);
    transaction2.DataByte = db;
    return transaction2;
}

uint8_t writeTransaction(transaction_t t) {
    uint8_t input = 0;
    
    LMP_CSB = 0;

    D_SPI_WriteByte(t.transaction1.INST1);
    D_SPI_WriteByte(t.transaction1.UAB);

    D_SPI_WriteByte(inst2ToByte(t.transaction2.INST2));
    input = D_SPI_WriteByte(t.transaction2.DataByte);
    
    LMP_CSB = 1;
    
    return input;
}

/*******************************************************************************
 *          DRIVER FUNCTIONS
 ******************************************************************************/
void D_LMP_Init() {
    // Ports
    LMP_CSB_Dir = 0;
    LMP_CSB = 1;
    
    // Initialize SPI
    D_SPI_Init(SPI_MODULE_1, SPI_MASTER);
    //D_SPI_Enable(true);

}

uint8_t D_LMP_ReadRegister(uint8_t addr) {
    uint8_t data = 0x00;
    transaction_t t;
    t.transaction1 = constructTransaction1(WRITE_ADDRESS, ConstructURA(addr));
    t.transaction2 = constructTransaction2(data, READ_DATA, SZ_1_BYTE, ConstructLRA(addr));
    return writeTransaction(t);
}

void D_LMP_WriteRegister(uint8_t addr, uint8_t data) {
    transaction_t t; 
    t.transaction1 = constructTransaction1(WRITE_ADDRESS, ConstructURA(addr));
    t.transaction2 = constructTransaction2(data, WRITE_DATA, SZ_1_BYTE, ConstructLRA(addr));
    writeTransaction(t);
}

void D_LMP_NormalStreamWriteRegister(uint8_t addr, uint8_t *buffer, uint8_t count) {
    transaction_t t;
    t.transaction1 = constructTransaction1(WRITE_ADDRESS, ConstructURA(addr));
    t.transaction2 = constructTransaction2(*buffer, WRITE_DATA, SZ_STREAM, ConstructLRA(addr));
    
    LMP_CSB = 0;
    D_SPI_WriteByte(t.transaction1.INST1);
    D_SPI_WriteByte(t.transaction1.UAB);
    
    D_SPI_WriteByte(inst2ToByte(t.transaction2.INST2));
    D_SPI_WriteByte(t.transaction2.DataByte); // Write first byte
    
    uint8_t i;
    for (i=1; i<count; i++) {
        D_SPI_WriteByte(*(buffer+i));
    }
    LMP_CSB = 1;
}

void D_LMP_NormalStreamReadRegister(uint8_t addr, uint8_t *buffer, uint8_t count) {
    transaction_t t;
    t.transaction1 = constructTransaction1(WRITE_ADDRESS, ConstructURA(addr));
    t.transaction2 = constructTransaction2(*buffer, READ_DATA, SZ_STREAM, ConstructLRA(addr));
    
    LMP_CSB = 0;
    D_SPI_WriteByte(t.transaction1.INST1);
    D_SPI_WriteByte(t.transaction1.UAB);
    
    D_SPI_WriteByte(inst2ToByte(t.transaction2.INST2));
    
    uint8_t i;
    for (i=0; i<count; i++) {
        *(buffer + i) = D_SPI_WriteByte(0x00);
    }
    LMP_CSB = 1;
}

void D_LMP_NormalStreamReadAdc(uint8_t addr, uint8_t* buffer, uint8_t count) {
    transaction_t t;
    t.transaction1 = constructTransaction1(WRITE_ADDRESS, ConstructURA(addr));
    t.transaction2 = constructTransaction2(*buffer, READ_DATA, SZ_STREAM, ConstructLRA(addr));
    
    LMP_CSB = 0;
    D_SPI_WriteByte(t.transaction1.INST1);
    D_SPI_WriteByte(t.transaction1.UAB);
    
    D_SPI_WriteByte(inst2ToByte(t.transaction2.INST2));
    
    uint8_t i;
    for (i=0; i<count; i++) {
        *(buffer + i) = D_SPI_WriteByte(0x00);
    }
    LMP_CSB = 1;
}

void D_LMP_ControlledStreamReadAdc(uint8_t addr, uint8_t* buffer, uint8_t count) {
    uint8_t i;
    static uint8_t repeat_controlled = 0;
    transaction_t t;
    t.transaction1 = constructTransaction1(WRITE_ADDRESS, ConstructURA(addr));
    
    LMP_CSB = 0; // ??
    
    D_SPI_WriteByte(t.transaction1.INST1);
    D_SPI_WriteByte(t.transaction1.UAB);
    
    if (!repeat_controlled) repeat_controlled = 0;
    if (!repeat_controlled) {
        t.transaction2 = constructTransaction2(*buffer, READ_DATA, SZ_STREAM, ConstructLRA(addr));
        D_SPI_WriteByte(inst2ToByte(t.transaction2.INST2));
        repeat_controlled = 1;
    }
    
    for (i=0; i<count; i++) {
        *(buffer + i) = D_SPI_WriteByte(NULL);
    }
    
    LMP_CSB = 1; // ??
}

void D_LMP_DataOnlyReadAdc(uint8_t* buffer, uint8_t count) {
    uint8_t i;
    
    LMP_CSB = 0;
    for (i=0; i<count; i++) {
        *(buffer + i) = D_SPI_WriteByte(NULL);
    }
    LMP_CSB = 1;
}

uint8_t D_LMP_CRC8MakeBitwise2(uint8_t crc, uint8_t poly, uint8_t* pmsg, uint8_t msg_size) {
    uint8_t i,j;
    uint8_t msg;
    
    for (i=0; i<msg_size; i++) {
        msg = (*pmsg++ << 0);
        for(j=0; j<8; j++) {
            if ((msg ^ crc) >> 7) {
                crc = (crc << 1) ^ poly;
            } else {
                crc <<= 1;
                msg <<= 1;
            }
        }
    }
    return (crc ^ CRC8_FINAL_XOR);
}

uint8_t D_LMP_CRCCheck(uint8_t* buffer, uint8_t count) {
    uint8_t crc_data, crc_calc;
    
    crc_data = buffer[count];
    crc_calc = D_LMP_CRC8MakeBitwise2(CRC8_INIT_REM, CRC8_POLY, buffer, count);
    
    if (crc_data == crc_calc) {
        return CRC_PASS;
    } else {
        return CRC_FAIL;
    }
}

uint8_t D_LMP_EnableDataFirstMode(uint8_t addr, uint8_t count) {
    uint8_t status, cnt = 0;
    D_LMP_WriteRegister(DATA_ONLY_1, addr); // Address of register to read
    D_LMP_WriteRegister(DATA_ONLY_2, count-1); // Times to read
    
    LMP_CSB = 0;
    
    D_SPI_WriteByte(DATA_FIRST_ENABLE); // Write enable instruction
    status = D_SPI_WriteByte(DATA_FIRST_STATUS); // Read status
    
    while (!(status & STATUS_MASK) && (cnt < 100)) { // Avoid dead locks
        status = D_SPI_WriteByte(DATA_FIRST_STATUS); // Read status
        cnt++;
        DelayUs(100);
    }
    
    LMP_CSB = 1;
    
    if (cnt >= 100) {
        return 0;
    } else {
        return 1;
    }
}

uint8_t D_LMP_DisableDataFirstMode(uint8_t* buffer, uint8_t count) {
    uint8_t i, cnt, status;
    
    LMP_CSB = 0;
    // First read all data bytes, than disable
    for(i=0; i<count; i++) {
        *(buffer + i) = D_SPI_WriteByte(NULL);
    }
    
    D_SPI_WriteByte(DATA_FIRST_DISABLE); // Write disable instruction
    status = D_SPI_WriteByte(DATA_FIRST_STATUS); // Read status
    
    while ((status & STATUS_MASK) && (cnt < 100)) { // Avoid dead locks
        status = D_SPI_WriteByte(DATA_FIRST_STATUS); // Read status
        cnt++;
        DelayUs(100);
    }
    
    LMP_CSB = 1;
    
    if (cnt >= 100) {
        return 0;
    } else {
        return 1;
    }
}
