
#pragma once
#include <cstdint>

#include "mQSPI_manager_config.hpp"
#include "main.h"

#ifdef HAL_XSPI_MODULE_ENABLED
#include "octospi.h"

namespace maidui3_hal {
namespace Drivers {
namespace QSPI {

class qspi_manager
{
public:
    bool init(setup_config_HandleTypeDef* setup_cpnf_, XSPI_HandleTypeDef* hxspi_);

    bool send(uint8_t* data_p_, uint32_t len_, XSPI_HandleTypeDef* hxspi_);

    bool getMessage(uint8_t* data_p_, uint32_t len_, XSPI_HandleTypeDef* hxspi_);
};

}  // namespace QSPI
}  // namespace Drivers

extern Drivers::QSPI::qspi_manager qspi_manager_;

}  // namespace maidui3_hal

#endif