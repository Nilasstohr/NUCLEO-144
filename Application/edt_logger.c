//
// Created by nilas on 15/10/2026.
//
#include "cmsis_os2.h"
#include "edt_logger.h"
#include "Drivers/edt_log_item_handler.h"

//#define EDT_LOGGING_ENABLED

extern osMessageQueueId_t logQueueHandle;

static void send_log(const char *msg) {
    const char *name = osThreadGetName(osThreadGetId());
    const edt_log_item_t item = create_logging_Item(msg,name);
    osMessageQueuePut(logQueueHandle, &item, 0, 0);
}

void edt_log_debug(const char *msg) {
#ifdef EDT_LOGGING_ENABLED
    send_log(msg);
#endif
}

void edt_log(const char *msg) {
    send_log(msg);
}