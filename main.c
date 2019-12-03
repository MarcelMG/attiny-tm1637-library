/**
 * Copyright (c) 2017-2018, ?ukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 * slightly modified by Marcel Meyer-Garcia to change pin settings easier via #define's
 * This is ATtiny24A "Running Digits" example using attiny-tm1637-library,
 * original library: https://github.com/lpodkalicki/attiny-tm1637-library .
 * modified version: https://github.com/MarcelMG/attiny-tm1637-library
 */

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "tm1637.h"

int main(void)
{
	uint8_t n, k = 0;

	/* setup */
	TM1637_init(1/*enable*/, 5/*brightness*/);

	/* loop */
	while (1) {
		for (n = 0; n < TM1637_POSITION_MAX; ++n) {
			TM1637_display_digit(n, (k + n) % 0x10);
		}
		TM1637_display_colon(1);
		_delay_ms(200);
		TM1637_display_colon(0);
		_delay_ms(200);
		k++;
	}
}


