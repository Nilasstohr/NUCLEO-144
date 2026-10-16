//
// Created by nilas on 15/10/2026.
//
#include "cmsis_os2.h"
#include "edt_logging_task.h"

#include <string.h>

#include "edt_log_item_handler.h"
#include "edt_uart_logger.h"

extern osMessageQueueId_t logQueueHandle;

void StartLoggingTask(void *argument) {
    EDT_USART_LOGGER_Init(argument);
    edt_log_item_t logItem;
    for(;;)
    {
        memset(&logItem, 0, sizeof(logItem));
        const osStatus_t status = osMessageQueueGet(logQueueHandle, &logItem, NULL, 500);
        if (status == osOK) {
            EDT_USART_LOGGER_Transmit_DMA_Blocking(logItem.msg, logItem.msg_len);
        }
    }
}