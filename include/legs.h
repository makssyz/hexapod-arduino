#include "../lib/Servo/src/Servo.h"

class Leg {
public:
    Servo shin{};
    Servo thigh{};

    char side{};
    int current_shin_angle{};
    int current_thigh_angle{};
    int neutral_shin_angle{};
    int neutral_thigh_angle{};

    void init(char l_or_r, int pin_thigh, int pin_shin, int neutral_angle_thigh, int neutral_angle_shin);

    void neutralize();
    void move(int degree, char direction, bool from_neutral);

    void print();

    void write(int absolute_degree, char shin_or_thigh);
};

class Legs {
public:
    Leg leg_left_front;
    Leg leg_left_middle;
    Leg leg_left_back;
    Leg leg_right_front;
    Leg leg_right_middle;
    Leg leg_right_back;

    void init();
    void neutralize();
    void dance(int degree, int wait);
    void move_three_legs(Leg leg_1, Leg leg_2, Leg leg_3, int degree, char movement);

    void walk_stance();

    void tripod_gait_move_left(char direction, int degree);

    void tripod_gait_move_right(char direction, int degree);

    void walk(int steps, char direction, int height, int distance, int wait);

    void command_to_legs(int *commands);
};