#include <string.h>

#include "ili9341.h"
#include "ili9341_framebuffer.h"

#define SIZE (ILI9341_TFTHEIGHT*ILI9341_TFTWIDTH)

static uint16_t buffer[ILI9341_TFTWIDTH*ILI9341_TFTHEIGHT];


void ili9341_fb_clear() {
    memset(buffer, 0, SIZE*sizeof(uint16_t));
}

void fb_put_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
	uint16_t *base_loc = &buffer[x*ILI9341_TFTWIDTH+y];

	for (int h=0; h<width; h++) {
	    uint16_t *loc = base_loc + h*ILI9341_TFTWIDTH;
    	for (int v=0; v<height; v++) {
			*loc++ = color;
    	}
	}
}

void fb_put_pixel(uint16_t x, uint16_t y, uint16_t color)
{
    uint32_t idx = x*ILI9341_TFTWIDTH+y;
    if (idx >= SIZE) return;
    uint16_t *base_loc = &buffer[x*ILI9341_TFTWIDTH+y];
    *base_loc = color;
}

void ili9341_fb_render() {
    ili9341_start_writing();
	ili9341_write_data_continuous(buffer, SIZE*sizeof(uint16_t));
	ili9341_stop_writing();
}


