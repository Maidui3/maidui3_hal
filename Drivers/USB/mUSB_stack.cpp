
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

bool usb_stack::stop(PCD_HandleTypeDef* husb_pcd_)
{
    HAL_PCD_Stop(husb_pcd_);
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

    if (USB_PCD_FS.hpcd__ == husb_pcd__) {
        if ((husb_pcd__->Setup[0] & bmRequestType_Dir_MSK)) {
            // Device -> Host
            // bit7 is 1
            switch (husb_pcd__->Setup[0] & bmRequestType_Type_MSK) {
                case bmRequestType_Type_Standard:
                    switch (husb_pcd__->Setup[0] & bmRequestType_Reci_MSK) {
                        case bmRequestType_Reci_Device:
                            switch (husb_pcd__->Setup[1]) {
                                case USB_GET_STATUS:
                                    for (uint8_t i = 0; i < 64; i++) {
                                        Transmit_Control_Stage_Buffer[i] = 0;
                                    }
                                    Transmit_Control_Stage_Buffer[0] = USB_BusPower | USB_Disable_RemotoWakeup;
                                    HAL_PCD_EP_Transmit(husb_pcd__, PCD_ENDP0, Transmit_Control_Stage_Buffer, 8);

                                    break;

                                case USB_GET_DESCRIPTOR:
                                    break;

                                case USB_GET_CONFIGURATION:
                                    break;
                            }
                            break;

                        case bmRequestType_Reci_Interface:
                            switch (husb_pcd__->Setup[1]) {
                                case USB_GET_STATUS:
                                    for (uint8_t i = 0; i < 64; i++) {
                                        Transmit_Control_Stage_Buffer[i] = 0;
                                    }

                                    break;

                                case USB_GET_INTERFACE:
                                    break;
                            }
                            break;

                        case bmRequestType_Reci_Endpoint:
                            switch (husb_pcd__->Setup[1]) {
                                case USB_GET_STATUS:
                                    break;

                                case USB_SYNCH_FRAME:
                                    break;
                            }
                            break;

                        case bmRequestType_Reci_Other:
                            break;
                    }
                    break;

                case bmRequestType_Type_Class:
                    /*CDCやAudioなど*/
                    break;

                case bmRequestType_Type_Vendor:
                    /*stmのdfuなど*/
                    break;
            }
        } else {
            // Host -> Device
            // bit7 is 0
            switch (husb_pcd__->Setup[0] & bmRequestType_Type_MSK) {
                case bmRequestType_Type_Standard:
                    switch (husb_pcd__->Setup[0] & bmRequestType_Reci_MSK) {
                        case bmRequestType_Reci_Device:
                            switch (husb_pcd__->Setup[1]) {
                                case USB_CLEAR_FEATURE:
                                    break;

                                case USB_SET_FEATURE:
                                    break;

                                case USB_SET_ADDRESS:
                                    break;

                                case USB_SET_DESCRIPTOR:
                                    break;

                                case USB_SET_CONFIGURATION:
                                    break;
                            }
                            break;

                        case bmRequestType_Reci_Interface:
                            switch (husb_pcd__->Setup[1]) {
                                case USB_CLEAR_FEATURE:
                                    break;

                                case USB_SET_FEATURE:
                                    break;

                                case USB_SET_INTERFACE:
                                    break;
                            }
                            break;

                        case bmRequestType_Reci_Endpoint:
                            switch (husb_pcd__->Setup[1]) {
                                case USB_CLEAR_FEATURE:
                                    break;

                                case USB_SET_FEATURE:
                                    break;
                            }
                            break;

                        case bmRequestType_Reci_Other:
                            break;
                    }
                    break;

                case bmRequestType_Type_Class:
                    /*CDCやAudioなど*/
                    break;

                case bmRequestType_Type_Vendor:
                    /*stmのdfuなど*/
                    break;
            }
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
