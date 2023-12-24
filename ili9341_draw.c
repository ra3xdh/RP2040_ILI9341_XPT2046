#include <stdlib.h>
#include <stdint.h>

#include "ili9341.h"
#include "ili9341_draw.h"


void set_col(uint16_t StartCol,uint16_t EndCol)
{
    ili9341_set_command(ILI9341_CASET); /* Column Command address */
    ili9341_command_param((uint8_t)(StartCol>>8));
    ili9341_command_param((uint8_t)(StartCol&0xFF));
    ili9341_command_param((uint8_t)(EndCol>>8));
    ili9341_command_param((uint8_t)(EndCol&0xFF));
}

void set_page(uint16_t StartPage,uint16_t EndPage)
{
    ili9341_set_command(ILI9341_PASET); /* Column Command address */
    ili9341_command_param((uint8_t)(StartPage>>8));
    ili9341_command_param((uint8_t)(StartPage&0xFF));
    ili9341_command_param((uint8_t)(EndPage>>8));
    ili9341_command_param((uint8_t)(EndPage&0xFF));
}


void set_XY(uint16_t poX, uint16_t poY)
{
    set_col(poX, poX);
    set_page(poY, poY);
    ili9341_set_command(ILI9341_RAMWR);
}

void draw_pixel(uint16_t poX, uint16_t poY,uint16_t color)
{
    set_XY(poX, poY);
    ili9341_write_data(&color,2);
}

void fill_screen(uint16_t color)
{
    set_col(0, ILI9341_TFTWIDTH);
    set_page(0, ILI9341_TFTHEIGHT);
    ili9341_set_command(0x2c); /* start to write to display ra */

    for(uint32_t i=0; i < ILI9341_TFTWIDTH*ILI9341_TFTHEIGHT; i++)
    {
        ili9341_write_data(&color,2);
    }


}

void fill_rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    set_col(x,x+w);
    set_page(y,y+h);
    ili9341_set_command(ILI9341_RAMWR);
    ili9341_start_writing();
    for(uint32_t i = 0; i < (w+1)*(h+1); i++) {
        ili9341_write_data_continuous(&color,2);
    }
    ili9341_stop_writing();
}

void draw_horizontal_line( uint16_t poX, uint16_t poY,uint16_t length, uint16_t color)
{
    set_col(poX,poX + length);
    set_page(poY,poY);
    ili9341_set_command(ILI9341_RAMWR);
    ili9341_start_writing();
    for(uint16_t i=0; i < length; i++) {
        ili9341_write_data_continuous(&color,2);
    }
    ili9341_stop_writing();
}

void draw_vertical_line( uint16_t poX, uint16_t poY, uint16_t length, uint16_t color)
{
    set_col(poX,poX);
    set_page(poY,poY+length);
    ili9341_set_command(ILI9341_RAMWR);
    ili9341_start_writing();
    for(uint16_t i=0; i < length; i++) {
        ili9341_write_data_continuous(&color,2);
    }
    ili9341_stop_writing();
}

void draw_line( uint16_t x0,uint16_t y0,uint16_t x1, uint16_t y1,uint16_t color)
{

    uint16_t x = x1-x0;
    uint16_t y = y1-y0;
    uint16_t dx = abs(x), sx = x0 < x1 ? 1 : -1;
    uint16_t dy = -abs(y), sy = y0 < y1 ? 1 : -1;
    uint16_t err = dx+dy, e2; /* error value e_xy */
    for (;;){ /* loop */
        draw_pixel(x0,y0,color);
        e2 = 2*err;
        if (e2 >= dy) { /* e_xy+e_x &amp; gt; 0 */
            if (x0 == x1) break;
            err += dy; x0 += sx;
        }
        if (e2 <= dx) { /* e_xy+e_y &amp; lt; 0 */
            if (y0 == y1) break;
            err += dx; y0 += sy;
        }
    }

}

void draw_circle(uint16_t poX, uint16_t poY, uint16_t r,uint16_t color)
{
    int16_t x , y , err , e2;
    x = -r;
    y = 0;
    err = 2-2*r;
    do {
        draw_pixel(poX-x, poY+y,color);
        draw_pixel(poX+x, poY+y,color);
        draw_pixel(poX+x, poY-y,color);
        draw_pixel(poX-x, poY-y,color);
        e2 = err;
        if (e2 <= y) {
            err += ++y*2+1;
            if (-x == y && e2 <= x) e2 = 0;
        }
        if (e2 > x) err += ++x*2+1;
    } while (x <= 0);
}


void fill_circle(uint16_t poX, uint16_t poY, uint16_t r,uint16_t color)
{
    int16_t x = -r, y = 0, err = 2-2*r, e2;
    do {

        draw_vertical_line(poX-x, poY-y, 2*y, color);
        draw_vertical_line(poX+x, poY-y, 2*y, color);

        e2 = err;
        if (e2 <= y) {
            err += ++y*2+1;
            if (-x == y && e2 <= x) e2 = 0;
        }
        if (e2 > x) err += ++x*2+1;
    } while (x <= 0);

}



