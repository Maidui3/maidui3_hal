
#pragma once
#include <cstdint>

#include "main.h"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {

#define PCD_EP_OUT 0x00U
#define PCD_EP_IN  0x80U

#define PCD_Control_mps 64U

#define PCD_Default_mps 2047U

#define bmRequestType_Dir_MSK (uint8_t)0x80U
#define bmRequestType_Dir_OUT (uint8_t)0x00U
#define bmRequestType_Dir_IN  (uint8_t)0x80U

#define bmRequestType_Type_MSK      (uint8_t)0x60U
#define bmRequestType_Type_Standard (uint8_t)0x00U
#define bmRequestType_Type_Class    (uint8_t)0x61U
#define bmRequestType_Type_Vendor   (uint8_t)0x62U

#define bmRequestType_Reci_MSK       (uint8_t)0x1FU
#define bmRequestType_Reci_Device    (uint8_t)0x00U
#define bmRequestType_Reci_Interface (uint8_t)0x01U
#define bmRequestType_Reci_Endpoint  (uint8_t)0x02U
#define bmRequestType_Reci_Other     (uint8_t)0x03U

#define USB_GET_STATUS        (uint8_t)0x00U
#define USB_CLEAR_FEATURE     (uint8_t)0x01U
#define USB_SET_FEATURE       (uint8_t)0x03U
#define USB_SET_ADDRESS       (uint8_t)0x05U
#define USB_GET_DESCRIPTOR    (uint8_t)0x06U
#define USB_SET_DESCRIPTOR    (uint8_t)0x07U
#define USB_GET_CONFIGURATION (uint8_t)0x08U
#define USB_SET_CONFIGURATION (uint8_t)0x09U
#define USB_GET_INTERFACE     (uint8_t)0x0AU
#define USB_SET_INTERFACE     (uint8_t)0x0BU
#define USB_SYNCH_FRAME       (uint8_t)0x0CU
// #define USB_SET_SEL           (uint8_t)0x30U
// #define USB_ISOCH_DELAY       (uint8_t)0x31U

#define USB_Device                   (uint8_t)0x01U
#define USB_Configuration            (uint8_t)0x02U
#define USB_String                   (uint8_t)0x03U
#define USB_Interface                (uint8_t)0x04U
#define USB_Endpoint                 (uint8_t)0x05U
#define USB_DeviceQualifier          (uint8_t)0x06U
#define USB_Other_SpeedConfiguration (uint8_t)0x07U
#define USB_InterfacePower           (uint8_t)0x08U
#define USB_On_The_Go                (uint8_t)0x09U

#define USB_BusPower  (uint8_t)0x00U
#define USB_SelfPower (uint8_t)0x01U

#define USB_Disable_RemotoWakeup (uint8_t)0x00U
#define USB_Enable_RemotoWakeup  (uint8_t)0x02U

#define USB_bLength_18 (uint8_t)0x12U
#define USB_bLength_9  (uint8_t)0x09U
#define USB_bLength_7  (uint8_t)0x07U

#define USB_bDescriptorTypes_DEVEICE                   (uint8_t)0x01U
#define USB_bDescriptorTypes_CONFIGURATION             (uint8_t)0x02U
#define USB_bDescriptorTypes_STRING                    (uint8_t)0x03U
#define USB_bDescriptorTypes_INTERFACE                 (uint8_t)0x04U
#define USB_bDescriptorTypes_ENDPOINT                  (uint8_t)0x05U
#define USB_bDescriptorTypes_DEVICE_QUALIFIER          (uint8_t)0x06U
#define USB_bDescriptorTypes_OTHER_SPEED_CONFIGURATION (uint8_t)0x07U
#define USB_bDescriptorTypes_INTERFACE_POWER           (uint8_t)0x08U

#define USB_bcdUSB_USB10 (uint16_t)0x0100  // USB1.0
#define USB_bcdUSB_USB11 (uint16_t)0x0110  // USB1.1
#define USB_bcdUSB_USB20 (uint16_t)0x0200  // USB2.0

#define USB_bDeviceClass_writeInterfaceClass (uint8_t)0x00U
#define USB_bDeviceClass_Communication       (uint8_t)0x02U
#define USB_bDeviceClass_Hub                 (uint8_t)0x09U
#define USB_bDeviceClass_DiagnosticDevice    (uint8_t)0xDCU
#define USB_bDeviceClass_Wireless            (uint8_t)0xE0U
#define USB_bDeviceClass_MiscDeveice         (uint8_t)0xEFU
#define USB_bDeviceClass_Vendor              (uint8_t)0xFFU

#define USB_bDeviceSubClass_00 (uint8_t)0x00U
#define USB_bDeviceSubClass_FF (uint8_t)0xFFU

#define USB_bDeviceProtocol_00 (uint8_t)0x00U
#define USB_bDeviceProtocol_FF (uint8_t)0xFFU

#define USB_bMaxPacketSizeEP0_8  (uint8_t)0x08U
#define USB_bMaxPacketSizeEP0_16 (uint8_t)0x10U
#define USB_bMaxPacketSizeEP0_32 (uint8_t)0x20U
#define USB_bMaxPacketSizeEP0_64 (uint8_t)0x40U

#define USB_bInterfaceClass_Audio            (uint8_t)0x01U
#define USB_bInterfaceClass_CDC_Control      (uint8_t)0x02U
#define USB_bInterfaceClass_HID              (uint8_t)0x03U
#define USB_bInterfaceClass_Physical         (uint8_t)0x05U
#define USB_bInterfaceClass_Image            (uint8_t)0x06U
#define USB_bInterfaceClass_Printer          (uint8_t)0x07U
#define USB_bInterfaceClass_Mass_Storage     (uint8_t)0x08U
#define USB_bInterfaceClass_HUB              (uint8_t)0x09U
#define USB_bInterfaceClass_CDC_Data         (uint8_t)0x0AU
#define USB_bInterfaceClass_Chip_SmartCard   (uint8_t)0x0BU
#define USB_bInterfaceClass_Content_Security (uint8_t)0x0DU
#define USB_bInterfaceClass_Video            (uint8_t)0x0EU
#define USB_bInterfaceClass_DiagnosticDevice (uint8_t)0xDCU
#define USB_bInterfaceClass_Wireless         (uint8_t)0xE0U
#define USB_bInterfaceClass_App_Specific     (uint8_t)0xEFU
#define USB_bInterfaceClass_Vendor           (uint8_t)0xFFU

/**/

struct BufferTypeDef {
    __IO uint8_t* Buffer_p_        = NULL;
    __IO uint16_t Buffer_Size_     = {0};
    __IO uint16_t Max_Buffer_Size_ = {0};
};

struct EP_BufferTypedef {
    __IO BufferTypeDef Transfer__;
    __IO BufferTypeDef Receive__;
};

enum class Transmission_speed : bool {
    Full_Speed,
    High_Speed,
};

struct Control_transmit_manageTypeDef {
    __IO bool is_descripting   = {0};
    __IO uint8_t rest_transmit = {0};
};

struct USB_PCD_StackTypeDef {
    __IO PCD_HandleTypeDef* hpcd__ = NULL;
    __IO EP_BufferTypedef EP_Buffer[8];

    __IO bool is_Control_Stage__ = false;
    __IO bool is_Reseted         = false;
    __IO Control_transmit_manageTypeDef control_transmit;
};

}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal
