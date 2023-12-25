
#include "Diag_communication.h"

void DiagCom_ACK_NRC_messasgeHandle(uint8_t serviceID, uint8_t NRC_value)
{
    //copy to com buffer
    uint8_t com_buffer[8]= {0xAA,0xAA,0xAA,0xAA, 0xAA,0xAA,0xAA,0xAA};

    com_buffer[0] = 0x7F;
    com_buffer[1] = serviceID;
    com_buffer[2] = NRC_value;

    //send to can bus
}

void DiagCom_ACK_messageServiceStatusHandle(uint8_t serviceID, uint8_t data)
{
    uint8_t com_buffer[8]= {0xAA,0xAA,0xAA,0xAA, 0xAA,0xAA,0xAA,0xAA,};

    com_buffer[0] = serviceID +40;
    com_buffer[1] = data;

    //send to can bus
}

///api wrapper to handle calling diag_com api
ServiceSendDataStatus_en DiagCom_handleSendData(TransportedData_st* p_transportedData)
{
    if (p_transportedData->m_data_arr8[0] == 0/*NRC check*/)
    {
        //need updae data here
        uint8_t serviceID = p_transportedData->m_data_arr8[0];
        uint8_t NRC_value = p_transportedData->m_data_arr8[0];
        DiagCom_ACK_NRC_messasgeHandle(serviceID, NRC_value);
        return SEND_DATA_STATE_END_SERVICE_NRC;
    }
    else if (p_transportedData->m_data_arr8[0] == 1/*jump to next state check*/)
    {
        //need updae data here
        uint8_t serviceID = p_transportedData->m_data_arr8[0];
        uint8_t data = p_transportedData->m_data_arr8[0];
        DiagCom_ACK_messageServiceStatusHandle(serviceID, data);
        return SEND_DATA_STATE_JUMP2IDLE;
    }
    else if (p_transportedData->m_data_arr8[0] == 2/*PRC check*/)
    {
        uint8_t serviceID = p_transportedData->m_data_arr8[0];
        uint8_t data = p_transportedData->m_data_arr8[0];
        DiagCom_ACK_messageServiceStatusHandle(serviceID, data);
        return SEND_DATA_STATE_END_SERVICE_SUC;
    }
    //need handle remain case
}







