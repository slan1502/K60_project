/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外初学论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       main.c
 * @brief      山外K60 平台主程序
 * @author     山外科技
 * @version    v5.0
 * @date       2013-08-28
 */

#include "common.h"
#include "include.h"

#define MOTOR11_IO      PTC1
#define MOTOR12_IO      PTC2
#define MOTOR21_IO      PTC3
#define MOTOR22_IO      PTC4
#define MOTOR31_IO      PTD4
#define MOTOR32_IO      PTD5

#define MOTOR_FTM       FTM0
#define MOTOR11_PWM     FTM_CH0       
#define MOTOR12_PWM     FTM_CH1       
#define MOTOR21_PWM     FTM_CH2       
#define MOTOR22_PWM     FTM_CH3       
#define MOTOR31_PWM     FTM_CH4       
#define MOTOR32_PWM     FTM_CH5

/*!
 *  @brief      main函数
 *  @since      v5.0
 *  @note       测试 LED 功能是否正常
                看到的效果是LED0和LED1同时亮灭闪烁
 */
void main()
{
    gpio_init(PTA15, GPO, 0);   //指示灯
    
    //配置PWM
    gpio_init(MOTOR11_IO, GPO, 0);
    gpio_init(MOTOR12_IO, GPO, 0);
    gpio_init(MOTOR21_IO, GPO, 0);
    gpio_init(MOTOR22_IO, GPO, 0);
    gpio_init(MOTOR31_IO, GPO, 0);
    gpio_init(MOTOR32_IO, GPO, 0);
    FTM_PWM_init(MOTOR_FTM, MOTOR11_PWM, 50, 10);
    FTM_PWM_init(MOTOR_FTM, MOTOR12_PWM, 50, 20);
    FTM_PWM_init(MOTOR_FTM, MOTOR21_PWM, 50, 30);
    FTM_PWM_init(MOTOR_FTM, MOTOR22_PWM, 50, 40);
    FTM_PWM_init(MOTOR_FTM, MOTOR31_PWM, 50, 50);
    FTM_PWM_init(MOTOR_FTM, MOTOR32_PWM, 50, 60);
    //配置管脚的服用功能为ALT4 需要查 K60 Signal Multiplexing and Pin Assignments
    port_init(MOTOR11_IO, ALT4);
    port_init(MOTOR12_IO, ALT4);
    port_init(MOTOR21_IO, ALT4);
    port_init(MOTOR22_IO, ALT4);
    port_init(MOTOR31_IO, ALT4);
    port_init(MOTOR32_IO, ALT4);
    
    
    while(1)
    {        
        
        DELAY_MS(100);                      //延时500ms
        gpio_turn(PTA15);
        FTM_PWM_Duty(MOTOR_FTM, MOTOR11_PWM, 80);
        DELAY_MS(100);                      //延时500ms
        gpio_turn(PTA15);
        FTM_PWM_Duty(MOTOR_FTM, MOTOR11_PWM, 10);
    }
}

