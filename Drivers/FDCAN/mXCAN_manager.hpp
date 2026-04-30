
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

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

class xcan_management
{
private:
#ifdef FDCAN1 | FDCAN2 | FDCAN3
    FDCAN_TxHeaderTypeDef XCAN_TxHeader;
#endif
#ifdef CAN1 | CAN2 | CAN3
    CAN_TxHeaderTypeDef XCAN_TxHeader;
#endif

public:
    bool xcan_init(FDCAN_HandleTypeDef* hxcan_, fifo fifo_, can_frame frame);

    bool xcan_send(hxcan_frame* frame_);

    bool xcan_receive(hxcan_frame* frame_);

    bool xcan_callback(FDCAN_HandleTypeDef* hfdcan);

    bool xcan_enable_timeout(FDCAN_HandleTypeDef* hxcan_, fifo fifo_, uint32_t counter);
    bool xcan_disable_timeout(FDCAN_HandleTypeDef* hxcan_);

    bool xcan_enable_beginning(FDCAN_HandleTypeDef* hxcan_);
    bool xcan_disable_biginning(FDCAN_HandleTypeDef* hxcan_);

    bool xcan_enable_tx_callback(FDCAN_HandleTypeDef* hxcan_);
    bool xcan_disable_tx_callback(FDCAN_HandleTypeDef* hxcan_);

    bool xcan_enable_rx_callback(FDCAN_HandleTypeDef* hxcan_);
    bool xcan_disable_rx_callback(FDCAN_HandleTypeDef* hxcan_);
};

extern xcan_management xcan_manager;

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal
