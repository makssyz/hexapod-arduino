//
// Created by Makss Golubs on 27.10.21.
//
#include "../lib/Servo/src/Servo.h"
#include "Arduino.h"
#include "legs.h"

/*
 * Initialisation
 */

void Leg::init(char l_or_r, int pin_thigh, int pin_shin, int neutral_angle_thigh, int neutral_angle_shin) {
    this->side = l_or_r;

    this->current_thigh_angle = neutral_angle_thigh;
    this->neutral_thigh_angle = neutral_angle_thigh;
    this->neutral_shin_angle = neutral_angle_shin;
    this->current_shin_angle = neutral_angle_shin;

    this->thigh.attach(pin_thigh);
    this->shin.attach(pin_shin);
}

void Legs::init() {
    leg_left_front.init('l', 2, 3, 90, 90);
    leg_left_middle.init('l', 4, 5, 83, 86);
    leg_left_back.init('l', 6, 7, 92, 96);
    leg_right_front.init('r', 8, 9, 100, 79);
    leg_right_middle.init('r', 10, 11, 94, 81);
    leg_right_back.init('r', 12, 13, 87, 90);
}

/*
 * Movement
 */

void Leg::move(int degree, char direction, bool from_neutral=false) {
    if (this->side == 'l') degree = -degree;
    int start_thigh_angle;
    int start_shin_angle;
    if (from_neutral) {
        start_thigh_angle = neutral_thigh_angle;
        start_shin_angle = neutral_shin_angle;
    } else {
        start_thigh_angle = current_thigh_angle;
        start_shin_angle = current_shin_angle;
    }
    switch (direction) {
        case 'f':
            this->current_thigh_angle = start_thigh_angle - degree;
            this->thigh.write(current_thigh_angle); break;
        case 'b':
            this->current_thigh_angle = start_thigh_angle + degree;
            this->thigh.write(this->current_thigh_angle); break;
        case 'u':
            this->current_shin_angle = start_shin_angle + degree;
            this->shin.write(this->current_shin_angle); break;
        case 'd':
            this->current_shin_angle = start_shin_angle - degree;
            this->shin.write(this->current_shin_angle); break;
        default: return;
    }
}

void Leg::write(int absolute_degree, char shin_or_thigh) {
    switch (shin_or_thigh) {
        case 's':
            this->current_shin_angle = absolute_degree;
            this->shin.write(this->current_shin_angle);
            break;
        case 't':
            this->current_thigh_angle = absolute_degree;
            this->thigh.write(this->current_thigh_angle); break;
        default:
            return;
    }
}

void Legs::move_three_legs(Leg leg_1, Leg leg_2, Leg leg_3, int degree, char direction) {
    leg_1.move(degree, direction, true);
    leg_2.move(degree, direction, true);
    leg_3.move(degree, direction, true);
}

void Legs::dance(int degree, int wait) {
    neutralize();
    delay(wait);

    move_three_legs(leg_left_front, leg_left_back, leg_right_middle, degree, 'u');
    delay(wait);

    neutralize();
    delay(wait);

    move_three_legs(leg_left_middle, leg_right_front, leg_right_back, degree, 'u');
    delay(wait);
}

void Legs::tripod_gait_move_left(char direction, int degree) {
    move_three_legs(leg_left_front, leg_left_back, leg_right_middle, degree, direction);
}

void Legs::tripod_gait_move_right(char direction, int degree) {
    move_three_legs(leg_left_middle, leg_right_front, leg_right_back, degree, direction);
}

// TODO !!! give walk function a table of movement (12xN degrees) (+1 for wait) !!!
void Legs::walk(int steps, char direction, int height, int distance, int wait) {
    this->walk_stance();

    tripod_gait_move_right('u', height); delay(wait);

    for (int i = 0; i < steps; i++) {
        tripod_gait_move_left('b', distance);
        tripod_gait_move_right('f', distance); delay(wait);

        tripod_gait_move_right('d', height); delay(wait);
        tripod_gait_move_left('u', height); delay(wait);

        tripod_gait_move_right('b', distance);
        tripod_gait_move_left('f', distance); delay(wait);

        tripod_gait_move_left('d', height); delay(wait);
        tripod_gait_move_right('u', height); delay(wait);
    }
}

/**
 * Stance
 */

/**
 * Stand with leg in neutral position.
 */
void Leg::neutralize() {
    this->thigh.write(neutral_thigh_angle);
    this->current_thigh_angle = this->neutral_thigh_angle;

    this->shin.write(neutral_shin_angle);
    this->current_shin_angle = this->neutral_shin_angle;
}

/**
 * Stand with all legs in the neutral position. Middle legs stand 90° from the body, front legs face 45° forward,
 * rear legs face 45° backwards. This is the most stable position the robot can stand in.
 */
void Legs::neutralize() {
    leg_left_front.neutralize();
    leg_left_middle.neutralize();
    leg_left_back.neutralize();
    leg_right_front.neutralize();
    leg_right_middle.neutralize();
    leg_right_back.neutralize();
}

/**
 * Stand with all legs in a 90° angle from the spider body.
 */
void Legs::walk_stance() {
    this->neutralize();
    leg_left_front.move(30, 'b', true);
    leg_right_front.move(30, 'b', true);
    leg_left_back.move(30, 'f', true);
    leg_right_back.move(30, 'f', true);
}

/**
 *
 * @param commands
 */
void Legs::command_to_legs(int commands[]) {
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


















