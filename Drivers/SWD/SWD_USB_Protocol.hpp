
#pragma once

namespace SWD_USB_Protocol {

enum class usb_class_t : uint8_t {
    source,
    command,
    cdc,
    folder,
    settings,
    optionbyte,
};

union source_protocol_host_t {
    struct __attribute__((__packed__)) {
        /*  1  Byte*/ uint8_t target_index;  // value : 0 ~ 255
                                             // 0 is master id for Mlink
                                             // 1,2 is Mlink prot number
                                             // 3 ~ 255 is extended port on extended board

        usb_class_t usb_class;

        /*  2  Byte*/ uint16_t addr_index;  // value : 0 ~ 3999
                                            // addr = addr_index * 500;
        /* 500 Byte*/ uint32_t data[125];

        /*  1  Byte*/ uint8_t length;  // value : 0 ~ 125
    };
    uint8_t buffer[512];  // buffer
};

union source_protocol_deveice_t {
};

union command_protocol_host_t {
    struct __attribute__((__packed__)) {
        uint8_t target_index;
    };
    uint8_t buffer[512];
};

union command_protocol_deveice_t {
};

union cdc_protocol_host_t {
};

union cdc_protocol_device_t {
};

union folder_protocol_host_t {
};

union folder_protocol_device_t {
};

union settings_protocol_host_t {
    struct __attribute__((__packed__)) {
        uint8_t target_index;
        char target_source_name[256];
        uint32_t target_write_speed;
        uint32_t target_debug_version;
        uint32_t target_release_version;
        uint8_t target_reset_mode;
    };
    uint8_t buffer[512];
};

union settings_protocol_device_t {
};

union optionbyte_protocol_host_t {
};

union optionbyte_protocol_device_t {
};

}  // namespace SWD_USB_Protocol
