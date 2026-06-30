
#pragma once

#include "main.h"
#ifdef HAL_UART_MODULE_ENABLED
#define Maidui3_HAL_Use_usart
#include "stm32g4xx_hal_uart.h"
#endif
#ifdef HAL_USART_MODULE_ENABLED
#define Maidui3_HAL_Use_usart
#include "stm32g4xx_hal_usart.h"
#endif
//
#ifdef Maidui3_HAL_Use_usart

#include "mUSART_data_config.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace USART {

class usart
{
private:
    UART_HandleTypeDef* huartx_;
    uint8_t Static_Tx_Buffer_[3072];

public:
    usart(UART_HandleTypeDef* _huartx) : huartx_(_huartx) {};

    bool SendMessage_polling(uint8_t* data_p, uint16_t size_, uint32_t timeout_ms_ = 100);

    bool GetMessage_polling(uint8_t* data_p, uint16_t size_, uint32_t timeout_ms_ = 100);

    bool SendMessage_exti(uint8_t* data_p, uint16_t size_);

    bool GetMessage_exti(uint8_t* data_p, uint16_t size_);

    bool SendMessage_dma();

    bool GetMessage_dma();
};

}  // namespace USART
}  // namespace Drivers
}  // namespace maidui3_hal

#endif
