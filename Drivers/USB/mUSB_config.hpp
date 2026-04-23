
#pragma once
#include <cstdint>

namespace maidui3_hal {
namespace Drivers {
namespace USB {

enum class EP_Direction : uint8_t {
    IN  = 0x00,
    OUT = 0x80,
};

}
}  // namespace Drivers
}  // namespace maidui3_hal
