
#include "mUSB_HID.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {
namespace hid_class {

bool usb_class_hid::add_module(hid_module_e type, uint8_t byte_nummber) {}

bool usb_class_hid::decide_module()
{
    USB_PCD::stack::Add_Request_Bace_Class(NULL, USB_PCD::Request_class_e::HID_class);
}

bool usb_class_hid::update_data(uint8_t* data, uint8_t len) {}

}  // namespace hid_class
}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal
