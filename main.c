/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "ili9341.h"
#include "ili9341_framebuffer.h"
#include "ili9341_draw.h"
#include "xpt2046.h"

#define LED_PIN 25

int main() {

    ili9341_init();
    ts_spi_setup();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN,GPIO_OUT);

    uint16_t x = 0;
    uint16_t y = 0;

    fill_screen(0x0000);
    for(uint16_t x=0; x < ILI9341_TFTWIDTH; x+=10) {
        for(uint16_t y=0; y < ILI9341_TFTHEIGHT; y+=10) {
            draw_pixel(x,y,0xFFFF);
        }
    }
    fill_rectangle(40,40,30,40,0xFFF0);
    fill_rectangle(140,200,30,40,0xFFF0);
    draw_vertical_line(20,20,40,0xFFF0);
    draw_vertical_line(80,80,60,0xFFF0);
    draw_horizontal_line(20,20,40,0xFFF0);
    fill_circle(180,60,30,0xFFF0);
    draw_circle(120,120,40,0xFFF0);
    //draw_line(20,20,40,80,0xFFF0);

    int state = 0;
	while (1) {
        if(gpio_get(TS_IRQ_PIN) == 0) {
            uint16_t x = ts_get_x();
            uint16_t y = ts_get_y();
            fill_circle(x,y,3,0xFFFF);
            if (state == 0) state = 1;
            else state = 0;
            gpio_put(LED_PIN,state);

        }
    }
}
