
#pragma once

#include <cstdint>

#include "mUSB_stack.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {
namespace hid_class {

enum hid_model_e : uint8_t {
    KeyBoard,
    GamePad,
};

enum hid_module_e : uint8_t {
    Analog_u8,
};

class usb_class_hid
{
private:
    hid_model_e model_;

public:
    usb_class_hid(hid_model_e model) : model_(model) {};

    bool add_module(hid_module_e type, uint8_t byte_nummber);
};

}  // namespace hid_class
}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal