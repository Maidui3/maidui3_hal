
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

void usb_stack::SOF_Callback(PCD_HandleTypeDef* husb_pcd__) {}

void usb_stack::SetupStage_Callback(PCD_HandleTypeDef* husb_pcd__)
{
    /**
     * 1Byte : bmRequestType
     * 1Byte : bRequest
     * 2Byte : wValue
     * 2Byte : wIndex
     * 2Byte : wLength
     */
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
