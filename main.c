/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "ili9341.h"
#include "ili9341_framebuffer.h"
#include "ili9341_draw.h"

#define LED_PIN 25

int main() {

    ili9341_init();

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

	while (1) {
    }
}
