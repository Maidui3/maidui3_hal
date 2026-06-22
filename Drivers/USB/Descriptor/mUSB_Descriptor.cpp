
#include "mUSB_Descriptor.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {
namespace USB_Descriptor {

bool usb_descriptor::get_deveice_descriptor(PCD_HandleTypeDef* husb_pcd__, Device_DescriptorTypeDef* buffer_)
{
    buffer_->bLength            = USB_bLength_18;
    buffer_->bDescriptorType    = USB_bDescriptorTypes_DEVEICE;
    buffer_->bcdUSB             = USB_bcdUSB_USB20;
    buffer_->bDeviceClass       = USB_bDeviceClass_writeInterfaceClass;
    buffer_->bDeviceSubClass    = USB_bDeviceSubClass_writeInterfaceClass;
    buffer_->bDeviceProtocol    = USB_bDeviceProtocol_writeInterfaceClass;
    buffer_->bMaxPacketSize0    = USB_bMaxPacketSizeEP0_64;
    buffer_->idVendor           = 0x0403;
    buffer_->idProduct          = 0x6015;
    buffer_->bcdDevice          = 0x1000;
    buffer_->iManufacturer      = 0x01;
    buffer_->iProduct           = 0x02;
    buffer_->iSerialNumber      = 0x03;
    buffer_->bNumConfigurations = 0x01;

    return 0;
}

bool usb_descriptor::get_configuration_descriptor(PCD_HandleTypeDef* husb_pcd__, Configuration_DescriptorTypeDef* buffer_)
{
    buffer_->bLength         = USB_bLength_9;
    buffer_->bDescriptorType = USB_bDescriptorTypes_CONFIGURATION;
    buffer_->wTotalLength;
    buffer_->bNumInterface;
    buffer_->bConfigurationValue;
    buffer_->iConfiguration;
    buffer_->bmAttributes;
    buffer_->bMaxPower;

    return 0;
}

bool usb_descriptor::get_interface_descriptor(PCD_HandleTypeDef* husb_pcd__, Interface_DescriptorTypeDef* buffer_)
{
    buffer_->bLength         = USB_bLength_9;
    buffer_->bDescriptorType = USB_bDescriptorTypes_INTERFACE;
    buffer_->bInterfaceNumber;
    buffer_->bAlternateSetting;
    buffer_->bNumEndpoints;
    buffer_->bInterfaceClass;
    buffer_->bInterfaceSubClass;
    buffer_->bInterfaceProtocol;
    buffer_->iInterface;

    return 0;
}

bool usb_descriptor::get_endpoint_descriptor(PCD_HandleTypeDef* husb_pcd__, Endpoint_DescriptorTypeDef* buffer_)
{
    buffer_->bLength         = USB_bLength_7;
    buffer_->bDescriptorType = USB_bDescriptorTypes_ENDPOINT;
    buffer_->bEndpointAddress;
    buffer_->bmAttributes;
    buffer_->wMaxPacketSize;
    buffer_->bInterval;

    return 0;
}

}  // namespace USB_Descriptor
}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal
