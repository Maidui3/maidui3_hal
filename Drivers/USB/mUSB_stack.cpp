
#include "mUSB_stack.hpp"

#include "stdlib.h"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {

bool usb_stack::transfer_()
{
    return 0;
}

bool usb_stack::Init(PCD_HandleTypeDef* husb_pcd_, Transmission_speed speed_)
{
    if (speed_ == Transmission_speed::Full_Speed) {
        USB_PCD_FS.hpcd__ = husb_pcd_;
    } else {
        USB_PCD_HS.hpcd__ = husb_pcd_;
    }

    HAL_PCD_Start(husb_pcd_);
    return 0;
}

bool usb_stack::transfer()
{
    return 0;
}

bool usb_stack::receive()
{
    return 0;
}

bool usb_stack::stop()
{
    return 0;
}

void usb_stack::SOF_Callback(PCD_HandleTypeDef* husb_pcd__)
{
    // SOF
    // 0000 0001 1010 0101 1011 0111 101 10011
    /* |  SYNC | |  PID  | |   FRAME   | |CRS| */

    // Setup Token
    // 0000 0001 1011 0100 0000 0000 000 01000
    /* |  SYNC | |  PID  | | ADDR || EN ||CRS| */

    // Setup Data
    // 0000 0001 1100 0011 0000 0001 0110 0000 0000 0000 1000 0000 0000 0000 0000 0000 0000 0010 0000 0000
    /* |  SYNC | |  PID  | | 1Byte | | 2Byte | | 3Byte | | 4Byte | | 5Byte | | 6Byte | | 7Byte | | 8Byte | */
    // 1011 1011 0010 1001
    /* |       CRS       | */

    // Setup Handshake
    // 0000 0001 0100 1011
    /* |  SYNC | |  PID  |*/
}

void usb_stack::SetupStage_Callback(PCD_HandleTypeDef* husb_pcd__)
{
    HAL_GPIO_WritePin(LED_Wio_E5_GPIO_Port, LED_Wio_E5_Pin, GPIO_PIN_SET);
    /**
     * 1Byte : bmRequestType
     * 1Byte : bRequest
     * 2Byte : wValue
     * 2Byte : wIndex
     * 2Byte : wLength
     */

    Transmit_Control_Stage_Buffer[0] = 0x03;
    Transmit_Control_Stage_Buffer[1] = 0x01;
    Transmit_Control_Stage_Buffer[2] = 0x00;
    Transmit_Control_Stage_Buffer[3] = 0x02;
    Transmit_Control_Stage_Buffer[4] = 0x00;
    Transmit_Control_Stage_Buffer[5] = 0x00;
    Transmit_Control_Stage_Buffer[6] = 0x00;
    Transmit_Control_Stage_Buffer[7] = 0x08;

    HAL_PCD_EP_Transmit(husb_pcd__, PCD_ENDP0, _USB_Stack_.Transmit_Control_Stage_Buffer, 8);

    if (USB_PCD_FS.hpcd__ == husb_pcd__) {
        if (!(husb_pcd__->Setup[0] & bmRequestType_Dir_MSK)) {
            // Host -> Device
        } else {
            // Device -> Host
        }
    } else {
    }
}

void usb_stack::Reset_Callback(PCD_HandleTypeDef* husb_pcd__)
{
    HAL_PCD_EP_Open(husb_pcd__, (PCD_ENDP0 | PCD_EP_OUT), PCD_Control_mps, EP_TYPE_CTRL);
    HAL_PCD_EP_Open(husb_pcd__, (PCD_ENDP0 | PCD_EP_IN), PCD_Control_mps, EP_TYPE_CTRL);

    if (USB_PCD_FS.hpcd__ == husb_pcd__) {
        USB_PCD_FS.is_Reseted = true;
    } else {
        USB_PCD_HS.is_Reseted = true;
    }
}

void usb_stack::Suspend_Callback(PCD_HandleTypeDef* husb_pcd__) {}

void usb_stack::Resume_Callback(PCD_HandleTypeDef* husb_pcd__) {}

void usb_stack::Connect_Callback(PCD_HandleTypeDef* husb_pcd__) {}

void usb_stack::Disconnect_Callback(PCD_HandleTypeDef* husb_pcd__) {}

void usb_stack::DataOutStage_Callback(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__) {}

void usb_stack::DataInStage_Callback(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__) {}

void usb_stack::Iso_OutIncomplete(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__) {}

void usb_stack::Iso_InIncomplete(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__) {}

}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal

#ifdef HAL_PCD_MODULE_ENABLED

maidui3_hal::Drivers::USB_PCD::usb_stack _USB_Stack_;

extern "C" {

void HAL_PCD_SOFCallback(PCD_HandleTypeDef* hpcd)
{
    _USB_Stack_.SOF_Callback(hpcd);
}

void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef* hpcd)
{
    _USB_Stack_.SetupStage_Callback(hpcd);
}

void HAL_PCD_ResetCallback(PCD_HandleTypeDef* hpcd)
{
    _USB_Stack_.Reset_Callback(hpcd);
}

void HAL_PCD_SuspendCallback(PCD_HandleTypeDef* hpcd)
{
    _USB_Stack_.Suspend_Callback(hpcd);
}

void HAL_PCD_ResumeCallback(PCD_HandleTypeDef* hpcd)
{
    _USB_Stack_.Resume_Callback(hpcd);
}

void HAL_PCD_ConnectCallback(PCD_HandleTypeDef* hpcd)
{
    _USB_Stack_.Connect_Callback(hpcd);
}

void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef* hpcd)
{
    _USB_Stack_.Disconnect_Callback(hpcd);
}

void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum)
{
    _USB_Stack_.DataOutStage_Callback(hpcd, epnum);
}

void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum)
{
    _USB_Stack_.DataInStage_Callback(hpcd, epnum);
}

void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum)
{
    _USB_Stack_.Iso_OutIncomplete(hpcd, epnum);
}

void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum)
{
    _USB_Stack_.Iso_InIncomplete(hpcd, epnum);
}
}

#endif
