#include "Arduino.h"
#include "math.h"

#include <ros.h>
#include <std_msgs/Int64.h>
#include <psi/ArmControl.h>
#include <psi/ArmFeedback.h>

// Constants definition
// Arduino connections
int const ENABLE_LEFT_WORMGEAR = 9;
int const WORMGEAR_LEFT_A = 6;
int const WORMGEAR_LEFT_B = 7;
int const WORMGEAR_LEFT_ENCODER_A = 18;
int const WORMGEAR_LEFT_ENCODER_B = 19;
int const WORMGEAR_SPEED = 250;
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
ros::Int64 encoder_count_a_msg;
ros::Int64 encoder_count_b_msg;
ros::NodeHandle nh;
ros::Publisher arm_feedback_pub("/psi/arm/feedback", &arm_fb_msg);
ros::Publisher encoder_a_pub("/psi/arm/encoder_a", &encoder_count_a_msg);
ros::Publisher encoder_b_pub("/psi/arm/encoder_b", &encoder_count_b_msg);

// Received data from main node
String arm_type = "";
String direction = "";
int servo_hinge_position = 0;
int servo_nozzle_position = 0;
float vertical_distance = 0.0;
float left_horizontal_distance = 0.0;
float right_horizontal_distance = 0.0;

// Servo initialization
// Servo left_hinge;
// Servo left_nozzle;

// Wormgear variables
unsigned long prev_ms = 0;
int desired_encoder_count = 0;
int wormgear_encoder_count_a = 0; // variables that counts the internal
int wormgear_encoder_count_b = 0; // -encoder in the wormgear

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
    left_horizontal_distance = msg.horizontal_distance;
    direction = msg.wormgear_direction;
}

ros::Subscriber<psi::ArmControl> arm_control_sub("/psi/arm/control", &arm_cb);

void setup()
{
    // Wormgear initialization
    pinMode(WORMGEAR_LEFT_A, OUTPUT);
    pinMode(WORMGEAR_LEFT_B, OUTPUT);
    pinMode(WORMGEAR_LEFT_ENCODER_A, INPUT);
    pinMode(WORMGEAR_LEFT_ENCODER_B, INPUT);
    pinMode(ENABLE_LEFT_WORMGEAR, OUTPUT);

    // Hardware interrupts initialization
    attachInterrupt(digitalPinToInterrupt(WORMGEAR_LEFT_ENCODER_A), encoder_isr_a, CHANGE);
    attachInterrupt(digitalPinToInterrupt(WORMGEAR_LEFT_ENCODER_B), encoder_isr_b, CHANGE);

    // ROS Subscriber and Publisher pair for feedback control
    nh.initNode();
    nh.subscribe(arm_control_sub);
    nh.advertise(arm_feedback_pub);
    nh.advertise(encoder_a_pub);
    nh.advertise(encoder_b_pub);
}

// Interrupt service routines for both encoders
void encoder_isr_a()
{
    if (digitalRead(WORMGEAR_LEFT_A) == HIGH)
    {
        if (digitalRead(WORMGEAR_LEFT_B == LOW))
        {
            wormgear_encoder_count_a++;
        }
        else
        {
            wormgear_encoder_count_a--;
        }
    }
    else
    {
        if (digitalRead(WORMGEAR_LEFT_B == LOW))
        {
            wormgear_encoder_count_a--;
        }
        else
        {
            wormgear_encoder_count_a++;
        }
    }
    encoder_count_a_msg.data = wormgear_encoder_count_a;
    encoder_a_pub.publish(&encoder_count_a_msg);
}

void encoder_isr_b()
{
    if (digitalRead(WORMGEAR_LEFT_B) == HIGH)
    {
        if (digitalRead(WORMGEAR_LEFT_A) == LOW)
        {
            wormgear_encoder_count_b++;
        }
        else
        {
            wormgear_encoder_count_b--;
        }
    }
    else
    {
        if (digitalRead(WORMGEAR_LEFT_A) == LOW)
        {
            wormgear_encoder_count_b--;
        }
        else
        {
            wormgear_encoder_count_b++;
        }
    }
    encoder_count_b_msg.data = wormgear_encoder_count_b;
    encoder_b_pub.publish(&encoder_count_b_msg);
}

void loop()
{
    while ((left_horizontal_distance <= wormgear_encoder_count_a) ||
           (left_horizontal_distance <= wormgear_encoder_count_b))
    {
        spin_wormgear(direction, WORMGEAR_SPEED);
    }
    nh.spinOnce();
    delay(1);
}
