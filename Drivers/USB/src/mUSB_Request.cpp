
#include "mUSB_Request.hpp"

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {
namespace stack {

void Host_Dir_Device_Request(PCD_HandleTypeDef* husb_pcd__, Setup_Packet_t* packet)
{
    switch (packet->bRequest) {
        case USB_GET_STATUS:
            Clear_Byte(Tx_Control_Buffer.buffer, 0x02);
            get_status(husb_pcd__, &Tx_Control_Buffer.Deveice_Status);
            HAL_PCD_EP_Transmit(husb_pcd__, PCD_ENDP0, Tx_Control_Buffer.buffer, 0x02);

            break;

        case USB_GET_DESCRIPTOR:
            get_descriptor(husb_pcd__, packet);

            break;

        case USB_GET_CONFIGURATION:
            break;
    }
}

void Host_Dir_Interface_Request(PCD_HandleTypeDef* husb_pcd__, Setup_Packet_t* packet)
{
    switch (packet->bRequest) {
        case USB_GET_STATUS:
            break;

        case USB_GET_INTERFACE:
            break;
    }
}

void Host_Dir_Endpoint_Request(PCD_HandleTypeDef* husb_pcd__, Setup_Packet_t* packet)
{
    switch (packet->bRequest) {
        case USB_GET_STATUS:
            break;

        case USB_SYNCH_FRAME:
            break;
    }
}

void Host_Dir_Other_Request(PCD_HandleTypeDef* husb_pcd__, Setup_Packet_t* packet) {}

}  // namespace stack
}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal