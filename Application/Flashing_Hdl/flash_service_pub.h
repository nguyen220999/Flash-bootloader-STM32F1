
#include "main_sm_pub.h"
#include "service_pub.h"

#define APP_BASE_ADDRESS_MIN 0x08000000
#define APP_BASE_ADDRESS_MAX 0x08000000 + 560000 //size of app 56K


ServiceState_en bootloader_handle_flash_erase_sequence(TransportedData_st* p_transportedData_st);

ServiceState_en bootloader_handle_flash_write_sequence(TransportedData_st* p_transportedData_st);

