//#ifndef SERVICE_HDL_SERVICE_PRI_H
//#define SERVICE_HDL_SERVICE_PRI_H

#include "service_pub.h"
#include "main_sm_pub.h"

void bootloader_jump_to_user_app(void);

#define ERASE_TIMEOUT 50 //ms
#define WRITE_HAFTWORK_TIMEOUT 50 //ms



#define LOOP_SERVICE_SEQUENCE(X)    while ((X != SERVICE_DONE) && (X != SERVICE_ERROR))



ServiceSM_en bootloader_handle_service(TransportedData_st *pBuffer);


//#endif