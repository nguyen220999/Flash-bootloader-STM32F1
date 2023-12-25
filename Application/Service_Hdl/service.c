
#include "service_pub.h"
#include "service_pri.h"


ServiceSM_en service_sm(TransportedData_st* p_message)
{
    ServiceSM_en l_serviceSet2NextState_en;
        
    l_serviceSet2NextState_en = bootloader_handle_service(p_message);

    if(l_serviceSet2NextState_en == SERVICE_SM_IDLE)
    {
        
    }

    return l_serviceSet2NextState_en;

}