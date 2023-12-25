
///@def Nvm check init state
///perform check flag isAppValid and isNeedUpdateApp
#define MAIN_SM_NVM_CHECK_INIT 0

///call function jump to App
#define MAIN_SM_JUMPING_APP_SW 1

//call state machine to handle Diag service
#define MAIN_SM_SERVICE_HANDLE 2

///Wait time out to jump to App
///or wait service request receive
#define MAIN_SM_IDLE           3

#define NVMCHECK_APP_TRUE_AND_FLASHFLAG_TRUE 0
#define NVMCHECK_APP_TRUE_AND_FLASHFLAG_FALSE 1
#define NVMCHECK_APP_FALSE_AND_FLASHFLAG_TRUE 2
#define NVMCHECK_APP_FALSE_AND_FLASHFLAG_FALSE 3

#define WAIT_TIMER_TO_JUMP_TO_APP 500

#define NRC_INVALID_DATA_INPUT 1


#define SWIL_START_ADDRESS (uint8_t*)0x20000000

void main_sm(void);