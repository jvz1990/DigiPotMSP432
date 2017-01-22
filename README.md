## DigiPot X9C104 Example Summary

Digipot Example using the X9C104 as a DCP (Digitally Controlled Potentiometer) along with the MSP432 as uC.
Button S1 (P1.1) will in/decrease resistance. Button S2 (P1.4) will change direction.
Resistance range of 0 -  100kOhms. 100 Wiper tap points (1kOhm steps).
This example is based upon TI's TI-RTOS empty project. Search for @jvz for project modifications.

** See main.c for more details **

## Peripherals Exercised

* `X9C104` DCP - See `X9C104` folder.
* `GPIO Buttons` - See main() for interupts.

## Example Usage

* Button S1 (P1.1) will in/decrease resistance. 
* Button S2 (P1.4) will change direction.

## (TI-RTOS) Application Design Details

This examples is the same as the __Empty_Minimal__ example except many
development and debug features are enabled. For example:

* Logging is enabled
* Assert checking is enabled
* Kernel Idle task
* Stack overflow checking
* Default kernel heap is present

> Please refer to the __Memory Footprint Reduction__ section in the
> TI-RTOS User Guide *spruhd4.pdf* for a complete and detailed list of the
> differences between the empty minimal and empty projects.

## (TI) References
* For GNU and IAR users, please read the following website for details
  about enabling [semi-hosting](http://processors.wiki.ti.com/index.php/TI-RTOS_Examples_SemiHosting)
  in order to view console output.

* For more help, search either the SYS/BIOS User Guide or the TI-RTOS
  Getting Started Guide within your TI-RTOS installation.