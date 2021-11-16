#include "Arduino.h"
#include "legs.h"

Legs legs;

void setup() {
    Serial.begin(9600);

    legs.init();
    legs.neutralize();
//    for (int i = 0; i < 2; i++) {
//        legs.step();
//    }

    legs.neutralize();
}

void loop() {

//    Serial.println(1);

}

