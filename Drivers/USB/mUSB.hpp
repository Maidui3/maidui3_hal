
#pragma once

#include <cstdint>

#include "mUSB_stack.hpp"
#include "main.h"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {

class usb
{
private:
    uint8_t Tx_Buffer[PCD_Default_mps];
    uint8_t Rx_Buffer[PCD_Default_mps];

    PCD_HandleTypeDef* husbx_ = NULL;

public:
    usb(PCD_HandleTypeDef* _husbx) : husbx_(_husbx) {};

    bool begin();

    bool print(const char* __format, ...);

    bool print(signed char __data_s8);

    bool print(unsigned char __data_u8);

    bool print(signed short __data_s16);

    bool print(unsigned short __data_s16);

    bool print(signed long __data_s32);

    bool print(unsigned long __data_u32);

    bool print(signed long long __data_s64);

    bool print(unsigned long long __data_u64);

    bool print(float __float);

    bool print(double __double);

    uint16_t available();

    bool getMessage();

    bool end();
};

}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal

// extern maidui3_hal::Drivers::USB_PCD::usb Serial;
