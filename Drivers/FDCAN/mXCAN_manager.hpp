
#pragma once

#include <cstdint>

#include "main.h"
#ifdef FDCAN1 | FDCAN2 | FDCAN3
#include "fdcan.h"
#endif
#ifdef CAN1 | CAN2 | CAN3
#include "can.h"
#endif

#include "mXCAN_data_template.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

class xcan_manager
{
public:
    bool xcan_send(hxcan_frame* frame_);

    bool xcan_callback(hxcan_frame* frame_);
};

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal
