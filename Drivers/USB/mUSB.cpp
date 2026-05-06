
#include "mUSB.hpp"

#include "main.h"

namespace maidui3_hal {
namespace Drivers {
namespace USB {

bool usb::begin(const int __speed)
{
    HAL_PCD_Start(husbx_); /*STMのUSBハードウェア起動*/

    HAL_PCD_DevConnect(husbx_); /*USBバスをプルアップ*/

    if (husbx_ == NULL) {
        while (1);
        /*husbx_内になにも渡されていなければエラー*/
    }

    HAL_Delay(100);

    // HAL_PCD_SetAddress(husbx_, husbx_->USB_Address);

    return 0;
}

bool usb::print(const char* __format)
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

void HAL_PCD_SOFCallback(PCD_HandleTypeDef* hpcd)
{
    /*SOFパケット割り込み 確認済み*/

    // HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_SET);
}

void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef* hpcd)
{
    /*PIDの設定時に呼ばれるらしいい 確認済み*/
    HAL_PCD_EP_Transmit(Serial.husbx_, (PCD_ENDP0 | maidui3_hal::Drivers::USB::EP_Direction::IN), Serial.setup_buffer_TX_, 64);
    HAL_PCD_EP_Receive(Serial.husbx_, (PCD_ENDP0 | maidui3_hal::Drivers::USB::EP_Direction::OUT), Serial.setup_buffer_RX_, 64);
    for (uint8_t i = 0; i < 64; i++) {
        if (Serial.setup_buffer_RX_[i] != 0) HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);
    }

    HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_SET);
}

void HAL_PCD_ResetCallback(PCD_HandleTypeDef* hpcd)
{
    /*ホストがデバイスのプルアップを認識し、0を送り続けている　確認済み*/

    HAL_PCD_EP_Open(hpcd, (PCD_ENDP0 | maidui3_hal::Drivers::USB::EP_Direction::OUT), 64, EP_TYPE_CTRL);
    HAL_PCD_EP_Open(hpcd, (PCD_ENDP0 | maidui3_hal::Drivers::USB::EP_Direction::IN), 64, EP_TYPE_CTRL);
}

void HAL_PCD_SuspendCallback(PCD_HandleTypeDef* hpcd) {}

void HAL_PCD_ResumeCallback(PCD_HandleTypeDef* hpcd) {}

void HAL_PCD_ConnectCallback(PCD_HandleTypeDef* hpcd)
{
    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_SET);
}

void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef* hpcd)
{
    // HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_RESET);
}

void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum) {}

void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum) {}

void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum) {}

void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum) {}
}
