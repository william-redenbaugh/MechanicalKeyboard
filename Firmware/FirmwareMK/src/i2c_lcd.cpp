#include "i2c_lcd.h"
#include "STM32FreeRTOS.h"
#include "stm32f1xx_hal.h"
#include "stdlib.h"

static I2C_HandleTypeDef hi2c1;
static char *buffer = NULL;
static uint8_t addr = 0x21;

static uint8_t i2c_write(uint8_t *data, uint8_t len);
static uint8_t i2c_read(uint8_t *data, uint8_t len);

static void gpio_i2c_init(void);

void init_lcd(int width, int height){
    // Setup GPIO and i2c peripherals
    gpio_i2c_init();

    // Single time allocation for LCD display size
    buffer = (char*)malloc(sizeof(char) * width * height);

}

void gpio_i2c_init(void){

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 400000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK){
        Error_Handler();
    }
}

static uint8_t i2c_write(uint8_t *data, uint8_t len){
    return HAL_I2C_Master_Transmit(&hi2c1, addr, data, len, 10);
}

static uint8_t i2c_read(uint8_t *data, uint8_t len){
    return HAL_I2C_Master_Receive(&hi2c1, addr, data, len, 10);
}
