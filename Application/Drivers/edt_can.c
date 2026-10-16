//
// Created by nilas on 16/10/2026.
//

#include "edt_can.h"
#include "fdcan.h"
#include "edt_logger.h"

#define LOOP_BACK_ID 0x123

static FDCAN_TxHeaderTypeDef TxHeader;
static FDCAN_RxHeaderTypeDef RxHeader;
static uint8_t TxData[8] = {0};
static uint8_t RxData[8];

static FDCAN_HandleTypeDef *hfdcan_ptr;

static can_rx_callback_t rx_callback_ptr;

void EDT_FDCAN_Init(FDCAN_HandleTypeDef *hfdcan, can_rx_callback_t rx_callback) {
    hfdcan_ptr = hfdcan;
    rx_callback_ptr = rx_callback;
    // Enabling one filter for testing
    // find inspiration in:
    //      stm32h7xx_hal_fdcan.h and
    //      reference manual RM0468 section 61.4.21 FDCAN standard message ID filter element
    FDCAN_FilterTypeDef sFilterConfig;
    sFilterConfig.IdType = FDCAN_STANDARD_ID; // The filter will accept standard IDs only
    sFilterConfig.FilterIndex = 0; // Configure filter 0 in the filter list
    sFilterConfig.FilterID1 = LOOP_BACK_ID; // set filter to accept messages with ID 0x123
    sFilterConfig.FilterID2 = 0x7FF; // all 11 bits of ID1 (0x123) must match to be accepted.
    sFilterConfig.FilterType = FDCAN_FILTER_MASK; // we are only interested in checking bits in the one ID
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0; // when ID matches, store the message in RX FIFO 0

    if (HAL_FDCAN_ConfigFilter(hfdcan_ptr, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    // Activating interrupt for when new message in RX FIFO 0 had arrived.
    if (HAL_FDCAN_ActivateNotification(hfdcan_ptr, FDCAN_IT_RX_FIFO0_NEW_MESSAGE,0) != HAL_OK)
    {
        /* Notification Error */
        Error_Handler();
    }
    HAL_FDCAN_Start(hfdcan_ptr);
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan,uint32_t RxFifo0ITs)
{
    if (hfdcan_ptr != hfdcan) return;
    if (RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) {
        if (HAL_FDCAN_GetRxMessage(hfdcan_ptr, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK){
            Error_Handler();
        }
        if (rx_callback_ptr != NULL) {
            rx_callback_ptr(&RxHeader, RxData);
        }
    }
}

void HAL_FDCAN_ErrorCallback(FDCAN_HandleTypeDef *hfdcan)
{
    if (hfdcan_ptr != hfdcan) return;
    Error_Handler();
}

void EDT_FDCAN_Transmit_Loopback_testing() {
    TxHeader.Identifier          = LOOP_BACK_ID;
    TxHeader.IdType              = FDCAN_STANDARD_ID;
    TxHeader.TxFrameType         = FDCAN_DATA_FRAME;
    TxHeader.DataLength          = FDCAN_DLC_BYTES_8;
    TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    TxHeader.BitRateSwitch       = FDCAN_BRS_OFF;
    TxHeader.FDFormat            = FDCAN_CLASSIC_CAN;
    TxHeader.TxEventFifoControl  = FDCAN_NO_TX_EVENTS;
    TxHeader.MessageMarker       = 0;
    TxData[0] = 0;
    TxData[7] = 0xFF;
    if (HAL_FDCAN_AddMessageToTxFifoQ(hfdcan_ptr,&TxHeader,TxData) != HAL_OK){
        Error_Handler();
    }
}