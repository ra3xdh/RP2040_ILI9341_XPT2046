
/* Author, Copyright: Oleg Borodin <onborodin@gmail.com> 2018 */

#ifndef XPT2046_H_XYZ
#define XPT2046_H_XYZ

#define TS_SPI          spi0
#define TS_MO_PIN       7
#define TS_MI_PIN       0
#define TS_SCL_PIN      6
#define TS_CS_PIN       9
#define TS_IRQ_PIN      15


#define TS_SB       (1 << 7)
#define TS_A2       (1 << 6)
#define TS_A1       (1 << 5)
#define TS_A0       (1 << 4)
#define TS_MODE8    (1 << 3)
#define TS_MODE12   (0 << 3)
#define TS_SER      (1 << 2)
#define TS_DFR      (0 << 2)
#define TS_PD1      (1 << 1)
#define TS_PD0      (1 << 0)

#define TS_COMM_Y_SPOS    (TS_MODE12 | TS_SER | TS_SB | TS_A0)
#define TS_COMM_X_SPOS    (TS_MODE12 | TS_SER | TS_SB | TS_A2 | TS_A0)
#define TS_COMM_Y_DPOS    (TS_MODE12 | TS_SB | TS_A0)
#define TS_COMM_X_DPOS    (TS_MODE12 | TS_SB | TS_A2 | TS_A0)
#define TS_COMM_Z1_POS    (TS_MODE12 | TS_SB | TS_A1 | TS_A0)
#define TS_COMM_Z2_POS    (TS_MODE12 | TS_SB | TS_A2)
#define TS_COMM_TEMP      (TS_MODE12 | TS_SB)

#define TS_EVAL_COUNT 5

#define TS_X_MIN_EDGE 128
#define TS_X_MAX_EDGE 1904
#define TS_Y_MIN_EDGE 96
#define TS_Y_MAX_EDGE 1856

#define TS_X_SCREEN_MIN 0
#define TS_X_SCREEN_MAX 239
#define TS_Y_SCREEN_MIN 0
#define TS_Y_SCREEN_MAX 319

void ts_spi_setup(void);
uint16_t ts_get_data16(uint8_t command);
uint16_t ts_get_x_raw(void);
uint16_t ts_get_y_raw(void);
uint16_t ts_get_x(void);
uint16_t ts_get_y(void);
uint16_t ts_get_z1_raw(void);
uint16_t ts_get_z2_raw(void);

#endif

/* EOF */
