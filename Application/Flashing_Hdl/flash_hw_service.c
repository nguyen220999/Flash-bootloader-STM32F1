#include "flash_drv_api.h"c
#include "flash_service_pub.h"
#include "service_pub.h"
#include "Diag_communication.h"
#include "NvM_handle_pub.h"
#include "main_sm_pub.h"
#include "Crc.h"
#include "flash_drv_api.h"

FLASH_ErasePage_Type FLASH_ErasePage_ptr = FLASH_ErasePage;
FLASH_ProgramHalfWord_Type FLASH_ProgramHalfWord_ptr= FLASH_ProgramHalfWord;
unsigned char (*PROJ_CHK_SAE_J1850_0x1D_ptr)(uint8_t* , uint8_t) = PROJ_CHK_SAE_J1850_0x1D_ADD;
void (*FLASH_SetLatency_ptr)() = FLASH_SetLatency;
void (*FLASH_Lock_ptr)() = FLASH_Lock;
void (*FLASH_Unlock_ptr)() = FLASH_Unlock;

/////////////////////////////////////////////////////////

/// @brief this global variable
/// @brief check wether flash erase done before perform write-flash or nor
/// @brief if need perform write flash, this variable must be set to true
static bool g_isEraseFlashDONE = false;

///@brief
///check flash driver api loaded in RAM
///@param [out] 0: valid api
///             1: invalid api
uint8_t flashing_check_api_flash_drv()
{
    if(*FLASH_SetLatency_ptr ==0)
        return 1;
    return 0;
}


uint8_t flashing_execute_flash_erase(uint8_t start_page , uint8_t number_of_page)
{
    //mapping start page to address of start page
    uint32_t start_page_address = start_page*400 + 0x08000000;
    uint8_t status =1;

    for (uint8_t page_idx = start_page; page_idx++; page_idx < number_of_page)
    {
	    FLASH_Unlock_ptr();
	    status = (uint8_t)FLASH_ErasePage_ptr(start_page_address);
        start_page_address = start_page_address +400;
	    FLASH_Lock_ptr();
    }
	return status;
}


ServiceTaskResult_en flashing_handle_flash_erase(uint8_t *pBuffer)
{
    ServiceTaskResult_en erase_status = 0x00;

    //Total length of the command packet
	uint32_t command_packet_len = pBuffer[0]+1 ;
    uint8_t start_page = pBuffer[2];
    uint8_t num_of_page = pBuffer[3];

    //check valid input
    //check page and num of page to erase
    //10 page of fbl, not allow erase
    if ((start_page < 64)&(start_page > 10)&(num_of_page <64 -10))
    {
        if (flashing_execute_flash_erase(start_page , num_of_page) == 0)
            erase_status = SERVICE_TASK_SUCCESSFUL;
    }
    else 
    {   erase_status = SERVICE_NRC_INVALID_INPUT_DATA;}

    return erase_status;
}

uint8_t flashing_verify_address(uint8_t* go_address)
{
    uint32_t address_compile = go_address[3]+ go_address[2]<<8+ go_address[1]<<16+ go_address[0]<<24;

    if ((address_compile <= APP_BASE_ADDRESS_MAX) && (address_compile >= APP_BASE_ADDRESS_MIN))
        return 0;
    else
        return 1;
}


/// @brief this function for erase-service state machine
/// @brief it will loop in this function until service done or error
/// @param [in] p_transportedData_st
/// @return status of service process
ServiceState_en bootloader_handle_flash_erase_sequence(TransportedData_st* p_transportedData_st)
{
    //reserve for advance handling

    static ServiceSM_en l_serviceState_en = SERVICE_SM_START;
    ServiceState_en r_value;

    ///TODO:
    ///only perform one check when start service
    if (l_serviceState_en == SERVICE_SM_START)
    {
        ///TODO:
        ///check flash driver api valid
        ///if there are no valid set of api driver 
        ///-> set sate to SEND_DATA and update p_transportedData_st to send NRC data
        if(flashing_check_api_flash_drv() == 1)
        {
            l_serviceState_en = SERVICE_SM_SEND_DATA;
            //update here
            p_transportedData_st->m_data_arr8[0] = 0;
        }
        else
        {
            l_serviceState_en = SERVICE_SM_SERVICE_HANDLE;
        }

    }

    ServiceTaskResult_en handle_status;
    switch(l_serviceState_en)
    {
        case SERVICE_SM_START:
            break;

        case SERVICE_SM_SERVICE_HANDLE:

            
            handle_status = flashing_handle_flash_erase(&(p_transportedData_st->m_data_arr8));

            if (handle_status == SERVICE_TASK_SUCCESSFUL)
            {
                l_serviceState_en = SERVICE_SM_SEND_DATA;

                ///TODO:
                ///update data here for send PRC
                p_transportedData_st->m_data_arr8[0] = 0;

                ///work-aground solution because Nvm is not available
                ///TODO:
                ///set it to true to indicate that: can perform write new app SW
                ///                                 accept write flash service request
                g_isEraseFlashDONE = true;

                ///TODO:
                ///Reserve function to update to Nvm
                ///set AppSWStatus to invalid
                (void)NvM_WriteAppSWStatus2Nvm(1);

            }
            else if (handle_status = SERVICE_NRC_INVALID_INPUT_DATA)
            { 
                l_serviceState_en = SERVICE_SM_SEND_DATA;

                ///TODO:
                ///update data here for send NRC
                p_transportedData_st->m_data_arr8[0] = 0;
            }

            break;

        case SERVICE_SM_SEND_DATA:

            ///TODO:
            ///handle send positive respond
            ///complete erase old sw
            DiagCom_handleSendData(p_transportedData_st);

            ///TODO:
            ///set service state machine to new cycle
            l_serviceState_en = SERVICE_SM_SERVICE_HANDLE;
            r_value = SERVICE_DONE;

            break;

        case SERVICE_SM_RECIVE_DATA:
            break;
        default:
            break;
    }

    return r_value;
}

ServiceTaskResult_en flashing_execute_mem_flash_write(uint8_t *pBuffer, uint32_t mem_address)
{

    ServiceTaskResult_en r_value = SERVICE_NRC_WRITE_FLASH_FAIL;

    //We have to unlock flash module to get control of registers
    FLASH_Unlock_ptr();

    //Here we program the flash byte by byte
    uint32_t address = pBuffer[2]<<24 + pBuffer[3]<<16 + pBuffer[4]<<8 + pBuffer[5];
    uint16_t data = pBuffer[6]<<8 + pBuffer[7];

    
    //FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
    ///check wether program successful
    if (FLASH_ProgramHalfWord_ptr(address, data) == 0)
        r_value = SERVICE_TASK_SUCCESSFUL;

    FLASH_Lock_ptr();

    return r_value;
}


//4 bytes address
//2 bytes data
ServiceTaskResult_en flashing_handle_mem_write(uint8_t *pBuffer)
{
    ServiceTaskResult_en r_value ;
    //check CRC
    uint8_t checksum_value = pBuffer[0];
    
    //check address
    uint8_t* mem_address = pBuffer[2];
    uint8_t* data2cal_checksum = &pBuffer[1];

    uint8_t checksum_cal_value = PROJ_CHK_SAE_J1850_0x1D_ptr(data2cal_checksum, 7);

    if ( checksum_value == checksum_cal_value)
    {
        //check address
		if( flashing_verify_address(mem_address) == 0 )
		{
            //execute mem write
            r_value = flashing_execute_mem_flash_write(&pBuffer ,mem_address);

		}else
		{
            r_value = SERVICE_NRC_INVALID_INPUT_DATA;
		}
    }
    else
    {
        r_value = SERVICE_NRC_WRONG_CRC;
    }

    return r_value;
}

/// @brief this function for write-flash-service state machine
/// @brief it will loop in this function until service done or error
/// @param p_transportedData_st 
/// @return status of service process
ServiceState_en bootloader_handle_flash_write_sequence(TransportedData_st* p_transportedData_st)
{

    static ServiceSM_en l_serviceState_en = SERVICE_SM_START;
    ServiceState_en r_value;


    if (l_serviceState_en == SERVICE_SM_START)
    {
        //send to status can start flash or not
        //check memory erase
        uint8_t app_status = 0;
        if (g_isEraseFlashDONE == true)
        {   
            app_status = 1; //clean app

            ///TODO:
            ///send message accept request
            ///start send new SW
            p_transportedData_st;
            l_serviceState_en = SERVICE_SM_SEND_DATA;
        }
        else 
        {   app_status = 0; //NRC app flash status not clean
            DiagCom_ACK_NRC_messasgeHandle(SERVICE_BOOTLOADER_WRITE_FLASH,  app_status );

            l_serviceState_en = SERVICE_SM_START;
            ///TODO:
            ///flush data for new state machine
            p_transportedData_st =0;
        }
    }

    switch(l_serviceState_en)
    {
        case SERVICE_SM_START:
            break;

        case SERVICE_SM_SERVICE_HANDLE:
        {
        /// use { here
        /// because error: a label can only be part of a statement and a declaration is not a statement

            uint8_t p_serviceData[8];
            for (uint8_t idx = 0; idx<8; idx++)
            {
                p_serviceData[idx] = p_transportedData_st->m_data_arr8[idx];
            }
            //receive new start address and new size
            uint8_t* new_start_address = &p_serviceData[1];
            uint32_t address_compile = new_start_address[3]+ new_start_address[2]<<8+ new_start_address[1]<<16+ new_start_address[0]<<24;
            uint16_t new_app_size = p_serviceData[5]<<8 +p_serviceData[6]; // uint:byte

            ///TODO:
            ///check size of new SW and start address of new SW
            ///included in message 2nd of sequence
            if (flashing_verify_address(new_start_address)==0 )
            {

                if ( (address_compile + new_app_size) < END_ADDRESS_FLASH)
                {
                    ///TODO:
                    ///send PRC and accept start receive new SW
                    p_transportedData_st->m_data_arr8[0] = 0;
                    l_serviceState_en = SERVICE_SM_SEND_DATA;
                }
                else
                {
                    ///TODO:
                    ///send NRC because of invalid size of new SW
                    p_transportedData_st->m_data_arr8[0] = 0;
                    l_serviceState_en = SERVICE_SM_SEND_DATA;
                }
            }

            ///TODO:
            ///start receive data and write to flash
            ///check valid address
            uint8_t p_serviceData_arr[8];
            for (uint8_t idx = 0; idx<8; idx++)
            {
                p_serviceData[idx] = p_transportedData_st->m_data_arr8[idx];
            }
            uint32_t start_address = p_serviceData_arr[2]<<24 +p_serviceData_arr[3]<<16+ p_serviceData_arr[4]<<8 +p_serviceData_arr[5];
            uint32_t address_counter = 0; //increase each new data message
            if( start_address ==(address_compile + address_counter*4) )
            {
                flashing_handle_mem_write(p_transportedData_st->m_data_arr8);
                address_counter++;
                ///TODO:
                ///write successful and send status 
                p_transportedData_st;
                l_serviceState_en = SERVICE_SM_SEND_DATA;
            }
            else 
            {
                ///TODO:
                ///send NRC because it is wrong address between received and expected
                p_transportedData_st;
                l_serviceState_en = SERVICE_SM_SEND_DATA; 
            }
        }
            break;

        case SERVICE_SM_SEND_DATA:

            ///TODO:
            ///handle send respond
            DiagCom_handleSendData(p_transportedData_st);

            ///TODO:
            ///set service state machine to idle
            l_serviceState_en = SERVICE_SM_IDLE;
            r_value = SERVICE_HANDLE;
            break;
        case SERVICE_SM_RECIVE_DATA:

            l_serviceState_en = SERVICE_SM_SERVICE_HANDLE;
            
            break;

        case SERVICE_SM_IDLE:

            if (g_transmitData_st.m_metaData = METADATA_NEWDATA_SWIL)
            {
                if (g_transmitData_st.m_semaphoreToken_u8 == 0)
                {
                l_serviceState_en = SERVICE_SM_RECIVE_DATA;
                //update g_transmitData_st
                }
            } else
            {   l_serviceState_en = SERVICE_SM_IDLE;}
            
            break;

        default:
            break;

    }

}




