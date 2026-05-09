
#include "mXCAN_manager.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

#ifdef FDCAN1

bool xcan_management::xcan_init(xcan_setup_type* setup_)
{
#ifdef FDCAN1
    FDCAN_FilterTypeDef XCAN_filter;
#endif
#ifdef CAN1
    CAN_FilterTypeDef XCAN_filter;
#endif

    if (xcan_disable_timeout(setup_->hxcan_)) return 1;

    if (xcan_disable_tx_callback(setup_->hxcan_)) return 1;

    if (xcan_disable_rx_callback(setup_->hxcan_, setup_->fifo_)) return 1;

    if (xcan_disable_biginning(setup_->hxcan_)) return 1;

    if (setup_->fifo_ == fifo::FIFO0) {
        XCAN_filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    } else if (setup_->fifo_ == fifo::FIFO1) {
        XCAN_filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO1;
    } else {
    }

    if (setup_->frame_ == can_frame::Classic_CAN) {
        XCAN_filter.IdType = FDCAN_STANDARD_ID;
    } else if (setup_->frame_ == can_frame::FDCAN) {
        XCAN_filter.IdType = FDCAN_EXTENDED_ID;
    } else {
    }

    XCAN_filter.FilterType  = FDCAN_FILTER_MASK;
    XCAN_filter.FilterIndex = 0;
    XCAN_filter.FilterID1   = 0;
    XCAN_filter.FilterID2   = 0;

    if (HAL_FDCAN_ConfigFilter(setup_->hxcan_, &XCAN_filter)) return 1;

    if (setup_->rx_timeout_counter_ != 0) {
        if (xcan_enable_timeout(setup_->hxcan_, setup_->fifo_, setup_->rx_timeout_counter_)) return 1;
    }

    if (setup_->tx_callback_) {
        if (xcan_enable_tx_callback(setup_->hxcan_)) return 1;
    }

    if (xcan_enable_rx_callback(setup_->hxcan_, setup_->fifo_)) return 1;

    if (xcan_enable_beginning(setup_->hxcan_)) return 1;

    return 0;
}

uint8_t xcan_management::dlc_table(uint8_t len_)
{
    if (len_ >= FDCAN_DLC_BYTES_0 || len_ <= FDCAN_DLC_BYTES_8) return len_;

    if (len_ <= FDCAN_DLC_BYTES_12) return FDCAN_DLC_BYTES_12;
    if (len_ <= FDCAN_DLC_BYTES_16) return FDCAN_DLC_BYTES_16;
    if (len_ <= FDCAN_DLC_BYTES_20) return FDCAN_DLC_BYTES_20;
    if (len_ <= FDCAN_DLC_BYTES_24) return FDCAN_DLC_BYTES_24;
    if (len_ <= FDCAN_DLC_BYTES_32) return FDCAN_DLC_BYTES_32;
    if (len_ <= FDCAN_DLC_BYTES_48) return FDCAN_DLC_BYTES_48;

    return FDCAN_DLC_BYTES_64;
}

bool xcan_management::xcan_send(xcan_setup_type* setup_, hxcan_frame* frame_)
{
    if (HAL_FDCAN_GetTxFifoFreeLevel(setup_->hxcan_) == 0) return 1;

    XCAN_TxHeader.Identifier = frame_->id;

    if (setup_->frame_ == can_frame::Classic_CAN) {
        XCAN_TxHeader.IdType   = FDCAN_STANDARD_ID;
        XCAN_TxHeader.FDFormat = FDCAN_FD_CAN;
    } else if (setup_->frame_ == can_frame::FDCAN) {
        XCAN_TxHeader.IdType   = FDCAN_EXTENDED_ID;
        XCAN_TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
    } else {
    }

    XCAN_TxHeader.TxFrameType         = FDCAN_DATA_FRAME;
    XCAN_TxHeader.DataLength          = dlc_table(frame_->len);
    XCAN_TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    XCAN_TxHeader.BitRateSwitch       = FDCAN_BRS_OFF;

    if (setup_->tx_callback_) {
        XCAN_TxHeader.TxEventFifoControl = FDCAN_STORE_TX_EVENTS;
    } else {
        XCAN_TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    }

    XCAN_TxHeader.MessageMarker = 0;

    if (HAL_FDCAN_AddMessageToTxFifoQ(setup_->hxcan_, &XCAN_TxHeader, frame_->data_p)) return 1;

    return 0;
}

bool xcan_management::xcan_receive(FDCAN_HandleTypeDef* hxcan_, hxcan_frame* frame_)
{
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
        if (HAL_FDCAN_ActivateNotification(
                hxcan_, FDCAN_IT_RX_FIFO0_NEW_MESSAGE | FDCAN_IT_RX_FIFO0_FULL | FDCAN_IT_RX_FIFO0_MESSAGE_LOST, 0
            ))
            return 1;

    } else {
        if (HAL_FDCAN_ActivateNotification(
                hxcan_, FDCAN_IT_RX_FIFO1_NEW_MESSAGE | FDCAN_IT_RX_FIFO1_FULL | FDCAN_IT_RX_FIFO1_MESSAGE_LOST, 0
            ))
            return 1;
    }

    return 0;
}
bool xcan_management::xcan_disable_rx_callback(FDCAN_HandleTypeDef* hxcan_, fifo fifo_)
{
    if (fifo_ == fifo::FIFO0) {
        if (HAL_FDCAN_DeactivateNotification(
                hxcan_, FDCAN_IT_RX_FIFO0_NEW_MESSAGE | FDCAN_IT_RX_FIFO0_FULL | FDCAN_IT_RX_FIFO0_MESSAGE_LOST
            ))
            return 1;

    } else {
        if (HAL_FDCAN_DeactivateNotification(
                hxcan_, FDCAN_IT_RX_FIFO1_NEW_MESSAGE | FDCAN_IT_RX_FIFO1_FULL | FDCAN_IT_RX_FIFO1_MESSAGE_LOST
            ))
            return 1;
    }

    return 0;
}
#endif

#ifdef CAN1

bool xcan_management::xcan_send(hxcan_frame* frame_) {}

bool xcan_management::xcan_receive(hxcan_frame* frame_) {}

#endif

xcan_management xcan_manager;

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal

extern "C" {

#ifdef FDCAN1

#ifdef mXCAN_FIFO0_Callback
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef* hfdcan, uint32_t RxFifo0ITs)
{
    if (RxFifo0ITs == FDCAN_IT_RX_FIFO0_NEW_MESSAGE) {
        maidui3_hal::Drivers::XCAN::xcan_manager.xcan_callback(hfdcan);
    } else if (RxFifo0ITs == FDCAN_IT_RX_FIFO0_FULL) {
    } else if (RxFifo0ITs == FDCAN_IT_RX_FIFO0_MESSAGE_LOST) {
    } else {
    }
}
#endif

#ifdef mXCAN_FIFO1_Callback
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

#endif

#ifdef CAN1

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