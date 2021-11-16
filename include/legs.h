#include "leg.h"

/**
 * All 6 legs the hexapod has.
 */
class Legs {
public:
    Leg leg_left_front;
    Leg leg_left_middle;
    Leg leg_left_back;
    Leg leg_right_front;
    Leg leg_right_middle;
    Leg leg_right_back;

    /**
     * Initialize the legs of the robot according to the corresponding servos and pins. The angles need to be hard-coded,
     * same goes for the pins for each leg's shin and thigh. Find YOUR neutral angles by trial-and-error, until the robot
     * stands perfectly with 45° angles on the ground. See README.md for details.
     */
    void init() {
        leg_left_front.init('l', 2, 3, 90, 90);
        leg_left_middle.init('l', 4, 5, 83, 86);
        leg_left_back.init('l', 6, 7, 92, 96);
        leg_right_front.init('r', 8, 9, 100, 79);
        leg_right_middle.init('r', 10, 11, 94, 81);
        leg_right_back.init('r', 12, 13, 87, 95);
    }

    /**
     * Executes a full list of commands one after the other, allowing for complex movements.
     * @param command_list
     * @param amount_of_commands
     */
    void execute_command_list(int command_list[][13], int amount_of_commands) {
        for (int command_index = 0; command_index < amount_of_commands; command_index++) {
            execute_command(command_list[command_index]);
        }
    }

    /**
     * Executes a command, which is an array of 13 integer values. Nested into the execute_command_list function.
     * @param commands: Array of 13 integer values. Delay at index 0, absolute servo angles at index 1 to 12.
     */
    void execute_command(int commands[13]) {
        delay(commands[0]);

        leg_left_front.write(commands[1], 't');
        leg_left_front.write(commands[2], 's');

        leg_left_middle.write(commands[3], 't');
        leg_left_middle.write(commands[4], 's');

        leg_left_back.write(commands[5], 't');
        leg_left_back.write(commands[6], 's');

        leg_right_front.write(commands[7], 't');
        leg_right_front.write(commands[8], 's');

        leg_right_middle.write(commands[9], 't');
        leg_right_middle.write(commands[10], 's');

        leg_right_back.write(commands[11], 't');
        leg_right_back.write(commands[12], 's');
    }

    /**
     * Perform a cute lil' dance move that can be looped.
     * @param wait: Delay between dance movements.
     */
    void dance(int wait) {
        int command_list[4][13] = {
                {wait, 90, 90, 90, 40, 90, 90, 90, 140, 90,  90, 90, 140},
                {wait, 90, 90, 90, 90, 90, 90, 90,  90, 90,  90, 90,  90},
                {wait, 90, 40, 90, 90, 90, 40, 90,  90, 90, 140, 90,  90},
                {wait, 90, 90, 90, 90, 90, 90, 90,  90, 90,  90, 90,  90}
        };

        int amount_of_commands = sizeof(command_list) / sizeof(command_list[0]);
        this->execute_command_list(command_list, amount_of_commands);
    }

    /**
     * Stand with all legs in the neutral position. Middle legs stand 90° from the body, front legs face 45° forward,
     * rear legs face 45° backwards. This is the most stable position the robot can stand in.
     */
    void neutralize() {
        int command[] = {0, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90};
        this->execute_command(command);
    }
};