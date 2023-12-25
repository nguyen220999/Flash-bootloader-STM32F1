
#include "service_pri.h"
#include "service_pub.h"
#include "flash_service_pub.h"
#include "SWIL_service_pub.h"

bool isServiceRequestValid(uint8_t p_serviceID_u8)
{
    uint8_t idx = 0;
    bool r_value = false;
    for (idx++; idx<= SERVICE_BOOTLOADER_NUMOFSERVICE; )
    {
        if (p_serviceID_u8 == idx )
        {   r_value =true;}
    }
    return r_value;
}

ServiceSM_en bootloader_handle_service(TransportedData_st* pBuffer)
{
    uint8_t l_serviceSequense_u8 = pBuffer->m_data_arr8[0];

    ServiceState_en l_serviceState_en;

    ServiceSM_en r_value;

    if (isServiceRequestValid(l_serviceState_en))
    {
        return SERVICE_SM_ERROR;
    }

    switch (l_serviceSequense_u8)
    {
    case SERVICE_JUMP_TO_APPLICATION:

        //when service called, sw jump to app and no longer responde status to fbl sw
        bootloader_jump_to_user_app();

        break;

    case SERVICE_BOOTLOADER_ERASE_FLASH:

        LOOP_SERVICE_SEQUENCE(l_serviceState_en)
        {
            l_serviceState_en = bootloader_handle_flash_erase_sequence(pBuffer);
        }
        
        break;

    case SERVICE_BOOTLOADER_WRITE_FLASH:

        LOOP_SERVICE_SEQUENCE(l_serviceState_en)
        {
            l_serviceState_en = bootloader_handle_flash_write_sequence(pBuffer);
        }
        break;

    case SERVICE_BOOTLOADER_WRITE_SWIL:
    
        LOOP_SERVICE_SEQUENCE(l_serviceState_en)
        {
            l_serviceState_en = bootloader_handle_write_swil_sequence(pBuffer);
        }

        break;

    default:
        r_value = SERVICE_SM_ERROR;
        break;
    }

    ///@brief
    ///after handle service state machine in while loop
    ///set return value to IDLE to set main state machine to IDLE state and wait for next service request
    r_value = SERVICE_SM_IDLE;

    return r_value;
}

