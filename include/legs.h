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
     * same goes for the pins for each leg's knee and hip. Find YOUR neutral angles by trial-and-error, until the robot
     * stands perfectly with 45° angles on the ground. See README.md for details.
     */
    void init() {
        leg_left_front.init('l', 2, 3, 55, 90);
        leg_left_middle.init('l', 4, 5, 83, 86);
        leg_left_back.init('l', 6, 7, 135, 96);
        leg_right_front.init('r', 8, 9, 148, 100);
        leg_right_middle.init('r', 10, 11, 94, 105);
        leg_right_back.init('r', 12, 13, 40, 95);
    }

    /**
     * Executes a full list of commands one after the other, allowing for complex movements.
     * @param command_list: 2D Array consisting of commands, including info on delay time and 12 servo angles.
     * @param amount_of_commands: Integer that describes how many commands are in the command_list.
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

        leg_left_front.write(commands[1], 'h');
        leg_left_front.write(commands[2], 'k');

        leg_left_middle.write(commands[3], 'h');
        leg_left_middle.write(commands[4], 'k');

        leg_left_back.write(commands[5], 'h');
        leg_left_back.write(commands[6], 'k');

        leg_right_front.write(commands[7], 'h');
        leg_right_front.write(commands[8], 'k');

        leg_right_middle.write(commands[9], 'h');
        leg_right_middle.write(commands[10], 'k');

        leg_right_back.write(commands[11], 'h');
        leg_right_back.write(commands[12], 'k');
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

    /**
     * Walk algorithm of the typical tripod gait for a single step.
     */
    void step_forward() {
        int step_forward[6][13] = {
                {300, 120, 90, 60, 90, 120, 90, 120, 90, 60, 90, 120, 90},
                {300, 120, 90, 60, 60, 120, 90, 120, 120, 60, 90, 120, 120},
                {100, 60, 90, 120, 60, 60, 90, 60, 120, 120, 90, 60, 120},
                {300, 60, 90, 120, 90, 60, 90, 60, 90, 120, 90, 60, 90},
                {300, 60, 60, 120, 90, 60, 60, 60, 90, 120, 120, 60, 90},
                {100, 120, 60, 60, 90, 120, 60, 120, 90, 60, 120, 120, 90},
        };

        int amount_of_commands = sizeof(step_forward) / sizeof(step_forward[0]);
        execute_command_list(step_forward, amount_of_commands);
    }

    /**
     * Walk algorithm generated by the machine learning algorithm.
     */
    void step_forward_command_file() {
        int step_forward_command_file[30][13] = {
                {300, 48, 45, 61, 82, 134, 79, 115, 64, 118, 125, 124, 120},
                {300, 106, 91, 105, 55, 74, 80, 47, 53, 130, 47, 133, 56},
                {300, 66, 90, 132, 113, 134, 72, 128, 121, 133, 127, 120, 94},
                {300, 91, 83, 107, 45, 53, 83, 46, 125, 132, 45, 130, 50},
                {300, 55, 77, 132, 107, 130, 71, 123, 132, 133, 128, 119, 94},
                {300, 109, 57, 93, 48, 76, 72, 60, 113, 132, 50, 127, 58},
                {300, 65, 82, 130, 111, 134, 72, 123, 81, 132, 130, 124, 92},
                {300, 97, 79, 62, 45, 63, 80, 80, 53, 131, 46, 124, 63},
        };

        int amount_of_commands = sizeof(step_forward_command_file) / sizeof(step_forward_command_file[0]);
        execute_command_list(step_forward_command_file, amount_of_commands);
    }

};