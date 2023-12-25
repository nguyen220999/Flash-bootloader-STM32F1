
#include "main_sm_pub.h"
typedef enum
{
    NVM_WRITE_DATA_DONE,
    NVM_WRITE_DATA_ERROR
} NvMWriteDataStatus_en;


NvMWriteDataStatus_en NvM_WriteAppSWStatus2Nvm(uint8_t p_buffer);

NvMWriteDataStatus_en NvM_WriteReflashFlag2Nvm(uint8_t p_buffer);

uint8_t NvM_ReadAppSWStatusFromNvm();
uint8_t NvM_ReadReflashFlag();


