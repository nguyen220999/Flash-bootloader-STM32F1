

set ( APPLICATION_SOURCE 

    Diag_com/Diag_communication.c
    Diag_com/Diag_communication.h

    ECU_Cfg/ECU_MemoryLayout.h

    Flashing_Hdl/flash_drv_api.h
    Flashing_Hdl/flash_hw_service.c
    Flashing_Hdl/flash_service_pub.h

    main/main_state_machine/main_sm_pri.h
    main/main_state_machine/main_sm_pub.h
    main/main_state_machine/main_sm.c

    main/hardware_handle/stm32f10x_it.c
    main/hardware_handle/stm32f10x_it.h
    main/hardware_handle/stm32f10x_conf.h
    main/hardware_handle/platform_config.h

    main/main.c
    main/main.h

    NvM_Hdl/NvM_handle_pub.h
    NvM_Hdl/NvM_handle.c

    Service_Hdl/app_jumping.c
    Service_Hdl/service_pri.h
    Service_Hdl/service_pub.h
    Service_Hdl/service_sm.c
    Service_Hdl/service.c

    SWIL_Hdl/SWIL_service_pri.h
    SWIL_Hdl/SWIL_service_pub.h
    SWIL_Hdl/SWIL_sm.c

)