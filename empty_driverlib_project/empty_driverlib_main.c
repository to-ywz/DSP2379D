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

void Reg_setupOutputPin(uint32_t pin);
void Fun_setupOutputPin(uint32_t pin);
void test_function(void);

//
// Main
//
void main(void)
{
    // ϵͳ��ʼ��
    Device_init();

    // Reg_setupOutputPin(24);
    Fun_setupOutputPin(24);

    // ���Ժ���
    test_function();

    while (1)
        ;
}

/**
 * @b ��ʼ�� pin Ϊ���ģʽ
 */
void Fun_setupOutputPin(uint32_t pin)
{
    GPIO_setPinConfig(pin);                          // ����Ϊ ͨ���������ģʽ
    GPIO_setDirectionMode(pin, GPIO_DIR_MODE_OUT);   // ����Ϊ ���ģʽ
    GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);       // ����Ϊ �������
}

/**
 * @b ��ʼ�� pin Ϊ���ģʽ
 */
void Reg_setupOutputPin(uint32_t pin)
{
    uint32_t pinMask = 0;                   // ���� 1λ�Ĵ�������
    uint32_t muxPinMask = 0;                // MUX �Ĵ�������
    volatile uint32_t *gpioCtrlReg = NULL;  // ָ�� gpioCtrlReg �� ָ��

    // ��λ GPIOA���мĴ������׵�ַ, GPIO_CTRL_REGS_STEP �ǼĴ�������,һ��GPIO�Ĵ����ĳ���
    gpioCtrlReg = (uint32_t*) ((uintptr_t) GPIOCTRL_BASE
            + (pin / 32) * GPIO_CTRL_REGS_STEP);

    // Ҫ����λ�������������
    pinMask = (uint32_t) 1U << (pin % 32);
    // һ�� MUX ���� 16������, ���� �� 16 ȡ����
    // �� 2 ����Ϊһ�����Ŷ�Ӧ����λ, ÿ��һ������Ҫ ����λ
    muxPinMask = ((uint32_t) 3U << ((pin % 16) * 2));

    EALLOW;
    // ����Ϊ���ģʽ
    gpioCtrlReg[GPIO_GPxDIR_INDEX] |= pinMask;
    // ����Ϊ�������
    gpioCtrlReg[GPIO_GPxODR_INDEX] &= ~pinMask;
    // ����λ ͨ�����ģʽ
    if ((int)(pin % 32) - 16 >= 0)    // �ж���������MUX1 ���� MUX2
    {//Ϊʲô+1������ +2 ��ҲûŪ��,��ͷ,��Ū���ٸ���
        gpioCtrlReg[GPIO_GPxMUX_INDEX + 1] &= ~muxPinMask;
    }
    else
    {
        gpioCtrlReg[GPIO_GPxMUX_INDEX] &= ~muxPinMask;
    }
    EDIS;
}

/**
 * @b ���Ժ���:����6������
 */
void test_function(void)
{
    uint32_t pin = 24;
    uint32_t pinMask = 0;
    volatile uint32_t *gpioDataRegs = NULL;

    gpioDataRegs = (uint32_t*) ((uintptr_t) GPIODATA_BASE + (pin / 32) * 0x8);
    pinMask = (uint32_t) 1U << (pin % 32);

    for (volatile int i = 0; i < 12; i++)
    {
        gpioDataRegs[GPIO_GPxTOGGLE_INDEX] |= pinMask;
        int j = 1000;
        while (j--)
            ;
    }
}

//
// End of File
//
