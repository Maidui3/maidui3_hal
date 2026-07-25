
#include "mXCAN.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

bool xcan::init()
{
    if (setup_type.hxcan_ == NULL) return 1;

    if (Handler_was_null) {
        if (setup_type.hxcan_->Init.FrameFormat == FDCAN_FRAME_CLASSIC) {
            max_len    = 8U;
            max_id_bit = 0x7FF;

        } else if ((setup_type.hxcan_->Init.FrameFormat == FDCAN_FRAME_FD_BRS) || (setup_type.hxcan_->Init.FrameFormat == FDCAN_FRAME_FD_NO_BRS)) {
            max_len    = 64U;
            max_id_bit = 0x1FFFFF;

        } else {
            max_len    = 8U;
            max_id_bit = 0x7FF;
        }
    }

    if (xcan_manager.xcan_init(&setup_type)) return 1;

    return 0;
}

void xcan::set_Id(uint32_t id)
{
    static uint8_t counter = 0;

    if (id > max_id_bit) id = 0x00;

    setup_type.Id_[counter] = id;
    ++counter;
    if (counter == setup_type.max_id_num) counter = 0;
}

void xcan::set_Id_mask(uint32_t mask)
{
    if (mask > max_id_bit) mask = max_id_bit;

    setup_type.Id_mask = mask;
}

bool xcan::SendMessage(hxcan_frame* frame)
{
    // value 0 ~ 255

    if (setup_type.hxcan_ == NULL) return 1;

    if (frame->data_p_ == NULL) return 1;
    if (frame->len_ > max_len) return 1;
    if (frame->id_ > max_id_bit) return 1;

    ++MessageMarker;
    if (MessageMarker == 256) MessageMarker = 0;

    if (xcan_manager.xcan_send(&setup_type, frame, MessageMarker)) return 1;

    return 0;
}
bool xcan::SendMessage_for_timer_loop(hxcan_frame* frame)
{
    if (frame->data_p_ == NULL) return 1;
    if (frame->len_ > max_len) return 1;
    if (frame->id_ > max_id_bit) return 1;

    if (xcan_manager.xcan_send(&setup_type, frame, 0)) return 1;

    return 0;
}

void xcan::wait_tx_event_fin()
{
    static uint32_t last_tx_tick;
    last_tx_tick = HAL_GetTick();
    while (1) {
        if ((HAL_GetTick() - last_tx_tick) > 1) break;

        if (setup_type.TxMessageMarker == MessageMarker) break;

        /**
         * 1ミリ秒以上txが来なかった場合、
         * 動作させることを優先し、強制的にループからでる。
         */
    };
    return;
}

bool xcan::GetMessage(hxcan_frame* frame, uint8_t index)
{
    frame->id_  = setup_type.buffer->id_buffer_[index].id_;
    frame->len_ = setup_type.buffer->id_buffer_[index].len_;
    for (uint8_t i = 0; i < frame->len_; i++) {
        frame->data_p_[i] = setup_type.buffer->id_buffer_[index].buffer_[i];
    }

    return 0;
}

bool xcan::callback(uint8_t index)
{
    bool flag;

    if (index < 64) {
        flag = (bool)((buffer.nvic_.Id_filter_bit[0] & (1 << index)) >> index);
        buffer.nvic_.Id_filter_bit[0] &= ~(1 << index);
    } else if (index < 128) {
        flag = (bool)((buffer.nvic_.Id_filter_bit[1] & (1 << (index - 64))) >> index);
        buffer.nvic_.Id_filter_bit[1] &= ~(1 << (index - 64));
    } else {
        return 0;
    }

    return flag;
}

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal
