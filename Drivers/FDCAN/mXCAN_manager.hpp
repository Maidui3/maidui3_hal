
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
public:
#ifdef FDCAN1
#define XCAN_HandleTypeDef FDCAN_HandleTypeDef
    FDCAN_TxHeaderTypeDef XCAN_TxHeader;
    FDCAN_RxHeaderTypeDef XCAN_RxHeader;

    FDCAN_TxEventFifoTypeDef XCAN_TxEvent;
#endif

#ifdef CAN1
#define XCAN_HandleTypeDef CAN_HandleTypeDef
    CAN_TxHeaderTypeDef XCAN_TxHeader;
    CAN_RxHeaderTypeDef XCAN_RxHeader;

    CAN_TxEventFifoTypeDef XCAN_TxEvent;
#endif

private:
    uint8_t dlc_table(uint8_t len_);

    xcan_port_buffer* xcan_buffer[3];

    XCAN_HandleTypeDef* hxcanx_[3] = {NULL};

public:
    uint32_t* TxMessageMarker[3];

    uint8_t local_Rx_buffer[64];

    bool xcan_init(xcan_setup_type* setup_);

    uint32_t xcan_send(xcan_setup_type* setup_, hxcan_frame* frame_, uint32_t messagemarker_);

    void xcan_fifo0_callback(XCAN_HandleTypeDef* hxcan_);
    void xcan_fifo1_callback(XCAN_HandleTypeDef* hxcan_);

    void xcan_TxEvent_callback(XCAN_HandleTypeDef* hxcan_);

    bool xcan_set_timeout_counter(XCAN_HandleTypeDef* hxcan_, fifo fifo_, uint32_t counter_);
    bool xcan_enable_timeout(XCAN_HandleTypeDef* hxcan_);
    bool xcan_disable_timeout(XCAN_HandleTypeDef* hxcan_);

    bool xcan_enable_beginning(XCAN_HandleTypeDef* hxcan_);
    bool xcan_disable_biginning(XCAN_HandleTypeDef* hxcan_);

    bool xcan_enable_tx_callback(XCAN_HandleTypeDef* hxcan_);
    bool xcan_disable_tx_callback(XCAN_HandleTypeDef* hxcan_);

    bool xcan_enable_rx_callback(XCAN_HandleTypeDef* hxcan_, fifo fifo_);
    bool xcan_disable_rx_callback(XCAN_HandleTypeDef* hxcan_, fifo fifo_);
};

#ifdef HAL_FDCAN_MODULE_ENABLED
extern xcan_management xcan_manager;
#endif

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal
