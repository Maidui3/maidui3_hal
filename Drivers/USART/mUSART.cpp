
#include "mUSART.hpp"

#ifdef Maidui3_HAL_Use_usart
#include <cstdint>

#include "stdlib.h"
#include "string.h"

namespace maidui3_hal {
namespace Drivers {
namespace USART {

bool usart::init(UART_HandleTypeDef* huartx_, uart_callback_t callback)
{
    static uint8_t module_counter = 0;  // module num is max 10

    if (module_counter >= 10) return 1;

    function_s[module_counter].callback_p = callback;
    function_s[module_counter].huartx_    = huartx_;
    module_counter++;

    return 0;
}

void usart::RxCpltCallback(UART_HandleTypeDef* huartx_)
{
    for (uint8_t i = 0; i < 10; i++) {
        if (huartx_ == function_s[i].huartx_) {
            function_s[i].callback_p();
            return;
        }
    }
    return;
}

bool usart::SendMessage_polling(UART_HandleTypeDef* huartx_, uint8_t* data_p, uint16_t size_, uint32_t timeout_ms_)
{
    if (HAL_UART_Transmit(huartx_, data_p, size_, timeout_ms_)) return 1;
    return 0;
}

bool usart::GetMessage_polling(UART_HandleTypeDef* huartx_, uint8_t* data_p, uint16_t size_, uint32_t timeout_ms_)
{
    if (HAL_UART_Receive(huartx_, data_p, size_, timeout_ms_)) return 1;
    return 0;
}

bool usart::SendMessage_exti(UART_HandleTypeDef* huartx_, uint8_t* data_p, uint16_t size_)
{
    if (HAL_UART_Transmit_IT(huartx_, data_p, size_)) return 1;
    return 0;
}

bool usart::GetMessage_exti(UART_HandleTypeDef* huartx_, uint8_t* data_p, uint16_t size_)
{
    if (HAL_UART_Receive_IT(huartx_, data_p, size_)) return 1;
    return 0;
}

bool usart::SendMessage_dma()
{
    return 0;
}

bool usart::GetMessage_dma()
{
    return 0;
}

}  // namespace USART
}  // namespace Drivers
}  // namespace maidui3_hal

maidui3_hal::Drivers::USART::usart usart_stack;

extern "C" {
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    usart_stack.RxCpltCallback(huart);
}
}

#endif
