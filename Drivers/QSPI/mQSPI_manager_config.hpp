
#pragma once
#include <cstdint>

#include "main.h"

#ifdef HAL_XSPI_MODULE_ENABLED
#include "octospi.h"

namespace maidui3_hal {
namespace Drivers {
namespace QSPI {

typedef struct {
} setup_config_HandleTypeDef;

}  // namespace QSPI
}  // namespace Drivers
}  // namespace maidui3_hal

#endif