
#include "mUSB_stack.hpp"

#include "stdlib.h"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {

bool usb_stack::transfer_()
{
    return 0;
}

void usb_stack::Clear_Byte(uint8_t* buf, uint8_t len)
{
    for (uint8_t i = 0; i < len; i++) {
        *(buf + i) = 0;
    }

    return;
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

    // 0000 0010 0000 0000
}

void usb_stack::SetupStage_Callback(PCD_HandleTypeDef* husb_pcd__, uint32_t* setup__)
{
    /**
     * 1Byte : bmRequestType
     * 1Byte : bRequest
     * 2Byte : wValue
     * 2Byte : wIndex
     * 2Byte : wLength
     */

    static uint8_t bmRequestType;
    static uint8_t bRequest;
    static uint16_t wValue;
    static uint16_t wIndex;
    static uint16_t wLength;

    bmRequestType = (uint8_t)(*setup__);
    bRequest      = (uint8_t)((*setup__ & 0xFF00) >> 8);
    wValue        = (uint16_t)((*setup__ & 0xFFFF0000) >> 16);
    wIndex        = (uint16_t)(*(setup__ + 1) & 0xFFFF);
    wLength       = (uint16_t)((*(setup__ + 1) & 0xFFFF0000) >> 16);

    static __IO USB_PCD_StackTypeDef* USB_PCD_XX;

    if (USB_PCD_FS.hpcd__ == husb_pcd__) {
        USB_PCD_XX = &USB_PCD_FS;
    } else {
        USB_PCD_XX = &USB_PCD_HS;
    }

    if (bmRequestType & bmRequestType_Dir_MSK) {
        // Device -> Host
        // bit7 is 1

        switch (bmRequestType & bmRequestType_Type_MSK) {
            case bmRequestType_Type_Standard:

                switch (bmRequestType & bmRequestType_Reci_MSK) {
                    case bmRequestType_Reci_Device:

                        switch (bRequest) {
                            case USB_GET_STATUS:

                                Clear_Byte(Tx_Control_Buffer.buffer, 0x02);

                                Tx_Control_Buffer.Deveice_Status.SelfPower    = USB_BusPower;
                                Tx_Control_Buffer.Deveice_Status.RemoteWakeup = USB_Disable_RemotoWakeup;

                                HAL_PCD_EP_Transmit(husb_pcd__, PCD_ENDP0, Tx_Control_Buffer.buffer, 0x02);

                                break;

                            case USB_GET_DESCRIPTOR:

                                USB_PCD_XX->control_transmit.is_device_get_descripting = true;

                                switch (wValue >> 8) {
                                    case USB_Device:

                                        Clear_Byte(Tx_Control_Buffer.buffer, 0x12);

                                        Tx_Control_Buffer.Device_Descriptor.bLength            = USB_bLength_18;
                                        Tx_Control_Buffer.Device_Descriptor.bDescriptorType    = USB_bDescriptorTypes_DEVEICE;
                                        Tx_Control_Buffer.Device_Descriptor.bcdUSB             = USB_bcdUSB_USB20;
                                        Tx_Control_Buffer.Device_Descriptor.bDeviceClass       = USB_bDeviceClass_writeInterfaceClass;
                                        Tx_Control_Buffer.Device_Descriptor.bDeviceSubClass    = USB_bDeviceSubClass_writeInterfaceClass;
                                        Tx_Control_Buffer.Device_Descriptor.bDeviceProtocol    = USB_bDeviceProtocol_writeInterfaceClass;
                                        Tx_Control_Buffer.Device_Descriptor.bMaxPacketSize0    = USB_bMaxPacketSizeEP0_8;
                                        Tx_Control_Buffer.Device_Descriptor.idVendor           = 0x0403;
                                        Tx_Control_Buffer.Device_Descriptor.idProduct          = 0x6015;
                                        Tx_Control_Buffer.Device_Descriptor.bcdDevice          = 0x1000;
                                        Tx_Control_Buffer.Device_Descriptor.iManufacturer      = 0x01;
                                        Tx_Control_Buffer.Device_Descriptor.iProduct           = 0x02;
                                        Tx_Control_Buffer.Device_Descriptor.iSerialNumber      = 0x03;
                                        Tx_Control_Buffer.Device_Descriptor.bNumConfigurations = 0x01;

                                        HAL_PCD_EP_Transmit(husb_pcd__, PCD_ENDP0, Tx_Control_Buffer.buffer, 0x12);

                                        HAL_PCD_EP_Receive(husb_pcd__, PCD_ENDP0, Rx_Control_Buffer.buffer, 0x00);

                                        HAL_GPIO_WritePin(LED_W5500_GPIO_Port, LED_W5500_Pin, GPIO_PIN_SET);

                                        break;

                                    case USB_Configuration:

                                        Clear_Byte(Tx_Control_Buffer.buffer, 0x09);

                                        Tx_Control_Buffer.Configuration_Descriptor.bLength         = USB_bLength_9;
                                        Tx_Control_Buffer.Configuration_Descriptor.bDescriptorType = USB_bDescriptorTypes_CONFIGURATION;
                                        Tx_Control_Buffer.Configuration_Descriptor.wTotalLength;
                                        Tx_Control_Buffer.Configuration_Descriptor.bNumInterface;
                                        Tx_Control_Buffer.Configuration_Descriptor.bConfigurationValue;
                                        Tx_Control_Buffer.Configuration_Descriptor.iConfiguration;
                                        Tx_Control_Buffer.Configuration_Descriptor.bmAttributes;
                                        Tx_Control_Buffer.Configuration_Descriptor.bMaxPower;

                                        HAL_PCD_EP_Transmit(husb_pcd__, PCD_ENDP0, Tx_Control_Buffer.buffer, 0x09);

                                        HAL_PCD_EP_Receive(husb_pcd__, PCD_ENDP0, Rx_Control_Buffer.buffer, 0x00);

                                        break;

                                    case USB_Interface:

                                        Clear_Byte(Tx_Control_Buffer.buffer, 0x09);

                                        Tx_Control_Buffer.Interface_Descriptor.bLength         = USB_bLength_9;
                                        Tx_Control_Buffer.Interface_Descriptor.bDescriptorType = USB_bDescriptorTypes_INTERFACE;
                                        Tx_Control_Buffer.Interface_Descriptor.bInterfaceNumber;
                                        Tx_Control_Buffer.Interface_Descriptor.bAlternateSetting;
                                        Tx_Control_Buffer.Interface_Descriptor.bNumEndpoints;
                                        Tx_Control_Buffer.Interface_Descriptor.bInterfaceClass;
                                        Tx_Control_Buffer.Interface_Descriptor.bInterfaceSubClass;
                                        Tx_Control_Buffer.Interface_Descriptor.bInterfaceProtocol;
                                        Tx_Control_Buffer.Interface_Descriptor.iInterface;

                                        HAL_PCD_EP_Transmit(husb_pcd__, PCD_ENDP0, Tx_Control_Buffer.buffer, 0x09);

                                        break;

                                    case USB_Endpoint:

                                        Clear_Byte(Tx_Control_Buffer.buffer, 0x07);

                                        Tx_Control_Buffer.Endpoint_Descriptor.bLength         = USB_bLength_7;
                                        Tx_Control_Buffer.Endpoint_Descriptor.bDescriptorType = USB_bDescriptorTypes_ENDPOINT;
                                        Tx_Control_Buffer.Endpoint_Descriptor.bEndpointAddress;
                                        Tx_Control_Buffer.Endpoint_Descriptor.bmAttributes;
                                        Tx_Control_Buffer.Endpoint_Descriptor.wMaxPacketSize;
                                        Tx_Control_Buffer.Endpoint_Descriptor.bInterval;

                                        HAL_PCD_EP_Transmit(husb_pcd__, PCD_ENDP0, Tx_Control_Buffer.buffer, 0x07);

                                        break;

                                    case USB_String:
                                        break;

                                    case USB_DeviceQualifier:
                                        break;

                                    case USB_Other_SpeedConfiguration:
                                        break;
                                }

                                break;

                            case USB_GET_CONFIGURATION:
                                break;
                        }
                        break;

                    case bmRequestType_Reci_Interface:

                        switch (bRequest) {
                            case USB_GET_STATUS:
                                break;

                            case USB_GET_INTERFACE:
                                break;
                        }
                        break;

                    case bmRequestType_Reci_Endpoint:
                        switch (bRequest) {
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

    return;
}

void usb_stack::Reset_Callback(PCD_HandleTypeDef* husb_pcd__)
{
    HAL_PCD_EP_Open(husb_pcd__, (PCD_ENDP0 | PCD_EP_OUT), PCD_Control_mps, EP_TYPE_CTRL);
    HAL_PCD_EP_Open(husb_pcd__, (PCD_ENDP0 | PCD_EP_IN), PCD_Control_mps, EP_TYPE_CTRL);
}

void usb_stack::Suspend_Callback(PCD_HandleTypeDef* husb_pcd__) {}

void usb_stack::Resume_Callback(PCD_HandleTypeDef* husb_pcd__) {}

void usb_stack::Connect_Callback(PCD_HandleTypeDef* husb_pcd__) {}

void usb_stack::Disconnect_Callback(PCD_HandleTypeDef* husb_pcd__) {}

void usb_stack::DataOutStage_Callback(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__)
{
    static __IO USB_PCD_StackTypeDef* USB_PCD_XX;

    if (USB_PCD_FS.hpcd__ == husb_pcd__) {
        USB_PCD_XX = &USB_PCD_FS;
    } else {
        USB_PCD_XX = &USB_PCD_HS;
    }

    // HAL_GPIO_WritePin(LED_Wio_E5_GPIO_Port, LED_Wio_E5_Pin, GPIO_PIN_SET);

    switch (epnum__) {
        case PCD_ENDP0:
            break;

        case PCD_ENDP1:
            break;
    }
}

void usb_stack::DataInStage_Callback(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__)
{
    static __IO USB_PCD_StackTypeDef* USB_PCD_XX;

    if (USB_PCD_FS.hpcd__ == husb_pcd__) {
        USB_PCD_XX = &USB_PCD_FS;
    } else {
        USB_PCD_XX = &USB_PCD_HS;
    }

    switch (epnum__) {
        case PCD_ENDP0:
            break;

        case PCD_ENDP1:
            break;
    }
}

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
    _USB_Stack_.SetupStage_Callback(hpcd, hpcd->Setup);
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
