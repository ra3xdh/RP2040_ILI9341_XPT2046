#ifndef ILI9341_FRAMEBUFFER_H
#define ILI9341_FRAMEBUFFER_H

void ili9341_fb_clear();
void fb_put_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void fb_put_pixel(uint16_t x, uint16_t y, uint16_t color);
void ili9341_fb_render();

#endif

