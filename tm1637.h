/**
 * Copyright (c) 2017-2018, Łukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 * slightly modified by Marcel Meyer-Garcia to change pin settings easier via #define's
 * This is ATtiny13/25/45/85/24/44/84 library for 4-Digit LED Display based on TM1637 chip.
 *
 * Features:
 * - display raw segments
 * - display digits
 * - display colon
 * - display on/off
 * - brightness control
 *
 * References:
 * - library: https://github.com/lpodkalicki/attiny-tm1637-library
 * - documentation: https://github.com/lpodkalicki/attiny-tm1637-library/README.md
 * - TM1637 datasheet: https://github.com/lpodkalicki/attiny-tm1637-library/blob/master/docs/TM1637_V2.4_EN.pdf
 */

#ifndef	_ATTINY_TM1637_H_
#define	_ATTINY_TM1637_H_

#include <stdint.h>

// Pin settings
#define TM1637_CLK_OUTPUT() DDRA|=(1<<4) // set CLK pin as output
#define TM1637_CLK_INPUT() DDRA&=~(1<<4) // set CLK pin as input
#define TM1637_CLK_HIGH() PORTA|=(1<<4) // set CLK pin high
#define TM1637_CLK_LOW() PORTA&=~(1<<4) // set CLK pin low
#define TM1637_DIO_OUTPUT() DDRA|=(1<<6) // set DIO pin as output
#define TM1637_DIO_INPUT() DDRA&=~(1<<6) // set DIO pin as input
#define TM1637_DIO_HIGH() PORTA|=(1<<6) // set DIO pin high
#define TM1637_DIO_LOW() PORTA&=~(1<<6) // set DIO pin low
#define TM1637_DIO_READ() (PINA&(1<<6))// read DIO pin state

// Main Settings

#define	TM1637_DELAY_US			(5)
#define	TM1637_BRIGHTNESS_MAX		(7)
#define	TM1637_POSITION_MAX		(4)

// TM1637 commands
#define	TM1637_CMD_SET_DATA		0x40
#define	TM1637_CMD_SET_ADDR		0xC0
#define	TM1637_CMD_SET_DSIPLAY		0x80

// TM1637 data settings (use bitwise OR to contruct complete command)
#define	TM1637_SET_DATA_WRITE		0x00 // write data to the display register
#define	TM1637_SET_DATA_READ		0x02 // read the key scan data
#define	TM1637_SET_DATA_A_ADDR		0x00 // automatic address increment
#define	TM1637_SET_DATA_F_ADDR		0x04 // fixed address
#define	TM1637_SET_DATA_M_NORM		0x00 // normal mode
#define	TM1637_SET_DATA_M_TEST		0x10 // test mode

// TM1637 display control command set (use bitwise OR to consruct complete command)
#define	TM1637_SET_DISPLAY_OFF		0x00 // off
#define	TM1637_SET_DISPLAY_ON		0x08 // on


/**
 * Initialize TM1637 display driver.
 * Clock pin (TM1637_CLK_PIN) and data pin (TM1637_DIO_PIN)
 * are defined at the top of this file.
 */
void TM1637_init(const uint8_t enable, const uint8_t brightness);

/**
 * Turn display on/off.
 * value: 1 - on, 0 - off
 */
void TM1637_enable(const uint8_t value);

/**
 * Set display brightness.
 * Min value: 0
 * Max value: 7
 */
void TM1637_set_brightness(const uint8_t value);

/**
 * Display raw segments at position (0x00..0x03)
 *
 *      bits:
 *        -- 0 --
 *       |       |
 *       5       1
 *       |       |
 *        -- 6 --
 *       |       |
 *       4       2
 *       |       |
 *        -- 3 --
 *
 * Example segment configurations:
 * - for character 'H', segments=0b01110110
 * - for character '-', segments=0b01000000
 * - etc.
 */
void TM1637_display_segments(const uint8_t position, const uint8_t segments);

/**
 * Display digit ('0'..'9') at position (0x00..0x03)
 */
void TM1637_display_digit(const uint8_t position, const uint8_t digit);

/**
 * Display colon on/off.
 * value: 1 - on, 0 - off
 */
void TM1637_display_colon(const uint8_t value);

/**
 * Clear all segments (including colon).
 */
void TM1637_clear(void);

#endif	/* !_ATTINY_TM1637_H_ */
