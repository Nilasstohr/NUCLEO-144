//
// Created by nilas on 15/10/2026.
//
#include "cmsis_os2.h"
#include "edt_logger.h"

void StartTestLoggingTask(void *argument) {
    for(;;)
    {
        edt_log("Test log message from StartTestLoggingTask\n\r");
        osDelay(500);
    }
}