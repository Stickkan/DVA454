#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "drivers/buttons.h"
#include "drivers/pinout.h"
#include "Lab_1/helper_function_lab_1.h"
// The error routine that is called if the driver library
// encounters an error.
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
 while(1);
}
#endif
// Main Function
int main(void)
{
    unsigned char ucDelta, ucState;
    volatile uint32_t counter=0;
    // Configure the device pins.
    PinoutSet(false, false);
    // Initialize the button driver.
    ButtonsInit();
    // Enable the GPIO pin for the LED (PN0).
    // Set the direction as output, and
    // enable the GPIO pin for digital function.
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    // Loop forever.
    while (1)
    {
        // Poll the buttons.
        ucState = ButtonsPoll(&ucDelta, 0);
        if (BUTTON_PRESSED(RIGHT_BUTTON, ucState, ucDelta))
        {
//            LEDChaser(); //The LED turn on and off in sequence
//            LEDFlicker(); //The first LED flicker until the plug is pulled
            counter = LEDButtonOnOff(counter); //The LED is turned on and off depending on the value of the counter

        }
        else if (BUTTON_PRESSED(LEFT_BUTTON, ucState, ucDelta)) //If Left button is pressed then turn light on
            LEDWrite(CLP_D1, 0x01);
        else if (BUTTON_RELEASED(LEFT_BUTTON, ucState, ucDelta)) //If Left button is pressed then turn light off
            LEDWrite(CLP_D1, 0x0);
    }
}
