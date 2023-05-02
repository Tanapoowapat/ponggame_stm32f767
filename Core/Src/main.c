/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "rng.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdbool.h>
#include "ILI9341_GFX.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_Touchscreen.h"
#include "string.h"
#include "stdio.h"
#include "picture.h"
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

/* USER CODE BEGIN PV */


volatile adc_value = 0 ;
volatile adc_value_2 = 0 ;
char score_sender[20] = "";
bool game_running = false;
bool reset_game = false;
char str[100] ;
char str1[] = "\r\n";
char str2[] = "PD4 HAS BEEN PRESS\r\n";
char str3[] = "Game Running\r\n";
uint8_t player_1_score = 0 ;
uint8_t player_2_score = 0 ;
char str_player_1[] = "1";





//Paddle Size
uint8_t paddle_1_x1 = 60 ;
uint8_t paddle_1_x2 = 65 ;
uint8_t paddle_1_y1 = 78 ;
uint8_t paddle_1_y2 = 133;
uint8_t oldpaddle_1_x1, oldpaddle_1_x2, oldpaddle_1_y1, oldpaddle_1_y2;


//Paddle 2 Size
uint8_t paddle_2_x1 = 240;
uint8_t paddle_2_x2 = 245;
uint8_t paddle_2_y1 = 78 ;
uint8_t paddle_2_y2 = 133;
uint8_t oldpaddle_2_x1, oldpaddle_2_x2, oldpaddle_2_y1, oldpaddle_2_y2;


//ball location
uint8_t ball_x = 150;
uint8_t ball_y = 100;
uint8_t ballDirectionX = 1;
uint8_t ballDirectionY = 1;
uint8_t oldball_x, oldball_y;
//DEFIND SCREEN

uint32_t screen_hight = 250;
uint32_t screen_width = 240;


HAL_StatusTypeDef status;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */


uint16_t CRC16_2(uint8_t *,uint8_t);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI5_Init();
  MX_TIM1_Init();
  MX_ADC1_Init();
  MX_RNG_Init();
  MX_USART3_UART_Init();
  MX_ADC2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  ILI9341_Init();

  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);

  ILI9341_Fill_Screen(WHITE);




  HAL_ADC_Start(&hadc1);
  HAL_ADC_Start(&hadc2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4) == GPIO_PIN_RESET){



			reset_game = !reset_game;
			ILI9341_Fill_Screen(WHITE);

			paddle_1_x1 = 60 ;
			paddle_1_x2 = 65 ;
			paddle_1_y1 = 78 ;
			paddle_1_y2 = 133;

			paddle_2_x1 = 240;
			paddle_2_x2 = 245;
			paddle_2_y1 = 78 ;
			paddle_2_y2 = 133;

			ball_x = 150;
			ball_y = 100;

		      // Toggle game_running
		      game_running = !game_running;
		      // Wait for button release
		      while (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == GPIO_PIN_RESET) {}
	  }
	   // Check if button is pressed
	    if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == GPIO_PIN_RESET) {
	      // Toggle game_running
	      game_running = !game_running;
	      // Wait for button release
	      while (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == GPIO_PIN_RESET) {}
	    }

	    // If game is running, call game function



	    if (game_running) {
	      game();
	    }



	  }
  }

  /* USER CODE END 3 */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void game(){
	  //DEBUG TERMINAL
	  adc_value = HAL_ADC_GetValue(&hadc1);
	  adc_value_2 = HAL_ADC_GetValue(&hadc2);
//	  display(adc_value, adc_value_2);
//	  HAL_UART_Transmit(&huart3, (uint32_t*)&str, sizeof(str), 100);
//	  HAL_UART_Transmit(&huart3, (uint8_t*)str1, strlen(str1), 1000);
	  HAL_UART_Transmit(&huart3, (uint32_t*)str3, strlen(str3), 100);


		//check edge for paddle
		if(paddle_1_y1 <= 1){
			paddle_1_y1 = 1;
			paddle_1_y2 = 56;
		}else if (paddle_1_y2 >= 240){
			paddle_1_y1 = 185;
			paddle_1_y2 = 240;
		}if(paddle_2_y1 <= 1){
			paddle_2_y1 = 1;
			paddle_2_y2 = 56;
		}else if(paddle_2_y2 >= 240){
			paddle_2_y1 = 185;
			paddle_2_y2 = 240;
		}
	  	//Move Paddle
		if(adc_value >= 0 && adc_value <= 2000){
			paddle_1_y1 --;
			paddle_1_y2 --;
		}else if(adc_value >= 2800 && adc_value <= 2890){
			paddle_1_y1 ++;
			paddle_1_y2 ++;
		}if(adc_value_2 >= 100 && adc_value_2 <= 2000){
			paddle_2_y1 --;
			paddle_2_y2 --;
		}else if(adc_value_2 >= 2800 && adc_value_2 <= 2890){paddle_2_y1 ++;paddle_2_y2 ++;}




		ILI9341_Draw_Filled_Rectangle_Coord(paddle_1_x1, paddle_1_y1, paddle_1_x2, paddle_1_y2, BLACK);
		ILI9341_Draw_Filled_Rectangle_Coord(oldpaddle_1_x1, oldpaddle_1_y1, oldpaddle_1_x2, oldpaddle_1_y2, WHITE);
		ILI9341_Draw_Filled_Rectangle_Coord(paddle_1_x1, paddle_1_y1, paddle_1_x2, paddle_1_y2, BLACK);

		oldpaddle_1_x1 = paddle_1_x1;
		oldpaddle_1_y1 = paddle_1_y1;
		oldpaddle_1_x2 = paddle_1_x2;
		oldpaddle_1_y2 = paddle_1_y2;

		//DRAW
		ILI9341_Draw_Filled_Rectangle_Coord(paddle_2_x1, paddle_2_y1, paddle_2_x2, paddle_2_y2, BLACK);
		ILI9341_Draw_Filled_Rectangle_Coord(oldpaddle_2_x1, oldpaddle_2_y1, oldpaddle_2_x2, oldpaddle_2_y2, WHITE);
		ILI9341_Draw_Filled_Rectangle_Coord(paddle_2_x1, paddle_2_y1, paddle_2_x2, paddle_2_y2, BLACK);

		oldpaddle_2_x1 = paddle_2_x1;
		oldpaddle_2_y1 = paddle_2_y1;
		oldpaddle_2_x2 = paddle_2_x2;
		oldpaddle_2_y2 = paddle_2_y2;


	  //UPDATE THE BALL
	  move_ball();
}

//DISPLAY FUNCTION FOR DEBUG ON TERMINAL
void display(int val_1, int val_2){
	sprintf(str, "Player Score 1 : %d Player Score 2 : %d", player_1_score, player_2_score);
}

bool inPaddle(int x, int y, int rectX, int rectY, int rectWidth, int rectHeight) {
  bool  result = false;
  if ((x >= rectX && x <= rectWidth) &&
    (y >= rectY && y <= rectHeight)) {
    result = true;
  }
  return result;
}

void move_ball(){

	if(ball_x+2 == screen_hight || ball_x == 30){
		if(ball_x+2 == screen_hight){
			player_1_score += 1 ;
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11);

		}else if(ball_x == 30){
			player_2_score += 1;
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);

		}
		//SEND BALL BACK TO SPAWN BALL AREA

		ball_x = 150;
		ball_y = 100;

		//MAKE IT MOVE DIFFERNT SIDE
		ballDirectionX = -ballDirectionX;
		ballDirectionY = -ballDirectionY;



	}

	if (ball_y > screen_width || ball_y < 0) {
	    ballDirectionY = -ballDirectionY;
	}

	if (inPaddle(ball_x, ball_y, paddle_1_x1, paddle_1_y1, paddle_1_x2, paddle_1_y2)||(inPaddle(ball_x, ball_y, paddle_2_x1, paddle_2_y1, paddle_2_x2, paddle_2_y2))) {
	    ballDirectionX = -ballDirectionX;

	}
	  ball_x += ballDirectionX;
	  ball_y += ballDirectionY;
	  ILI9341_Draw_Filled_Circle(ball_x, ball_y, 3, BLACK);
	  ILI9341_Draw_Filled_Circle(oldball_x, oldball_y, 3, WHITE);
	  ILI9341_Draw_Filled_Circle(ball_x, ball_y, 3, BLACK);

	  oldball_x = ball_x;
	  oldball_y = ball_y;


}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
