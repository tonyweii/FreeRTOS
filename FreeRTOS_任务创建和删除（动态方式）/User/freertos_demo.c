/**
 ****************************************************************************************************
 * @file        freertos.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.4
 * @date        2022-01-04
 * @brief       FreeRTOS 移植实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 探索者F407开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
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
/*FreeRTOS配置*/

/* START_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define START_TASK_PRIO         1
#define START_TASK_STACK_SIZE    128 //单位 字，共128x4字节
TaskHandle_t    start_task_handler;
void StartTask( void * pvParameters );
/******************************************************************************************************/
/* Task1 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK1_PRIO          2
#define TASK1_STACK_SIZE    128 //单位 字，共128x4字节
TaskHandle_t    task1_handler;
void Task1( void * pvParameters );
/******************************************************************************************************/
/* Task2 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK2_PRIO          3
#define TASK2_STACK_SIZE    128 //单位 字，共128x4字节
TaskHandle_t    task2_handler;
void Task2( void * pvParameters );
/******************************************************************************************************/
/* Task1 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK3_PRIO          4
#define TASK3_STACK_SIZE    128 //单位 字，共128x4字节
TaskHandle_t    task3_handler;
void Task3( void * pvParameters );
/******************************************************************************************************/

/**
 * @brief       FreeRTOS例程入口函数
 * @param       无
 * @retval      无
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
    taskENTER_CRITICAL();               /* 进入临界区 */
    /* 创建任务1 */
    xTaskCreate(( TaskFunction_t        )   Task1,              //创建的任务
               ( char *                 )   "Task1",            //任务名称
               ( configSTACK_DEPTH_TYPE )   TASK1_STACK_SIZE,   //任务堆栈大小
               ( void *                 )   NULL,               //传入参数
               ( UBaseType_t            )   TASK1_PRIO,         //任务优先级
               ( TaskHandle_t *         )   &task1_handler );   //任务处理函数句柄
               
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
    taskEXIT_CRITICAL();                /* 退出临界区 */
}
/*任务1,实现LED0每500ms翻转一次*/
void Task1( void * pvParameters )
{
    while(1)
    {
        LED0_TOGGLE();
        vTaskDelay(500);
    }

 
}
/*任务1,实现LED0每1s翻转一次*/
void Task2( void * pvParameters )
{
    while(1)
    {
        LED1_TOGGLE();
        vTaskDelay(500);
    }

}
/*任务1,实现判断按键按下，并删除任务1*/
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
