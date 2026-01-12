#pragma once

#include <cstdint>

class Register {
    public:
    constexpr Register(): value_(0) {}
    constexpr explicit Register(uint8_t value): value_(value) {}

    constexpr Register& set_bit(uint8_t bit) {
        value_ |= (1 << bit);
        return *this;
    }

    constexpr Register& clear_bit(uint8_t bit) {
        value_ &= ~(1 << bit);
        return *this;
    }

    constexpr Register& set_mask(uint8_t mask) {
        value_ |= mask;
        return *this;
    }

    constexpr Register& clear_mask(uint8_t mask) {
        value_ &= ~mask;
        return *this;
    }

    constexpr Register& write_field(uint8_t value, uint8_t mask, uint8_t shift) {
        value_ = (value_ & ~mask) | ((value << shift) & mask);
        return *this;
    }

    constexpr bool is_set(uint8_t bit) const {
        return (value_ & (1 << bit)) != 0;
    }

    constexpr bool test_mask(uint8_t mask) const {
        return (value_ & mask) != 0;
    }

    constexpr uint8_t get_value() const {
        return value_;
    }

    constexpr operator uint8_t() const {
        return value_;
    }

    constexpr Register& operator=(uint8_t value) {
        value_ = value;
        return *this;
    }


    private:
        uint8_t value_;
};