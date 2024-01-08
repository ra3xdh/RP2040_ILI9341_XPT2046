
/* Author, Copyright: Oleg Borodin <onborodin@gmail.com> 2018 */

#include <stdlib.h>


#include "pico/stdlib.h"
#include "ili9341.h"
#include "xpt2046.h"

void ts_spi_setup(void) {

    spi_init(TS_SPI, 100 * 1000);
    int baudrate = spi_set_baudrate(TS_SPI, 50 * 1000);


    gpio_set_function(TS_MO_PIN, GPIO_FUNC_SPI);
    gpio_set_function(TS_MI_PIN, GPIO_FUNC_SPI);
    gpio_set_function(TS_SCL_PIN, GPIO_FUNC_SPI);

    gpio_init(TS_CS_PIN);
    gpio_set_dir(TS_CS_PIN, GPIO_OUT);
    gpio_put(TS_CS_PIN, 0);

    gpio_init(TS_IRQ_PIN);
    gpio_set_dir(TS_IRQ_PIN, GPIO_IN);
}



uint16_t ts_get_data16(uint8_t command) {
    gpio_put(TS_CS_PIN,0);
    spi_write_blocking(TS_SPI, &command, 1);
    uint16_t res1,res2;
    uint8_t b1,b2;
    //sleep_us(10);
    spi_read_blocking(TS_SPI, 0x00, &b1, 1);
    spi_read_blocking(TS_SPI, 0x00, &b2, 1);
    gpio_put(TS_CS_PIN,1);
    res1 = b1; res2 = b2;
    return ((res1 << 8) | (res2 && 0xFF)) >> 4;
}


uint16_t ts_get_x_raw(void) {
    int16_t res = 0;
    for (uint8_t i = 0; i < TS_EVAL_COUNT; i++) {
        res += ts_get_data16(TS_COMM_X_DPOS);
    }
    return res / TS_EVAL_COUNT;
}

uint16_t ts_get_y_raw(void) {
    int16_t res = 0;
    for (uint8_t i = 0; i < TS_EVAL_COUNT; i++) {
        res += ts_get_data16(TS_COMM_Y_DPOS);
    }
    return res / TS_EVAL_COUNT;
}

uint16_t ts_get_x(void) {

    uint16_t res = ts_get_x_raw();

    if (res >= TS_X_MAX_EDGE)
        return TS_X_SCREEN_MAX;
    if (res <= TS_X_MIN_EDGE)
        return TS_X_SCREEN_MIN;

    res = (TS_X_SCREEN_MAX * (res - TS_X_MIN_EDGE)) / (TS_X_MAX_EDGE - TS_X_MIN_EDGE);
    //return TS_X_SCREEN_MAX - res;
    return res;

}

uint16_t ts_get_y(void) {

    uint16_t res = ts_get_y_raw();

    if (res >= TS_Y_MAX_EDGE)
        return TS_Y_SCREEN_MIN;
    if (res <= TS_Y_MIN_EDGE)
        return TS_Y_SCREEN_MIN;

    res = (TS_Y_SCREEN_MAX * (res - TS_Y_MIN_EDGE)) / (TS_Y_MAX_EDGE - TS_Y_MIN_EDGE);
    return TS_Y_SCREEN_MAX - res;
}

uint16_t ts_get_z1_raw(void) {
    uint16_t res = 0;
    for (uint8_t i = 0; i < TS_EVAL_COUNT; i++) {
        res += ts_get_data16(TS_COMM_Z1_POS);
    }
    return res / TS_EVAL_COUNT;
}

uint16_t ts_get_z2_raw(void) {
    uint16_t res = 0;
    for (uint8_t i = 0; i < TS_EVAL_COUNT; i++) {
        res += ts_get_data16(TS_COMM_Z2_POS);
    }
    return res / TS_EVAL_COUNT;
}

/* EOF */
