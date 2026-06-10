
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
#define USB_SET_INTERFACE     (uint8_t)0x11U
#define USB_SYNCH_FRAME       (uint8_t)0x12U

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

struct USB_PCD_StackTypeDef {
    __IO PCD_HandleTypeDef* hpcd__ = NULL;
    __IO EP_BufferTypedef EP_Buffer[8];

    __IO bool is_Control_Stage__ = false;
    __IO bool is_Reseted         = false;
    // uint16_t frame_counter_      = {0};
};

}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal
