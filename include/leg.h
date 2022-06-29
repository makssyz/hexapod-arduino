#include "../lib/Servo/src/Servo.h"

/**
 * A single Leg which combines two servos into a single object. Information on the current angle and the initial
 * neutral angle for both the knee and hip servo are saved, since it's faster and more reliable than reading
 * the actual angle from the physical servo.
 */
class Leg {
public:
    Servo knee{};
    Servo hip{};

    char side{};
    int current_knee_angle{};
    int current_hip_angle{};
    int neutral_knee_angle{};
    int neutral_hip_angle{};

    /**
     * Initialize a single leg and connect the servo objects to the physical pins on the robot.
     *
     * For details on the Adeept Pixie's pins, refer to the robot's instructions.
     *
     * @param l_or_r: Is the leg on the left = 'l' or on the right = 'r' side of the robot according to its head.
     * @param pin_hip: Pin for the servo which is closer to the body was connected.
     * @param pin_knee: Pin for the servo which controls the lower part of the leg that touches the ground.
     * @param neutral_angle_hip: The hip's neutral angle, should be 45° from the body.
     * @param neutral_angle_knee: The knee's neutral angle, should be 45° from the ground.
     */
    void init(char l_or_r, int pin_hip, int pin_knee, int neutral_angle_hip, int neutral_angle_knee) {
        this->side = l_or_r;

        this->current_hip_angle = neutral_angle_hip;
        this->neutral_hip_angle = neutral_angle_hip;
        this->neutral_knee_angle = neutral_angle_knee;
        this->current_knee_angle = neutral_angle_knee;

        this->hip.attach(pin_hip);
        this->knee.attach(pin_knee);
    }

    /**
     * Moves a servo to an absolute angle while respecting the individual neutral angle of each servo.
     *
     * @param absolute_angle: Angle to move the servo.
     * @param knee_or_hip: Select the servo of a leg, e.g., knee = 'k' or hip = 'h'.
     */
    void write(int absolute_angle, char knee_or_hip) {
        switch (knee_or_hip) {
            case 'h':
                this->current_hip_angle = absolute_angle - 90 + this->neutral_hip_angle;
                this->hip.write(this->current_hip_angle); break;
            case 'k':
                this->current_knee_angle = absolute_angle - 90 + this->neutral_knee_angle;
                this->knee.write(this->current_knee_angle);
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
            start_thigh_angle = neutral_hip_angle;
            start_shin_angle = neutral_knee_angle;
        } else {
            start_thigh_angle = current_hip_angle;
            start_shin_angle = current_knee_angle;
        }
        switch (direction) {
            case 'f':
                this->current_hip_angle = start_thigh_angle - degree;
                this->hip.write(current_hip_angle); break;
            case 'b':
                this->current_hip_angle = start_thigh_angle + degree;
                this->hip.write(this->current_hip_angle); break;
            case 'u':
                this->current_knee_angle = start_shin_angle + degree;
                this->knee.write(this->current_knee_angle); break;
            case 'd':
                this->current_knee_angle = start_shin_angle - degree;
                this->knee.write(this->current_knee_angle); break;
            default: return;
        }
    }
};