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
void test_function(uint8_t n);

//
// Main
//
void main(void)
{
    // ��ʼ����
    Device_init();

    // ��ʼ�� ����
    gpioInputCfg();

    while (1)
    {
        test_function(5);
        if (!GPIO_readPin(24))
        {// ���ż��
            DEVICE_DELAY_US(10 * 1000); // ������������
            if (!GPIO_readPin(24))
            {// ȷ�����ż��
                GPIO_writePin(25, 0);   // ����͵�ƽ
                DEVICE_DELAY_US(1000L); //ά��1ms
            }
        }
    }
}

void test_function(uint8_t n)
{
    for (int i = 0; i < n*2; i++){
        GPIO_togglePin(25); // ��ת��ƽ
        DEVICE_DELAY_US(100);
    }
}

/**
 * ���� GPIO24 Ϊ
 */
void gpioInputCfg(void)
{
    GPIO_setPinConfig(24);                              // ����ΪGPIOģʽ
    GPIO_setQualificationMode(24, GPIO_QUAL_SYNC);      // ����Ϊͬ������
    GPIO_setDirectionMode(24, GPIO_DIR_MODE_IN);        // ����Ϊ����ģʽ
    GPIO_setPadConfig(24, GPIO_PIN_TYPE_PULLUP);        // ����Ϊ����ģʽ

    // ����Ϊ���ģʽ
    GPIO_setPinConfig(25);
    GPIO_setDirectionMode(25, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(25, GPIO_PIN_TYPE_STD);
}

//
// End of File
//
