
#pragma once

#include "mUSB_Descriptor_Def.hpp"
#include "mUSB_stack_config.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {
namespace stack {

void get_descriptor(PCD_HandleTypeDef* husb_pcd__, Setup_Packet_t* packet);
bool get_deveice_descriptor(Device_Descriptor_t* buffer_, Setup_Packet_t* packet);
bool get_configuration_descriptor(Configuration_Descriptor_t* buffer_, Setup_Packet_t* packet);
bool get_interface_descriptor(Interface_Descriptor_t* buffer_, Setup_Packet_t* packet);
bool get_endpoint_descriptor(Endpoint_Descriptor_t* buffer_, Setup_Packet_t* packet);

}  // namespace stack
}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal