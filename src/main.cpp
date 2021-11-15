#include "Arduino.h"
#include "legs.h"

Legs legs;

void setup() {
    legs.init();
    legs.neutralize();
//    legs.dance(30, 1000);
//    for (int i = 0; i < 100; i++) {
//        legs.dance(60, 500);
//    }
//    legs.walk_stance();
    //legs.dance(30, 1000);

    //legs.walk(4, 'f', 60, 20, 1000);

    //int commands[] = {200, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60};

    //legs.command_to_legs(commands);
}

void loop() {
//    legs.dance(60, 1000);
    //legs.walk(5, 'f', 60, 30, 500);
    //legs.walk('f', 30, 1000);
}

