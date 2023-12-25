
#include "SWIL_service_pri.h"
#include "SWIL_service_pub.h"
#include "main_sm_pub.h"
#include "flash_drv_api.h"

ServiceSWILPrivateState_en SWIL_verify_ram_address( uint8_t* p_inputMemAddress);
ServiceSWILPrivateState_en SWIL_CopyData2RAM(uint32_t p_address, uint16_t p_data);
ServiceSWILPrivateState_en SWIL_execute_swil_write(uint8_t *pBuffer);
ServiceSWILPrivateState_en SWIL_handle_write_swil(uint8_t *pBuffer);
ServiceSWILSendDataStatus_en SWIL_handleSendData(TransportedData_st* p_transportedData);
bool SWIL_checkTransitionHandle2Send(uint8_t *p_message, ServiceSM_en* p_transportedData);

ServiceState_en bootloader_handle_write_swil_sequence(TransportedData_st *p_transportedData_st)
{
    
    static ServiceSM_en l_serviceState_en = SERVICE_SM_START;
    ServiceState_en r_value;
    ServiceSWILPrivateState_en l_serviceSWILPrivateStatus;
    
    switch (l_serviceState_en)
    {
        case SERVICE_SM_START:
            break;
        case SERVICE_SM_SERVICE_HANDLE:
        {
            ///after service handle check valid service
            ///it call bootloader_handle_write_swil_sequence
            ///if it is first message receive, then service handle state move to send data state to send accept service 
            ///check first message receive
            ///if checkTransitionHandle2Send equal true
            ///change state to SERVICE_SM_SEND_DATA and end handle state
            ///else handle bootloader_handle_write_swil
            ///get status from bootloader_handle_write_swil to set next state

            uint8_t l_message_arr[8];
            for (uint8_t idx =0; idx < 8; idx++)
            {
                l_message_arr[idx] = p_transportedData_st->m_data_arr8[idx] ;
            } 
            
            ///TODO:
            ///update data before jump to SEND_DATA STATE
            if (SWIL_checkTransitionHandle2Send(&l_message_arr, p_transportedData_st))
            {
                l_serviceState_en = SERVICE_SM_SEND_DATA;
            }
            else 
            {
                l_serviceSWILPrivateStatus = SWIL_handle_write_swil(&l_message_arr);

                if (l_serviceSWILPrivateStatus == SERVICE_SWIL_COPYDATA2RAM_ERROR)
                {
                    //update data to g_transmitData_st 
                    l_serviceState_en = SERVICE_SEND_DATA;
                } 
                else if (l_serviceSWILPrivateStatus == SERVICE_SWIL_RAMADDRESS_ERROR)
                {   //update data to g_transmitData_st 
                    l_serviceState_en = SERVICE_SEND_DATA;
                } 
                else
                {   //update data to g_transmitData_st 
                    l_serviceState_en = SERVICE_SEND_DATA;
                }
            }

            break;
        }
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

        case SERVICE_SM_SEND_DATA:
        {
            ServiceSWILSendDataStatus_en l_SendDataStatus = SWIL_handleSendData(&g_transmitData_st);

            //send accept request
            if (g_transmitData_st.m_semaphoreToken_u8 == 0)
            {   
                //need update data here
                g_transmitData_st.m_data_arr8[0] = 0;
                g_transmitData_st.m_metaData = METADATA_NEWDATA_SWIL;

                if (g_transmitData_st.m_data_arr8[0] = 1/*done*/)
                {   l_serviceState_en = SERVICE_DONE;}
                else
                {   l_serviceState_en = SERVICE_IDLE;}

            } else
            {   l_serviceState_en = SERVICE_SEND_DATA;}

            if(l_SendDataStatus = SEND_DATA_STATE_JUMP2IDLE)
            {
                l_serviceState_en = SERVICE_SM_IDLE;
            }
            else if (l_SendDataStatus = SEND_DATA_STATE_END_SERVICE_NRC)
            {
                l_serviceState_en = SERVICE_SM_ERROR;
            }

            break;
        }
        case SERVICE_SM_RECIVE_DATA:

            l_serviceState_en = SERVICE_SM_SERVICE_HANDLE;

            break;
        
        default:
            break;
    }

    return r_value;
}

bool SWIL_checkTransitionHandle2Send(uint8_t *p_message, ServiceSM_en* p_transportedData)
{
    if (p_message[0] == SERVICE_BOOTLOADER_WRITE_SWIL)
    {
        // update p_transportedData;
        return true;
    } else 
    {   //p_transportedData
        return false;}
}

///api wrapper to handle calling diag_com api
ServiceSWILSendDataStatus_en SWIL_handleSendData(TransportedData_st* p_transportedData)
{
    if (p_transportedData->m_data_arr8[0] == 0/*NRC check*/)
    {
        //need updae data here
        uint8_t serviceID = p_transportedData->m_data_arr8[0];
        uint8_t NRC_value = p_transportedData->m_data_arr8[0];
        DiagCom_ACK_NRC_messasgeHandle(serviceID, NRC_value);
        return SEND_DATA_STATE_END_SERVICE_NRC;
    }
    else
    {
        //need updae data here
        uint8_t serviceID = p_transportedData->m_data_arr8[0];
        uint8_t data = p_transportedData->m_data_arr8[0];
        DiagCom_ACK_messageServiceStatusHandle(serviceID, data);
        return SEND_DATA_STATE_JUMP2IDLE;
    }
    //need handle remain case
}

//4 bytes address
//2 bytes data
ServiceSWILPrivateState_en SWIL_handle_write_swil(uint8_t *pBuffer)
{
    ServiceSWILPrivateState_en r_servicePrivateState_en;

    //check CRC
    uint8_t l_checksum_value_u8 = pBuffer[0];
    
    //check address
    uint8_t* l_mem_address_u8 = pBuffer[2];
    uint8_t* l_data2cal_checksum_u8 = &pBuffer[1];

    uint8_t l_checksum_cal_value_u8 = PROJ_CHK_SAE_J1850_0x1D_ptr(l_data2cal_checksum_u8, 7);

    if ( l_checksum_value_u8 == l_checksum_cal_value_u8)
    {
        //check address
		if( SWIL_verify_ram_address(l_mem_address_u8) == SERVICE_SWIL_RAMADDRESS_VALID )
		{
            //execute mem write
            r_servicePrivateState_en = SWIL_execute_swil_write(&pBuffer);

		}else
		{
            r_servicePrivateState_en = SERVICE_SWIL_RAMADDRESS_ERROR;
		}
    }
    else
    {   r_servicePrivateState_en = SERVICE_ERROR;}

    return r_servicePrivateState_en;
}

ServiceSWILPrivateState_en SWIL_execute_swil_write(uint8_t *pBuffer)
{
    ServiceSWILPrivateState_en r_status=0;
    uint32_t l_address = pBuffer[2]<<24 + pBuffer[3]<<16 + pBuffer[4]<<8 + pBuffer[5];
    uint16_t l_data_u16 = pBuffer[6]<<8 + pBuffer[7];

    r_status = SWIL_CopyData2RAM(l_address, l_data_u16);

    return r_status;
}

ServiceSWILPrivateState_en SWIL_CopyData2RAM(uint32_t p_address, uint16_t p_data)
{
    uint8_t* temp_add = p_address;
    uint8_t* temp_next_add = p_address +1;

    *temp_add = (uint8_t)p_data>>8;
    *temp_next_add = (uint8_t)p_data;

    return SERVICE_SWIL_COPYDATA2RAM_DONE;
}

ServiceSWILPrivateState_en SWIL_verify_ram_address( uint8_t* p_inputMemAddress)
{
    uint32_t l_address_compile = p_inputMemAddress[3]+ p_inputMemAddress[2]<<8+ p_inputMemAddress[1]<<16+ p_inputMemAddress[0]<<24;

    if ((l_address_compile <= SWIL_RAM_ADDRESS_END) & (l_address_compile >= SWIL_RAM_ADDRESS_START))
        return SERVICE_SWIL_RAMADDRESS_VALID;
    else
        return SERVICE_SWIL_RAMADDRESS_ERROR;
}
