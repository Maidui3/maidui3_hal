
#include "mXCAN_manager.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

#ifdef FDCAN1 | FDCAN2 | FDCAN3

bool xcan_init(FDCAN_HandleTypeDef* hxcan_, fifo fifo_)
{
#ifdef FDCAN1 | FDCAN2 | FDCAN3
    FDCAN_FilterTypeDef XCAN_filter;
#endif
#ifdef CAN1 | CAN2 | CAN3
    CAN_FilterTypeDef XCAN_filter;
#endif

    if (fifo_ == fifo::FIFO0) {
        XCAN_filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    } else {
        XCAN_filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO1;
    }
    XCAN_filter.IdType      = FDCAN_STANDARD_ID;
    XCAN_filter.FilterIndex = 0;
    XCAN_filter.FilterType  = FDCAN_FILTER_MASK;
    XCAN_filter.FilterID1   = 0;
    XCAN_filter.FilterID2   = 0;
}

bool xcan_management::xcan_send(hxcan_frame* frame_) {}

bool xcan_management::xcan_receive(hxcan_frame* frame_)
{
#ifdef FDCAN1 | FDCAN2 | FDCAN3
    FDCAN_RxHeaderTypeDef XCAN_RxHeader;
#endif
#ifdef CAN1 | CAN2 | CAN3
    CAN_RxHeaderTypeDef XCAN_RxHeader;
#endif
}

bool xcan_callback(FDCAN_HandleTypeDef* hfdcan) {}

bool xcan_enable_timeout(FDCAN_HandleTypeDef* hxcan_, fifo fifo_, uint32_t counter) {}
bool xcan_disable_timeout(FDCAN_HandleTypeDef* hxcan_) {}

bool xcan_enable_beginning(FDCAN_HandleTypeDef* hxcan_) {}
bool xcan_disable_biginning(FDCAN_HandleTypeDef* hxcan_) {}

bool xcan_enable_tx_callback(FDCAN_HandleTypeDef* hxcan_) {}
bool xcan_disable_tx_callback(FDCAN_HandleTypeDef* hxcan_) {}

bool xcan_enable_rx_callback(FDCAN_HandleTypeDef* hxcan_) {}
bool xcan_disable_rx_callback(FDCAN_HandleTypeDef* hxcan_) {}
#endif

#ifdef CAN1 | CAN2 | CAN3

bool xcan_management::xcan_send(hxcan_frame* frame_) {}

bool xcan_management::xcan_receive(hxcan_frame* frame_) {}

#endif

xcan_management xcan_manager;

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal

extern "C" {

#ifdef FDCAN1 | FDCAN2 | FDCAN3

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef* hfdcan, uint32_t RxFifo0ITs)
{
    if (RxFifo0ITs == FDCAN_IT_RX_FIFO0_NEW_MESSAGE) {
        maidui3_hal::Drivers::XCAN::xcan_manager.xcan_callback(hfdcan);
    } else if (RxFifo0ITs == FDCAN_IT_RX_FIFO0_FULL) {
    } else if (RxFifo0ITs == FDCAN_IT_RX_FIFO0_MESSAGE_LOST) {
    } else {
    }
}
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef* hfdcan, uint32_t RxFifo1ITs)
{
    if (RxFifo1ITs == FDCAN_IT_RX_FIFO1_NEW_MESSAGE) {
        maidui3_hal::Drivers::XCAN::xcan_manager.xcan_callback(hfdcan);
    } else if (RxFifo1ITs == FDCAN_IT_RX_FIFO1_FULL) {
    } else if (RxFifo1ITs == FDCAN_IT_RX_FIFO1_MESSAGE_LOST) {
    } else {
    }
}

#endif

#ifdef CAN1 | CAN2 | CAN3

void HAL_CAN_RxFifo0Callback(CAN_HandleTypeDef* hcan, uint32_t RxFifo0ITs)
{
    if (RxFifo0ITs == CAN_IT_RX_FIFO0_NEW_MESSAGE) {
        maidui3_hal::Drivers::XCAN::xcan_manager.xcan_callback(hcan);
    } else if (RxFifo0ITs == CAN_IT_RX_FIFO0_FULL) {
    } else if (RxFifo0ITs == CAN_IT_RX_FIFO0_MESSAGE_LOST) {
    } else {
    }
}
void HAL_CAN_RxFifo1Callback(CAN_HandleTypeDef* hcan, uint32_t RxFifo1ITs)
{
    if (RxFifo1ITs == CAN_IT_RX_FIFO1_NEW_MESSAGE) {
        maidui3_hal::Drivers::XCAN::xcan_manager.xcan_callback(hfdcan);
    } else if (RxFifo1ITs == CAN_IT_RX_FIFO1_FULL) {
    } else if (RxFifo1ITs == CAN_IT_RX_FIFO1_MESSAGE_LOST) {
    } else {
    }
}

#endif
}