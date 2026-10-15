//
// Created by nilas on 15/10/2026.
//

#include "edt_log_item_handler.h"
#include <string.h>

// Appends src at pos without exceeding the buffer (room kept for the terminator).
static size_t append(char *dst, const size_t pos, const char *src) {
    const size_t len = strnlen(src, EDT_LOG_MSG_SIZE - 1 - pos);
    memcpy(dst + pos, src, len);
    return pos + len;
}

edt_log_item_t create_logging_Item(const char *log_msg,const char *task_name) {
    edt_log_item_t item;
    size_t pos = append(item.msg, 0, task_name);
    pos = append(item.msg, pos, " - ");
    pos = append(item.msg, pos, log_msg);
    item.msg[pos] = '\0';
    item.msg_len = (uint8_t)pos;
    return item;
}