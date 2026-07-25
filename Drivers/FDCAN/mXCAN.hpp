
#pragma once

#include <cstdint>

#include "main.h"
#ifdef HAL_FDCAN_MODULE_ENABLED
#include "stm32h7xx_hal_fdcan.h"
#endif
#ifdef HAL_CAN_MODULE_ENABLED
#include "stm32h7xx_hal_can.h"
#endif

#include "mXCAN_data_template.hpp"
#include "mXCAN_manager.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

class xcan
{
private:
    uint8_t max_len        = 0;
    uint32_t max_id_bit    = 0;
    uint32_t MessageMarker = 0;
    bool Handler_was_null  = 0;

public:
    xcan_setup_type setup_type;
    xcan_port_buffer buffer;

public:
    xcan(FDCAN_HandleTypeDef* _hxcan = NULL, fifo _fifo = fifo::FIFO0, uint32_t _rx_timeout_counter = {0}, bool _tx_callback = {0})
    {
        setup_type.hxcan_              = _hxcan;
        setup_type.fifo_               = _fifo;
        setup_type.rx_timeout_counter_ = _rx_timeout_counter;
        setup_type.tx_callback_        = _tx_callback;
        setup_type.buffer              = &buffer;

        if (_hxcan == NULL) {
            Handler_was_null = 1;
            return;
        }

        if (setup_type.hxcan_->Init.FrameFormat == FDCAN_FRAME_CLASSIC) {
            max_len               = 8U;
            max_id_bit            = 0x7FF;
            setup_type.max_id_num = setup_type.hxcan_->Init.StdFiltersNbr;

        } else if ((setup_type.hxcan_->Init.FrameFormat == FDCAN_FRAME_FD_BRS) || (setup_type.hxcan_->Init.FrameFormat == FDCAN_FRAME_FD_NO_BRS)) {
            max_len               = 64U;
            max_id_bit            = 0x1FFFFF;
            setup_type.max_id_num = setup_type.hxcan_->Init.ExtFiltersNbr;

        } else {
            max_len               = 8U;
            max_id_bit            = 0x7FF;
            setup_type.max_id_num = setup_type.hxcan_->Init.StdFiltersNbr;
        }

        setup_type.Id_mask = max_id_bit;
    };

    bool init();

    void set_Id(uint32_t id);

    void set_Id_mask(uint32_t mask = 0x00);

    bool SendMessage(hxcan_frame* frame);

    bool SendMessage_for_timer_loop(hxcan_frame* frame);

    void wait_tx_event_fin();

    bool GetMessage(hxcan_frame* frame, uint8_t index = 0);

    bool callback(uint8_t index);
};

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal