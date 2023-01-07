//###########################################################################
//
// FILE:   main_cpu01.c
//
// TITLE:  Empty Example for F2837xD.
//
//! \addtogroup cpu01_example_list
//! <h1> Empty Project </h1>
//!
//! This is an empty project for bit field development
//!
//! \note If using a Launchpad, use the Launchpad build configurations.
//!
//
//###########################################################################
//
// $Release Date:  $
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
//###########################################################################

//
// Included Files
//
#include "F28x_Project.h"

void Fun_GpioCfg(void);
void Reg_GpioCfg(void);
void test_function(void);

void main(void)
{

    InitSysCtrl();  // ��ʼ��ϵͳ����,(��������ʱ��, �رտ��Ź�...)
    InitGpio();     // ��ʼ�� GPIO ģ��

    // ���ж�
    DINT;
    InitPieCtrl();      // ��ʼ���жϿ�����
    InitPieVectTable(); //��ʼ���ж�������
    // ���ж�
    EINT;

    // ��ʼ��GPIO, ��ѡһ����
    Reg_GpioCfg();
    //Fun_GpioCfg();


    test_function();

    while (1)
    {

    }
}

/**
 * @b ���Ժ���:����5������
 */
void test_function(void)
{
    for (volatile int i = 0; i < 10; i++)
    {
        GpioDataRegs.GPATOGGLE.bit.GPIO24 = 1;
        int j = 1000;
        while (j--)
            ;
    }
}

/**
 * @b �������� ����
 */
void Fun_GpioCfg(void)
{
    GPIO_SetupPinMux(24, GPIO_MUX_CPU1, 0);                 // 31 ������ΪGPIO
    GPIO_SetupPinOptions(24, GPIO_OUTPUT, GPIO_PULLUP);     // 31 ������Ϊ �������
}

/**
 * @b �Ĵ�����������
 */
void Reg_GpioCfg(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO24 = 1;
    GpioCtrlRegs.GPAODR.bit.GPIO24 = 0;
    EDIS;
}

//
// End of file
//
