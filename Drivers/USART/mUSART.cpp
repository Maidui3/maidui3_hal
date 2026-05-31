
#include "mUSART.hpp"

#include <cstdint>

#include "stdlib.h"
#include "string.h"

namespace maidui3_hal {
namespace Drivers {
namespace USART {

bool usart::SendMessage(uint8_t* data_p, uint16_t size_)
{
    if (HAL_UART_Transmit(huartx_, data_p, size_, timeout_)) return 1;
    return 0;
}

bool usart::GetMessage(uint8_t* data_p, uint16_t size_)
{
    if (HAL_UART_Receive(huartx_, data_p, size_, timeout_)) return 1;
    return 0;
}

//

bool usart_exti::SendMessage(uint8_t* data_p, uint16_t size_)
{
    if (size_ > 256) {
        memcpy(Static_Tx_Buffer_, data_p, size_);
        HAL_UART_Transmit_IT(huartx_, Static_Tx_Buffer_, size_);
    } else {
        static uint8_t* Dynamic_Tx_Buffer_;
        Dynamic_Tx_Buffer_ = (uint8_t*)malloc(size_);
        memcpy(Dynamic_Tx_Buffer_, data_p, size_);
        HAL_UART_Transmit_IT(huartx_, Dynamic_Tx_Buffer_, size_);
    }
    return 0;
}

bool usart_exti::GetMessage(uint8_t* data_p, uint16_t size_)
{
    return 0;
}

//

bool usart_dma::SendMessage()
{
    return 0;
}

bool usart_dma::GetMessage()
{
    return 0;
}

}  // namespace USART
}  // namespace Drivers
}  // namespace maidui3_hal