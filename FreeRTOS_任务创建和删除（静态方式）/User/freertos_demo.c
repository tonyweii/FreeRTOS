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
StackType_t     start_task_stack[START_TASK_STACK_SIZE];
StaticTask_t    start_task_tcb;
void StartTask( void * pvParameters );
/******************************************************************************************************/
/* Task1 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK1_PRIO          2
#define TASK1_STACK_SIZE    128 //单位 字，共128x4字节
StackType_t     task1_stack[TASK1_STACK_SIZE];
StaticTask_t    task1_tcb;
TaskHandle_t    task1_handler;
void Task1( void * pvParameters );
/******************************************************************************************************/
/* Task2 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK2_PRIO          3
#define TASK2_STACK_SIZE    128 //单位 字，共128x4字节
StackType_t     task2_stack[TASK2_STACK_SIZE];
StaticTask_t    task2_tcb;
TaskHandle_t    task2_handler;
void Task2( void * pvParameters );
/******************************************************************************************************/
/* Task1 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK3_PRIO          4
#define TASK3_STACK_SIZE    128 //单位 字，共128x4字节
StackType_t     task3_stack[TASK3_STACK_SIZE];
StaticTask_t    task3_tcb;
TaskHandle_t    task3_handler;
void Task3( void * pvParameters );
/******************************************************************************************************/

/*空闲任务内存分配*/
StaticTask_t idle_task_tcb;
StackType_t  idle_task_stack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize )
{
	* ppxIdleTaskTCBBuffer = &idle_task_tcb;
	* ppxIdleTaskStackBuffer = idle_task_stack;
	* pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/* 软件定时器内存分配 */
StaticTask_t timer_task_tcb;
StackType_t  timer_task_stack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                     StackType_t ** ppxTimerTaskStackBuffer,
                                     uint32_t * pulTimerTaskStackSize )
{
	* ppxTimerTaskTCBBuffer = &timer_task_tcb;
	* ppxTimerTaskStackBuffer = timer_task_stack;
	* pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
/**
 * @brief       FreeRTOS例程入口函数
 * @param       无
 * @retval      无
 */
void freertos_demo(void)
{
	start_task_handler = xTaskCreateStatic( (TaskFunction_t) 	StartTask,
											(char *		   ) 	"start_task", /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
											(uint32_t      )	START_TASK_STACK_SIZE,
											(void *        ) 	NULL,
											(UBaseType_t   ) 	START_TASK_PRIO,
											(StackType_t * ) 	start_task_stack,
											(StaticTask_t *) 	&start_task_tcb );
    vTaskStartScheduler();
}
void StartTask( void * pvParameters )
{
    taskENTER_CRITICAL();               /* 进入临界区 */
    /*创建Task1*/
	task1_handler = xTaskCreateStatic(  (TaskFunction_t) 	Task1,
										(char *		   ) 	"Task1", /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
										(uint32_t      )	TASK1_STACK_SIZE,
										(void *        ) 	NULL,
										(UBaseType_t   ) 	TASK1_PRIO,
										(StackType_t * ) 	task1_stack,
										(StaticTask_t *) 	&task1_tcb );
	
	/*创建Task2*/
	task2_handler = xTaskCreateStatic(  (TaskFunction_t) 	Task2,
										(char *		   ) 	"Task2", /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
										(uint32_t      )	TASK2_STACK_SIZE,
										(void *        ) 	NULL,
										(UBaseType_t   ) 	TASK2_PRIO,
										(StackType_t * ) 	task2_stack,
										(StaticTask_t *) 	&task2_tcb );
	
	/*创建Task3*/
	task3_handler = xTaskCreateStatic(  (TaskFunction_t) 	Task3,
										(char *		   ) 	"Task3", /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
										(uint32_t      )	TASK3_STACK_SIZE,
										(void *        ) 	NULL,
										(UBaseType_t   ) 	TASK3_PRIO,
										(StackType_t * ) 	task3_stack,
										(StaticTask_t *) 	&task3_tcb );
               
    vTaskDelete(start_task_handler);//或者NULL
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
