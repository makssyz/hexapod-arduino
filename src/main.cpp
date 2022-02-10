#include "Arduino.h"
#include "legs.h"

Legs legs;

void setup() {
//    Serial.begin(9600);

    legs.init();
    legs.neutralize();
//    for (int i = 0; i < 5; i++) {
//        legs.step_forward();
//    }
//    legs.step_backward();
    int raise_left_front[13] = {0, 90, 40, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90};
//    int raise_right_middle[13] = {0, 90, 90, 90, 90, 90, 90, 90, 90, 90, 115, 90, 90};
    legs.execute_command(raise_left_front);

//    legs.neutralize();
}

void loop() {

//    Serial.println(1);

}

