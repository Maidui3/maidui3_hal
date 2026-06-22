
#pragma once

#include <cstdint>

#include "main.h"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {
namespace USB_Descriptor {

struct Device_DescriptorTypeDef {
    __IO uint8_t bLength;
    __IO uint8_t bDescriptorType;
    __IO uint16_t bcdUSB;
    __IO uint8_t bDeviceClass;
    __IO uint8_t bDeviceSubClass;
    __IO uint8_t bDeviceProtocol;
    __IO uint8_t bMaxPacketSize0;
    __IO uint16_t idVendor;
    __IO uint16_t idProduct;
    __IO uint16_t bcdDevice;
    __IO uint8_t iManufacturer;
    __IO uint8_t iProduct;
    __IO uint8_t iSerialNumber;
    __IO uint8_t bNumConfigurations;
};

#define USB_bLength_18 (uint8_t)0x12U
#define USB_bLength_9  (uint8_t)0x09U
#define USB_bLength_7  (uint8_t)0x07U

#define USB_bDescriptorTypes_DEVEICE                   (uint8_t)0x01U
#define USB_bDescriptorTypes_CONFIGURATION             (uint8_t)0x02U
#define USB_bDescriptorTypes_STRING                    (uint8_t)0x03U
#define USB_bDescriptorTypes_INTERFACE                 (uint8_t)0x04U
#define USB_bDescriptorTypes_ENDPOINT                  (uint8_t)0x05U
#define USB_bDescriptorTypes_DEVICE_QUALIFIER          (uint8_t)0x06U
#define USB_bDescriptorTypes_OTHER_SPEED_CONFIGURATION (uint8_t)0x07U
#define USB_bDescriptorTypes_INTERFACE_POWER           (uint8_t)0x08U

#define USB_bcdUSB_USB10 (uint16_t)0x0100  // USB1.0
#define USB_bcdUSB_USB11 (uint16_t)0x0110  // USB1.1
#define USB_bcdUSB_USB20 (uint16_t)0x0200  // USB2.0

#define USB_bDeviceClass_writeInterfaceClass (uint8_t)0x00U
#define USB_bDeviceClass_Communication       (uint8_t)0x02U
#define USB_bDeviceClass_Hub                 (uint8_t)0x09U
#define USB_bDeviceClass_DiagnosticDevice    (uint8_t)0xDCU
#define USB_bDeviceClass_Wireless            (uint8_t)0xE0U
#define USB_bDeviceClass_MiscDeveice         (uint8_t)0xEFU
#define USB_bDeviceClass_Vendor              (uint8_t)0xFFU

#define USB_bDeviceSubClass_writeInterfaceClass (uint8_t)0x00U
#define USB_bDeviceSubClass_Vendor              (uint8_t)0xFFU

#define USB_bDeviceProtocol_writeInterfaceClass (uint8_t)0x00U
#define USB_bDeviceProtocol_Vendor              (uint8_t)0xFFU

#define USB_bMaxPacketSizeEP0_8  (uint8_t)0x08U
#define USB_bMaxPacketSizeEP0_16 (uint8_t)0x10U
#define USB_bMaxPacketSizeEP0_32 (uint8_t)0x20U
#define USB_bMaxPacketSizeEP0_64 (uint8_t)0x40U

#define USB_idVendor_STMicroelectronics (uint16_t)0x0483U

#define USB_idProduct_STMicroelectronics (uint16_t)0x5740U

struct Configuration_DescriptorTypeDef {
    __IO uint8_t bLength;
    __IO uint8_t bDescriptorType;
    __IO uint16_t wTotalLength;
    __IO uint8_t bNumInterface;
    __IO uint8_t bConfigurationValue;
    __IO uint8_t iConfiguration;
    __IO uint8_t bmAttributes;
    __IO uint8_t bMaxPower;
};

struct Interface_DescriptorTypeDef {
    __IO uint8_t bLength;
    __IO uint8_t bDescriptorType;
    __IO uint8_t bInterfaceNumber;
    __IO uint8_t bAlternateSetting;
    __IO uint8_t bNumEndpoints;
    __IO uint8_t bInterfaceClass;
    __IO uint8_t bInterfaceSubClass;
    __IO uint8_t bInterfaceProtocol;
    __IO uint8_t iInterface;
};

#define USB_bInterfaceClass_Audio            (uint8_t)0x01U
#define USB_bInterfaceClass_CDC_Control      (uint8_t)0x02U
#define USB_bInterfaceClass_HID              (uint8_t)0x03U
#define USB_bInterfaceClass_Physical         (uint8_t)0x05U
#define USB_bInterfaceClass_Image            (uint8_t)0x06U
#define USB_bInterfaceClass_Printer          (uint8_t)0x07U
#define USB_bInterfaceClass_Mass_Storage     (uint8_t)0x08U
#define USB_bInterfaceClass_HUB              (uint8_t)0x09U
#define USB_bInterfaceClass_CDC_Data         (uint8_t)0x0AU
#define USB_bInterfaceClass_Chip_SmartCard   (uint8_t)0x0BU
#define USB_bInterfaceClass_Content_Security (uint8_t)0x0DU
#define USB_bInterfaceClass_Video            (uint8_t)0x0EU
#define USB_bInterfaceClass_DiagnosticDevice (uint8_t)0xDCU
#define USB_bInterfaceClass_Wireless         (uint8_t)0xE0U
#define USB_bInterfaceClass_App_Specific     (uint8_t)0xEFU
#define USB_bInterfaceClass_Vendor           (uint8_t)0xFFU

struct Endpoint_DescriptorTypeDef {
    __IO uint8_t bLength;
    __IO uint8_t bDescriptorType;
    __IO uint8_t bEndpointAddress;
    __IO uint8_t bmAttributes;
    __IO uint16_t wMaxPacketSize;
    __IO uint8_t bInterval;
};

}  // namespace USB_Descriptor
}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal