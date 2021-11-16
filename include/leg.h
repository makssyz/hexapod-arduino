#include "../lib/Servo/src/Servo.h"

/**
 * A single Leg which combines two servos into a single object. Information on the current angle and the initial
 * neutral angle for both the shin and thigh servo are saved, since it's faster and more reliable than reading
 * the actual angle from the physical servo.
 */
class Leg {
public:
    Servo shin{};
    Servo thigh{};

    char side{};
    int current_shin_angle{};
    int current_thigh_angle{};
    int neutral_shin_angle{};
    int neutral_thigh_angle{};

    /**
     * Initialize a single leg and connect the servo objects to the physical pins on the robot.
     *
     * For details on the Adeept Pixie's pins, refer to the robot's instructions.
     *
     * @param l_or_r: Is the leg on the left = 'l' or on the right = 'r' side of the robot according to its head.
     * @param pin_thigh: Pin for the servo which is closer to the body was connected.
     * @param pin_shin: Pin for the servo which controls the lower part of the leg that touches the ground.
     * @param neutral_angle_thigh: The thigh's neutral angle, should be 45° from the body.
     * @param neutral_angle_shin: The shin's neutral angle, should be 45° from the ground.
     */
    void init(char l_or_r, int pin_thigh, int pin_shin, int neutral_angle_thigh, int neutral_angle_shin) {
        this->side = l_or_r;

        this->current_thigh_angle = neutral_angle_thigh;
        this->neutral_thigh_angle = neutral_angle_thigh;
        this->neutral_shin_angle = neutral_angle_shin;
        this->current_shin_angle = neutral_angle_shin;

        this->thigh.attach(pin_thigh);
        this->shin.attach(pin_shin);
    }

    /**
     * Moves a servo to an absolute angle while respecting the individual neutral angle of each servo.
     *
     * @param absolute_angle: Angle to move the servo.
     * @param shin_or_thigh: Select the servo of a leg, e.g., shin = 's' or thigh = 't'.
     */
    void write(int absolute_angle, char shin_or_thigh) {
        switch (shin_or_thigh) {
            case 't':
                this->current_thigh_angle = absolute_angle - 90 + this->neutral_thigh_angle;
                this->thigh.write(this->current_thigh_angle); break;
            case 's':
                this->current_shin_angle = absolute_angle - 90 + this->neutral_shin_angle;
                this->shin.write(this->current_shin_angle);
                break;
            default:
                return;
        }
    }

    // todo consider whether this function is useful or nah.
    void move(int degree, char direction, bool from_neutral=false) {
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
};