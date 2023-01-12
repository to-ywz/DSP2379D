//#############################################################################
//
// FILE:   empty_driverlib_main.c
//
// TITLE:  Empty Project
//
// Empty Project Example
//
// This example is an empty project setup for Driverlib development.
//
//#############################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2013-2022 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

void gpioInputCfg(void);

//
// Main
//
void main(void)
{
    Device_init();

    gpioInputCfg();

    while (1)
    {
        if (GPIO_readPin(24)){
            DEVICE_DELAY_US(10000);;
            if (GPIO_readPin(24))
            {
                GPIO_togglePin(31);
            }
        }
    }
}

void gpioInputCfg(void)
{
    GPIO_setPinConfig(24);                              // 配置为GPIO模式
    GPIO_setQualificationMode(24, GPIO_QUAL_3SAMPLE);   // 配置为 3倍采样
    GPIO_setDirectionMode(24, GPIO_DIR_MODE_IN);        // 配置为输入模式
    GPIO_setPadConfig(24, GPIO_PIN_TYPE_PULLUP);        // 配置为上拉模式

    GPIO_setPinConfig(31);
    GPIO_setDirectionMode(31, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(31, GPIO_PIN_TYPE_STD);
}

//
// End of File
//
