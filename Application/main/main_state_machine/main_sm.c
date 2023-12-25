


#include "main_sm_pri.h"
#include "main_sm_pub.h"
#include "service_pub.h"

static uint8_t g_main_state = MAIN_SM_NVM_CHECK_INIT;
static uint8_t g_waitTime = WAIT_TIMER_TO_JUMP_TO_APP;

///@brief
///this is gobal variable for transporting data in service state machine
///when ever receive CAN message -> update data to it for injecting data to service state machine
///when ever send CAN message -> update data to it and change state to SEND_DATA to send in CAN 
TransportedData_st g_transmitData_st;

///@brief
///handle main state machine
/// this function is called when main function start in while loop
///     -1: check app-valid-status-nvm (1), flashing-flag-nvm (2)
///     -2: if (1) & (2) true -> wait to expire timeout timer -> jump to app
///             (1) true & (2) false -> wait to expire timeout timer -> jump to app
///     @note sw only support (1) & (2) true
///@param [in] 
///@param [out]
void main_sm(void)
{
    switch (g_main_state)
    {
        case MAIN_SM_NVM_CHECK_INIT:
        {
            //call Nvm check function
            uint8_t isNvMcheck;

            if(isNvMcheck == NVMCHECK_APP_TRUE_AND_FLASHFLAG_FALSE)
            {
                g_main_state = MAIN_SM_JUMPING_APP_SW;
            } else
            {
                g_main_state = MAIN_SM_IDLE;
            }
            break;
        }
        case MAIN_SM_JUMPING_APP_SW:

            ///TODO:
            ///call function jump to app
            bootloader_jump_to_user_app();
            break;

        case MAIN_SM_IDLE:
        {
            //wait service receive
            //can receive message
            bool l_isNewMessage_b;

            ///TODO:
            ///call Nvm check again
            uint8_t l_isNvMcheck_u8;

            if (l_isNvMcheck_u8== NVMCHECK_APP_TRUE_AND_FLASHFLAG_FALSE)
            {
                if (g_waitTime ==0)
                {
                    g_main_state = MAIN_SM_JUMPING_APP_SW;
                } else
                {
                    g_waitTime--;
                }
            }

            if (g_waitTime >0)
            {
                if(l_isNewMessage_b == true) 
                {
                    ///TODO:
                    ///update message to local message
                    g_transmitData_st.m_data_arr8[0] = 0;
                    g_main_state = MAIN_SM_SERVICE_HANDLE;
                } else
                {
                    g_main_state = MAIN_SM_IDLE;
                }
            }
            break;
        }
        case MAIN_SM_SERVICE_HANDLE:
        {
            //jump to service state machine
            ServiceSM_en l_serviceHandleStatus = SERVICE_SM_START;

            ///TODO:
            ///loop in service state machine untill there is no request service
            ///untill service handle done
            l_serviceHandleStatus = service_sm(&g_transmitData_st);

            if (l_serviceHandleStatus == SERVICE_SM_IDLE)
            {
                g_main_state = MAIN_SM_IDLE;
            }

            break;
        }
        default:
        //wait until timeout timer expire
            break;
    }

}