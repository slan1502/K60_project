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

#define MOTOR11_IO      PTC1
#define MOTOR12_IO      PTC2

#define MOTOR_FTM       FTM0
#define MOTOR11_PWM     FTM_CH0       
#define MOTOR12_PWM     FTM_CH1       

/*!
 *  @brief      main函数
 *  @since      v5.0
 *  @note       测试 LED 功能是否正常
                看到的效果是LED0和LED1同时亮灭闪烁
 */
char DMA_COUNT_ADDR;
void dma_ch0_handler(void);
void dma_ch1_handler(void);
uint32 DMA0_TIME1=0, DMA0_TIME2, DMA0_DELAY=0;
uint32 count1=0, count2=0;

void main()
{
    gpio_init(PTA15, GPO, 0);   //指示灯
    
    //配置PWM
    FTM_PWM_init(MOTOR_FTM, MOTOR11_PWM, 100, 10);
    FTM_PWM_init(MOTOR_FTM, MOTOR12_PWM, 100, 10);
    //配置管脚的服用功能为ALT4 需要查 K60 Signal Multiplexing and Pin Assignments
    port_init(MOTOR11_IO, ALT4);
    port_init(MOTOR12_IO, ALT4);
    //DMA配置
    dma_portx2buff_init(DMA_CH0, &DMA_COUNT_ADDR, &DMA_COUNT_ADDR, PTB1, DMA_BYTE1, 0x7fff, DADDR_RECOVER);
    dma_portx2buff_init(DMA_CH1, &DMA_COUNT_ADDR, &DMA_COUNT_ADDR, PTC2, DMA_BYTE1, 0x7fff, DADDR_RECOVER);
    port_init_NoALT(PTB1, DMA_RISING);  //上升沿触发
    port_init_NoALT(PTC2, DMA_RISING);  //上升沿触发
    set_vector_handler(DMA0_VECTORn, dma_ch0_handler);
    set_vector_handler(DMA0_VECTORn, dma_ch1_handler);
    DMA_EN(DMA_CH0);                                    //使能通道DMA_CH0 硬件请求
    DMA_EN(DMA_CH1);                                    //使能通道DMA_CH0 硬件请求
    DMA_IRQ_EN(DMA_CH0);                                //允许DMA_CH0通道传输
    DMA_IRQ_EN(DMA_CH1);                                //允许DMA_CH0通道传输
    
    //使能计时功能
//    DEMCR            |=  (1<<24);        //使能 调试时钟 （默认已经打开）
//    DWT_CTRL         |=  (1<<0);
   
    while(1)
    {        
        
        DELAY_MS(50);                      //延时500ms
        gpio_turn(PTA15);
        DELAY_MS(50);                      //延时500ms
        gpio_turn(PTA15);
        count1 = 0x7fff-DMA_CITER_ELINKNO(DMA_CH0);
        count2 = 0x7fff-DMA_CITER_ELINKNO(DMA_CH1);
        printf("count1=%d, count2=%d\r\n", count1, count2);
    }
}

/*!
 *  @brief      DMA通道0中断
 *  @since      v5.0
 */
void dma_ch0_handler(void)
{
    DMA_IRQ_CLEAN(DMA_CH0);                  //清除通道传输中断标志位
//    //计算DMA整个主循环花费的时间
//    DMA0_TIME1 = DWT_CYCCNT;
//    if(DMA0_TIME1>DMA0_TIME2) DMA0_DELAY = DMA0_TIME1-DMA0_TIME2;
//    else DMA0_DELAY = 0xffffffff-DMA0_TIME2+DMA0_TIME1;
//    DMA0_DELAY = DMA0_DELAY/core_clk_khz;       //将DMA0_DELAY的单位转换为ms
//    DMA0_TIME2 = DMA0_TIME1;
      
    //DMA_DADDR(DMA_CH0) = BUFF;            //恢复地址 (由于初始化时配置为恢复目的地址，因而此处不需要)
    DMA_EN(DMA_CH0);                        //使能通道CHn 硬件请求
}
void dma_ch1_handler(void)
{
    DMA_IRQ_CLEAN(DMA_CH1);                  //清除通道传输中断标志位

    //DMA_DADDR(DMA_CH0) = BUFF;            //恢复地址 (由于初始化时配置为恢复目的地址，因而此处不需要)
    DMA_EN(DMA_CH1);                        //使能通道CHn 硬件请求
}

