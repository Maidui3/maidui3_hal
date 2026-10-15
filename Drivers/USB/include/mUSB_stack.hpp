
#pragma once

#include <cstdint>

#include "mUSB_GetDescriptor.hpp"
#include "mUSB_Request.hpp"
#include "mUSB_stack_config.hpp"
#include "main.h"
#ifdef STM32H7
#include "stm32h7xx_hal_pcd.h"
#else
#ifdef STM32G4
#include "stm32g4xx_hal_pcd.h"
#define PCD_MAX_EP 8U
#endif
#endif

#define STM_MCU_MAX_USB_Device 2U

namespace maidui3_hal {
namespace Drivers {
namespace USB_PCD {

__IO uint32_t last_tick[STM_MCU_MAX_USB_Device];

PCD_HandleTypeDef* hpcd__[STM_MCU_MAX_USB_Device];
USB_PCD_Stack_t USB_PCD_Device[STM_MCU_MAX_USB_Device];

union {
    uint8_t buffer[PCD_Control_mps];
    Device_Status_t Deveice_Status;
    Device_Descriptor_t Device_Descriptor;
    Configuration_Descriptor_t Configuration_Descriptor;
    Interface_Descriptor_t Interface_Descriptor;
    Endpoint_Descriptor_t Endpoint_Descriptor;
} Tx_Control_Buffer;

union {
    uint8_t buffer[PCD_Control_mps];
} Rx_Control_Buffer;

bool Init(PCD_HandleTypeDef* _hpcd_Device1, PCD_HandleTypeDef* _hpcd_Device2);

bool Add_Request_Bace_Class();

bool Stop(PCD_HandleTypeDef* husb_pcd_);

void Clear_Byte(uint8_t* buf, uint8_t len);
bool get_status(PCD_HandleTypeDef* husb_pcd__, Device_Status_t* buffer_);

void SOF_Callback(PCD_HandleTypeDef* husb_pcd__);
void SetupStage_Callback(PCD_HandleTypeDef* husb_pcd__, uint32_t* setup__);
void Reset_Callback(PCD_HandleTypeDef* husb_pcd__);
void Suspend_Callback(PCD_HandleTypeDef* husb_pcd__);
void Resume_Callback(PCD_HandleTypeDef* husb_pcd__);
void Connect_Callback(PCD_HandleTypeDef* husb_pcd__);
void Disconnect_Callback(PCD_HandleTypeDef* husb_pcd__);
void DataOutStage_Callback(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__);
void DataInStage_Callback(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__);
void Iso_OutIncomplete(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__);
void Iso_InIncomplete(PCD_HandleTypeDef* husb_pcd__, uint8_t epnum__);

}  // namespace USB_PCD
}  // namespace Drivers
}  // namespace maidui3_hal

#ifdef HAL_PCD_MODULE_ENABLED

#endif
