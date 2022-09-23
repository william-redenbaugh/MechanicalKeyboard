#ifndef _WS2812B_DMA_H
#define _WS2812B_DMA_H

#include "sys/_stdint.h"
#include "stm32f1xx_hal.h"

#define LED_COUNT 64

#define SPI_NEO0 ((uint8_t) 0b11000000)
#define SPI_NEO1 ((uint8_t) 0b11111100)

typedef struct color {
    uint8_t G;
    uint8_t R;
    uint8_t B;
} Color;

void setLed(int i, Color color);

/**
 * Output LED Data vie DMI
 * @param hspi SPI Handle, should be set to 5MHz, Data Size 8Bit, CPHA = 1 ("2 Edge" in CubeMX)
 */
void show(SPI_HandleTypeDef *hspi);


#endif