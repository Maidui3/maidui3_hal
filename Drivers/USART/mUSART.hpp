
#pragma once

#include "main.h"
#include "usart.h"
//
#include "mUSART_data_config.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace USART {

class usart
{
private:
    UART_HandleTypeDef* huartx_;
    uint32_t timeout_;
    uint8_t Static_Tx_Buffer_[256];

public:
    usart(UART_HandleTypeDef* _huartx, uint32_t _timeout_ms = 50) : huartx_(_huartx), timeout_(_timeout_ms) {};

    bool SendMessage(uint8_t* data_p, uint16_t size_);

    bool GetMessage(uint8_t* data_p, uint16_t size_);
};
/*通常関数*/

class usart_exti
{
private:
    UART_HandleTypeDef* huartx_;
    uint8_t Static_Tx_Buffer_[256];

public:
    usart_exti(UART_HandleTypeDef* _huartx) : huartx_(_huartx) {};

    bool SendMessage(uint8_t* data_p, uint16_t size_);

    bool GetMessage(uint8_t* data_p, uint16_t size_);
};
/*割り込み関数*/

class usart_dma
{
private:
    UART_HandleTypeDef huartx_;

public:
    usart_dma(UART_HandleTypeDef _huartx) : huartx_(_huartx) {};

    bool SendMessage();

    bool GetMessage();
};
/*dma使用関数*/

}  // namespace USART
}  // namespace Drivers
}  // namespace maidui3_hal
