#ifndef MAIN_STATE_MACHINE_MAIN_SM_PUB_H
#define MAIN_STATE_MACHINE_MAIN_SM_PUB_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    METADATA_NEWDATA_SWIL,
    METADATA_OLDDATA_SWIL,
    METADATA_NEWDATA_ERASE,
    METADATA_OLDDATA_ERASE,
    MEATADATA_INVALIDDATA
} MetaData_en;

//global data to transport data between states in state machine
//size is 8 byte due to fit with CAN message size
//use binary semaphore to protect data consistency
typedef struct 
{
    uint8_t m_data_arr8[8];

    //0: free
    //1: in updating
    uint8_t m_semaphoreToken_u8;

    MetaData_en m_metaData;

} TransportedData_st;

extern TransportedData_st g_transmitData_st;


#endif