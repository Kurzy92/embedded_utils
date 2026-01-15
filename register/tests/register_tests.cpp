#include <gtest/gtest.h>
#include "register.hpp"

TEST(RegisterTest, EmptyConstructorTest) {
    Register tmp;
    EXPECT_EQ(tmp.get_value(), 0);
}

TEST(RegisterTest, ValueConstructorTest) {
    Register tmp(100);
    EXPECT_EQ(tmp.get_value(), 100);
}

TEST(RegisterTest, SetBitTest) {
    Register tmp;
    tmp.set_bit(3);
    EXPECT_EQ(tmp.get_value(), 8);
}

TEST(RegisterTest, ClearBitTest) {
    Register tmp(0xFF);
    tmp.clear_bit(3);
    EXPECT_EQ(tmp.get_value(), 0xF7);
}

TEST(RegisterTest, SetMaskTest) {
    Register tmp(0x0F);
    tmp.set_mask(0xF0);
    EXPECT_EQ(tmp.get_value(), 0xFF);
}

TEST(RegisterTest, ClearMaskTest) {
    Register tmp(0xFF);
    tmp.clear_mask(0xF0);
    EXPECT_EQ(tmp.get_value(), 0x0F);
}

TEST(RegisterTest, WriteFieldTest) {
    Register tmp(0x00);
    tmp.write_field(0b101, 0b11100, 2);
    EXPECT_EQ(tmp.get_value(), 0b0010100);
}

TEST(RegisterTest, IsSetTest) {
    Register tmp(0b00001000);
    EXPECT_TRUE(tmp.is_set(3));
    EXPECT_FALSE(tmp.is_set(2));
}

TEST(RegisterTest, TestMaskTest) {
    Register tmp(0b00001111);
    EXPECT_TRUE(tmp.test_mask(0b00000101));
    EXPECT_FALSE(tmp.test_mask(0b00010000));
}

TEST(RegisterTest, AssignmentOperatorTest) {
    Register tmp;
    tmp = 42;
    EXPECT_EQ(tmp.get_value(), 42);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
