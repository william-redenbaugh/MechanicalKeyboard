#include "led_management_runtime.h"
#include "mk_helper.h"
#include "ws2812b_dma.h"
#include "SPI.h"

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{
pinMode(PA7, OUTPUT);
  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);

}


// Define the LED pin is attached
const uint8_t LED_PIN = PC13;

void turn_on_light(void){
    // Turn LED on.
    digitalWrite(LED_PIN, HIGH);
}

void turn_off_light(void){
    // Signal thread 1 to turn LED off.
    digitalWrite(LED_PIN, LOW);
}

#include "event_management.h"
void led_management_thread(void *params){
    (void)params;

    pinMode(LED_PIN, OUTPUT);
    event_type_t events[] = {
      EVENT_STATUS_LED_ON, 
      EVENT_STATUS_LED_OFF,
    };

    int event_sub = subscribe_eventlist(events, 2, 8);
    for(;;){
       event_data_t event = consume_event(event_sub);

       switch(event.event){
        case EVENT_STATUS_LED_OFF:
        turn_off_light();
        break;

        case EVENT_STATUS_LED_ON:
        turn_on_light();
        break;
       }
    }
}