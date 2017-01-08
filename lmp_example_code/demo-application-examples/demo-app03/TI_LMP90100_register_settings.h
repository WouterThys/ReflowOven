//----------------------------------------------------------------------------
//  Description:  This file contains the initialization values for the 
//  LMP90100 registers.
//
//  MSP430/LMP90100 Interface Code Library v1.0
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
#ifndef HEADER_FILE_TI_LMP90100_REGISTER_SETTINGS_H

#define HEADER_FILE_TI_LMP90100_REGISTER_SETTINGS_H

/************************************************************
* TI LMP90100 REGISTER SET INITIALIZATION VALUES
************************************************************/

#define TI_LMP90100_RESETCN_REG_VALUE                  (0xC3)             /* Register and Conversion Reset */             
#define TI_LMP90100_SPI_HANDSHAKECN_REG_VALUE          (0x01)             /* SPI SDO High Z Delayed */ 

#define TI_LMP90100_SPI_STREAMCN_REG_VALUE             (0x00)             /* SPI Normal Streaming mode */
#define TI_LMP90100_PWRCN_REG_VALUE                    (0x00)             /* Active Mode */

#define TI_LMP90100_ADC_RESTART_REG_VALUE              (0x00)             /* Disable restart Conversion */

#define TI_LMP90100_GPIO_DIRCN_REG_VALUE               (0x40)             /* D6 output, D0-D5 inputs */
#define TI_LMP90100_GPIO_DAT_REG_VALUE                 (0x40)             /* Set D6 high, others ignore */

#define TI_LMP90100_BGCALCN_REG_VALUE                  (0x00)             /* Background Calibration OFF */

#define TI_LMP90100_SPI_DRDYBCN_REG_VALUE              (0x83)             /* Enable DRDYB on D6, bits 0 & 1 must be 1, others default */

#define TI_LMP90100_ADC_AUXCN_REG_VALUE                (0x20)             /* bypass external clock detection, internal clock, select 0uA RTD current */
#define TI_LMP90100_SPI_CRC_CN_REG_VALUE               (0x00)             /* disable CRC, Bit 3 must be 0, DRDYB is deasserted after ADC_DOUTL is read */
#define TI_LMP90100_SENDIAG_THLDH_REG_VALUE            (0x00)             /* Sensor Diagnostic Threshold High */
#define TI_LMP90100_SENDIAG_THLDL_REG_VALUE            (0x00)             /* Sensor Diagnostic Threshold Low */

#define TI_LMP90100_SCALCN_REG_VALUE                   (0x00)             /* System Calibration Control Normal Mode */
#define TI_LMP90100_ADC_DONE_REG_VALUE                 (0xFF)             /* ADC Data unAvailable */
#define TI_LMP90100_SENDIAG_FLAGS_REG_VALUE            (0x00)             /* Sensor Diagnostic Flags - status output */
#define TI_LMP90100_ADC_DOUT2_REG_VALUE                (0x00)             /* ADC Conversion Data 2 */
#define TI_LMP90100_ADC_DOUT1_REG_VALUE                (0x00)             /* ADC Conversion Data 1 */
#define TI_LMP90100_ADC_DOUT0_REG_VALUE                (0x00)             /* ADC Conversion Data 0 */
#define TI_LMP90100_SPI_CRC_DAT_REG_VALUE              (0xFF)             /* Reset CRC Data */

#define TI_LMP90100_CH_STS_REG_VALUE                   (0x00)             /* Channel Status */

#define TI_LMP90100_CH_SCAN_REG_VALUE                  (0x00)             /* Single Channel Continuous Scan: Channel 0*/
#define TI_LMP90100_CH0_INPUTCN_REG_VALUE              (0x01)             /* diable sensor diagnostics, default ref, vinp 0 vinn 1 */
#define TI_LMP90100_CH0_CONFIG_REG_VALUE               (0x40)             /* CH0 Configuratio: 26.83SPS, FGA off, buffer in signal path*/

#define TI_LMP90100_CH1_INPUTCN_REG_VALUE              (0x13)             /* disable sensor diagnostics, default ref, vinp 2 vinn 3 */
#define TI_LMP90100_CH1_CONFIG_REG_VALUE               (0x40)             /* CH1 config: 26.835SPS, FGA off, buffer in signal path */
#define TI_LMP90100_CH2_INPUTCN_REG_VALUE              (0x25)             /* disable sensor diagnostics, default ref, vinp 4 vinn 5 */
#define TI_LMP90100_CH2_CONFIG_REG_VALUE               (0x70)             /* 214.65SPS, FGA off, buffer in signal path */
#define TI_LMP90100_CH3_INPUTCN_REG_VALUE              (0x37)             /* disable sensor diagnostics, default ref, vinp 6 vinn 7 */
#define TI_LMP90100_CH3_CONFIG_REG_VALUE               (0x70)             /* 214.65SPS, FGA off, buffer in signal path */
#define TI_LMP90100_CH4_INPUTCN_REG_VALUE              (0x01)             /* disable sensor diagnostics, default ref, vinp 2 vinn 3 */
#define TI_LMP90100_CH4_CONFIG_REG_VALUE               (0x70)             /* 214.65SPS, FGA off, buffer in signal path */
#define TI_LMP90100_CH5_INPUTCN_REG_VALUE              (0x13)             /* disable sensor diagnostics, default ref, vinp 4 vinn 5 */
#define TI_LMP90100_CH5_CONFIG_REG_VALUE               (0x70)             /* 214.65SPS, FGA off, buffer in signal path */
#define TI_LMP90100_CH6_INPUTCN_REG_VALUE              (0x25)             /* disable sensor diagnostics, default ref, vinp 6 vinn 7 */
#define TI_LMP90100_CH6_CONFIG_REG_VALUE               (0x70)             /* 214.65SPS, FGA off, buffer in signal path */

#define TI_LMP90100_CH0_SCAL_OFFSET2_REG_VALUE         (0x00)             /* CH0 System Calibration Offset Coefficient [23:16] */
#define TI_LMP90100_CH0_SCAL_OFFSET1_REG_VALUE         (0x00)             /* CH0 System Calibration Offset Coefficient [15:8] */
#define TI_LMP90100_CH0_SCAL_OFFSET0_REG_VALUE         (0x00)             /* CH0 System Calibration Offset Coefficient [7:0] */
#define TI_LMP90100_CH0_SCAL_GAIN2_REG_VALUE           (0x80)             /* CH0 System Calibration Gain Coefficient [23:16]  */
#define TI_LMP90100_CH0_SCAL_GAIN1_REG_VALUE           (0x00)             /* CH0 System Calibration Gain Coefficient [15:8]  */
#define TI_LMP90100_CH0_SCAL_GAIN0_REG_VALUE           (0x00)             /* CH0 System Calibration Gain Coefficient [7:0]  */ 
#define TI_LMP90100_CH0_SCAL_SCALING_REG_VALUE         (0x00)             /* CH0 System Calibration Scaling Coefficient */
#define TI_LMP90100_CH0_SCAL_BITS_SELECTOR_REG_VALUE   (0x00)             /* CH0 System Calibration Bits Selector */

#define TI_LMP90100_CH1_SCAL_OFFSET2_REG_VALUE         (0x00)             /* CH1 System Calibration Offset Coefficient [23:16] */
#define TI_LMP90100_CH1_SCAL_OFFSET1_REG_VALUE         (0x00)             /* CH1 System Calibration Offset Coefficient [15:8] */
#define TI_LMP90100_CH1_SCAL_OFFSET0_REG_VALUE         (0x00)             /* CH1 System Calibration Offset Coefficient [7:0] */
#define TI_LMP90100_CH1_SCAL_GAIN2_REG_VALUE           (0x80)             /* CH1 System Calibration Gain Coefficient [23:16]  */
#define TI_LMP90100_CH1_SCAL_GAIN1_REG_VALUE           (0x00)             /* CH1 System Calibration Gain Coefficient [15:8]  */
#define TI_LMP90100_CH1_SCAL_GAIN0_REG_VALUE           (0x00)             /* CH1 System Calibration Gain Coefficient [7:0]  */ 
#define TI_LMP90100_CH1_SCAL_SCALING_REG_VALUE         (0x00)             /* CH1 System Calibration Scaling Coefficient */
#define TI_LMP90100_CH1_SCAL_BITS_SELECTOR_REG_VALUE   (0x00)             /* CH1 System Calibration Bits Selector */

#define TI_LMP90100_CH2_SCAL_OFFSET2_REG_VALUE         (0x00)             /* CH2 System Calibration Offset Coefficient [23:16] */
#define TI_LMP90100_CH2_SCAL_OFFSET1_REG_VALUE         (0x00)             /* CH2 System Calibration Offset Coefficient [15:8] */
#define TI_LMP90100_CH2_SCAL_OFFSET0_REG_VALUE         (0x00)             /* CH2 System Calibration Offset Coefficient [7:0] */
#define TI_LMP90100_CH2_SCAL_GAIN2_REG_VALUE           (0x80)             /* CH2 System Calibration Gain Coefficient [23:16]  */
#define TI_LMP90100_CH2_SCAL_GAIN1_REG_VALUE           (0x00)             /* CH2 System Calibration Gain Coefficient [15:8]  */
#define TI_LMP90100_CH2_SCAL_GAIN0_REG_VALUE           (0x00)             /* CH2 System Calibration Gain Coefficient [7:0]  */
#define TI_LMP90100_CH2_SCAL_SCALING_REG_VALUE         (0x00)             /* CH2 System Calibration Scaling Coefficient */
#define TI_LMP90100_CH2_SCAL_BITS_SELECTOR_REG_VALUE   (0x00)             /* CH2 System Calibration Bits Selector */

#define TI_LMP90100_CH3_SCAL_OFFSET2_REG_VALUE         (0x00)             /* CH3 System Calibration Offset Coefficient [23:16] */
#define TI_LMP90100_CH3_SCAL_OFFSET1_REG_VALUE         (0x00)             /* CH3 System Calibration Offset Coefficient [15:8] */
#define TI_LMP90100_CH3_SCAL_OFFSET0_REG_VALUE         (0x00)             /* CH3 System Calibration Offset Coefficient [7:0] */
#define TI_LMP90100_CH3_SCAL_GAIN2_REG_VALUE           (0x80)             /* CH3 System Calibration Gain Coefficient [23:16]  */
#define TI_LMP90100_CH3_SCAL_GAIN1_REG_VALUE           (0x00)             /* CH3 System Calibration Gain Coefficient [15:8]  */
#define TI_LMP90100_CH3_SCAL_GAIN0_REG_VALUE           (0x00)             /* CH3 System Calibration Gain Coefficient [7:0]  */ 
#define TI_LMP90100_CH3_SCAL_SCALING_REG_VALUE         (0x00)             /* CH3 System Calibration Scaling Coefficient */
#define TI_LMP90100_CH3_SCAL_BITS_SELECTOR_REG_VALUE   (0x00)             /* CH3 System Calibration Bits Selector */


#endif                                                        // HEADER_FILE_TI_LMP90100_REGISTER_SETTINGS_H