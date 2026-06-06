
#include "mUSB.hpp"

#include "main.h"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {

#ifdef USB
bool usb::begin(PCD_HandleTypeDef* __husbx, const int __speed)
{
    husbx_ = __husbx;

    if (husbx_ == NULL) {
        while (1);
        /*husbx_内になにも渡されていなければエラー*/
    }

    HAL_PCD_Start(husbx_); /*STMのUSBハードウェア起動*/

    HAL_Delay(100);

    return 0;
}
#else
#ifdef STM32G4
bool usb::begin() {}
#endif

#endif

bool usb::printf(const char* __format, ...)
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

bool usb::print(signed int __data_s32)
{
    return 0;
}

bool usb::print(unsigned int __data_u32)
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

bool usb::send_USBD(uint8_t* __data_p, uint16_t __len)
{
    return 0;
}

bool usb::getMessage()
{
    return 0;
}

#ifdef USB
bool usb::end()
{
    HAL_PCD_Stop(husbx_);

    return 0;
}
#endif

}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal

// maidui3_hal::Drivers::USB_PCD::usb Serial;
