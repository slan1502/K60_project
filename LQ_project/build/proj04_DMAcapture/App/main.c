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

#define MOTOR11_IO      PTC1
#define MOTOR12_IO      PTC2

#define MOTOR_FTM       FTM0
#define MOTOR11_PWM     FTM_CH0       
#define MOTOR12_PWM     FTM_CH1       

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ���� LED �����Ƿ�����
                ������Ч����LED0��LED1ͬʱ������˸
 */
char DMA_COUNT_ADDR;
void dma_ch0_handler(void);
void dma_ch1_handler(void);
uint32 DMA0_TIME1=0, DMA0_TIME2, DMA0_DELAY=0;
uint32 count1=0, count2=0;

void main()
{
    gpio_init(PTA15, GPO, 0);   //ָʾ��
    
    //����PWM
    FTM_PWM_init(MOTOR_FTM, MOTOR11_PWM, 100, 10);
    FTM_PWM_init(MOTOR_FTM, MOTOR12_PWM, 100, 10);
    //���ùܽŵķ��ù���ΪALT4 ��Ҫ�� K60 Signal Multiplexing and Pin Assignments
    port_init(MOTOR11_IO, ALT4);
    port_init(MOTOR12_IO, ALT4);
    //DMA����
    dma_portx2buff_init(DMA_CH0, &DMA_COUNT_ADDR, &DMA_COUNT_ADDR, PTB1, DMA_BYTE1, 0x7fff, DADDR_RECOVER);
    dma_portx2buff_init(DMA_CH1, &DMA_COUNT_ADDR, &DMA_COUNT_ADDR, PTC2, DMA_BYTE1, 0x7fff, DADDR_RECOVER);
    port_init_NoALT(PTB1, DMA_RISING);  //�����ش���
    port_init_NoALT(PTC2, DMA_RISING);  //�����ش���
    set_vector_handler(DMA0_VECTORn, dma_ch0_handler);
    set_vector_handler(DMA0_VECTORn, dma_ch1_handler);
    DMA_EN(DMA_CH0);                                    //ʹ��ͨ��DMA_CH0 Ӳ������
    DMA_EN(DMA_CH1);                                    //ʹ��ͨ��DMA_CH0 Ӳ������
    DMA_IRQ_EN(DMA_CH0);                                //����DMA_CH0ͨ������
    DMA_IRQ_EN(DMA_CH1);                                //����DMA_CH0ͨ������
    
    //ʹ�ܼ�ʱ����
//    DEMCR            |=  (1<<24);        //ʹ�� ����ʱ�� ��Ĭ���Ѿ��򿪣�
//    DWT_CTRL         |=  (1<<0);
   
    while(1)
    {        
        
        DELAY_MS(50);                      //��ʱ500ms
        gpio_turn(PTA15);
        DELAY_MS(50);                      //��ʱ500ms
        gpio_turn(PTA15);
        count1 = 0x7fff-DMA_CITER_ELINKNO(DMA_CH0);
        count2 = 0x7fff-DMA_CITER_ELINKNO(DMA_CH1);
        printf("count1=%d, count2=%d\r\n", count1, count2);
    }
}

/*!
 *  @brief      DMAͨ��0�ж�
 *  @since      v5.0
 */
void dma_ch0_handler(void)
{
    DMA_IRQ_CLEAN(DMA_CH0);                  //���ͨ�������жϱ�־λ
//    //����DMA������ѭ�����ѵ�ʱ��
//    DMA0_TIME1 = DWT_CYCCNT;
//    if(DMA0_TIME1>DMA0_TIME2) DMA0_DELAY = DMA0_TIME1-DMA0_TIME2;
//    else DMA0_DELAY = 0xffffffff-DMA0_TIME2+DMA0_TIME1;
//    DMA0_DELAY = DMA0_DELAY/core_clk_khz;       //��DMA0_DELAY�ĵ�λת��Ϊms
//    DMA0_TIME2 = DMA0_TIME1;
      
    //DMA_DADDR(DMA_CH0) = BUFF;            //�ָ���ַ (���ڳ�ʼ��ʱ����Ϊ�ָ�Ŀ�ĵ�ַ������˴�����Ҫ)
    DMA_EN(DMA_CH0);                        //ʹ��ͨ��CHn Ӳ������
}
void dma_ch1_handler(void)
{
    DMA_IRQ_CLEAN(DMA_CH1);                  //���ͨ�������жϱ�־λ

    //DMA_DADDR(DMA_CH0) = BUFF;            //�ָ���ַ (���ڳ�ʼ��ʱ����Ϊ�ָ�Ŀ�ĵ�ַ������˴�����Ҫ)
    DMA_EN(DMA_CH1);                        //ʹ��ͨ��CHn Ӳ������
}

