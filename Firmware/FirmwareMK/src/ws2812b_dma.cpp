#include "ws2812b_dma.h"
#include "stm32f1xx_hal.h"

#define BITSPERLED (sizeof(Color) * 8)

// 32: 32 Bytes at 5MHz = 51.2µs reset time
static uint8_t spiBuffer[LED_COUNT * BITSPERLED + 32];
static Color ledBuffer[LED_COUNT];

static void buildSPIbuffer() {
    for (int i = 0; i < LED_COUNT; i++) {

        uint8_t m = 0b10000000;
        for (int b = 0; b < 8; b++) {
            spiBuffer[BITSPERLED * i + b] = ledBuffer[i].G & m ? SPI_NEO1 : SPI_NEO0;
            m >>= 1u;
        }

        m = 0b10000000;
        for (int b = 0; b < 8; b++) {
            spiBuffer[BITSPERLED * i + b + 8] = ledBuffer[i].R & m ? SPI_NEO1 : SPI_NEO0;
            m >>= 1u;
        }

        m = 0b10000000;
        for (int b = 0; b < 8; b++) {
            spiBuffer[BITSPERLED * i + b + 16] = ledBuffer[i].B & m ? SPI_NEO1 : SPI_NEO0;
            m >>= 1u;
        }
    }
}

void setLed(int i, Color color) {
    ledBuffer[i] = color;
}

void show(SPI_HandleTypeDef *hspi) {
    buildSPIbuffer();
    HAL_SPI_Transmit(hspi, spiBuffer, sizeof(spiBuffer), 2000);
}