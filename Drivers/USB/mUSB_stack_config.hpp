
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

#define bmRequestType_Dir_MSK 0x80
#define bmRequestType_Dir_OUT 0x00
#define bmRequestType_Dir_IN  0x81

#define bmRequestType_Type_MSK      0x70
#define bmRequestType_Type_Standard 0x00
#define bmRequestType_Type_Class    0x71
#define bmRequestType_Type_Vendor   0x72

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
};

}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal
