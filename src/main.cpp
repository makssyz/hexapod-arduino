#include "Arduino.h"
#include "legs.h"

Legs legs;

void setup() {
    Serial.begin(9600);

    legs.init();
    legs.neutralize();
    legs.dance(2000);
}

void loop() {

//    Serial.println(1);

}

