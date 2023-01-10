/**
 ****************************************************************************************************
 * @file        freertos.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.4
 * @date        2022-01-04
 * @brief       FreeRTOS ��ֲʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ̽����F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "freertos_demo.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
/*FreeRTOS*********************************************************************************************/
#include "FreeRTOS.h"
#include "task.h"

/******************************************************************************************************/
/*FreeRTOS����*/

/* START_TASK ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define START_TASK_PRIO         1
#define START_TASK_STACK_SIZE    128 //��λ �֣���128x4�ֽ�
TaskHandle_t    start_task_handler;
void StartTask( void * pvParameters );
/******************************************************************************************************/
/* Task1 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK1_PRIO          2
#define TASK1_STACK_SIZE    128 //��λ �֣���128x4�ֽ�
TaskHandle_t    task1_handler;
void Task1( void * pvParameters );
/******************************************************************************************************/
/* Task2 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK2_PRIO          3
#define TASK2_STACK_SIZE    128 //��λ �֣���128x4�ֽ�
TaskHandle_t    task2_handler;
void Task2( void * pvParameters );
/******************************************************************************************************/
/* Task1 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK3_PRIO          4
#define TASK3_STACK_SIZE    128 //��λ �֣���128x4�ֽ�
TaskHandle_t    task3_handler;
void Task3( void * pvParameters );
/******************************************************************************************************/

/**
 * @brief       FreeRTOS������ں���
 * @param       ��
 * @retval      ��
 */
void freertos_demo(void)
{
    xTaskCreate(( TaskFunction_t        )   StartTask,
               ( char *                 )   "StartTask", 
               ( configSTACK_DEPTH_TYPE )   START_TASK_STACK_SIZE,
               ( void *                 )   NULL,
               ( UBaseType_t            )   START_TASK_PRIO,
               ( TaskHandle_t *         )   &start_task_handler );
    vTaskStartScheduler();
}
void StartTask( void * pvParameters )
{
    taskENTER_CRITICAL();               /* �����ٽ��� */
    /* ��������1 */
    xTaskCreate(( TaskFunction_t        )   Task1,              //����������
               ( char *                 )   "Task1",            //��������
               ( configSTACK_DEPTH_TYPE )   TASK1_STACK_SIZE,   //�����ջ��С
               ( void *                 )   NULL,               //�������
               ( UBaseType_t            )   TASK1_PRIO,         //�������ȼ�
               ( TaskHandle_t *         )   &task1_handler );   //�����������
               
    xTaskCreate(( TaskFunction_t        )   Task2,
               ( char *                 )   "Task2", 
               ( configSTACK_DEPTH_TYPE )   TASK2_STACK_SIZE,
               ( void *                 )   NULL,
               ( UBaseType_t            )   TASK2_PRIO,
               ( TaskHandle_t *         )   &task2_handler ); 
               
    xTaskCreate(( TaskFunction_t        )   Task3,
               ( char *                 )   "Task3", 
               ( configSTACK_DEPTH_TYPE )   TASK3_STACK_SIZE,
               ( void *                 )   NULL,
               ( UBaseType_t            )   TASK3_PRIO,
               ( TaskHandle_t *         )   &task3_handler ); 
               
    vTaskDelete(NULL);
    taskEXIT_CRITICAL();                /* �˳��ٽ��� */
}
/*����1,ʵ��LED0ÿ500ms��תһ��*/
void Task1( void * pvParameters )
{
    while(1)
    {
        LED0_TOGGLE();
        vTaskDelay(500);
    }

 
}
/*����1,ʵ��LED0ÿ1s��תһ��*/
void Task2( void * pvParameters )
{
    while(1)
    {
        LED1_TOGGLE();
        vTaskDelay(500);
    }

}
/*����1,ʵ���жϰ������£���ɾ������1*/
void Task3( void * pvParameters )
{
    uint8_t key = 0;
    while(1)
    {
        key = key_scan(0);
        if(key == KEY0_PRES)
        {
            if(task1_handler != NULL)
            {   
                vTaskDelete(task1_handler);
            }
        }
        vTaskDelay(10);
    }

}
