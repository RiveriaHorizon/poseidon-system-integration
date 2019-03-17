#include "Arduino.h"
#include <Servo.h>
#include <ros.h>
#include <psi/ArmControl.h>
#include <psi/ArmFeedback.h>

#define ENABLE_LEFT_WORMGEAR 9
#define WORMGEAR_LEFT_A 6
#define WORMGEAR_LEFT_B 7
#define WORMGEAR_LEFT_ENCODER 10
#define WORMGEAR_SPEED 250

// ROS initialization
psi::ArmFeedback arm_fb_msg;
ros::NodeHandle nh;
ros::Publisher arm_feedback_pub("/psi/arm/feedback", &arm_fb_msg);

// Wormgear variables
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
