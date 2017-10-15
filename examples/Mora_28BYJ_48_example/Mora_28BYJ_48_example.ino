#include "Mora_28BYJ_48.h"

Mora_28BYJ_48 stepper(2, 3, 4, 5);    //Define Arduino pins connected to controller inputs In1, In2, In3, In4. This is intended for the commonly
                                      //available ULN2003 Module, other driver modules may require a different pin order.

void setup() {
  //stepper.setDelay(25, false);      //The first parameter is the delay between steps. The second Parameter is used to activate or deactivate
                                      //precision mode. If "false" the delay is measured in miliseconds with a minimum of 3 millis for <full step>
                                      //(stepF) and 2 millis for <half step> (stepH).
  //stepper.setDelay(1950, true);     //If "true" the delay is measured in microseconds with a minimum of 1700 micros for <full step> (stepF) and
                                      //900 micros for <half step> (stepH). Due to the tecnical imitations of "delayMicroseconds()" the maximal
                                      //usable value is 16383.
                                      //If your stepper motor isn't turning even though it should try setting a longer delay.
}

void loop() {
  stepper.setDelay(3, false);         //The delay can be set before every move.
  stepper.stepF(512);                 //stepF() executes a <full step> rotation, desired number of steps as parameter. Max (-)32,767 (16Bit value)
  delay(2000);                        //2048 steps per full <full step> revolution (might slighly vary depending on true gear reduction ratio).
  stepper.setDelay(2000, true);
  stepper.stepF(-512);                //Use negative numbers to change direction.
  delay(2000);
  stepper.setDelay(2, 0);             //The second parameter is a boolean value, you can use "true" and "false" or "1" and "0".
  stepper.stepH(1024);                //stepH() executes a <half step> rotation. Max (-)32,767 (16Bit value)
  delay(2000);                        //4096 steps per full <half step> revolution (might slighly vary depending on true gear reduction ratio)
  stepper.setDelay(900, 1);
  stepper.stepH(-1024);               //Full step and half step can be mixed if needed.
  delay(2000);
}