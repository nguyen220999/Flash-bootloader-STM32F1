#ifndef SERVICE_HDL_SERVICE_PUB_H
#define SERVICE_HDL_SERVICE_PUB_H

#include "main_sm_pub.h"

#define SERVICE_JUMP_TO_APPLICATION 1
#define SERVICE_BOOTLOADER_ERASE_FLASH 2
#define SERVICE_BOOTLOADER_WRITE_FLASH 3
#define SERVICE_BOOTLOADER_WRITE_SWIL  4
#define SERVICE_BOOTLOADER_NUMOFSERVICE 4

typedef enum
{
    SERVICE_HANDLE = 0,
    SERVICE_IDLE,
    SERVICE_SEND_DATA,
    SERVICE_RECEIVE_DATA,
    SERVICE_DONE,
    SERVICE_ERROR
} ServiceState_en;


typedef enum
{
    SERVICE_SM_START,
    SERVICE_SM_SERVICE_HANDLE,
    SERVICE_SM_IDLE,
    SERVICE_SM_SEND_DATA,
    SERVICE_SM_RECIVE_DATA,
    SERVICE_SM_ERROR,
    SERVICE_SM_DONE
} ServiceSM_en;

/// @brief 
/// this enum for classify Positive respond 
/// this enum for classify NRC type when handle service
/// @use in:
/// return value for function in handling service
typedef enum
{
    SERVICE_TASK_SUCCESSFUL,
    SERVICE_NRC_INVALID_INPUT_DATA,
    SERVICE_NRC_INVALID_FLASH_DRIVER,
    SERVICE_NRC_WRITE_FLASH_FAIL,
    SERVICE_NRC_WRONG_CRC

} ServiceTaskResult_en;

ServiceSM_en service_sm(TransportedData_st* p_message);

#endif