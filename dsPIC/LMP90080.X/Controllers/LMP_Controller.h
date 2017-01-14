/* 
 * File:   LMP_Controller.h
 * Author: wouter
 *
 * Created on January 2, 2017, 7:55 PM
 */

#ifndef LMP_CONTROLLER_H
#define	LMP_CONTROLLER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    
#define CHANNEL_0   0x00
#define CHANNEL_1   0x01
#define CHANNEL_2   0x02
#define CHANNEL_3   0x03
#define CHANNEL_4   0x04
#define CHANNEL_5   0x05
#define CHANNEL_6   0x06
    
// CHx_CONFIG    
#define ODR_0       0x00    /* 0x0: 13.42/8  = 1.6775   SPS */
#define ODR_1       0x10    /* 0x1: 13.42/4  = 3.355    SPS */
#define ODR_2       0x20    /* 0x2: 13.42/2  = 6.71     SPS */
#define ODR_3       0x30    /* 0x3: 214.65   = 13.42    SPS */
#define ODR_4       0x40    /* 0x4: 214.65/8 = 26.83125 SPS */
#define ODR_5       0x50    /* 0x5: 214.65/4 = 53.6625  SPS */
#define ODR_6       0x60    /* 0x6: 214.65/2 = 107.325  SPS */
#define ODR_7       0x70    /* 0x7: 214.65   = 214.65   SPS */

#define GAIN_1      0x00
#define GAIN_2      0x02
#define GAIN_4      0x04
#define GAIN_8      0x06
#define GAIN_16     0x08
#define GAIN_32     0x0A
#define GAIN_64     0x0C
#define GAIN_128    0x0E

#define BUFFER_EN   0x01 /* Include the buffer from the signal path */
#define BUFFER_DIS  0x00 /* (Default) Exclude the buffer from the signal path */   
    
// CHx_INPUTCN
#define BURNOUT_EN  0x80 /* Enable Sendor Diagnostics current injection */    
#define BURNOUT_DIS 0x00 /* (Default) Disable Sensor Diagnostics current injection */
    
#define VREF_SEL_1  0x00 /* (Default) Select VREFP1 and VREFN1 */
#define VREF_SEL_2  0x40 /* Select VREFP2 and VREFN2 */
    
#define VINP_0      0x00 /* VIN0 Positive input */    
#define VINP_1      0x08 /* VIN1 Positive input */
#define VINP_2      0x10 /* VIN2 Positive input */
#define VINP_3      0x18 /* VIN3 Positive input */
#define VINP_4      0x20 /* VIN4 Positive input */
#define VINP_5      0x28 /* VIN5 Positive input */
#define VINP_6      0x30 /* VIN6 Positive input */
#define VINP_7      0x38 /* VIN7 Positive input */    
    
#define VINN_0      0x00 /* VIN0 Negative input */    
#define VINN_1      0x01 /* VIN1 Negative input */
#define VINN_2      0x02 /* VIN2 Negative input */
#define VINN_3      0x03 /* VIN3 Negative input */
#define VINN_4      0x04 /* VIN4 Negative input */
#define VINN_5      0x05 /* VIN5 Negative input */
#define VINN_6      0x06 /* VIN6 Negative input */
#define VINN_7      0x07 /* VIN7 Negative input */    
    
// Background calibration control
#define BG_CAL_MODE_0 0x00 /* Background Calibration OFF */
#define BG_CAL_MODE_1 0x01 /* Offset Correction / Gain Estimation */    
#define BG_CAL_MODE_2 0x02 /* Offset Correction / Gain Correction */
#define BG_CAL_MODE_3 0x03 /* Offset Estimation / Gain Estimation */    
    
    
    /**
     * 
     */
    void C_LMP_Init(void );
    
    /**
     * 
     * @param which
     * @param odr
     * @param gain
     * @param buf_en
     * @param burn_en
     * @param vref_sel
     * @param vinp
     * @param vinn
     */
    void C_LMP_ConfigureChannel(uint8_t which, 
                            uint8_t odr, 
                            uint8_t gain, 
                            uint8_t buf_en,
                            uint8_t burn_en, 
                            uint8_t vref_sel, 
                            uint8_t vinp, 
                            uint8_t vinn, 
                            uint8_t bgcal);
    
    /**
     * 
     * @return 
     */
    uint16_t C_LMP_ReadAdc();
    
    /**
     * 
     */
    void C_LMP_FlashLED(void);
    
    
    /**
     * WRITE AND READ FROM LMP TEST
     * 
     * Writes a value to one of the registers of the LMP, and reads it back. If
     * these values are the same, "true" will be returned. 
     * The "value" is written to the "addr" using the functions 
     * D_LMP_WriteRegister and D_LMP_ReadRegister from the LMP_Driver.h
     * 
     * @param addr
     * @param value
     * @return true if success
     */
    bool C_LMP_TestWrite(uint8_t addr, uint8_t value);


#ifdef	__cplusplus
}
#endif

#endif	/* LMP_CONTROLLER_H */

