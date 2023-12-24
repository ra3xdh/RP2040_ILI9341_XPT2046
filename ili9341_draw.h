#ifndef ILI9341_DRAW_H
#define ILI9341_DRAW_H


void set_col(uint16_t StartCol,uint16_t EndCol);
void set_page(uint16_t StartPage,uint16_t EndPage);
void set_XY(uint16_t poX, uint16_t poY);
void draw_pixel(uint16_t poX, uint16_t poY,uint16_t color);
void draw_vertical_line(uint16_t poX, uint16_t poY, uint16_t length, uint16_t color);
void draw_horizontal_line(uint16_t poX, uint16_t poY, uint16_t length, uint16_t color);
void draw_line( uint16_t x0,uint16_t y0,uint16_t x1, uint16_t y1, uint16_t color);
void draw_circle(uint16_t poX, uint16_t poY, uint16_t r,uint16_t color);
void fill_circle(uint16_t poX, uint16_t poY, uint16_t r,uint16_t color);
void fill_screen(uint16_t color);
void fill_rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

uint16_t inline RGBConv(uint16_t R, uint16_t G, uint16_t B)
{
    return ((unsigned int)( (( R >> 3 ) << 11 ) | (( G >> 2 ) << 5 ) | ( B >> 3 )));
}

#endif

