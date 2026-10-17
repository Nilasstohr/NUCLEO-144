//
// Created by nilas on 15/10/2026.
//

#ifndef NUCLEO_144_HOST_EDT_LOGGING_H
#define NUCLEO_144_HOST_EDT_LOGGING_H
#include <stdint.h>

#define EDT_LOG_MSG_SIZE 100

typedef struct {
   char msg[EDT_LOG_MSG_SIZE];
   uint8_t msg_len;
}edt_log_item_t;

edt_log_item_t create_logging_Item(const char *log_msg,const char *task_name);

#endif //NUCLEO_144_HOST_EDT_LOGGING_H
