
#pragma once
#include <cstdint>

#include "main.h"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {

#define PCD_EP_OUT 0x00U
#define PCD_EP_IN  0x80U

#define PCD_Control_mps 64U

#define PCD_Default_mps 2048U

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
#define USB_Enable_RemotoWakeup  (uint8_t)0x01U

enum Request_class_e : uint8_t {
    CDC_class,
    HID_class,
};

struct Setup_Packet_t {
    __IO uint8_t bmRequestType;
    __IO uint8_t bRequest;
    __IO uint16_t wValue;
    __IO uint16_t wIndex;
    __IO uint16_t wLength;
};

/**/

struct BufferTypeDef {
    uint8_t* Buffer_p_         = NULL;
    __IO uint16_t Buffer_Size_ = {0};
    uint16_t Max_Buffer_Size_  = {0};
};

struct EP_BufferTypedef {
    BufferTypeDef Transfer__;
    BufferTypeDef Receive__;
};

enum class Transmission_speed : bool {
    Full_Speed,
    High_Speed,
};

struct Control_transmit_manageTypeDef {
    bool is_device_get_descripting = {0};
    uint8_t max_buffer_size        = {0};
    uint8_t max_transmit_length    = {0};
    uint8_t buffer_bace_addr       = {0};
};

struct USB_PCD_Stack_t {
    __IO EP_BufferTypedef EP_Buffer[8];

    Control_transmit_manageTypeDef control_transmit;
};

struct Device_Status_t {
    uint8_t SelfPower    : 1;
    uint8_t RemoteWakeup : 1;
    uint16_t unused      : 14;
};

enum Request_Bace_Class {
    CDC,
    HID,
};

}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal
