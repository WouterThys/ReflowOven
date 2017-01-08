#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>

#include "PORT_Driver.h"
#include "SPI_Driver.h"
#include "ADC_Driver.h"

/*******************************************************************************
 *          DEFINES
 ******************************************************************************/


/*******************************************************************************
 *          MACRO FUNCTIONS
 ******************************************************************************/
#define ConstructUAB(addr) ((addr >> 4) & UAB_MASK)
#define ConstructLRA(addr) (addr & LRA_MASK)

/*******************************************************************************
 *          VARIABLES
 ******************************************************************************/

/*******************************************************************************
 *          BASIC FUNCTIONS
 ******************************************************************************/
uint8_t inst2ToByte(INST2_t inst2);
INST2_t contructInstruction2Byte(uint8_t rwb, uint8_t sz, uint8_t lra);
transaction1_t constructTransaction1(uint8_t rw, uint8_t uab);
transaction2_t constructTransaction2(uint8_t db, uint8_t rwb, uint8_t sz, uint8_t lra);

uint8_t writeTransaction(transaction_t t);

uint8_t inst2ToByte(INST2_t inst2) {
    uint8_t a = ((inst2.R_WB << 7) & RWB_MASK);
    uint8_t b = ((inst2.SZ << 5) & SZ_MASK);
    uint8_t c = ((inst2.LRA) & LRA_MASK);
    uint8_t d = a + b + c;
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
    D_SPI_Write(t.transaction1.INST1);
    D_SPI_Write(t.transaction1.UAB);
    
    D_SPI_Write(inst2ToByte(t.transaction2.INST2));
    input = D_SPI_Write(t.transaction2.DataByte);
    LMP_CSB = 1;
    
    return input;
}

/*******************************************************************************
 *          DRIVER FUNCTIONS
 ******************************************************************************/
void D_ADC_Init() {
    // Ports
    LMP_CSB_Dir = 0;
    LMP_CSB = 1;
    
    // Initialize SPI
    D_SPI_Init(SPI_MASTER, 5);
    D_SPI_Enable(true);
    
    // LMP90080 interrupt

}

void D_ADC_Reset() {
    
}

uint8_t D_ADC_ReadRegister(uint8_t addr) {
    uint8_t data = 0x00;
    transaction_t transaction;
    transaction.transaction1 = constructTransaction1(WRITE_ADDRESS, ConstructUAB(addr));
    transaction.transaction2 = constructTransaction2(data, READ_DATA, SZ_1_BYTE, ConstructLRA(addr));
    return writeTransaction(transaction);
}

void D_ADC_WriteRegister(uint8_t addr, uint8_t data) {
    transaction_t transaction;
    transaction.transaction1 = constructTransaction1(WRITE_ADDRESS, ConstructUAB(addr));
    transaction.transaction2 = constructTransaction2(data, WRITE_DATA, SZ_1_BYTE, ConstructLRA(addr));
    writeTransaction(transaction);
}
