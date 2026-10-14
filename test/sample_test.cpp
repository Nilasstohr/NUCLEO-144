#include <gtest/gtest.h>

// For C firmware sources, include their headers like this:
// extern "C" {
// #include "my_logic.h"
// }

TEST(Sample, Works) {
    EXPECT_EQ(2 + 2, 4);
}
