#include "Arduino.h"
#include "math.h"

#include <Servo.h>
#include <ros.h>
#include <psi/ArmControl.h>
#include <psi/ArmFeedback.h>

// Constants definition
// Arduino connections
int const ENABLE_LEFT_WORMGEAR = 9;
int const WORMGEAR_LEFT_A = 6;
int const WORMGEAR_LEFT_B = 7;
int const WORMGEAR_LEFT_ENCODER = 10;
int const WORMGEAR_SPEED = 100;
// Constants used for arm
double const LENGTH_ARM_WORM = 384;   //length of worm arm
double const LENGTH_ARM_MID = 400;    //length of mid arm
double const LENGTH_ARM_NOZZLE = 112; //length of nozzle arm
double const DISTANCE_WE = 44;        //distance from worm to edge
double const PI = 3.141592654;
double const ACUTE_RADIAN = asin(DISTANCE_WE / LENGTH_ARM_MID); //acute fixed angle (radian)
double const ACUTE_DEGREE = (180 / PI) * ACUTE_RADIAN;          //acute fixed angle (degree)
// Height cosntants (wheel height WH, component height CH, effective stroke ES)
double const HEIGHT_WHEEL = 260;            //ground to wheel height
double const HEIGHT_COMPONENT = 480;        //base of robot to component height
double const EFFECTIVE_STROKE_LENGTH = 800; //effective stroke lenght of linear actuator

// ROS initialization
psi::ArmFeedback arm_fb_msg;
ros::NodeHandle nh;
ros::Publisher arm_feedback_pub("/psi/arm/feedback", &arm_fb_msg);

// Wormgear variables
unsigned long prev_ms = 0;
int desired_encoder_count = 0;
int wormgear_encoder_count = 0; // variable that counts the internal
                                // encoder in the wormgear
float theta_in = 0.0;
String direction = "";

void spin_wormgear(String direction, int speed)
{
    if (direction.equals("Forward"))
    {
        analogWrite(ENABLE_LEFT_WORMGEAR, speed);
        digitalWrite(WORMGEAR_LEFT_A, LOW);
        digitalWrite(WORMGEAR_LEFT_B, HIGH);
    }
    else if (direction.equals("Backward"))
    {
        analogWrite(ENABLE_LEFT_WORMGEAR, speed);
        digitalWrite(WORMGEAR_LEFT_A, HIGH);
        digitalWrite(WORMGEAR_LEFT_B, LOW);
    }
    else if (direction.equals("Pause"))
    {
        analogWrite(ENABLE_LEFT_WORMGEAR, 0);
        digitalWrite(WORMGEAR_LEFT_A, HIGH);
        digitalWrite(WORMGEAR_LEFT_B, LOW);
    }
}

void arm_cb(const psi::ArmControl &msg)
{
    theta_in = msg.wormgear_theta_in;
    direction = msg.wormgear_direction;
}

ros::Subscriber<psi::ArmControl> arm_control_sub("/psi/arm/control", &arm_cb);

void setup()
{
    // Wormgear initialization
    pinMode(WORMGEAR_LEFT_A, OUTPUT);
    pinMode(WORMGEAR_LEFT_B, OUTPUT);
    pinMode(WORMGEAR_LEFT_ENCODER, INPUT);
    pinMode(ENABLE_LEFT_WORMGEAR, OUTPUT);

    // ROS Subscriber and Publisher pair for feedback control
    nh.initNode();
    nh.subscribe(arm_control_sub);
    nh.advertise(arm_feedback_pub);
}

void loop()
{
    float gear_revolution = theta_in;
    float revolution = gear_revolution / 3;
    int desired_encoder_count = revolution * 64 * 2;

    while (wormgear_encoder_count <= desired_encoder_count)
    {
        spin_wormgear(direction, WORMGEAR_SPEED);
        if (digitalRead(WORMGEAR_LEFT_ENCODER))
        {
            wormgear_encoder_count++;
        }
    }

    if (direction.equals("Forward"))
    {
        arm_fb_msg.wormgear_status = "Retract Complete";
    }
    else if (direction.equals("Backward"))
    {
        arm_fb_msg.wormgear_status = "Extend Complete";
    }

    analogWrite(ENABLE_LEFT_WORMGEAR, 0);

    nh.spinOnce();
    delay(1);
}
