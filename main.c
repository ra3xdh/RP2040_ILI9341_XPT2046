/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include <stdbool.h>
#include "ili9341.h"
#include "ili9341_framebuffer.h"
#include "ili9341_draw.h"
#include "xpt2046.h"
#include "ugui.h"

#define LED_PIN 25

bool timer_ts_poll_callback(struct repeating_timer *t);

void pixel_set(UG_S16 x, UG_S16 y, UG_COLOR rgb);
UG_RESULT _HW_DrawLine(UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR rgb);
UG_RESULT _HW_FillFrame(UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR rgb);

void window_1_callback( UG_MESSAGE* msg );
void button_green_click(void);
void button_red_click(void);

static UG_GUI gui;
static UG_WINDOW window_1;
static UG_BUTTON button1_1;
static UG_BUTTON button1_2;

#define MAX_OBJECTS 10
UG_OBJECT obj_buff_wnd_1[MAX_OBJECTS];

void pixel_set(UG_S16 x, UG_S16 y, UG_COLOR rgb)
{
    uint16_t R = (rgb >> 16) & 0x0000FF;
    uint16_t G = (rgb >> 8) & 0x0000FF;
    uint16_t B = rgb & 0x0000FF;
    UG_COLOR RGB16 = RGBConv(R,G,B);
    draw_pixel(x,y,RGB16);
}

UG_RESULT _HW_DrawLine(UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR rgb)
{
    uint16_t R = (rgb >> 16) & 0x0000FF;
    uint16_t G = (rgb >> 8) & 0x0000FF;
    uint16_t B = rgb & 0x0000FF;
    UG_COLOR RGB16 = RGBConv(R,G,B);
    if (x1 == x2) {
        draw_vertical_line(x1,y1,y2-y1,RGB16);
    } else if (y1 == y2) {
        draw_horizontal_line(x1,y1,x2-x1,RGB16);
    } else {
        //drawLine(x1,y1,x2,y2,RGB16);
    }
    return UG_RESULT_OK;
}

UG_RESULT _HW_FillFrame(UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR rgb)
{
    uint16_t R = (rgb >> 16) & 0x0000FF;
    uint16_t G = (rgb >> 8) & 0x0000FF;
    uint16_t B = rgb & 0x0000FF;
    UG_COLOR RGB16 = RGBConv(R,G,B);
    fill_rectangle_alt(x1,x2,y1,y2,RGB16);
    return UG_RESULT_OK;
}

void window_1_callback( UG_MESSAGE* msg )
{
   if ( msg->type == MSG_TYPE_OBJECT )
   {
      if ( msg->id == OBJ_TYPE_BUTTON )
      {
         switch( msg->sub_id )
         {
            case BTN_ID_0: // Toggle green LED
            {
               button_green_click();
               break;
            }
            case BTN_ID_1: // Toggle red LED
            {
               button_red_click();
               break;
            }
            default : break;
         }
      }
   }
}

void button_green_click(void)
{
    static bool state = false;
    state = !state;
    if (state) {
        gpio_put(LED_PIN,1);
        UG_ButtonSetText(&window_1, BTN_ID_0, "ON");
    } else {
        gpio_put(LED_PIN,0);
        UG_ButtonSetText(&window_1, BTN_ID_0, "OFF");
    }
}

void button_red_click(void)
{
    static bool state = false;
    state = !state;
    if (state) {
        gpio_put(LED_PIN,1);
        UG_ButtonSetText(&window_1, BTN_ID_1, "ON");
    } else {
        gpio_put(LED_PIN,0);
        UG_ButtonSetText(&window_1, BTN_ID_1, "OFF");
    }
}




bool timer_ts_poll_callback(struct repeating_timer *t)
{
    if (gpio_get(TS_IRQ_PIN) == 0) {
        uint16_t x = ts_get_x();
        uint16_t y = ts_get_y();
        if ((x > 0 && x < 239) && (y > 0 && y < 319)) {
            UG_TouchUpdate(x, y, TOUCH_STATE_PRESSED);
        }
    } else {
        UG_TouchUpdate(-1, -1, TOUCH_STATE_RELEASED);
    }
    UG_Update();
    return true;
}


int main() {

    ili9341_init();
    ts_spi_setup();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN,GPIO_OUT);


    fill_screen(0x0000);
    struct repeating_timer timer;
    add_repeating_timer_ms(30, timer_ts_poll_callback, NULL, &timer);

    UG_Init(&gui, pixel_set, 240, 320);

    UG_DriverRegister( DRIVER_DRAW_LINE, (void*)_HW_DrawLine );
    UG_DriverRegister( DRIVER_FILL_FRAME, (void*)_HW_FillFrame );
    UG_DriverEnable( DRIVER_DRAW_LINE );
    UG_DriverEnable( DRIVER_FILL_FRAME );

    UG_FillScreen(C_BLUE);

    UG_WindowCreate( &window_1, obj_buff_wnd_1, MAX_OBJECTS, window_1_callback );
    UG_WindowSetTitleText( &window_1, "uGUI @ RPi PICO" );
    UG_WindowSetTitleTextFont( &window_1, &FONT_12X20 );

    UG_ButtonCreate( &window_1, &button1_1, BTN_ID_0, 10, 10, 110, 60 );
    UG_ButtonSetFont( &window_1, BTN_ID_0, &FONT_12X20 );
    UG_ButtonSetBackColor( &window_1, BTN_ID_0, C_LIME );
    UG_ButtonSetText( &window_1, BTN_ID_0, "OFF" );

    UG_ButtonCreate( &window_1, &button1_2, BTN_ID_1, 10, 80, 110, 130 );
    UG_ButtonSetFont( &window_1, BTN_ID_1, &FONT_12X20 );
    UG_ButtonSetBackColor( &window_1, BTN_ID_1, C_RED );
    UG_ButtonSetText( &window_1, BTN_ID_1, "OFF" );


    UG_WindowShow( &window_1 );
    UG_WaitForUpdate();

	while (1) {

    }
}
