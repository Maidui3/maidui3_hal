
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

typedef void (*uart_callback_t)(void);

namespace maidui3_hal {
namespace Drivers {
namespace USART {

class usart
{
private:
    uint8_t Static_Tx_Buffer_[1024];  // 1KByte

    struct function_callback_s {
        uart_callback_t callback_p;
        UART_HandleTypeDef* huartx_;
    };

    function_callback_s function_s[10];

public:
    void RxCpltCallback(UART_HandleTypeDef* huartx_);
    bool init(UART_HandleTypeDef* huartx_, uart_callback_t callback);

public:
    bool SendMessage_polling(UART_HandleTypeDef* huartx_, uint8_t* data_p, uint16_t size_, uint32_t timeout_ms_ = 100);

    bool GetMessage_polling(UART_HandleTypeDef* huartx_, uint8_t* data_p, uint16_t size_, uint32_t timeout_ms_ = 100);

    bool SendMessage_exti(UART_HandleTypeDef* huartx_, uint8_t* data_p, uint16_t size_);

    bool GetMessage_exti(UART_HandleTypeDef* huartx_, uint8_t* data_p, uint16_t size_);

    bool SendMessage_dma();

    bool GetMessage_dma();
};

}  // namespace USART
}  // namespace Drivers
}  // namespace maidui3_hal

extern maidui3_hal::Drivers::USART::usart usart_stack;

#endif
