
#include "mQSPI_manager.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace QSPI {

bool qspi_manager::init(setup_config_HandleTypeDef* setup_cpnf_, XSPI_HandleTypeDef* hxspi_)
{
    return 0;
}

bool qspi_manager::send(uint8_t* data_p_, uint32_t len_, XSPI_HandleTypeDef* hxspi_)
{
    return 0;
}

bool qspi_manager::getMessage(uint8_t* data_p_, uint32_t len_, XSPI_HandleTypeDef* hxspi_)
{
    return 0;
}

qspi_manager manager_;
}  // namespace QSPI
}  // namespace Drivers

Drivers::QSPI::qspi_manager qspi_manager_;

}  // namespace maidui3_hal