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
    // 系统初始化
    Device_init();

    // Reg_setupOutputPin(24);
    Fun_setupOutputPin(24);

    // 测试函数
    test_function();

    while (1)
        ;
}

/**
 * @b 初始化 pin 为输出模式
 */
void Fun_setupOutputPin(uint32_t pin)
{
    GPIO_setPinConfig(pin);                          // 配置为 通用输入输出模式
    GPIO_setDirectionMode(pin, GPIO_DIR_MODE_OUT);   // 配置为 输出模式
    GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);       // 配置为 推挽输出
}

/**
 * @b 初始化 pin 为输出模式
 */
void Reg_setupOutputPin(uint32_t pin)
{
    uint32_t pinMask = 0;                   // 其他 1位寄存器掩码
    uint32_t muxPinMask = 0;                // MUX 寄存器掩码
    volatile uint32_t *gpioCtrlReg = NULL;  // 指向 gpioCtrlReg 的 指针

    // 定位 GPIOA所有寄存器的首地址, GPIO_CTRL_REGS_STEP 是寄存器步长,一组GPIO寄存器的长度
    gpioCtrlReg = (uint32_t*) ((uintptr_t) GPIOCTRL_BASE
            + (pin / 32) * GPIO_CTRL_REGS_STEP);

    // 要被置位的引脚掩码计算
    pinMask = (uint32_t) 1U << (pin % 32);
    // 一个 MUX 管理 16个引脚, 所以 对 16 取余数
    // 乘 2 是因为一个引脚对应两个位, 每过一个引脚要 移两位
    muxPinMask = ((uint32_t) 3U << ((pin % 16) * 2));

    EALLOW;
    // 设置为输出模式
    gpioCtrlReg[GPIO_GPxDIR_INDEX] |= pinMask;
    // 设置为推挽输出
    gpioCtrlReg[GPIO_GPxODR_INDEX] &= ~pinMask;
    // 设置位 通用输出模式
    if ((int)(pin % 32) - 16 >= 0)    // 判断引脚属于MUX1 还是 MUX2
    {//为什么+1而不是 +2 我也没弄懂,挠头,等弄懂再更新
        gpioCtrlReg[GPIO_GPxMUX_INDEX + 1] &= ~muxPinMask;
    }
    else
    {
        gpioCtrlReg[GPIO_GPxMUX_INDEX] &= ~muxPinMask;
    }
    EDIS;
}

/**
 * @b 测试函数:产生6个方波
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
