
#pragma once

#include <cstdint>

#include "mUSB_stack_config.hpp"
#include "main.h"
#include "usb.h"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {

class usb_stack
{
private:
    bool transfer_();

    void Clear_Byte(uint8_t* buf, uint8_t len);

    __IO USB_PCD_StackTypeDef USB_PCD_FS;
    __IO USB_PCD_StackTypeDef USB_PCD_HS;

    union {
        uint8_t buffer[PCD_Control_mps];
        Device_StatusTypeDef Deveice_Status;
        Device_DescriptorTypeDef Device_Descriptor;
        Configuration_DescriptorTypeDef Configuration_Descriptor;
        Interface_DescriptorTypeDef Interface_Descriptor;
        Endpoint_DescriptorTypeDef Endpoint_Descriptor;
    } Tx_Control_Buffer;

    union {
        uint8_t buffer[PCD_Control_mps];
    } Rx_Control_Buffer;

public:
    bool Init(PCD_HandleTypeDef* husb_pcd_, Transmission_speed speed_);

    bool transfer();

    bool receive();

    bool stop(PCD_HandleTypeDef* husb_pcd_);

public:
    void SOF_Callback(PCD_HandleTypeDef* husb_pcd__);

    void SetupStage_Callback(PCD_HandleTypeDef* husb_pcd__, uint32_t* setup__);

    void Reset_Callback(PCD_HandleTypeDef* husb_pcd__);

    void Suspend_Callback(PCD_HandleTypeDef* husb_pcd__);

    void Resume_Callback(PCD_HandleTypeDef* husb_pcd__);

    void Connect_Callback(PCD_HandleTypeDef* husb_pcd__);

    void Disconnect_Callback(PCD_HandleTypeDef* husb_pcd__);

    void DataOutStage_Callback(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__);

    void DataInStage_Callback(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__);

    void Iso_OutIncomplete(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__);

    void Iso_InIncomplete(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__);
};

}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal

#ifdef HAL_PCD_MODULE_ENABLED

extern maidui3_hal::Drivers::USB_PCD::usb_stack _USB_Stack_;

#endif
