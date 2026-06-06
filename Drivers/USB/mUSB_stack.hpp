
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

public:
    bool Init();

    bool transfer();

    bool receive();

    bool stop();

public:
    void SOF_Callback(PCD_HandleTypeDef* husb_pcd__);

    void SetupStage_Callback(PCD_HandleTypeDef* husb_pcd__);

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
