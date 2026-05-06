
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
    bool xcan_init(FDCAN_HandleTypeDef* hxcan_, fifo fifo_, can_frame frame_, receive_id_filter filter_id);

    bool xcan_set_id(uint32_t Id);

    bool xcan_send(FDCAN_HandleTypeDef* hxcan_, hxcan_frame* frame_);

    bool xcan_receive(FDCAN_HandleTypeDef* hxcan_, hxcan_frame* frame_);

    void xcan_callback(FDCAN_HandleTypeDef* hxcan_);

    bool xcan_enable_timeout(FDCAN_HandleTypeDef* hxcan_, fifo fifo_, uint32_t counter_);
    bool xcan_disable_timeout(FDCAN_HandleTypeDef* hxcan_);

    bool xcan_enable_beginning(FDCAN_HandleTypeDef* hxcan_);
    bool xcan_disable_biginning(FDCAN_HandleTypeDef* hxcan_);

    bool xcan_enable_tx_callback(FDCAN_HandleTypeDef* hxcan_);
    bool xcan_disable_tx_callback(FDCAN_HandleTypeDef* hxcan_);

    bool xcan_enable_rx_callback(FDCAN_HandleTypeDef* hxcan_, fifo fifo_);
    bool xcan_disable_rx_callback(FDCAN_HandleTypeDef* hxcan_, fifo fifo_);
};

extern xcan_management xcan_manager;

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal
