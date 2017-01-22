/*
 * X9C104.c
 *
 *  Created on: 22 Jan 2017
 *      Author: j
 */

#include "X9C104.h"
#include <xdc/std.h>
#include <ti/drivers/GPIO.h>

UInt count = TICKS;

void changeResistanceBtnFxn(unsigned int index) {

	//acts as a debouncer
	count = 10000;
	while (--count > 1);
	count = TICKS;

    /* Clear the GPIO interrupt and increment direction */
	GPIO_write(INC, 0);
	//timer
    while (--count > 1);
    count = TICKS;
    GPIO_toggle(INC);

#ifndef SAVEVAL_
    saveVal();
#endif

}

void changeWiperDirBtnFxn(unsigned int index) {
    /* Clear the GPIO interrupt and toggle direction */
	GPIO_toggle(DIR);

	//timer
    while (--count > 1);
    count = TICKS;
}

// good function to test timing
void resetPot(void) {
	// ensure CS is LOW
	GPIO_write(CS, 0);

	//step down 100 times - no harm trying to step down into negative direction
	UChar i = 0;
	for(; i < 100; i++) {
		GPIO_toggle(INC);
		//timer
	    while (--count > 1);
	    count = TICKS;
	    GPIO_toggle(INC);
	}

	//ensure INC is positive
	GPIO_write(INC, 1); //INC needs to be HIGH to function
}

void saveVal(void) {

    //save to NVM
    GPIO_toggle(CS);
    //timer
    while (--count > 1);
    count = TICKS;
    GPIO_toggle(CS);

    // ensure CS is LOW
    GPIO_write(CS, 0);
}
