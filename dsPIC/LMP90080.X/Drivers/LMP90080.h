/* 
 * File:   LMP90080.h
 * Author: wouter
 *
 * Created on January 2, 2017, 7:30 PM
 */

#ifndef LMP90080_H
#define	LMP90080_H

#ifdef	__cplusplus
extern "C" {
#endif

// Register addresses
//      NAME            ADDR        DESC                         TYPE    DEFAULT 
    
#define RESETCN         0x00 // Reset Control.                    WO      -
    
#define SPI_HANDSHAKECN 0x01 // SPI Handshake Control.            R/W     0x00
#define SPI_RESET       0x02 // SPI Reset Control.                R/W     0x00
#define SPI_STREAMCN    0x03 // SPI Stream Control.               R/W     0x00
    
#define PWRCN           0x08 // Power Mode Control and Status.    R/W-WO  0x00
#define DATA_ONLY_1     0x09 // Data Only Read Conrol 1.          R/W     0x1A
#define DATA_ONLY_2     0x0A // Data Only Read Conrol 2.          R/W     0x02
#define ADC_RESTART     0x0B // ADC Restart Conversion.           WO      -
    
#define GPIO_DIRCN      0x0E // GPIO Direction Control.           R/W     0x00
#define GPIO_DAT        0x0F // GPIO Data.                        RO-WO   -
    
#define BGCALCN         0x10 // Background Calibration Control.   R/W     0x00
    
#define SPI_DRDYBCN     0x11 // SPI Data Ready Bar Control.       R/W     0x03
    
#define ADC_AUXCN       0x12 // ADC Auxilary Control.             R/W     0x00
#define SPI_CRC_CN      0x13 // CRC Control.                      R/W     0x02
#define SENDIAG_THLD    0x14 // Sensor Diagnose Threshold.        R/W     0x00
    
#define SCALCN          0x17 // System Calibration Control.       R/W     0x00
#define ADC_DONE        0x18 // ADC Data Available.               RO      -
#define SENDIAG_FLAGS   0x19 // Send Diagnostics Flags            RO      -
#define ADC_DOUT        0x1A // Conversion Data.                  RO      -
#define ADC_DOUT_1      0x1A // Conversion Data 1.                RO      -
#define ADC_DOUT_0      0x1B // Conversion Data 0.                RO      -
#define SPI_CRC_DAT     0x1D // CRC Data.                         RO-WO   -
    
#define CH_STS          0x1E // Channel Status.                   RO      0x00
#define CH_SCAN         0x1F // Channel Scan Mode.                R/W     0x30
    
#define CH0_INPUTCN     0x20 // CH0 Input Control.                R/W     0x01
#define CH0_CONFIG      0x21 // CH0 Configuration.                R/W     0x70
#define CH1_INPUTCN     0x22 // CH1 Input Control.                R/W     0x13
#define CH1_CONFIG      0x23 // CH1 Configuration.                R/W     0x70    
#define CH2_INPUTCN     0x24 // CH2 Input Control.                R/W     0x25
#define CH2_CONFIG      0x25 // CH2 Configuration.                R/W     0x70    
#define CH3_INPUTCN     0x26 // CH3 Input Control.                R/W     0x37
#define CH3_CONFIG      0x27 // CH3 Configuration.                R/W     0x70    
#define CH4_INPUTCN     0x28 // CH4 Input Control.                R/W     0x01
#define CH4_CONFIG      0x29 // CH4 Configuration.                R/W     0x70
#define CH5_INPUTCN     0x2A // CH5 Input Control.                R/W     0x13
#define CH5_CONFIG      0x2B // CH5 Configuration.                R/W     0x70 
#define CH6_INPUTCN     0x2C // CH6 Input Control.                R/W     0x25
#define CH6_CONFIG      0x2D // CH6 Configuration.                R/W     0x70
    
#define CH0_SCAL_OFFSET 0x30 // CH0 System Calibration Offset.    R/W     0x0000
#define CH0_SCAL_OFFSET_0  0x30 // CH0_SCAL_OFSET                  
#define CH0_SCAL_OFSET_1   0x31 // CH0_SCAL_OFSET                  
#define CH0_SCAL_GAIN   0x33 // CH0 System Calibration Gain.      R/W     0x8000
#define CH0_SCAL_GAIN_0    0x33 // CH0_SCAL_GAIN                                
#define CH0_SCAL_GAIN_1    0x34 // CH0_SCAL_GAIN
#define CH0_SCAL_SCALING 0x36 // CH0 System Calibration Scaling.  R/W     0x01
#define CH0_SCAL_BITS   0x37 // CH0 System Calibration Scaling.   R/W     0x00
    
#define CH1_SCAL_OFFSET 0x38 // CH1 System Calibration Offset.    R/W     0x0000
#define CH1_SCAL_OFFSET_0  0x38 // CH1_SCAL_OFSET                  
#define CH1_SCAL_OFSET_1   0x39 // CH1_SCAL_OFSET                  
#define CH1_SCAL_GAIN   0x3B // CH1 System Calibration Gain.      R/W     0x8000
#define CH1_SCAL_GAIN_0    0x3B // CH1_SCAL_GAIN                                
#define CH1_SCAL_GAIN_1    0x3C // CH1_SCAL_GAIN
#define CH1_SCAL_SCALING 0x33E // CH1 System Calibration Scaling. R/W     0x01
#define CH1_SCAL_BITS   0x3F // CH1 System Calibration Scaling.   R/W     0x00
    
#define CH2_SCAL_OFFSET 0x40 // CH2 System Calibration Offset.    R/W     0x0000
#define CH2_SCAL_OFFSET_0  0x40 // CH2_SCAL_OFSET                  
#define CH2_SCAL_OFSET_1   0x41 // CH2_SCAL_OFSET                  
#define CH2_SCAL_GAIN   0x43 // CH2 System Calibration Gain.      R/W     0x8000
#define CH2_SCAL_GAIN_0    0x43 // CH2_SCAL_GAIN                                
#define CH2_SCAL_GAIN_1    0x44 // CH2_SCAL_GAIN
#define CH2_SCAL_SCALING 0x46 // CH2 System Calibration Scaling.  R/W     0x01
#define CH2_SCAL_BITS   0x47 // CH2 System Calibration Scaling.   R/W     0x00
    
#define CH3_SCAL_OFFSET 0x48 // CH3 System Calibration Offset.    R/W     0x0000
#define CH3_SCAL_OFFSET_0  0x48 // CH3_SCAL_OFSET                  
#define CH3_SCAL_OFSET_1   0x49 // CH3_SCAL_OFSET                  
#define CH3_SCAL_GAIN   0x4B // CH3 System Calibration Gain.      R/W     0x8000
#define CH3_SCAL_GAIN_0    0x4B // CH3_SCAL_GAIN                                
#define CH3_SCAL_GAIN_1    0x4C // CH3_SCAL_GAIN
#define CH3_SCAL_SCALING 0x4E // CH3 System Calibration Scaling.  R/W     0x01
#define CH3_SCAL_BITS   0x4F // CH3 System Calibration Scaling.   R/W     0x00
    
#define ADC_DOUTH   0x1A // ADC Conversion Data [15:8]
#define ADC_DOUTL   0x1B // ADC Conversion Data [7:0]

    
#ifdef	__cplusplus
}
#endif

#endif	/* LMP90080_H */

