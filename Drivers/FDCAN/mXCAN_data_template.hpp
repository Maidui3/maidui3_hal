
#pragma once

#include <cstdint>

#include "fdcan.h"

#ifdef HAL_FDCAN_MODULE_ENABLED
#define XCAN_HandleTypeDef FDCAN_HandleTypeDef
#endif

#ifdef HAL_CAN_MODULE_ENABLED
#define XCAN_HandleTypeDef CAN_HandleTypeDef
#endif

namespace maidui3_hal {
namespace Drivers {
namespace XCAN {

enum class fifo : bool {
    FIFO0,
    FIFO1,
};

struct NVIC_Handle {
    bool Tx_Callback          = false; /*各フラグを呼んだら0に戻す*/
    bool Rx_Callback          = false; /*各フラグを呼んだら0に戻す*/
    bool Rx_Timeout           = false; /*各フラグを呼んだら0に戻す*/
    uint64_t Id_filter_bit[2] = {0};
    /**
     * Id Index 0 is 0x01
     * Id Index 1 is 0x02
     * Id Index 2 is 0x04
     * Id Index 3 is 0x08
     */
};

struct hxcan_frame {
    uint32_t id_     = {0};
    uint8_t* data_p_ = NULL;  // 64 Byte
    uint8_t len_     = {0};   // 64
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

struct xcan_setup_type {
    XCAN_HandleTypeDef* hxcan_   = NULL;
    fifo fifo_                   = fifo::FIFO0;
    uint8_t max_id_num           = {0};
    uint32_t rx_timeout_counter_ = {0};
    bool tx_callback_            = {0};
    uint32_t Id_[4]              = {0};
    uint32_t Id_mask             = {0};
    uint8_t bus_numbering_       = {0};
    xcan_port_buffer* buffer     = {0};
    uint32_t TxMessageMarker     = {0};
};

}  // namespace XCAN
}  // namespace Drivers
}  // namespace maidui3_hal
