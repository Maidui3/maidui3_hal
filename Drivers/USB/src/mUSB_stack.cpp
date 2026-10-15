
#include "mUSB_stack.hpp"

#include "stdlib.h"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {
namespace stack {

uint32_t last_tick[STM_MCU_MAX_USB_Device];
PCD_HandleTypeDef* hpcd__[STM_MCU_MAX_USB_Device];
USB_PCD_Stack_t USB_PCD_Device[STM_MCU_MAX_USB_Device];

bool Init(PCD_HandleTypeDef* _hpcd_Device1, PCD_HandleTypeDef* _hpcd_Device2)
{
    if ((_hpcd_Device1 == NULL) && (_hpcd_Device2 == NULL)) return 1;

    PCD_HandleTypeDef* hpcd[STM_MCU_MAX_USB_Device];
    hpcd[0] = _hpcd_Device1;
    hpcd[1] = _hpcd_Device2;

    for (uint8_t i = 0; i < STM_MCU_MAX_USB_Device; i++) {
        if (hpcd[i] == NULL) break;
        hpcd__[i] = hpcd[i];
        HAL_PCD_Start(hpcd__[i]);
    }

    return 0;
}

bool Stop(PCD_HandleTypeDef* husb_pcd_)
{
    HAL_PCD_Stop(husb_pcd_);
    return 0;
}

void Clear_Byte(uint8_t* buf, uint8_t len)
{
    for (uint8_t i = 0; i < len; i++) {
        *(buf + i) = 0;
    }

    return;
}

bool get_status(PCD_HandleTypeDef* husb_pcd__, Device_Status_t* buffer_)
{
    buffer_->SelfPower    = USB_BusPower;
    buffer_->RemoteWakeup = USB_Disable_RemotoWakeup;
    buffer_->unused       = 0x00;

    return 0;
}

void SOF_Callback(PCD_HandleTypeDef* husb_pcd__)
{
    for (uint8_t i = 0; i < STM_MCU_MAX_USB_Device; i++) {
        if (hpcd__[i] == husb_pcd__) {
            if ((HAL_GetTick() - last_tick[i]) >= 10) {
                Stop(husb_pcd__);
            }
            return;
        }
    }
}

void SetupStage_Callback(PCD_HandleTypeDef* husb_pcd__, uint32_t* setup__)
{
    /**
     * 1Byte : bmRequestType
     * 1Byte : bRequest
     * 2Byte : wValue
     * 2Byte : wIndex
     * 2Byte : wLength
     */

    static Setup_Packet_t packet;

    packet.bmRequestType = (uint8_t)(setup__[0]);
    packet.bRequest      = (uint8_t)((setup__[0] & 0xFF00) >> 8);
    packet.wValue        = (uint16_t)((setup__[0] & 0xFFFF0000) >> 16);
    packet.wIndex        = (uint16_t)(setup__[1] & 0xFFFF);
    packet.wLength       = (uint16_t)((setup__[1] & 0xFFFF0000) >> 16);

    if (packet.bmRequestType & bmRequestType_Dir_MSK) {
        // Device -> Host
        // bit7 is 1

        switch (packet.bmRequestType & bmRequestType_Type_MSK) {
            case bmRequestType_Type_Standard:

                switch (packet.bmRequestType & bmRequestType_Reci_MSK) {
                    case bmRequestType_Reci_Device:
                        Host_Dir_Device_Request(husb_pcd__, &packet);
                        break;

                    case bmRequestType_Reci_Interface:
                        Host_Dir_Interface_Request(husb_pcd__, &packet);
                        break;

                    case bmRequestType_Reci_Endpoint:
                        Host_Dir_Endpoint_Request(husb_pcd__, &packet);
                        break;

                    case bmRequestType_Reci_Other:
                        Host_Dir_Other_Request(husb_pcd__, &packet);
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
                                HAL_PCD_SetAddress(husb_pcd__, packet.wValue);
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

    return;
}

void Reset_Callback(PCD_HandleTypeDef* husb_pcd__)
{
    HAL_PCD_EP_Open(husb_pcd__, (PCD_ENDP0 | PCD_EP_OUT), PCD_Control_mps, EP_TYPE_CTRL);
    HAL_PCD_EP_Open(husb_pcd__, (PCD_ENDP0 | PCD_EP_IN), PCD_Control_mps, EP_TYPE_CTRL);
}

void Suspend_Callback(PCD_HandleTypeDef* husb_pcd__) {}

void Resume_Callback(PCD_HandleTypeDef* husb_pcd__) {}

void Connect_Callback(PCD_HandleTypeDef* husb_pcd__) {}

void Disconnect_Callback(PCD_HandleTypeDef* husb_pcd__) {}

void DataOutStage_Callback(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__)
{
    // HAL_GPIO_WritePin(LED_Wio_E5_GPIO_Port, LED_Wio_E5_Pin, GPIO_PIN_SET);

    switch (epnum__) {
        case PCD_ENDP0:
            break;

        case PCD_ENDP1:
            break;
    }
}

void DataInStage_Callback(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__)
{
    switch (epnum__) {
        case PCD_ENDP0:
            break;

        case PCD_ENDP1:
            break;
    }
}

void Iso_OutIncomplete(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__) {}

void Iso_InIncomplete(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__) {}

}  // namespace stack
}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal

#ifdef HAL_PCD_MODULE_ENABLED

extern "C" {

void HAL_PCD_SOFCallback(PCD_HandleTypeDef* hpcd)
{
    maidui3_hal::Drivers::USB_PCD::stack::SOF_Callback(hpcd);
}

void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef* hpcd)
{
    maidui3_hal::Drivers::USB_PCD::stack::SetupStage_Callback(hpcd, hpcd->Setup);
}

void HAL_PCD_ResetCallback(PCD_HandleTypeDef* hpcd)
{
    maidui3_hal::Drivers::USB_PCD::stack::Reset_Callback(hpcd);
}

void HAL_PCD_SuspendCallback(PCD_HandleTypeDef* hpcd)
{
    maidui3_hal::Drivers::USB_PCD::stack::Suspend_Callback(hpcd);
}

void HAL_PCD_ResumeCallback(PCD_HandleTypeDef* hpcd)
{
    maidui3_hal::Drivers::USB_PCD::stack::Resume_Callback(hpcd);
}

void HAL_PCD_ConnectCallback(PCD_HandleTypeDef* hpcd)
{
    maidui3_hal::Drivers::USB_PCD::stack::Connect_Callback(hpcd);
}

void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef* hpcd)
{
    maidui3_hal::Drivers::USB_PCD::stack::Disconnect_Callback(hpcd);
}

void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum)
{
    maidui3_hal::Drivers::USB_PCD::stack::DataOutStage_Callback(hpcd, epnum);
}

void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum)
{
    maidui3_hal::Drivers::USB_PCD::stack::DataInStage_Callback(hpcd, epnum);
}

void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum)
{
    maidui3_hal::Drivers::USB_PCD::stack::Iso_OutIncomplete(hpcd, epnum);
}

void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum)
{
    maidui3_hal::Drivers::USB_PCD::stack::Iso_InIncomplete(hpcd, epnum);
}
}

#endif
