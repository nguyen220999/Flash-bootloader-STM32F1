
#include "main_sm_pub.h"

typedef enum
{
    SEND_DATA_STATE_WAIT,
    SEND_DATA_STATE_JUMP2IDLE,
    SEND_DATA_STATE_END_SERVICE_NRC,
    SEND_DATA_STATE_END_SERVICE_SUC
} ServiceSendDataStatus_en;


void DiagCom_ACK_NRC_messasgeHandle(uint8_t serviceID, uint8_t NRC_value);

void DiagCom_ACK_messageServiceStatusHandle(uint8_t serviceID, uint8_t data);

ServiceSendDataStatus_en DiagCom_handleSendData(TransportedData_st *p_transportedData);

