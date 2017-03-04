/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外初学论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 *      本程序主要测试DMA的脉冲计数功能，通过PWM输出接到DMA的触发管脚，计算得出PWM的脉冲周期
 *
 * @file       main.c
 * @brief      山外K60 平台主程序
 * @author     山外科技
 * @version    v5.0
 * @date       2017-03-05
 */

#include "common.h"
#include "include.h"

/*!
 *  @brief      main函数
 *  @since      v5.0
 *  @note       测试 LED 功能是否正常
                看到的效果是LED0和LED1同时亮灭闪烁
 */

void main()
{
    gpio_init(PTA15, GPO, 0);   //指示灯
    while(1)
    {        
        printf("hello\r\n");         
        DELAY_MS(50);                      //延时500ms
        gpio_turn(PTA15);
        DELAY_MS(50);                      //延时500ms
        gpio_turn(PTA15);
    }
}

