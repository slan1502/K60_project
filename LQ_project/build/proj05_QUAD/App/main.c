/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ���ѧ��̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 *      ��������Ҫ����DMA������������ܣ�ͨ��PWM����ӵ�DMA�Ĵ����ܽţ�����ó�PWM����������
 *
 * @file       main.c
 * @brief      ɽ��K60 ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2017-03-05
 */

#include "common.h"
#include "include.h"

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ���� LED �����Ƿ�����
                ������Ч����LED0��LED1ͬʱ������˸
 */
void PIT0_IRQHandler(void);

void main()
{
    gpio_init(PTA15, GPO, 0);   //ָʾ��
    
    FTM_QUAD_Init(FTM1);
    FTM_QUAD_Init(FTM2);

    pit_init_ms(PIT0, 200);                                 //��ʼ��PIT0����ʱʱ��Ϊ�� 1000ms
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //����PIT0���жϸ�λ����Ϊ PIT0_IRQHandler
    enable_irq (PIT0_IRQn);                                 //ʹ��PIT0�ж�

    while(1)
    {        
        DELAY_MS(50);                      //��ʱ500ms
        gpio_turn(PTA15);
        DELAY_MS(50);                      //��ʱ500ms
        gpio_turn(PTA15);
    }
}

void PIT0_IRQHandler(void)
{

    int16 val;
    val = FTM_QUAD_get(FTM2);          //��ȡFTM �������� ��������(������ʾ������)
    FTM_QUAD_clean(FTM2);

    if(val>=0)
    {
        printf("\n��ת��%d",val);
    }
    else
    {
        printf("\n��ת��%d",-val);
    }


    PIT_Flag_Clear(PIT0);       //���жϱ�־λ
}