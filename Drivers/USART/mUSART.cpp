
#include "mUSART.hpp"

#ifdef Maidui3_HAL_Use_usart
#include <cstdint>

#include "stdlib.h"
#include "string.h"

namespace maidui3_hal {
namespace Drivers {
namespace USART {

bool usart::SendMessage_polling(uint8_t* data_p, uint16_t size_, uint32_t timeout_ms_)
{
    if (HAL_UART_Transmit(huartx_, data_p, size_, timeout_ms_)) return 1;
    return 0;
}

bool usart::GetMessage_polling(uint8_t* data_p, uint16_t size_, uint32_t timeout_ms_)
{
    if (HAL_UART_Receive(huartx_, data_p, size_, timeout_ms_)) return 1;
    return 0;
}

bool usart::SendMessage_exti(uint8_t* data_p, uint16_t size_)
{
    return 0;
}

bool usart::GetMessage_exti(uint8_t* data_p, uint16_t size_)
{
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

#endif
