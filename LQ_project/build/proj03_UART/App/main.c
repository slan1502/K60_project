/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ���ѧ��̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ������������������ҵ��;��
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

void main()
{
    gpio_init(PTA15, GPO, 0);   //ָʾ��
    while(1)
    {        
        printf("hello\r\n");         
        DELAY_MS(50);                      //��ʱ500ms
        gpio_turn(PTA15);
        DELAY_MS(50);                      //��ʱ500ms
        gpio_turn(PTA15);
    }
}
