
#include "mXCAN.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

bool xcan::init()
{
    if (setup_type.hxcan_ == NULL) return 1;

    if (xcan_manager.xcan_init(&setup_type)) return 1;

    return 0;
}

void xcan::set_Id(uint32_t id)
{
    static uint8_t counter  = 0;
    setup_type.Id_[counter] = id;
    ++counter;
    if (counter == 4) counter = 0;
}

void xcan::set_FDCAN_HandleTypedef(FDCAN_HandleTypeDef* hxcan)
{
    setup_type.hxcan_ = hxcan;
}

bool xcan::SendMessage(hxcan_frame* frame)
{
    if (frame->data_p == NULL) return 1;
    if (frame->len > max_len) return 1;
    if (frame->id > max_id) return 1;

    if (xcan_manager.xcan_send(&setup_type, frame, 0)) return 1;

    return 0;
}

bool xcan::GetMessage(hxcan_frame* frame)
{
    return 0;
}

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal
