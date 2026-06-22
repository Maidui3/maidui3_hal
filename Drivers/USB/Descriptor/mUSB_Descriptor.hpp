
#pragma once

#include "mUSB_Descriptor_Def.hpp"
#include "stm32g4xx_hal_pcd.h"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {
namespace USB_Descriptor {

class usb_descriptor
{
protected:
    bool get_deveice_descriptor(PCD_HandleTypeDef* husb_pcd__, Device_DescriptorTypeDef* buffer_);

    bool get_configuration_descriptor(PCD_HandleTypeDef* husb_pcd__, Configuration_DescriptorTypeDef* buffer_);

    bool get_interface_descriptor(PCD_HandleTypeDef* husb_pcd__, Interface_DescriptorTypeDef* buffer_);

    bool get_endpoint_descriptor(PCD_HandleTypeDef* husb_pcd__, Endpoint_DescriptorTypeDef* buffer_);
};

}  // namespace USB_Descriptor
}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal