
#pragma once

#include <cstdint>

#include "main.h"
#ifdef FDCAN1
#include "fdcan.h"
#endif
#ifdef CAN1
#include "can.h"
#endif

#include "mXCAN_data_template.hpp"

// #define mXCAN_FIFO0_Callback
#define mXCAN_FIFO1_Callback

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

class xcan_management
{
private:
    uint8_t dlc_table(uint8_t len_);

    uint8_t xcan1_Rx_buffer[4][64];  // hxcanx_[0]
    uint8_t xcan2_Rx_buffer[4][64];  // hxcanx_[1]
    uint8_t xcan3_Rx_buffer[4][64];  // hxcanx_[2]

    FDCAN_HandleTypeDef* hxcanx_[3];

    uint32_t xcan_id[3][4];

public:
#ifdef FDCAN1
    FDCAN_TxHeaderTypeDef XCAN_TxHeader;
    FDCAN_RxHeaderTypeDef XCAN_RxHeader;
#endif
#ifdef CAN1
    CAN_TxHeaderTypeDef XCAN_TxHeader;
    CAN_RxHeaderTypeDef XCAN_RxHeader;
#endif

    uint8_t local_Rx_buffer[64];

    bool xcan_init(xcan_setup_type* setup_);

    uint32_t xcan_send(xcan_setup_type* setup_, hxcan_frame* frame_, uint32_t messagemarker_);

    bool xcan_receive(FDCAN_HandleTypeDef* hxcan_, hxcan_frame* frame_);

    void xcan_callback(FDCAN_HandleTypeDef* hxcan_);

    bool xcan_set_timeout_counter(FDCAN_HandleTypeDef* hxcan_, fifo fifo_, uint32_t counter_);
    bool xcan_enable_timeout(FDCAN_HandleTypeDef* hxcan_);
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
