/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ���ѧ��̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��K60 ƽ̨������
 * @author     ɽ��Ƽ�
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
 *  @brief      main����
 *  @since      v5.0
 *  @note       ���� LED �����Ƿ�����
                ������Ч����LED0��LED1ͬʱ������˸
 */
void main()
{
    gpio_init(PTA15, GPO, 0);   //ָʾ��
    
    //����PWM
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
    //���ùܽŵķ��ù���ΪALT4 ��Ҫ�� K60 Signal Multiplexing and Pin Assignments
    port_init(MOTOR11_IO, ALT4);
    port_init(MOTOR12_IO, ALT4);
    port_init(MOTOR21_IO, ALT4);
    port_init(MOTOR22_IO, ALT4);
    port_init(MOTOR31_IO, ALT4);
    port_init(MOTOR32_IO, ALT4);
    
    
    while(1)
    {        
        
        DELAY_MS(100);                      //��ʱ500ms
        gpio_turn(PTA15);
        FTM_PWM_Duty(MOTOR_FTM, MOTOR11_PWM, 80);
        DELAY_MS(100);                      //��ʱ500ms
        gpio_turn(PTA15);
        FTM_PWM_Duty(MOTOR_FTM, MOTOR11_PWM, 10);
    }
}

