
#include "mXCAN_manager.hpp"

#define maidui3_xcan maidui3_hal::Drivers::XCAN

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

bool xcan_management::xcan_init(xcan_setup_type* setup_)
{
#ifdef FDCAN1
    FDCAN_FilterTypeDef XCAN_filter;
#endif
#ifdef CAN1
    CAN_FilterTypeDef XCAN_filter;
#endif

    static uint8_t numbering_num_ = 0;

    if (numbering_num_ >= 3) return 1;

    numbering_num_++;
    setup_->bus_numbering_ = numbering_num_ << 6;

    hxcanx_[numbering_num_] = setup_->hxcan_;

    xcan_buffer[numbering_num_] = setup_->buffer;

    TxMessageMarker[numbering_num_] = &setup_->TxMessageMarker;

    if (setup_->hxcan_->Init.FrameFormat == FDCAN_FRAME_CLASSIC) {
        XCAN_filter.IdType = FDCAN_STANDARD_ID;

    } else if ((setup_->hxcan_->Init.FrameFormat == FDCAN_FRAME_FD_BRS) || (setup_->hxcan_->Init.FrameFormat == FDCAN_FRAME_FD_NO_BRS)) {
        XCAN_filter.IdType = FDCAN_EXTENDED_ID;

    } else {
    }

    if (setup_->fifo_ == fifo::FIFO0) {
        XCAN_filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;

    } else if (setup_->fifo_ == fifo::FIFO1) {
        XCAN_filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO1;

    } else {
    }

    XCAN_filter.FilterType = FDCAN_FILTER_MASK;

    if (setup_->filter_id_ == id_filter_type::Non_mask_id) {
        XCAN_filter.FilterIndex = 0;
        XCAN_filter.FilterID1   = 0;
        XCAN_filter.FilterID2   = 0;

        if (HAL_FDCAN_ConfigFilter(setup_->hxcan_, &XCAN_filter)) return 1;
    } else if (
        (static_cast<uint8_t>(setup_->filter_id_) >= static_cast<uint8_t>(id_filter_type::mask_one_id)) &&
        (static_cast<uint8_t>(setup_->filter_id_) <= static_cast<uint8_t>(id_filter_type::mask_four_id))
    ) {
        for (uint8_t i = 0; i < static_cast<uint8_t>(setup_->filter_id_); i++) {
            XCAN_filter.FilterIndex = i;
            XCAN_filter.FilterID1   = setup_->Id_[i];
            XCAN_filter.FilterID2   = setup_->Id_mask;

            if (HAL_FDCAN_ConfigFilter(setup_->hxcan_, &XCAN_filter)) return 1;
        }
    }

    if (setup_->rx_timeout_counter_ != 0) {
        if (xcan_set_timeout_counter(setup_->hxcan_, setup_->fifo_, setup_->rx_timeout_counter_)) return 1;
    }

    if (xcan_enable_beginning(setup_->hxcan_)) return 1;

    if (setup_->rx_timeout_counter_ != 0) {
        if (xcan_enable_timeout(setup_->hxcan_)) return 1;
    }

    if (setup_->tx_callback_) {
        if (xcan_enable_tx_callback(setup_->hxcan_)) return 1;
    }

    if (xcan_enable_rx_callback(setup_->hxcan_, setup_->fifo_)) return 1;

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

uint32_t xcan_management::xcan_send(xcan_setup_type* setup_, hxcan_frame* frame_, uint32_t messagemarker_)
{
    if (HAL_FDCAN_GetTxFifoFreeLevel(setup_->hxcan_) == 0) return 1;

    XCAN_TxHeader.Identifier = frame_->id_;

    if (setup_->hxcan_->Init.FrameFormat == FDCAN_FRAME_CLASSIC) {
        XCAN_TxHeader.IdType   = FDCAN_STANDARD_ID;
        XCAN_TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
    } else if ((setup_->hxcan_->Init.FrameFormat == FDCAN_FRAME_FD_BRS) || (setup_->hxcan_->Init.FrameFormat == FDCAN_FRAME_FD_NO_BRS)) {
        XCAN_TxHeader.IdType   = FDCAN_EXTENDED_ID;
        XCAN_TxHeader.FDFormat = FDCAN_FD_CAN;

    } else {
    }

    XCAN_TxHeader.TxFrameType         = FDCAN_DATA_FRAME;
    XCAN_TxHeader.DataLength          = dlc_table(frame_->len_);
    XCAN_TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    XCAN_TxHeader.BitRateSwitch       = FDCAN_BRS_OFF;

    if (setup_->tx_callback_) {
        XCAN_TxHeader.TxEventFifoControl = FDCAN_STORE_TX_EVENTS;
    } else {
        XCAN_TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    }

    XCAN_TxHeader.MessageMarker = setup_->bus_numbering_ | messagemarker_;

    if (HAL_FDCAN_AddMessageToTxFifoQ(setup_->hxcan_, &XCAN_TxHeader, frame_->data_p_)) return 1;

    return 0;
}

void xcan_management::xcan_fifo0_callback(XCAN_HandleTypeDef* hxcan_)
{
    if (hxcan_ == hxcanx_[0]) {
        xcan_buffer[0]->id_buffer_[XCAN_RxHeader.FilterIndex].id_  = XCAN_RxHeader.Identifier;
        xcan_buffer[0]->id_buffer_[XCAN_RxHeader.FilterIndex].len_ = XCAN_RxHeader.DataLength;

        for (uint8_t i = 0; i < XCAN_RxHeader.DataLength; i++) {
            xcan_buffer[0]->id_buffer_[XCAN_RxHeader.FilterIndex].buffer_[i] = local_Rx_buffer[i];
        }

        xcan_buffer[0]->nvic_.Rx_Callback                   = 1;
        xcan_buffer[0]->nvic_.Id[XCAN_RxHeader.FilterIndex] = 1;

    } else if (hxcan_ == hxcanx_[1]) {
        xcan_buffer[1]->id_buffer_[XCAN_RxHeader.FilterIndex].id_  = XCAN_RxHeader.Identifier;
        xcan_buffer[1]->id_buffer_[XCAN_RxHeader.FilterIndex].len_ = XCAN_RxHeader.DataLength;

        for (uint8_t i = 0; i < XCAN_RxHeader.DataLength; i++) {
            xcan_buffer[1]->id_buffer_[XCAN_RxHeader.FilterIndex].buffer_[i] = local_Rx_buffer[i];
        }

        xcan_buffer[1]->nvic_.Rx_Callback                   = 1;
        xcan_buffer[1]->nvic_.Id[XCAN_RxHeader.FilterIndex] = 1;

    } else if (hxcan_ == hxcanx_[2]) {
        xcan_buffer[2]->id_buffer_[XCAN_RxHeader.FilterIndex].id_  = XCAN_RxHeader.Identifier;
        xcan_buffer[2]->id_buffer_[XCAN_RxHeader.FilterIndex].len_ = XCAN_RxHeader.DataLength;

        for (uint8_t i = 0; i < XCAN_RxHeader.DataLength; i++) {
            xcan_buffer[2]->id_buffer_[XCAN_RxHeader.FilterIndex].buffer_[i] = local_Rx_buffer[i];
        }

        xcan_buffer[2]->nvic_.Rx_Callback                   = 1;
        xcan_buffer[2]->nvic_.Id[XCAN_RxHeader.FilterIndex] = 1;
    } else {
    }
}

void xcan_management::xcan_fifo1_callback(XCAN_HandleTypeDef* hxcan_)
{
    if (hxcan_ == hxcanx_[0]) {
        xcan_buffer[0]->id_buffer_[XCAN_RxHeader.FilterIndex].id_  = XCAN_RxHeader.Identifier;
        xcan_buffer[0]->id_buffer_[XCAN_RxHeader.FilterIndex].len_ = XCAN_RxHeader.DataLength;

        for (uint8_t i = 0; i < XCAN_RxHeader.DataLength; i++) {
            xcan_buffer[0]->id_buffer_[XCAN_RxHeader.FilterIndex].buffer_[i] = local_Rx_buffer[i];
        }

        xcan_buffer[0]->nvic_.Rx_Callback                   = 1;
        xcan_buffer[0]->nvic_.Id[XCAN_RxHeader.FilterIndex] = 1;

    } else if (hxcan_ == hxcanx_[1]) {
        xcan_buffer[1]->id_buffer_[XCAN_RxHeader.FilterIndex].id_  = XCAN_RxHeader.Identifier;
        xcan_buffer[1]->id_buffer_[XCAN_RxHeader.FilterIndex].len_ = XCAN_RxHeader.DataLength;

        for (uint8_t i = 0; i < XCAN_RxHeader.DataLength; i++) {
            xcan_buffer[1]->id_buffer_[XCAN_RxHeader.FilterIndex].buffer_[i] = local_Rx_buffer[i];
        }

        xcan_buffer[1]->nvic_.Rx_Callback                   = 1;
        xcan_buffer[1]->nvic_.Id[XCAN_RxHeader.FilterIndex] = 1;

    } else if (hxcan_ == hxcanx_[2]) {
        xcan_buffer[2]->id_buffer_[XCAN_RxHeader.FilterIndex].id_  = XCAN_RxHeader.Identifier;
        xcan_buffer[2]->id_buffer_[XCAN_RxHeader.FilterIndex].len_ = XCAN_RxHeader.DataLength;

        for (uint8_t i = 0; i < XCAN_RxHeader.DataLength; i++) {
            xcan_buffer[2]->id_buffer_[XCAN_RxHeader.FilterIndex].buffer_[i] = local_Rx_buffer[i];
        }

        xcan_buffer[2]->nvic_.Rx_Callback                   = 1;
        xcan_buffer[2]->nvic_.Id[XCAN_RxHeader.FilterIndex] = 1;
    } else {
    }
}

void xcan_management::xcan_TxEvent_callback(XCAN_HandleTypeDef* hxcan_)
{
    if (hxcan_ == hxcanx_[0]) {
        *TxMessageMarker[0] = XCAN_TxEvent.MessageMarker;
    } else if (hxcan_ == hxcanx_[1]) {
        *TxMessageMarker[1] = XCAN_TxEvent.MessageMarker;
    } else if (hxcan_ == hxcanx_[2]) {
        *TxMessageMarker[2] = XCAN_TxEvent.MessageMarker;
    } else {
    }
}

bool xcan_management::xcan_set_timeout_counter(XCAN_HandleTypeDef* hxcan_, fifo fifo_, uint32_t counter_)
{
    if (fifo_ == fifo::FIFO0) {
        if (HAL_FDCAN_ConfigTimeoutCounter(hxcan_, FDCAN_TIMEOUT_RX_FIFO0, counter_)) return 1;

    } else if (fifo_ == fifo::FIFO1) {
        if (HAL_FDCAN_ConfigTimeoutCounter(hxcan_, FDCAN_TIMEOUT_RX_FIFO1, counter_)) return 1;

    } else {
    }

    if (HAL_FDCAN_EnableTimeoutCounter(hxcan_)) return 1;

    return 0;
}
bool xcan_management::xcan_enable_timeout(XCAN_HandleTypeDef* hxcan_)
{
    if (HAL_FDCAN_ActivateNotification(hxcan_, FDCAN_IT_TIMEOUT_OCCURRED, 0)) return 1;

    return 0;
}
bool xcan_management::xcan_disable_timeout(XCAN_HandleTypeDef* hxcan_)
{
    if (HAL_FDCAN_DeactivateNotification(hxcan_, FDCAN_IT_TIMEOUT_OCCURRED)) return 1;

    if (HAL_FDCAN_DisableTimestampCounter(hxcan_)) return 1;

    return 0;
}

bool xcan_management::xcan_enable_beginning(XCAN_HandleTypeDef* hxcan_)
{
    if (HAL_FDCAN_Start(hxcan_)) return 1;

    return 0;
}
bool xcan_management::xcan_disable_biginning(XCAN_HandleTypeDef* hxcan_)
{
    if (HAL_FDCAN_Stop(hxcan_)) return 1;

    return 0;
}

bool xcan_management::xcan_enable_tx_callback(XCAN_HandleTypeDef* hxcan_)
{
    if (HAL_FDCAN_ActivateNotification(hxcan_, FDCAN_IT_TX_EVT_FIFO_NEW_DATA, 0)) return 1;

    return 0;
}
bool xcan_management::xcan_disable_tx_callback(XCAN_HandleTypeDef* hxcan_)
{
    if (HAL_FDCAN_DeactivateNotification(hxcan_, FDCAN_IT_TX_EVT_FIFO_NEW_DATA)) return 1;

    return 0;
}

bool xcan_management::xcan_enable_rx_callback(XCAN_HandleTypeDef* hxcan_, fifo fifo_)
{
    if (fifo_ == fifo::FIFO0) {
        if (HAL_FDCAN_ActivateNotification(
                hxcan_, FDCAN_IT_RX_FIFO0_NEW_MESSAGE | FDCAN_IT_RX_FIFO0_FULL | FDCAN_IT_RX_FIFO0_MESSAGE_LOST, 0
            )) {
            return 1;
        }

    } else if (fifo_ == fifo::FIFO1) {
        if (HAL_FDCAN_ActivateNotification(
                hxcan_, FDCAN_IT_RX_FIFO1_NEW_MESSAGE | FDCAN_IT_RX_FIFO1_FULL | FDCAN_IT_RX_FIFO1_MESSAGE_LOST, 0
            )) {
            return 1;
        }

    } else {
    }

    return 0;
}

bool xcan_management::xcan_disable_rx_callback(XCAN_HandleTypeDef* hxcan_, fifo fifo_)
{
    if (fifo_ == fifo::FIFO0) {
        if (HAL_FDCAN_DeactivateNotification(
                hxcan_, FDCAN_IT_RX_FIFO0_NEW_MESSAGE | FDCAN_IT_RX_FIFO0_FULL | FDCAN_IT_RX_FIFO0_MESSAGE_LOST
            )) {
            return 1;
        }

    } else if (fifo_ == fifo::FIFO1) {
        if (HAL_FDCAN_DeactivateNotification(
                hxcan_, FDCAN_IT_RX_FIFO1_NEW_MESSAGE | FDCAN_IT_RX_FIFO1_FULL | FDCAN_IT_RX_FIFO1_MESSAGE_LOST
            )) {
            return 1;
        }

    } else {
    }

    return 0;
}

#ifdef CAN1

bool xcan_management::xcan_send(hxcan_frame* frame_) {}

bool xcan_management::xcan_receive(hxcan_frame* frame_) {}

#endif

#ifdef HAL_FDCAN_MODULE_ENABLED
xcan_management xcan_manager;
#endif

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal

extern "C" {

#ifdef FDCAN1

#ifdef mXCAN_FIFO0_Callback
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef* hfdcan, uint32_t RxFifo0ITs)
{
    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) == FDCAN_IT_RX_FIFO0_NEW_MESSAGE) {
        if (HAL_FDCAN_GetRxMessage(
                hfdcan, FDCAN_RX_FIFO0, &maidui3_xcan::xcan_manager.XCAN_RxHeader, maidui3_xcan::xcan_manager.local_Rx_buffer
            )) {
            return;
        }

        maidui3_xcan::xcan_manager.xcan_fifo0_callback(hfdcan);
    }
    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_FULL) == FDCAN_IT_RX_FIFO0_FULL) {
    }
    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_MESSAGE_LOST) == FDCAN_IT_RX_FIFO0_MESSAGE_LOST) {
    }
}
#endif

#ifdef mXCAN_FIFO1_Callback
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef* hfdcan, uint32_t RxFifo1ITs)
{
    if ((RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) == FDCAN_IT_RX_FIFO1_NEW_MESSAGE) {
        if (HAL_FDCAN_GetRxMessage(
                hfdcan, FDCAN_RX_FIFO1, &maidui3_xcan::xcan_manager.XCAN_RxHeader, maidui3_xcan::xcan_manager.local_Rx_buffer
            )) {
            return;
        }

        maidui3_xcan::xcan_manager.xcan_fifo1_callback(hfdcan);
    }
    if ((RxFifo1ITs & FDCAN_IT_RX_FIFO1_FULL) == FDCAN_IT_RX_FIFO1_FULL) {
    }
    if ((RxFifo1ITs & FDCAN_IT_RX_FIFO1_MESSAGE_LOST) == FDCAN_IT_RX_FIFO1_MESSAGE_LOST) {
    }
}
#endif

void HAL_FDCAN_TxEventFifoCallback(FDCAN_HandleTypeDef* hfdcan, uint32_t TxEventFifoITs)
{
    if (HAL_FDCAN_GetTxEvent(hfdcan, &maidui3_xcan::xcan_manager.XCAN_TxEvent)) {
        return;
    }
    maidui3_xcan::xcan_manager.xcan_TxEvent_callback(hfdcan);
    // HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_SET);
}

void HAL_FDCAN_TimeoutOccurredCallback(FDCAN_HandleTypeDef* hfdcan) {}

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
