#include "Arduino.h"
#include "legs.h"

Legs legs;

void setup() {
    legs.init();
    legs.neutralize();
    for (int i = 0; i < 5; i++)
        legs.step_forward_command_file();

    legs.neutralize();
}

void loop() {

}

