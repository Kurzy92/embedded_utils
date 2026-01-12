#include <catch2/catch_test_macros.hpp>
#include "register.hpp"

TEST_CASE("Register construction", "[register]") {
    SECTION("Default constructor initializes to zero") {
        Register reg;
        REQUIRE(reg.get_value() == 0);
    }

    SECTION("Value constructor sets initial value") {
        Register reg(0xAB);
        REQUIRE(reg.get_value() == 0xAB);
    }
}

TEST_CASE("Register bit operations", "[register]") {
    Register reg;

    SECTION("Setting a bit") {
        reg.set_bit(3);
        REQUIRE(reg.is_set(3));
        REQUIRE(reg.get_value() == 0x08);
    }

    SECTION("Clearing a bit") {
        reg = 0xFF;
        reg.clear_bit(2);
        REQUIRE_FALSE(reg.is_set(2));
        REQUIRE(reg.get_value() == 0xFB);
    }

    SECTION("Chaining bit operations") {
        reg.set_bit(0).set_bit(4).clear_bit(4);
        REQUIRE(reg.is_set(0));
        REQUIRE_FALSE(reg.is_set(4));
        REQUIRE(reg.get_value() == 0x01);
    }
}

TEST_CASE("Register mask operations", "[register]") {
    Register reg;

    SECTION("Setting a mask") {
        reg.set_mask(0x0F);
        REQUIRE(reg.get_value() == 0x0F);
    }

    SECTION("Clearing a mask") {
        reg = 0xFF;
        reg.clear_mask(0x0F);
        REQUIRE(reg.get_value() == 0xF0);
    }

    SECTION("Testing a mask") {
        reg = 0xA5;  // 10100101
        REQUIRE(reg.test_mask(0x01));
        REQUIRE(reg.test_mask(0x80));
        REQUIRE_FALSE(reg.test_mask(0x02));
    }
}

TEST_CASE("Register field operations", "[register]") {
    Register reg;

    SECTION("Writing a field") {
        // Write value 0b101 (5) to bits [4:2] (mask 0x1C, shift 2)
        reg.write_field(5, 0x1C, 2);
        REQUIRE(reg.get_value() == 0x14);  // 0b00010100
    }

    SECTION("Overwriting a field preserves other bits") {
        reg = 0xFF;
        reg.write_field(0, 0x1C, 2);  // Clear bits [4:2]
        REQUIRE(reg.get_value() == 0xE3);  // 0b11100011
    }
}

TEST_CASE("Register operators", "[register]") {
    SECTION("Assignment operator") {
        Register reg;
        reg = 0x42;
        REQUIRE(reg.get_value() == 0x42);
    }

    SECTION("uint8_t conversion operator") {
        Register reg(0x55);
        uint8_t value = reg;
        REQUIRE(value == 0x55);
    }
}

TEST_CASE("Register constexpr operations", "[register]") {
    SECTION("Compile-time register operations") {
        constexpr Register reg = Register(0x00).set_bit(3).set_bit(5);
        static_assert(reg.get_value() == 0x28, "Constexpr bit setting failed");
        REQUIRE(reg.get_value() == 0x28);
    }

    SECTION("Compile-time field operations") {
        constexpr Register reg = Register().write_field(7, 0x1C, 2);
        static_assert(reg.get_value() == 0x1C, "Constexpr field write failed");
        REQUIRE(reg.get_value() == 0x1C);
    }
}
