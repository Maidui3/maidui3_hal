
#pragma once

#include <cstdint>

#include "fdcan.h"

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

enum class can_frame : bool {
    FDCAN,
    Classic_CAN,
};

enum class fifo : bool {
    FIFO0,
    FIFO1,
};

enum class id_filter_type : uint8_t {
    all_id,
    only_one_id,
    only_two_id,
    only_three_id,
    only_four_id,
    Non_id,
};

struct xcan_setup_type {
    FDCAN_HandleTypeDef* hxcan_  = NULL;
    fifo fifo_                   = fifo::FIFO0;
    can_frame frame_             = can_frame::Classic_CAN;
    id_filter_type filter_id_    = id_filter_type::Non_id;
    uint32_t rx_timeout_counter_ = {0};
    bool tx_callback_            = {0};
    uint32_t Id_[4]              = {0};
};

struct hxcan_frame {
    uint32_t id     = {0};
    uint8_t* data_p = NULL;
    uint8_t len     = {0};
};

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal
