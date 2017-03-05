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
void PIT0_IRQHandler(void);

void main()
{
    gpio_init(PTA15, GPO, 0);   //指示灯
    
    FTM_QUAD_Init(FTM1);
    FTM_QUAD_Init(FTM2);

    pit_init_ms(PIT0, 200);                                 //初始化PIT0，定时时间为： 1000ms
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //设置PIT0的中断复位函数为 PIT0_IRQHandler
    enable_irq (PIT0_IRQn);                                 //使能PIT0中断

    while(1)
    {        
        DELAY_MS(50);                      //延时500ms
        gpio_turn(PTA15);
        DELAY_MS(50);                      //延时500ms
        gpio_turn(PTA15);
    }
}

void PIT0_IRQHandler(void)
{

    int16 val;
    val = FTM_QUAD_get(FTM2);          //获取FTM 正交解码 的脉冲数(负数表示反方向)
    FTM_QUAD_clean(FTM2);

    if(val>=0)
    {
        printf("\n正转：%d",val);
    }
    else
    {
        printf("\n反转：%d",-val);
    }


    PIT_Flag_Clear(PIT0);       //清中断标志位
}