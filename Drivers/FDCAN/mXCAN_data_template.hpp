
#pragma once

#include <cstdint>

#include "fdcan.h"

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

enum class bus_mode : bool {
    FDCAN,
    Normal_CAN,
};

enum class fifo : bool {
    FIFO0,
    FIFO1,
};

enum class receive_id_filter : uint8_t {
    all_id,
    only_one_id,
    only_two_id,
    only_three_id,
    only_four_id,
};

struct hxcan_frame {
    uint32_t id       = {0};
    uint8_t* data_p   = NULL;
    uint8_t len       = {0};
    bus_mode bus_type = bus_mode::Normal_CAN;
};

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal