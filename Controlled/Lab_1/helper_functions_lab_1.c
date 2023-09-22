#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "drivers/buttons.h"
#include "drivers/pinout.h"

void LEDChaser()
{
    volatile uint32_t ui32Loop, lightsOnOff; //Declaration of some variables needed
    volatile uint32_t LEDs[] = { CLP_D1, CLP_D2, CLP_D3, CLP_D4 }; //Declaration of an array with the "names" of each LED
    while (1)
    {

        for (lightsOnOff = 0; lightsOnOff < 4; lightsOnOff++) //Counts from 0 to 3
        {
            LEDWrite(LEDs[lightsOnOff], pow(2, lightsOnOff)); //Turns on the LED. pow() is the function for exponentials
            for (ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
            {
            }//A minor delay
            LEDWrite(LEDs[lightsOnOff], 0x0); //Turns off the LED
        }
        for (lightsOnOff = 2; lightsOnOff > 0; lightsOnOff--) //This is the same as the previous loop but in this case only the 3rd and 2nd LED is lit and in that order.
        {
            LEDWrite(LEDs[lightsOnOff], pow(2, lightsOnOff));
            for (ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
            {

            }
            LEDWrite(LEDs[lightsOnOff], 0x0);
        }
    }
}

void LEDFlicker()
{
    volatile uint32_t ui32Loop;
    while (1)
    {
        LEDWrite(CLP_D1, 0x01); //Turns on the LED
        for (ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }//Delay
        LEDWrite(CLP_D1, 0x0); //Turns off the LED
        for (ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }//Delay
    }
}

uint32_t LEDButtonOnOff(uint32_t counter){
    counter++; //At the start of the program the counter is at 0 and this line increments it
    counter = counter %2; //Counter should only have the value of either 0 or 1 thus it it modulo 2
    LEDWrite(CLP_D1, counter); //Turns on or off depending on the value of counter
    return counter; //Return the counter value so the next time the button is pushed it should turn on if off or off if on.
}
