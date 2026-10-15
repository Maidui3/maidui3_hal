
#include "mUSB_GetDescriptor.hpp"

#include "mUSB_stack.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {
namespace stack {

void get_descriptor(PCD_HandleTypeDef* husb_pcd__, Setup_Packet_t* packet)
{
    switch (packet->wValue >> 8) {
        case USB_Device:
            Clear_Byte(Tx_Control_Buffer.buffer, 0x12);
            get_deveice_descriptor(&Tx_Control_Buffer.Device_Descriptor, packet);
            HAL_PCD_EP_Transmit(husb_pcd__, PCD_ENDP0, Tx_Control_Buffer.buffer, 0x12);
            HAL_PCD_EP_Receive(husb_pcd__, PCD_ENDP0, Rx_Control_Buffer.buffer, 0x00);

            break;

        case USB_Configuration:
            Clear_Byte(Tx_Control_Buffer.buffer, 0x09);
            get_configuration_descriptor(&Tx_Control_Buffer.Configuration_Descriptor, packet);
            HAL_PCD_EP_Transmit(husb_pcd__, PCD_ENDP0, Tx_Control_Buffer.buffer, 0x09);
            HAL_PCD_EP_Receive(husb_pcd__, PCD_ENDP0, Rx_Control_Buffer.buffer, 0x00);

            break;

        case USB_Interface:
            Clear_Byte(Tx_Control_Buffer.buffer, 0x09);
            get_interface_descriptor(&Tx_Control_Buffer.Interface_Descriptor, packet);
            HAL_PCD_EP_Transmit(husb_pcd__, PCD_ENDP0, Tx_Control_Buffer.buffer, 0x09);

            break;

        case USB_Endpoint:
            Clear_Byte(Tx_Control_Buffer.buffer, 0x07);
            get_endpoint_descriptor(&Tx_Control_Buffer.Endpoint_Descriptor, packet);
            HAL_PCD_EP_Transmit(husb_pcd__, PCD_ENDP0, Tx_Control_Buffer.buffer, 0x07);

            break;

        case USB_String:
            break;

        case USB_DeviceQualifier:
            break;

        case USB_Other_SpeedConfiguration:
            break;
    }
}

bool get_deveice_descriptor(Device_Descriptor_t* buffer_, Setup_Packet_t* packet)
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
    buffer_->bNumConfigurations = PCD_MAX_EP;

    return 0;
}

bool get_configuration_descriptor(Configuration_Descriptor_t* buffer_, Setup_Packet_t* packet)
{
    buffer_->bLength             = USB_bLength_9;
    buffer_->bDescriptorType     = USB_bDescriptorTypes_CONFIGURATION;
    buffer_->wTotalLength        = 0xFF;
    buffer_->bNumInterface       = 0xFF;
    buffer_->bConfigurationValue = 0xFF;
    buffer_->iConfiguration      = 0xFF;
    buffer_->bmAttributes        = 0xFF;
    buffer_->bMaxPower           = 0xFF;

    return 0;
}

bool get_interface_descriptor(Interface_Descriptor_t* buffer_, Setup_Packet_t* packet)
{
    buffer_->bLength            = USB_bLength_9;
    buffer_->bDescriptorType    = USB_bDescriptorTypes_INTERFACE;
    buffer_->bInterfaceNumber   = 0xFF;
    buffer_->bAlternateSetting  = 0xFF;
    buffer_->bNumEndpoints      = 0xFF;
    buffer_->bInterfaceClass    = 0xFF;
    buffer_->bInterfaceSubClass = 0xFF;
    buffer_->bInterfaceProtocol = 0xFF;
    buffer_->iInterface         = 0xFF;

    return 0;
}

bool get_endpoint_descriptor(Endpoint_Descriptor_t* buffer_, Setup_Packet_t* packet)
{
    buffer_->bLength          = USB_bLength_7;
    buffer_->bDescriptorType  = USB_bDescriptorTypes_ENDPOINT;
    buffer_->bEndpointAddress = 0xFF;
    buffer_->bmAttributes     = 0xFF;
    buffer_->wMaxPacketSize   = 0xFF;
    buffer_->bInterval        = 0xFF;

    return 0;
}

}  // namespace stack
}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal
