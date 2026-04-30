
#include "mXCAN_manager.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

#ifdef FDCAN1 | FDCAN2 | FDCAN3

bool xcan_manager::xcan_send(hxcan_frame* frame_) {}

bool xcan_manager::xcan_callback(hxcan_frame* frame_) {}

#endif

#ifdef CAN1 | CAN2 | CAN3

bool xcan_manager::xcan_send(hxcan_frame* frame_) {}

bool xcan_manager::xcan_callback(hxcan_frame* frame_) {}

#endif

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal
