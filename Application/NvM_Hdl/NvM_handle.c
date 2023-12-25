
#include "NvM_handle_pub.h"


/// @brief this is to write AppSWStatus to Nvm
/// @param [in] p_buffer: 1 valid App SW
///                       0 invalid App SW 
/// @return 
NvMWriteDataStatus_en NvM_WriteAppSWStatus2Nvm(uint8_t p_buffer)
{

}

/// @brief this is to write reflash flag to Nvm
/// @param [in] p_buffer: 1 Need wait time to re-flash
///                       0 No need wait time to re-flash 
/// @return 
NvMWriteDataStatus_en NvM_WriteReflashFlag2Nvm(uint8_t p_buffer)
{

}

/// @brief 
/// @return 
uint8_t NvM_ReadAppSWStatusFromNvm()
{
    return 0;
}

uint8_t NvM_ReadReflashFlag()
{
    return 0;
}