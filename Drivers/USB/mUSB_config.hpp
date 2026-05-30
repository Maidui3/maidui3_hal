
#pragma once
#include <cstdint>

#include "main.h"

#ifdef USB

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {

enum EP_Direction : uint8_t {
    IN  = 0x80,
    OUT = 0x00,
};

}
}  // namespace Drivers
}  // namespace maidui3_hal

#endif
