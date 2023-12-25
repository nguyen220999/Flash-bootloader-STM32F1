/*
 * Copyright 2001-2010 Georges Menie (www.menie.org)
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the University of California, Berkeley nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "Crc.h"

/* CRC16 implementation according to CCITT standards */

static const uint8_t CRC_8_H1D_Tbl[256] =
    {
        /*  0:*/ 0x00, 0x1d, 0x3a, 0x27, 0x74, 0x69, 0x4e, 0x53,
        /*  8:*/ 0xe8, 0xf5, 0xd2, 0xcf, 0x9c, 0x81, 0xa6, 0xbb,
        /* 16:*/ 0xcd, 0xd0, 0xf7, 0xea, 0xb9, 0xa4, 0x83, 0x9e,
        /* 24:*/ 0x25, 0x38, 0x1f, 0x02, 0x51, 0x4c, 0x6b, 0x76,
        /* 32:*/ 0x87, 0x9a, 0xbd, 0xa0, 0xf3, 0xee, 0xc9, 0xd4,
        /* 40:*/ 0x6f, 0x72, 0x55, 0x48, 0x1b, 0x06, 0x21, 0x3c,
        /* 48:*/ 0x4a, 0x57, 0x70, 0x6d, 0x3e, 0x23, 0x04, 0x19,
        /* 56:*/ 0xa2, 0xbf, 0x98, 0x85, 0xd6, 0xcb, 0xec, 0xf1,
        /* 64:*/ 0x13, 0x0e, 0x29, 0x34, 0x67, 0x7a, 0x5d, 0x40,
        /* 72:*/ 0xfb, 0xe6, 0xc1, 0xdc, 0x8f, 0x92, 0xb5, 0xa8,
        /* 80:*/ 0xde, 0xc3, 0xe4, 0xf9, 0xaa, 0xb7, 0x90, 0x8d,
        /* 88:*/ 0x36, 0x2b, 0x0c, 0x11, 0x42, 0x5f, 0x78, 0x65,
        /* 96:*/ 0x94, 0x89, 0xae, 0xb3, 0xe0, 0xfd, 0xda, 0xc7,
        /*104:*/ 0x7c, 0x61, 0x46, 0x5b, 0x08, 0x15, 0x32, 0x2f,
        /*112:*/ 0x59, 0x44, 0x63, 0x7e, 0x2d, 0x30, 0x17, 0x0a,
        /*120:*/ 0xb1, 0xac, 0x8b, 0x96, 0xc5, 0xd8, 0xff, 0xe2,
        /*128:*/ 0x26, 0x3b, 0x1c, 0x01, 0x52, 0x4f, 0x68, 0x75,
        /*136:*/ 0xce, 0xd3, 0xf4, 0xe9, 0xba, 0xa7, 0x80, 0x9d,
        /*144:*/ 0xeb, 0xf6, 0xd1, 0xcc, 0x9f, 0x82, 0xa5, 0xb8,
        /*152:*/ 0x03, 0x1e, 0x39, 0x24, 0x77, 0x6a, 0x4d, 0x50,
        /*160:*/ 0xa1, 0xbc, 0x9b, 0x86, 0xd5, 0xc8, 0xef, 0xf2,
        /*168:*/ 0x49, 0x54, 0x73, 0x6e, 0x3d, 0x20, 0x07, 0x1a,
        /*176:*/ 0x6c, 0x71, 0x56, 0x4b, 0x18, 0x05, 0x22, 0x3f,
        /*184:*/ 0x84, 0x99, 0xbe, 0xa3, 0xf0, 0xed, 0xca, 0xd7,
        /*192:*/ 0x35, 0x28, 0x0f, 0x12, 0x41, 0x5c, 0x7b, 0x66,
        /*200:*/ 0xdd, 0xc0, 0xe7, 0xfa, 0xa9, 0xb4, 0x93, 0x8e,
        /*208:*/ 0xf8, 0xe5, 0xc2, 0xdf, 0x8c, 0x91, 0xb6, 0xab,
        /*216:*/ 0x10, 0x0d, 0x2a, 0x37, 0x64, 0x79, 0x5e, 0x43,
        /*224:*/ 0xb2, 0xaf, 0x88, 0x95, 0xc6, 0xdb, 0xfc, 0xe1,
        /*232:*/ 0x5a, 0x47, 0x60, 0x7d, 0x2e, 0x33, 0x14, 0x09,
        /*240:*/ 0x7f, 0x62, 0x45, 0x58, 0x0b, 0x16, 0x31, 0x2c,
        /*248:*/ 0x97, 0x8a, 0xad, 0xb0, 0xe3, 0xfe, 0xd9, 0xc4
    };


uint8_t PROJ_CHK_SAE_J1850_0x1D (uint8_t* ptr, uint8_t p_length)
{
    uint8_t t_RetCrc;
    uint8_t t_CRC_temp;
    uint8_t t_index;

    t_CRC_temp = 0x00;
  
    for (t_index = 0; t_index < (p_length + 1); ++t_index)
    {
        t_CRC_temp ^= ptr[t_index];
        t_CRC_temp = CRC_8_H1D_Tbl[t_CRC_temp];
    }
    t_CRC_temp ^= 0x00;
  
    t_RetCrc = t_CRC_temp;

    return t_RetCrc;
}
