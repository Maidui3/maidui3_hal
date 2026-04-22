
#pragma once

// #include <cstdint>

#include "../../../Core/Inc/usb.h"

namespace maidui3_hal {
namespace Drivers {
namespace USB {

class usb
{
protected:
    PCD_HandleTypeDef* husbx_;

public:
    usb(PCD_HandleTypeDef* __husbx) : husbx_(__husbx) {};

    bool begin(const int __speed = 0);

    bool print(const char* __format);

    bool print(const signed char __data_s8);

    bool print(const unsigned char __data_u8);

    bool print(const signed short __data_s16);

    bool print(const unsigned short __data_s16);

    bool print(const signed int __data_s32);

    bool print(const unsigned int __data_u32);

    bool print(const signed long long __data_s64);

    bool print(const unsigned long long __data_u64);

    bool print(float __float);

    bool print(double __double);

    bool getMessage();

    bool send(uint8_t* __data_p, uint16_t __len);

    bool end();
};

}  // namespace USB
}  // namespace Drivers
}  // namespace maidui3_hal
