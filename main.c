#include <stdlib.h>
#include "stdio.h"

#include "pico/stdlib.h"

#include "consts.h"
#include "badapple-testframe.h"
#include "badapple-testframe2.h"
#include "chain_decode.h"

#include "pico/st7789.h"

// lcd configuration
const struct st7789_config lcd_config = {
    .spi = PICO_DEFAULT_SPI_INSTANCE,
    .gpio_din = PICO_DEFAULT_SPI_TX_PIN,
    .gpio_clk = PICO_DEFAULT_SPI_SCK_PIN,
    .gpio_cs = PICO_DEFAULT_SPI_CSN_PIN,
    .gpio_dc = 20,
    .gpio_rst = 21,
    .gpio_bl = 22,
};

int main()
{
    stdio_uart_init();

    printf("begin\n\n\n");

    // initialize the lcd
    st7789_init(&lcd_config, LCD_WIDTH, LCD_HEIGHT);

    int num_pixels = WIDTH * HEIGHT;
    uint16_t *frame_buffer = (uint16_t *)malloc(num_pixels * sizeof(uint16_t));

    decode_chain_coded_frame(test_frame_two_bin, test_frame_two_bin_len, frame_buffer);

    st7789_write(frame_buffer, num_pixels * sizeof(uint16_t));

    free(frame_buffer);
}