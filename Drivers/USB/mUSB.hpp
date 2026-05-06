
#pragma once

// #include <cstdint>

#include "../../../Core/Inc/usb.h"
#include "mUSB_config.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace USB {

class usb
{
protected:
    bool send(uint8_t* __data_p, uint16_t __len);

public:
    usb(PCD_HandleTypeDef* __husbx) : husbx_(__husbx) {};

    bool begin(const int __speed = 0);

    bool print(const char* __format);

    bool print(signed char __data_s8);

    bool print(unsigned char __data_u8);

    bool print(signed short __data_s16);

    bool print(unsigned short __data_s16);

    bool print(signed int __data_s32);

    bool print(unsigned int __data_u32);

    bool print(signed long long __data_s64);

    bool print(unsigned long long __data_u64);

    bool print(float __float);

    bool print(double __double);

    bool getMessage();

    bool end();

    PCD_HandleTypeDef* husbx_ = NULL;

    uint8_t setup_buffer_TX_[64];

    uint8_t setup_buffer_RX_[64];
};

}  // namespace USB
}  // namespace Drivers
}  // namespace maidui3_hal

extern maidui3_hal::Drivers::USB::usb Serial;
