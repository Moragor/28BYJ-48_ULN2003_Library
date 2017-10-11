#include "Mora_28BYJ_48.h"

Mora_28BYJ_48 stepper(2, 3, 4, 5);              //Define Arduino pins connected to controller inputs In1, In2, In3, In4

void setup() {
  //stepper.setDelay(65535);                    //Set delay in micros between steps to determine speed. Max 65535, Min 1700 for full step, Min 900 for half step
}

void loop() {
  stepper.setDelay(10000);                      //The delay can be set before every move
  stepper.stepF(512);                           //stepF() executes a full step rotation, desired number of steps as parameter. Max (-)32,767
  delay(2000);                                  //2048 steps per full <full step> revolution (might slighly vary depending on true gear reduction ratio)
  stepper.setDelay(2000);
  stepper.stepF(-512);                          //Negative numbers to change direction
  delay(2000);
  stepper.setDelay(10000);
  stepper.stepH(1024);                          //stepH() executes a half step rotation. Max (-)32,767
  delay(2000);                                  //4096 steps per full <half step> revolution (might slighly vary depending on true gear reduction ratio)
  stepper.setDelay(2000);                       //Full step and half step can be mixed if needed.
  stepper.stepH(-1024);
  delay(2000);

}
