
#include "mUSB.hpp"

#include <stdarg.h>

#include "main.h"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {

bool usb::begin()
{
    Transmission_speed speed_ = Transmission_speed::Full_Speed;

    if (husbx_->Init.speed == PCD_SPEED_FULL) {
        speed_ = Transmission_speed::Full_Speed;
    } else {
        speed_ = Transmission_speed::High_Speed;
    }

    _USB_Stack_.Init(husbx_, speed_);
    return 0;
}

bool usb::print(const char* __format, ...)
{
    return 0;
}

bool usb::print(signed char __data_s8)
{
    return 0;
}

bool usb::print(unsigned char __data_u8)
{
    return 0;
}

bool usb::print(signed short __data_s16)
{
    return 0;
}

bool usb::print(unsigned short __data_s16)
{
    return 0;
}

bool usb::print(signed long __data_s32)
{
    return 0;
}

bool usb::print(unsigned long __data_u32)
{
    return 0;
}

bool usb::print(signed long long __data_s64)
{
    return 0;
}

bool usb::print(unsigned long long __data_u64)
{
    return 0;
}

bool usb::print(float __float)
{
    return 0;
}

bool usb::print(double __double)
{
    return 0;
}

bool usb::getMessage()
{
    return 0;
}

bool usb::end()
{
    return 0;
}

}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal
