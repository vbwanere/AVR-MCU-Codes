//PA5. LED is connected to PA5
//AHB1. PA5 is connected to AHB1
//RCC->AHB1ENR. To enable clock of ports on AHB1
//GPIOx_MODER
//GPIOx_ODR

#include "main.h"

// volatile int user_delay = 100;

// // Crude delay function (blocking)
// void delayMs(int delay)
// {
//     for (; delay > 0; delay--)
//         for (volatile int i = 0; i < 3195; i++);
// }

// void UART2_Init(void)
// {
//     // Enable GPIOA and USART2 clocks
//     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
//     RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

//     // Set PA2 as alternate function for USART2_TX, PA3 for RX
//     GPIOA->MODER &= ~(0xF << 2*2);          // Clear mode for PA2, PA3
//     GPIOA->MODER |=  (0xA << 2*2);          // Alternate function mode

//     GPIOA->AFR[0] &= ~((0xF << 8) | (0xF << 12)); // Clear bits first
//     GPIOA->AFR[0] |= (7 << 8) | (7 << 12);  // AF7 for USART2 on PA2 and PA3

//     // Configure USART2: 9600 baud, 8N1
//     USART2->BRR = 0x0683; // For 16MHz and 9600 baud (see RM)
//     USART2->CR1 |= USART_CR1_RE | USART_CR1_RXNEIE; // Enable receiver + interrupt
//     USART2->CR1 |= USART_CR1_UE; // Enable USART

//     // Enable USART2 IRQ in NVIC
//     NVIC_EnableIRQ(USART2_IRQn);
//     NVIC_SetPriority(USART2_IRQn, 1);
// }

// void USART2_IRQHandler(void)
// {
//     if (USART2->SR & USART_SR_RXNE)
//     {
//         char ch = USART2->DR; // Read received byte

//         // Expecting digits '1' to '9' -> 100ms to 900ms
//         if (ch >= '1' && ch <= '9') {
//             user_delay = (ch - '0') * 100;
//         }
//     }
// }


// int main(void)
// {
//     // Init UART
//     UART2_Init();

//     // Enable GPIOA clock
//     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

//     // Configure PA5 as output
//     GPIOA->MODER &= ~(0x3 << (5 * 2));
//     GPIOA->MODER |=  (0x1 << (5 * 2));

//     while (1)
//     {
//         GPIOA->ODR |= (1 << 5);  // LED ON
//         delayMs(user_delay);
//         GPIOA->ODR &= ~(1 << 5); // LED OFF
//         delayMs(user_delay);
//     }
// }
/*---------------------------------------------------------------------------------*/

/**
  ******************************************************************************
  * @file    UART/UART_Printf/Src/main.c 
  * @author  MCD Application Team
  * @brief   This example shows how to retarget the C library printf function 
  *          to the UART.
  */

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup UART_Printf
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
     */
  HAL_Init();
  
  /* Configure the system clock to 100 MHz */
  SystemClock_Config();
   
  /*##-1- Configure the UART peripheral ######################################*/
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART1 configured as follow:
      - Word Length = 8 Bits
      - Stop Bit = One Stop bit
      - Parity = ODD parity
      - BaudRate = 9600 baud
      - Hardware flow control disabled (RTS and CTS signals) */
  UartHandle.Instance          = USARTx;
  
  UartHandle.Init.BaudRate     = 9600;
  UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits     = UART_STOPBITS_1;
  UartHandle.Init.Parity       = UART_PARITY_ODD;
  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode         = UART_MODE_TX_RX;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
    
  if(HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  /* Output a message on Hyperterminal using printf function */
  printf("\n\r UART Printf Example: retarget the C library printf function to the UART\n\r");

  /* Infinite loop */ 
  while (1)
  {
  }
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF); 

  return ch;
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 100000000
  *            HCLK(Hz)                       = 100000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 16
  *            PLL_N                          = 400
  *            PLL_P                          = 4
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 3
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSI Oscillator and activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 0x10;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED2 on */
  BSP_LED_On(LED2);
  while(1)
  {
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
 