
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
#include "mXCAN_manager.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

class xcan
{
private:
    FDCAN_HandleTypeDef* hxcan_;
    fifo fifo_;
    can_frame frame_;

public:
    xcan(FDCAN_HandleTypeDef* _hxcan, can_frame _frame = can_frame::Classic_CAN, fifo _fifo = fifo::FIFO0) : hxcan_(_hxcan), fifo_(_fifo), frame_(_frame)
    {
        xcan_manager.xcan_init(hxcan_, fifo_, frame_);
    };

    bool init(receive_id_filter id_filter);

    bool SendMessage(hxcan_frame* frame);

    bool GetMessage(hxcan_frame* frame);
};

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal