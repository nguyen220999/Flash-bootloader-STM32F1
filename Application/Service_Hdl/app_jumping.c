#include "main_sm_pub.h"
#include "flash_service_pub.h"


extern void __set_MSP(uint32_t topOfMainStack);

void bootloader_jump_to_user_app(void)
{

   //just a function pointer to hold the address of the reset handler of the user app.
    void (*app_reset_handler)(void);


    // 1. configure the MSP by reading the value from the base address of the sector 2
    uint32_t msp_value = *(volatile uint32_t *)APP_BASE_ADDRESS_MIN;

    //This function comes from CMSIS.
    __set_MSP(msp_value);

    //SCB->VTOR = FLASH_SECTOR1_BASE_ADDRESS;

    /* 2. Now fetch the reset handler address of the user application
     * from the location FLASH_SECTOR2_BASE_ADDRESS+4
     */
    uint32_t resethandler_address = *(volatile uint32_t *) (APP_BASE_ADDRESS_MIN + 4);

    app_reset_handler = (void*) resethandler_address;


    //3. jump to reset handler of the user application
    app_reset_handler();

}
