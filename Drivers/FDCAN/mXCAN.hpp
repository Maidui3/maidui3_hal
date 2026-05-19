
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
#include "mXCAN_manager.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

class xcan
{
private:
    uint8_t max_len;
    uint32_t max_id;
    uint64_t messagemarker;

public:
    xcan_setup_type setup_type;
    xcan_port_buffer buffer;

public:
    xcan(
        FDCAN_HandleTypeDef* _hxcan  = NULL,
        fifo _fifo                   = fifo::FIFO0,
        can_frame _frame             = can_frame::Classic_CAN,
        id_filter_type _id_type      = id_filter_type::Non_mask_id,
        uint32_t _rx_timeout_counter = {0},
        bool _tx_callback            = {0}
    )
    {
        setup_type.hxcan_              = _hxcan;
        setup_type.fifo_               = _fifo;
        setup_type.frame_              = _frame;
        setup_type.filter_id_          = _id_type;
        setup_type.rx_timeout_counter_ = _rx_timeout_counter;
        setup_type.tx_callback_        = _tx_callback;

        if (setup_type.frame_ == can_frame::Classic_CAN) {
            max_len = 8U;
            max_id  = 0x7FF;
        } else if (setup_type.frame_ == can_frame::FDCAN) {
            max_len = 64U;
            max_id  = 0x1FFFFF;
        } else {
        }
    };

    bool init();

    void set_Id(uint32_t id);

    void set_FDCAN_HandleTypedef(FDCAN_HandleTypeDef* hxcan);

    bool SendMessage(hxcan_frame* frame);

    bool GetMessage(hxcan_frame* frame, uint8_t id = 0);
};

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal