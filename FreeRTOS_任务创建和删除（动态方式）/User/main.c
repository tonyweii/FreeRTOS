/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-11-04
 * @brief       �ڴ���� ʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ̽���� F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/SDRAM/sdram.h"
#include "./MALLOC/malloc.h"
#include "freertos_demo.h"


int main(void)
{

    HAL_Init();                         /* ��ʼ��HAL�� */
    //sys_stm32_clock_init(144, 25, 2, 7); /* ����ʱ��,168Mhz */
    delay_init(36);                    /* ��ʱ��ʼ�� */
    usart_init(115200);                 /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                         /* ��ʼ��LED */
    key_init();                         /* ��ʼ������ */
    SDRAM_Init();                        /* SRAM��ʼ�� */
    
//    my_mem_init(SRAMIN);                /* ��ʼ���ڲ�SRAM�ڴ�� */
//    my_mem_init(SRAMEX);                /* ��ʼ���ⲿSRAM�ڴ�� */
//    my_mem_init(SRAMCCM);               /* ��ʼ���ڲ�CCM�ڴ�� */

    freertos_demo();
    
}


