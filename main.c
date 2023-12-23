/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "ili9341.h"
#include "ili9341_framebuffer.h"

#define LED_PIN 25

int main() {

    ili9341_init();

    uint16_t x = 0;
	while (1) {
    	ili9341_fb_clear();
		fb_put_rect(x, 40, 40, 80, 0xFFF0);
		ili9341_fb_render();

		x += 1;
		x = x%280;
	}
}
