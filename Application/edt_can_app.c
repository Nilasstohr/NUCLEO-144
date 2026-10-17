//
// Created by nilas on 15/10/2026.
//
#include "cmsis_os2.h"
#include "edt_logger.h"
#include "edt_can_app.h"
#include <string.h>
#include "Drivers/edt_can.h"

extern osMessageQueueId_t canRxQueueHandle;

static edt_can_rx_message_t canRxMessage;

static void EDT_CAN_RX_callback(const FDCAN_RxHeaderTypeDef *header, const uint8_t *data);

void StartCanAppTask(void *argument) {
    EDT_FDCAN_Init(argument, EDT_CAN_RX_callback);
    //EDT_FDCAN_Transmit_Loopback_testing();
    for(;;)
    {
        const osStatus_t status = osMessageQueueGet(canRxQueueHandle, &canRxMessage, NULL, 500); // 10ms timeout
        if(status == osOK) {
            edt_log_debug("Received message in RX FIFO 0");
        }
        BSP_LED_Toggle(LED_GREEN);
    }
}

static void EDT_CAN_RX_callback(const FDCAN_RxHeaderTypeDef *header, const uint8_t *data) {
    edt_log_debug("Received message in RX FIFO 0");
    canRxMessage.DataLength = header->DataLength;
    canRxMessage.Identifier = header->Identifier;
    memcpy(canRxMessage.data, data, header->DataLength);
    osMessageQueuePut(canRxQueueHandle, &canRxMessage, 0, 0);
}