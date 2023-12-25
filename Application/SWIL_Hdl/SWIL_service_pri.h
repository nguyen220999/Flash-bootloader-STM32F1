
#include "service_pub.h"
#include "main_sm_pub.h"

#define SWIL_RAM_ADDRESS_START 0x20000000
#define SWIL_RAM_ADDRESS_END 0x20000FFF

//private of swil status
typedef enum
{
    SERVICE_SWIL_COPYDATA2RAM_DONE,
    SERVICE_SWIL_COPYDATA2RAM_ERROR,
    SERVICE_SWIL_RAMADDRESS_VALID,
    SERVICE_SWIL_RAMADDRESS_ERROR
} ServiceSWILPrivateState_en;

typedef enum
{
    SEND_DATA_STATE_WAIT,
    SEND_DATA_STATE_JUMP2IDLE,
    SEND_DATA_STATE_END_SERVICE_NRC,
    SEND_DATA_STATE_END_SERVICE_SUC
} ServiceSWILSendDataStatus_en;

extern TransportedData_st g_transmitData_st;