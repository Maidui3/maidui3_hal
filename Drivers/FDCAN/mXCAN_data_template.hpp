
#pragma once

#include <cstdint>

#include "fdcan.h"

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

enum class can_frame : bool {
    FDCAN,
    Classic_CAN,
};

enum class fifo : bool {
    FIFO0,
    FIFO1,
};

enum class id_filter_type : uint8_t {
    Non_mask_id   = 0,
    mask_one_id   = 1,
    mask_two_id   = 2,
    mask_three_id = 3,
    mask_four_id  = 4,
};

struct NVIC_Handle {
    bool Tx_Callback; /*各フラグを呼んだら0に戻す*/
    bool Rx_Callback; /*各フラグを呼んだら0に戻す*/
    bool Rx_Timeout;  /*各フラグを呼んだら0に戻す*/
    uint8_t Id;       /*各フラグを呼んだら0に戻す*/
    /** Id[0] is Id_Index 0
     *  Id[1] is Id_Index 1
     *  Id[2] is Id_Index 2
     *  Id[3] is Id_Index 3
     */
};

struct xcan_setup_type {
    FDCAN_HandleTypeDef* hxcan_  = NULL;
    fifo fifo_                   = fifo::FIFO0;
    can_frame frame_             = can_frame::Classic_CAN;
    id_filter_type filter_id_    = id_filter_type::Non_mask_id;
    uint32_t rx_timeout_counter_ = {0};
    bool tx_callback_            = {0};
    uint32_t Id_[4]              = {0};
    uint32_t Id_mask             = {0};
    NVIC_Handle callback_flag_   = {0};
    uint8_t bus_numbering_       = {0};
};

struct hxcan_frame {
    uint32_t id_     = {0};
    uint8_t* data_p_ = NULL;
    uint8_t len_     = {0};
};

struct xcan_buffer {
    uint32_t id_        = {0};
    uint8_t buffer_[64] = {0};
    uint8_t len_        = {0};
};

struct xcan_port_buffer {
    xcan_buffer id_buffer_[4];
    NVIC_Handle nvic_;
};

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal
