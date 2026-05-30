
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
    UART_HandleTypeDef huartx_;

public:
    usart(UART_HandleTypeDef _huartx, Mode function_Mode) : huartx_(_huartx) {};
};
}  // namespace USART
}  // namespace Drivers
}  // namespace maidui3_hal
