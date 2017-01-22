/*
 * X9C104.h
 *
 *  Created on: 22 Jan 2017
 *  Author: jvz1990
 *
 *  Description: header file for X9C104 Digital Pot
 */

/* from main.c */
/*
 * NOTES: The X9C104 does not use a standard protocol. Therefore the interface relies on bit-bashing 3 pins.
 * 		  INPUTS:
 * 		  PIN 1: INC: Controls increment/decrement resistance according to the direction assigned by PIN 2.
 * 		  		 Negative-edge triggered.
 * 		  		 1 uS MIN LOW/HIGH toggle period.
 * 		  		 High Voltage: 2V min.
 * 		  		 Low Voltage: 0.8V max.
 * 		  PIN 2: UP/DOWN: Controls the movement direction of wiper. Positive -> UP. GND -> DOWN.
 * 		  		 2.9 uS MIN U/D to INC setup.
 * 		  		 100ns MIN INC HIGH to U/D change.
 * 		  PIN 7: CS: Controls the value stored in non-volatile memory. Connect to P3.5.
 * 		  			 Leave grounded to activate device. High for storing current value.
 *
 * 		  OUTPUTS:
 * 		  PIN 6: RL/VL: The equivalent of a low terminal of a potentiometer.
 * 		  PIN 5: VW/RW: The equivalent of a wiper terminal of a potentiometer.
*/

#ifndef X9C104_X9C104_H_
#define X9C104_X9C104_H_

#include "../Board.h"
#define INC Board_P3_7
#define DIR Board_P3_6
#define CS Board_P3_5

/*
 * ===== changeResistanceBtnFxn ====
 * @jvz
 * Changes resistance into the direction defined by UP/DOWN (P3.5)
 */
void changeResistanceBtnFxn(unsigned int index);

/*
 * ===== changeWiperDirBtnFxn ====
 * @jvz
 * Changes direction for wiper P3.6
 */
void changeWiperDirBtnFxn(unsigned int index);

/*
 * ===== resetPot ====
 * @jvz
 * Reset Pot, brings down the POT close to 0 ohm
 */
void resetPot(void);

/*
 * ===== saveVal ====
 * @jvz
 * Saves current potentiometer value
 */
void saveVal(void);

#endif /* X9C104_X9C104_H_ */
