//
// Created by nilas on 15/10/2026.
//
#include "cmsis_os2.h"
#include "edt_logger.h"
#include "edt_log_item_handler.h"

extern osMessageQueueId_t logQueueHandle;

void edt_log(const char *msg) {
    const char *name = osThreadGetName(osThreadGetId());
    const edt_log_item_t item = create_logging_Item(msg,name);
    osMessageQueuePut(logQueueHandle, &item, 0, 0);
}