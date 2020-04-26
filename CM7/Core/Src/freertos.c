/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

#include "lwip.h"
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include <string.h>

#include "usart.h"
#include <string.h>
#include <stdlib.h>
#include "eth_comm.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

struct netconn *newconn;

extern char uart3_send[200];

/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */


void vTaskEthReceiveCommand(void * argument);
void vTaskEthSendData(void * argument);

   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */

  xTaskCreate(vTaskEthReceiveCommand, "TaskEthReceiveCommand", 3000, NULL, 1, NULL);

  xTaskCreate(vTaskEthSendData, "TaskEthSendData", 1000, NULL, 1, NULL);

  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for LWIP */
//  MX_LWIP_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {

	  osDelay(1000);
  }
  osThreadTerminate(NULL);
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     

/* task to hold tcp communication */
void vTaskEthReceiveCommand(void * argument){

	/* tcp connection variable */
	struct netconn *conn;
	err_t err, accept_err;
	struct netbuf *buf;
	void *data;
	uint16_t len;
	err_t recv_err;

	/* tcp packet struct */
	Eth_Packet tcp_command;

	for(;;){

		/* Infinite loop */
		/* Create a new connection identifier. */
		conn = netconn_new(NETCONN_TCP);

		if (conn != NULL) {

			/* Bind connection to well known port number. */
			err = netconn_bind(conn, NULL, 4242);

			if (err == ERR_OK) {

				/* Tell connection to go into listening mode. */
				netconn_listen(conn);

				while (1) {

					/* Grab new connection. */
					accept_err = netconn_accept(conn, &newconn);

					/* Process the new connection. */
					if (accept_err == ERR_OK) {

						while ((recv_err = netconn_recv(newconn, &buf)) == ERR_OK) {

							do {

								/* receive command from control station */
								netbuf_data(buf, &data, &len);

								/* parse received command that control ROV */
								parse_eth_command((char *) data, len, &tcp_command);

							} while (netbuf_next(buf) >= 0);

							netbuf_delete(buf);

						}

						/* Close connection and discard connection identifier. */
						netconn_close(newconn);
						netconn_delete(newconn);
					}
				}

			} else {
				netconn_delete(newconn);
			}

		}


	}

	vTaskDelete(NULL);

}


void vTaskEthSendData(void * argument){

	// status of netconn send
	err_t tcp_send_data_status;

	// data to be send
	char eth_packet_data[200];
	uint16_t eth_packet_data_len = 0;

	// ethernet packet
	Eth_Packet pacekt;

	for(;;){

		/* queue which contain ethernet packet to be send */


		/* convert eth packet to tcp data array to be send */
		pacekt.pacet_type = 49;
		pacekt.data_length = 1;
		pacekt.data[0] = 51;

		convert_eth_packet_to_tcp_array(eth_packet_data, &eth_packet_data_len, &pacekt);


		/* send data packet with netconn_write function */
		tcp_send_data_status = netconn_write(newconn, eth_packet_data, eth_packet_data_len, NETCONN_COPY);


		sprintf(uart3_send, "Netconn write status: %s \n\r", eth_packet_data);
		HAL_UART_Transmit(&huart3, (uint8_t*) uart3_send, strlen(uart3_send), HAL_MAX_DELAY);


		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}

	vTaskDelete(NULL);

}


/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
