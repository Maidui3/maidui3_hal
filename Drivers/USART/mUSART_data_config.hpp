
#pragma once

#include <cstdint>

namespace maidui3_hal {
namespace Drivers {
namespace USART {

enum class Mode : uint8_t {
    Normal,
    Exti,
    DMA,
};

}  // namespace USART
}  // namespace Drivers
}  // namespace maidui3_hal