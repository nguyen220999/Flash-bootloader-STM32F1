
/* -------------------------------- Arctic Core ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * -------------------------------- Arctic Core ------------------------------*/

#ifndef CRC_H_
#define CRC_H_

#include <stdint.h>
/** req 3.1.5|CRC022 */


#define CRC_VENDOR_ID			    VENDOR_ID_ARCCORE
#define CRC_MODULE_ID			    MODULE_ID_CRC
#define CRC_AR_MAJOR_VERSION  		3
#define CRC_AR_MINOR_VERSION 		1
#define CRC_AR_PATCH_VERSION		5

#define CRC_SW_MAJOR_VERSION		1
#define CRC_SW_MINOR_VERSION 		0
#define CRC_SW_PATCH_VERSION		0



uint8_t PROJ_CHK_SAE_J1850_0x1D (uint8_t ptr[], uint8_t p_length);

#if ( CRC_VERSION_INFO_API == STD_ON )
#define Crc_GetVersionInfo(_vi) STD_GET_VERSION_INFO(_vi,CRC)
#endif


#endif /* CRC_H_ */
