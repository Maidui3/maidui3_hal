
#include "mXCAN.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

bool xcan::init()
{
    if (setup_type.hxcan_ == NULL) return 1;

    if (xcan_manager.xcan_init(&setup_type)) return 1;

    return 0;
}

void xcan::set_Id(uint32_t id)
{
    static uint8_t counter = 0;

    if (id > max_id) id = 0x00;

    setup_type.Id_[counter] = id;
    ++counter;
    if (counter == 4) counter = 0;
}

void xcan::set_Id_mask(uint32_t mask)
{
    if (mask > max_id) mask = 0x00;

    setup_type.Id_mask = mask;
}

void xcan::set_FDCAN_HandleTypedef(FDCAN_HandleTypeDef* hxcan)
{
    setup_type.hxcan_ = hxcan;
}

bool xcan::SendMessage(hxcan_frame* frame)
{
    if (frame->data_p_ == NULL) return 1;
    if (frame->len_ > max_len) return 1;
    if (frame->id_ > max_id) return 1;

    if (xcan_manager.xcan_send(&setup_type, frame, 0)) return 1;

    return 0;
}

void xcan::wait_tx_event_fin()
{
    static uint32_t last_tx_tick;
    last_tx_tick = HAL_GetTick();
    while (!setup_type.buffer->nvic_.Tx_Callback) {
        if ((HAL_GetTick() - last_tx_tick) > 1) break;

        /**
         * 1ミリ秒以上txが来なかった場合、
         * 動作させることを優先し、強制的にループからでる。
         */
    };
    setup_type.buffer->nvic_.Tx_Callback = 0;
    return;
}

bool xcan::GetMessage(hxcan_frame* frame, uint8_t index)
{
    frame->id_     = setup_type.buffer->id_buffer_[index].id_;
    frame->data_p_ = setup_type.buffer->id_buffer_[index].buffer_;
    frame->len_    = setup_type.buffer->id_buffer_[index].len_;

    return 0;
}

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal
