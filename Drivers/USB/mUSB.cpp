
#include "mUSB.hpp"

#include "main.h"

namespace maidui3_hal {
namespace Drivers {
namespace USB {

bool usb::begin(const int __speed)
{
    HAL_PCD_Start(husbx_);

    HAL_PCD_DevConnect(husbx_);

    HAL_PCD_EP_Open(husbx_, (PCD_ENDP0 | static_cast<uint8_t>(EP_Direction::OUT)), 64, )

        return 0;
}

bool usb::print(const char* __format)
{
    return 0;
}

bool usb::print(const signed char __data_s8)
{
    return 0;
}

bool usb::print(const unsigned char __data_u8)
{
    return 0;
}

bool usb::print(const signed short __data_s16)
{
    return 0;
}

bool usb::print(const unsigned short __data_s16)
{
    return 0;
}

bool usb::print(const signed int __data_s32)
{
    return 0;
}

bool usb::print(const unsigned int __data_u32)
{
    return 0;
}

bool usb::print(const signed long long __data_s64)
{
    return 0;
}

bool usb::print(const unsigned long long __data_u64)
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

bool usb::send(uint8_t* __data_p, uint16_t __len)
{
    return 0;
}

bool usb::getMessage()
{
    return 0;
}

bool usb::end()
{
    HAL_PCD_Stop(husbx_);

    HAL_PCD_DevDisconnect(husbx_);

    return 0;
}

}  // namespace USB
}  // namespace Drivers
}  // namespace maidui3_hal

extern "C" {

void HAL_PCD_SOFCallback(PCD_HandleTypeDef* hpcd) {}

void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef* hpcd) {}

void HAL_PCD_ResetCallback(PCD_HandleTypeDef* hpcd) {}

void HAL_PCD_SuspendCallback(PCD_HandleTypeDef* hpcd) {}

void HAL_PCD_ResumeCallback(PCD_HandleTypeDef* hpcd) {}

void HAL_PCD_ConnectCallback(PCD_HandleTypeDef* hpcd)
{
    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_SET);
}

void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef* hpcd)
{
    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_RESET);
}

void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum) {}

void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum) {}

void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum) {}

void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum) {}
}