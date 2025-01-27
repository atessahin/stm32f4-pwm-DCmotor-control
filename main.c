#include "stm32f4xx_hal.h"              // Device:STM32Cube HAL:Common

// Global variables
uint16_t buttonState=0;
uint16_t buttonFlag=0;
uint16_t potValue=0;
uint16_t adcValue=0;
TIM_HandleTypeDef htim2;
ADC_HandleTypeDef hadc1; 

// Configure GPIO pin PA1 for PWM output
void gpioConfig()
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    GPIO_InitTypeDef gpioASturct;
    gpioASturct.Pin=GPIO_PIN_1;                  // Using PA1 for PWM output
    gpioASturct.Mode = GPIO_MODE_AF_PP;          // Alternate function push-pull mode
    gpioASturct.Alternate = GPIO_AF1_TIM2;       // TIM2 alternate function
    gpioASturct.Speed=GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOA,&gpioASturct);
}

// Configure Timer2 for 20khz PWM generation
void timConfig()
{
    __HAL_RCC_TIM2_CLK_ENABLE();
    htim2.Instance=TIM2;
    htim2.Init.CounterMode=TIM_COUNTERMODE_UP;
    htim2.Init.Prescaler=47;                     // Timer prescaler
    htim2.Init.Period=41;                        // PWM period
    htim2.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload=    TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_PWM_Init(&htim2); 
}

// Configure PWM channel settings
void pwmConfig()
{
    TIM_OC_InitTypeDef ConfigOC = {0};
    ConfigOC.OCMode = TIM_OCMODE_PWM1;          // PWM mode 1
    ConfigOC.Pulse = 5;                         // Initial PWM duty cycle
    ConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;  // Output polarity
    HAL_TIM_PWM_ConfigChannel(&htim2, &ConfigOC, TIM_CHANNEL_2);
}

// Error handler function
void Error_Handler(void)
{
    while(1)
    {
    }
}

// System clock configuration
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 192;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 8;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
    {
        Error_Handler();
    }
}

int main()
{
    // Initialize system and peripherals
    HAL_Init();
    SystemClock_Config();
    gpioConfig();
    timConfig();
    pwmConfig();
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

    while(1)
    {       
        // Step through different fixed PWM duty cycles
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 11);  // 25% duty cycle
        
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 21);  // 50% duty cycle
        
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 31);  // 75% duty cycle
        
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 42);  // 100% duty cycle
    
        // Gradually increase motor speed
        for(int pulse = 5; pulse <= 42; pulse += 2) {
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pulse);
            HAL_Delay(300);  // 300ms delay between speed changes
        }
        
        // Gradually decrease motor speed
        for(int pulse = 42; pulse >= 0; pulse -= 2) {
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pulse);
            HAL_Delay(300);  // 300ms delay between speed changes
        }
    }
}

// System tick handler for HAL timing functions
void SysTick_Handler(void) {
    HAL_IncTick();
}