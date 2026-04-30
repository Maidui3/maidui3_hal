
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

struct hxcan_frame {
    uint32_t id       = {0};
    uint8_t* data_p   = NULL;
    uint8_t len       = {0};
    bus_mode bus_type = bus_mode::Normal_CAN;
};

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal