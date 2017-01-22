/*
 * AUTHOR: Johan van Zyl
 *
 * DESCRIPTION: Digipot Example using the X9C104 as a DCP (Digitally Controlled Potentiometer) along with the MSP432 as uC.
 * 				Button S1 (P1.1) will in/decrease resistance. Button S2 (P1.4) will change direction.
 * 				Resistance range of 0 -  100kOhms. 100 Wiper tap points (1kOhm steps).
 * 				This example is based upon TI's TI-RTOS empty project. Search for @jvz for project modifications.
 *
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
 *
 *
 * VERSION: 1.02
 *
 * CHANGES:
 * 			* Continued cleaning project.
 * 			* Split into folders/header.
 * 			* Added resetPot and saveVal functions.
 *
 * TODO: verify timing with oscilloscope.
 *
 */

// TI header
/*
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== main.c ========
 */
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SDSPI.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>
// #include <ti/drivers/WiFi.h>

/* Board Header file */
#include "Board.h"

// @jvz
/* X9C104 Header file */
#include <X9C104/X9C104.h>

/*
 *  ======== main ========
 */
int main(void)
{
    //Task_Params taskParams;

    /* Call board init functions */
    Board_initGeneral();
    Board_initGPIO();
    // Board_initI2C();
    // Board_initSDSPI();
    // Board_initSPI();
    // Board_initUART();
    // Board_initWatchdog();
    // Board_initWiFi();

    /* Install Button callback */
    GPIO_setCallback(Board_BUTTON0, changeResistanceBtnFxn);

    /* Enable interrupts */
    GPIO_enableInt(Board_BUTTON0);

    /*
     *  If more than one input pin is available for your device, interrupts
     *  will be enabled on Board_BUTTON1.
     */
    if (Board_BUTTON0 != Board_BUTTON1) {
        /* install Button callback */
        GPIO_setCallback(Board_BUTTON1, changeWiperDirBtnFxn);
        GPIO_enableInt(Board_BUTTON1);
    }

    /* Start BIOS */
    BIOS_start();

    return (0);
}
