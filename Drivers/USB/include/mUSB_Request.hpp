
#pragma once

#include <cstdint>

#include "mUSB_stack.hpp"
#include "mUSB_stack_config.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {
namespace stack {

void Host_Dir_Device_Request(PCD_HandleTypeDef* husb_pcd__, Setup_Packet_t* packet);
void Host_Dir_Interface_Request(PCD_HandleTypeDef* husb_pcd__, Setup_Packet_t* packet);
void Host_Dir_Endpoint_Request(PCD_HandleTypeDef* husb_pcd__, Setup_Packet_t* packet);
void Host_Dir_Other_Request(PCD_HandleTypeDef* husb_pcd__, Setup_Packet_t* packet);

}  // namespace stack
}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal