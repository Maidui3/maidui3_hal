
#include "mXCAN_manager.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

#ifdef FDCAN1 | FDCAN2 | FDCAN3

bool xcan_management::xcan_init(FDCAN_HandleTypeDef* hxcan_, fifo fifo_, can_frame frame_, receive_id_filter filter_id)
{
#ifdef FDCAN1 | FDCAN2 | FDCAN3
    FDCAN_FilterTypeDef XCAN_filter;
#endif
#ifdef CAN1 | CAN2 | CAN3
    CAN_FilterTypeDef XCAN_filter;
#endif

    if (xcan_disable_timeout(hxcan_)) return 1;

    if (xcan_disable_tx_callback(hxcan_)) return 1;

    if (xcan_disable_rx_callback(hxcan_, fifo_)) return 1;

    if (xcan_disable_biginning(hxcan_)) return 1;

    if (fifo_ == fifo::FIFO0) {
        XCAN_filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    } else {
        XCAN_filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO1;
    }

    if (frame_ == can_frame::Classic_CAN) {
        XCAN_filter.IdType = FDCAN_STANDARD_ID;
    } else {
        XCAN_filter.IdType = FDCAN_EXTENDED_ID;
    }

    XCAN_filter.FilterType  = FDCAN_FILTER_MASK;
    XCAN_filter.FilterIndex = 0;
    XCAN_filter.FilterID1   = 0;
    XCAN_filter.FilterID2   = 0;

    if (HAL_FDCAN_ConfigFilter(hxcan_, &XCAN_filter)) return 1;

    if (xcan_enable_timeout(hxcan_, fifo_, 2000)) return 1;

    if (xcan_enable_tx_callback(hxcan_)) return 1;

    if (xcan_enable_rx_callback(hxcan_, fifo_)) return 1;

    if (xcan_enable_beginning(hxcan_)) return 1;

    return 0;
}

bool xcan_management::xcan_send(FDCAN_HandleTypeDef* hxcan_, hxcan_frame* frame_)
{
    return 0;
}

bool xcan_management::xcan_receive(FDCAN_HandleTypeDef* hxcan_, hxcan_frame* frame_)
{
#ifdef FDCAN1 | FDCAN2 | FDCAN3
    FDCAN_RxHeaderTypeDef XCAN_RxHeader;
#endif
#ifdef CAN1 | CAN2 | CAN3
    CAN_RxHeaderTypeDef XCAN_RxHeader;
#endif

    return 0;
}

void xcan_management::xcan_callback(FDCAN_HandleTypeDef* hxcan_) {}

bool xcan_management::xcan_enable_timeout(FDCAN_HandleTypeDef* hxcan_, fifo fifo_, uint32_t counter_)
{
    if (fifo_ == fifo::FIFO0) {
        if (HAL_FDCAN_ConfigTimeoutCounter(hxcan_, FDCAN_TIMEOUT_RX_FIFO0, counter_)) return 1;

    } else {
        if (HAL_FDCAN_ConfigTimeoutCounter(hxcan_, FDCAN_TIMEOUT_RX_FIFO1, counter_)) return 1;
    }

    if (HAL_FDCAN_ActivateNotification(hxcan_, FDCAN_IT_TIMEOUT_OCCURRED, 0)) return 1;

    if (HAL_FDCAN_EnableTimeoutCounter(hxcan_)) return 1;

    return 0;
}
bool xcan_management::xcan_disable_timeout(FDCAN_HandleTypeDef* hxcan_)
{
    if (HAL_FDCAN_DeactivateNotification(hxcan_, FDCAN_IT_TIMEOUT_OCCURRED)) return 1;

    if (HAL_FDCAN_DisableTimestampCounter(hxcan_)) return 1;

    return 0;
}

bool xcan_management::xcan_enable_beginning(FDCAN_HandleTypeDef* hxcan_)
{
    if (HAL_FDCAN_Start(hxcan_)) return 1;

    return 0;
}
bool xcan_management::xcan_disable_biginning(FDCAN_HandleTypeDef* hxcan_)
{
    if (HAL_FDCAN_Stop(hxcan_)) return 1;

    return 0;
}

bool xcan_management::xcan_enable_tx_callback(FDCAN_HandleTypeDef* hxcan_)
{
    if (HAL_FDCAN_ActivateNotification(hxcan_, FDCAN_IT_TX_COMPLETE, 0)) return 1;

    return 0;
}
bool xcan_management::xcan_disable_tx_callback(FDCAN_HandleTypeDef* hxcan_)
{
    if (HAL_FDCAN_DeactivateNotification(hxcan_, FDCAN_IT_TX_COMPLETE)) return 1;

    return 0;
}

bool xcan_management::xcan_enable_rx_callback(FDCAN_HandleTypeDef* hxcan_, fifo fifo_)
{
    if (fifo_ == fifo::FIFO0) {
        if (HAL_FDCAN_ActivateNotification(hxcan_, FDCAN_IT_RX_FIFO0_NEW_MESSAGE | FDCAN_IT_RX_FIFO0_FULL | FDCAN_IT_RX_FIFO0_MESSAGE_LOST, 0)) return 1;

    } else {
        if (HAL_FDCAN_ActivateNotification(hxcan_, FDCAN_IT_RX_FIFO1_NEW_MESSAGE | FDCAN_IT_RX_FIFO1_FULL | FDCAN_IT_RX_FIFO1_MESSAGE_LOST, 0)) return 1;
    }

    return 0;
}
bool xcan_management::xcan_disable_rx_callback(FDCAN_HandleTypeDef* hxcan_, fifo fifo_)
{
    if (fifo_ == fifo::FIFO0) {
        if (HAL_FDCAN_DeactivateNotification(hxcan_, FDCAN_IT_RX_FIFO0_NEW_MESSAGE | FDCAN_IT_RX_FIFO0_FULL | FDCAN_IT_RX_FIFO0_MESSAGE_LOST)) return 1;

    } else {
        if (HAL_FDCAN_DeactivateNotification(hxcan_, FDCAN_IT_RX_FIFO1_NEW_MESSAGE | FDCAN_IT_RX_FIFO1_FULL | FDCAN_IT_RX_FIFO1_MESSAGE_LOST)) return 1;
    }

    return 0;
}
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