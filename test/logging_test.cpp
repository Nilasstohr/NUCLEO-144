#include <gtest/gtest.h>

// For C firmware sources, include their headers like this:
 extern "C" {
 #include "edt_log_item_handler.h"
 }

TEST(loggingTest, CanGetLogItem) {
    const edt_log_item_t item = create_logging_Item("This is a test log message","TestTask");
    const std::string expected_msg = "TestTask - This is a test log message";
    EXPECT_STREQ(item.msg, expected_msg.c_str());
    EXPECT_EQ(item.msg_len, strlen(expected_msg.c_str()));
 }
