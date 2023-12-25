#ifndef FLASHING_HDL_FLASH_DRV_API_H
#define FLASHING_HDL_FLASH_DRV_API_H

#define FLASH_API_TABLE 0x20000000
#include "main_sm_pub.h"


#define END_ADDRESS_FLASH 0x08000000 + 560000 //dummy data, need check spec

#define BYTES_OFFSET 4

#define FLASH_SetLatency                    (FLASH_API_TABLE + 1*BYTES_OFFSET)
#define FLASH_HalfCycleAccessCmd            (FLASH_API_TABLE + 2*BYTES_OFFSET)
#define FLASH_PrefetchBufferCmd             (FLASH_API_TABLE + 3*BYTES_OFFSET)
#define FLASH_Unlock                        (FLASH_API_TABLE + 4*BYTES_OFFSET)
#define FLASH_Lock                          (FLASH_API_TABLE + 5*BYTES_OFFSET)
#define FLASH_ErasePage                     (FLASH_API_TABLE + 6*BYTES_OFFSET)
#define FLASH_EraseAllPages                 (FLASH_API_TABLE + 7*BYTES_OFFSET)
#define FLASH_EraseOptionBytes              (FLASH_API_TABLE + 8*BYTES_OFFSET)
#define FLASH_ProgramWord                   (FLASH_API_TABLE + 9*BYTES_OFFSET)
#define FLASH_ProgramHalfWord               (FLASH_API_TABLE + 10*BYTES_OFFSET)
#define FLASH_ProgramOptionByteData         (FLASH_API_TABLE + 11*BYTES_OFFSET)
#define FLASH_EnableWriteProtection         (FLASH_API_TABLE + 12*BYTES_OFFSET)
#define FLASH_ReadOutProtection             (FLASH_API_TABLE + 13*BYTES_OFFSET)
#define FLASH_UserOptionByteConfig          (FLASH_API_TABLE + 14*BYTES_OFFSET)
#define FLASH_GetUserOptionByte             (FLASH_API_TABLE + 15*BYTES_OFFSET)
#define FLASH_GetWriteProtectionOptionByte  (FLASH_API_TABLE + 16*BYTES_OFFSET)
#define FLASH_GetReadOutProtectionStatus    (FLASH_API_TABLE + 17*BYTES_OFFSET)
#define FLASH_GetPrefetchBufferStatus       (FLASH_API_TABLE + 18*BYTES_OFFSET)
#define FLASH_ITConfig                      (FLASH_API_TABLE + 19*BYTES_OFFSET)
#define FLASH_GetFlagStatus                 (FLASH_API_TABLE + 20*BYTES_OFFSET)
#define FLASH_ClearFlag                     (FLASH_API_TABLE + 21*BYTES_OFFSET)
#define FLASH_GetStatus                     (FLASH_API_TABLE + 22*BYTES_OFFSET)
#define FLASH_WaitForLastOperation          (FLASH_API_TABLE + 23*BYTES_OFFSET)

#define FLASH_UnlockBank1                   (FLASH_API_TABLE + 24*BYTES_OFFSET)
#define FLASH_LockBank1                     (FLASH_API_TABLE + 25*BYTES_OFFSET)
#define FLASH_EraseAllBank1Pages            (FLASH_API_TABLE + 26*BYTES_OFFSET)
#define FLASH_GetBank1Status                (FLASH_API_TABLE + 27*BYTES_OFFSET)
#define FLASH_WaitForLastBank1Operation     (FLASH_API_TABLE + 28*BYTES_OFFSET)
#define PROJ_CHK_SAE_J1850_0x1D_ADD         (FLASH_API_TABLE + 29*BYTES_OFFSET)

typedef unsigned char (*FLASH_ErasePage_Type)(uint32_t) ;
extern FLASH_ErasePage_Type FLASH_ErasePage_ptr;

//uint8_t (*FLASH_ProgramHalfWord_Test)(uint32_t, uint16_t) ;

typedef unsigned char (*FLASH_ProgramHalfWord_Type)(uint32_t, uint16_t) ;
extern FLASH_ProgramHalfWord_Type FLASH_ProgramHalfWord_ptr;

//uint8_t (*FLASH_ErasePage_Test)(uint32_t) ;
extern unsigned char (*PROJ_CHK_SAE_J1850_0x1D_ptr)(uint8_t* , uint8_t);

extern void (*FLASH_SetLatency_ptr)();
extern void (*FLASH_Lock_ptr)();
extern void (*FLASH_Unlock_ptr)();



#endif
