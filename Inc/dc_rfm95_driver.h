/*
 * dc_rfm95_driver.h
 *
 *  Created on: Dec 6, 2020
 *      Author: DC
 */

#ifndef DC_RFM95_DRIVER_H_
#define DC_RFM95_DRIVER_H_

/**********************************************************************
*     Include Files
**********************************************************************/
#include <stdio.h>



/**********************************************************************
* Global Macro Definitions
**********************************************************************/
// RFM95 Module Register Names (LoRa Mode, from table 85)
#define DRD_RFM95_REG_00_FIFO                                0x00U
#define DRD_RFM95_REG_01_OP_MODE                             0x01U
#define DRD_RFM95_REG_02_RESERVED                            0x02U
#define DRD_RFM95_REG_03_RESERVED                            0x03U
#define DRD_RFM95_REG_04_RESERVED                            0x04U
#define DRD_RFM95_REG_05_RESERVED                            0x05U
#define DRD_RFM95_REG_06_FRF_MSB                             0x06U
#define DRD_RFM95_REG_07_FRF_MID                             0x07U
#define DRD_RFM95_REG_08_FRF_LSB                             0x08U
#define DRD_RFM95_REG_09_PA_CONFIG                           0x09U
#define DRD_RFM95_REG_0A_PA_RAMP                             0x0aU
#define DRD_RFM95_REG_0B_OCP                                 0x0bU
#define DRD_RFM95_REG_0C_LNA                                 0x0cU
#define DRD_RFM95_REG_0D_FIFO_ADDR_PTR                       0x0dU
#define DRD_RFM95_REG_0E_FIFO_TX_BASE_ADDR                   0x0eU
#define DRD_RFM95_REG_0F_FIFO_RX_BASE_ADDR                   0x0fU
#define DRD_RFM95_REG_10_FIFO_RX_CURRENT_ADDR                0x10U
#define DRD_RFM95_REG_11_IRQ_FLAGS_MASK                      0x11U
#define DRD_RFM95_REG_12_IRQ_FLAGS                           0x12U
#define DRD_RFM95_REG_13_RX_NB_BYTES                         0x13U
#define DRD_RFM95_REG_14_RX_HEADER_CNT_VALUE_MSB             0x14U
#define DRD_RFM95_REG_15_RX_HEADER_CNT_VALUE_LSB             0x15U
#define DRD_RFM95_REG_16_RX_PACKET_CNT_VALUE_MSB             0x16U
#define DRD_RFM95_REG_17_RX_PACKET_CNT_VALUE_LSB             0x17U
#define DRD_RFM95_REG_18_MODEM_STAT                          0x18U
#define DRD_RFM95_REG_19_PKT_SNR_VALUE                       0x19U
#define DRD_RFM95_REG_1A_PKT_RSSI_VALUE                      0x1aU
#define DRD_RFM95_REG_1B_RSSI_VALUE                          0x1bU
#define DRD_RFM95_REG_1C_HOP_CHANNEL                         0x1cU
#define DRD_RFM95_REG_1D_MODEM_CONFIG1                       0x1dU
#define DRD_RFM95_REG_1E_MODEM_CONFIG2                       0x1eU
#define DRD_RFM95_REG_1F_SYMB_TIMEOUT_LSB                    0x1fU
#define DRD_RFM95_REG_20_PREAMBLE_MSB                        0x20U
#define DRD_RFM95_REG_21_PREAMBLE_LSB                        0x21U
#define DRD_RFM95_REG_22_PAYLOAD_LENGTH                      0x22U
#define DRD_RFM95_REG_23_MAX_PAYLOAD_LENGTH                  0x23U
#define DRD_RFM95_REG_24_HOP_PERIOD                          0x24U
#define DRD_RFM95_REG_25_FIFO_RX_BYTE_ADDR                   0x25U
#define DRD_RFM95_REG_26_MODEM_CONFIG3                       0x26U

#define DRD_RFM95_REG_27_PPM_CORRECTION                      0x27U
#define DRD_RFM95_REG_28_FEI_MSB                             0x28U
#define DRD_RFM95_REG_29_FEI_MID                             0x29U
#define DRD_RFM95_REG_2A_FEI_LSB                             0x2aU
#define DRD_RFM95_REG_2C_RSSI_WIDEBAND                       0x2cU
#define DRD_RFM95_REG_31_DETECT_OPTIMIZ                      0x31U
#define DRD_RFM95_REG_33_INVERT_IQ                           0x33U
#define DRD_RFM95_REG_37_DETECTION_THRESHOLD                 0x37U
#define DRD_RFM95_REG_39_SYNC_WORD                           0x39U

#define DRD_RFM95_REG_40_DIO_MAPPING1                        0x40U
#define DRD_RFM95_REG_41_DIO_MAPPING2                        0x41U
#define DRD_RFM95_REG_42_VERSION                             0x42U

#define DRD_RFM95_REG_4B_TCXO                                0x4bU
#define DRD_RFM95_REG_4D_PA_DAC                              0x4dU
#define DRD_RFM95_REG_5B_FORMER_TEMP                         0x5bU
#define DRD_RFM95_REG_61_AGC_REF                             0x61U
#define DRD_RFM95_REG_62_AGC_THRESH1                         0x62U
#define DRD_RFM95_REG_63_AGC_THRESH2                         0x63U
#define DRD_RFM95_REG_64_AGC_THRESH3                         0x64U


/**********************************************************************
* Global Type Definitions
**********************************************************************/
#ifdef UNIT_TEST
#define unit_static
#else
#define unit_static static
#endif

#ifdef UNIT_TEST
typedef struct
{
	uint8_t virtualRegister; // generic container for single byte
}TestHandle;
#endif


/***************************************************************************************************
* Global Function Declarations
***************************************************************************************************/
uint8_t DRD_ReadMode();
void DRD_SetModeIdle();
void DRD_SetModeSleep();




#endif /* DC_RFM95_DRIVER_H_ */
