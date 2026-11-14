#include <gtest/gtest.h>

#include "lib.h"

TEST(TestVersion, ValidVersion) { EXPECT_GT(version(), 0); }
