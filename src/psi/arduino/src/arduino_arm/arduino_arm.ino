// Arm control logic written by Nur Farzana
// ROS integration by Cheng Yong Quan

#include <Arduino.h>
#include <math.h>
#include <Servo.h> //Servo library
#include <ros.h>
#include <psi/ArmControl.h>
#include <psi/ArmHorizontalFeedback.h>

#define SERVO_MIDARM 36
#define SERVO_NOZARM 33
#define MIDARM_HOME_ANGLE 11
#define NOZARM_HOME_ANGLE 110
#define ENABLE_A 10
#define MOTOR_1 6
#define MOTOR_2 7
#define WORMGEAR_SPEED 250

// ROS initialization
ros::NodeHandle nh;
psi::ArmHorizontalFeedback debug_msg;
ros::Publisher debug_pub("/psi/sensors/arm/horizontal", &debug_msg);

Servo servo_midarm; //initialize a servo object for the connected servo
Servo servo_nozarm;
float Xin = -1.0;

//values of arm (worm arm L1, mid arm L2, nozzle arm L3, dist worm to edge D)
double const L1 = 390; //length of worm arm
double const L2 = 400; //length of mid arm
double const L3 = 110; //length of nozzle arm
double const D1 = 45;  //distance from worm to edge
double const D2 = 80;  //distance from edge to noz arm servo at home state

double a = 15;                //angle for mid arm at home state
double arad = (PI / 180) * a; //radian angle
double b = 10;                //angle for nozzle arm when horizontal (degree)
double brad = (PI / 180) * b; //acute fixed angle (radian)

float theta3; //noz arm angle
float theta2; //mid arm angle
float theta1; //worm arm angle
float theta1in = 90;
float theta2in = 10;
float X = -1;

//values of heights (wheel height WH, component height CH, effective stroke ES)
double WH = 260; //ground to wheel height
double CH = 480; //base of robot to component height
double ES = 800; //effective stroke lenght of linear actuator
//current height of plate wrt component, Yplate height to be obtained

int Encoder1 = 3; //yellow wiring

int count_encoder1 = 0;

void arm_control_cb(const psi::ArmControl &msg)
{
    int v;

    Xin = msg.horizontal_distance;
    X = Xin;
    checkvalue(v);
}

ros::Subscriber<psi::ArmControl> arm_control_sub("/psi/arm/control", &arm_control_cb);

void setup()
{
    // ROS initialization
    nh.initNode();
    nh.subscribe(arm_control_sub);
    debug_msg.header.frame_id = "horizontal_arm_link";

    servo_midarm.attach(SERVO_MIDARM); // attach the signal pin of servo to pin of arduino
    servo_nozarm.attach(SERVO_NOZARM);
    servo_midarm.write(MIDARM_HOME_ANGLE); // home state of mid arm servo
    servo_nozarm.write(NOZARM_HOME_ANGLE); // home state of noz arm servo

    pinMode(MOTOR_1, OUTPUT);
    pinMode(MOTOR_2, OUTPUT);
    pinMode(Encoder1, INPUT);
    pinMode(ENABLE_A, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(Encoder1), encoder_isr, CHANGE);
}

void encoder_isr()
{
    if (digitalRead(Encoder1))
    {
        count_encoder1 = count_encoder1 + 1;
    }
}

void spin_wormgear(double WgrA)
{
    if (WgrA > 0)
    {
        //Arm Gear Motor will turn CLOCKWISE
        analogWrite(ENABLE_A, WORMGEAR_SPEED);
        digitalWrite(MOTOR_1, HIGH);
        digitalWrite(MOTOR_2, LOW); //high backwards
    }
    else if (WgrA < 0)
    {
        //Arm Gear Motor will turn ANTI-CLOCKWISE
        analogWrite(ENABLE_A, WORMGEAR_SPEED);
        digitalWrite(MOTOR_1, LOW);
        digitalWrite(MOTOR_2, HIGH); //high backwards
    }
}
void (*resetFunc)(void) = 0; //declare reset

void loop()
{
    //Obtain Angles
    // Serial.print("Worm Gear Motor Angle : ");
    // Serial.print(theta1in); //check state of worm gear arm
    // Serial.println(" ");
    // Serial.print("Servo Mid Arm Angle : ");
    // Serial.print(servo_midarm.read()); //check state of mid arm
    // Serial.println(" ");
    // Serial.print("Servo Nozzle Arm Angle : ");
    // Serial.print(servo_nozarm.read()); //check state of noz arm
    // Serial.println(" ");

    // Serial.println(X);

    //run check of X value and obtain corresponding required values
    //run check of Y value and obtain required distance for actuator to move
    delay(500);

    //reset arduino, to eliminate the drifting
    if (X == 0)
    {
        nh.logdebug("Resetting Arduino.");
        resetFunc();
    }

    nh.spinOnce();

    //trigger motion only if no error and to show error if above the limits
}

void checkvalue(int v) {
  //obtain input value from inputvalues()
  //convert readString to a number


  //calculation
  //check X value distance
  //return result of arm angles

  debug_msg.header.stamp = nh.now();

  if (X <= 20) {
    nh.loginfo("Returning to Home State.");
    //input X value less than 58 will be at rest state (Standard X Home value = 0)
    //Angles
    theta1 = 90; //worm arm angle at rest (degree)
    theta2 = 11; //mid arm angle at rest (degree)
    theta3 = 98; //noz arm angle at rest (degree)

  }
  else if (X <= 180) {
    nh.loginfo("Horizontal value less than or equal to 180.");
    //input X value less than 158 will be at ready state (Standard X ready value = 100)
    //Activate only noz arm at horizontal angle
    //Angles
    theta1 = 90; //worm arm angle at rest (degree)
    theta2 = 11; //mid arm angle at rest (degree)
    theta3 = 5; //noz angle at ready state (degree - horizontal)

  }
  else if (X <= 465) {
    nh.loginfo("Horizontal value less than or equal to 465.");
    //input X value less than 465
    //Activate mid arm to extend further and ensure noz arm is horizontal
    //Angles
    theta1 = 90; //worm arm angle at rest(degree)
    float theta2rad = asin((X - L3 + D1) / L2); //mid arm angle varies (radian)
    theta2 = round((180 / PI) * theta2rad)-3; //mid arm angle varies (degree)
    theta3 = theta2-7; //noz arm angle varies wrt to mid arm angle (at rest 15, 20) (degree)
  }
    else if (X <= 485) {
    nh.loginfo("Horizontal value less than or equal to 485.");
    //Activate mid arm to extend further and ensure noz arm is horizontal
    //Angles
    X=X-20;
    theta1 = 90; //worm arm angle at rest(degree)
    float theta2rad = asin((X - L3 + D1) / L2); //mid arm angle varies (radian)
    theta2 = round((180 / PI) * theta2rad)-1; //mid arm angle varies (degree)
    theta3 = theta2-7; //noz arm angle varies wrt to mid arm angle (at rest 15, 20) (degree)
  }
  else if (X <= 500) {
    //input X value less than 835
    //Activate worm arm to extend further, keep mid arm and noz arm horizontal
    //Angles
    X=X-30;
    float theta1rad = acos((X - 510 + D1) / L1); //worm arm angle varies (radian)
    theta1 = ((180 / PI) * theta1rad); //worm arm angle varies (degree)
    theta2 = 180 - theta1; //mid arm angle varies (degree)
    theta3 = theta1-10; //noz arm angle at rest (degree)
  }
  else if (X <= 650) {
    //input X value less than 835
    //Activate worm arm to extend further, keep mid arm and noz arm horizontal
    //Angles
    X=X-80;
    float theta1rad = acos((X - 510 + D1) / L1); //worm arm angle varies (radian)
    theta1 = ((180 / PI) * theta1rad); //worm arm angle varies (degree)
    theta2 = 180 - theta1; //mid arm angle varies (degree)
    theta3 = theta1-8; //noz arm angle at rest (degree)
  }
  else if (X <= 750) {
    //input X value less than 835
    //Activate worm arm to extend further, keep mid arm and noz arm horizontal
    //Angles
    X=X-60;
    float theta1rad = acos((X - 510 + D1) / L1); //worm arm angle varies (radian)
    theta1 = ((180 / PI) * theta1rad); //worm arm angle varies (degree)
    theta2 = 180 - theta1; //mid arm angle varies (degree)
    theta3 = theta1+12; //noz arm angle at rest (degree)
  }
  
  else if (X <= 835) {
    //input X value less than 835
    //Activate worm arm to extend further, keep mid arm and noz arm horizontal
    //Angles
    float theta1rad = acos((X - 510 + D1) / L1); //worm arm angle varies (radian)
    theta1 = ((180 / PI) * theta1rad); //worm arm angle varies (degree)
    theta2 = 180 - theta1; //mid arm angle varies (degree)
    theta3 = theta1+45; //noz arm angle at rest (degree)
  }
  else {
    nh.logerror("Max horizontal value was input, please check horizontal value again.");
  }

  delay(100);
  debug_msg.theta1 = theta1;
  debug_msg.theta2 = theta2;
  debug_msg.theta3 = theta3;

  //Move Servo
  delay(1000);
  servo_nozarm.write(theta3);
  delay(1000);

  //Move Motor
  if (theta1 == theta1in) {
    analogWrite(ENABLE_A, 0);
  }
  else {
    double WgrA = theta1in - theta1; //angle which gearmotor is to move
    //    if (WgrA<0){
    //      WgrA=WgrA-6;
    //    }
    double Ec = 37 * (abs(WgrA)); //Eqn of encoder count from Angle (Experimental)
    debug_msg.wormgear_angle = WgrA;
    debug_msg.wormgear_desired_encoder_count = Ec;
    Serial.println(WgrA);
    Serial.println(Ec);

    while (count_encoder1 <= Ec) {
      spin_wormgear(WgrA); //Worm Gear Motor Direction
    }
    debug_msg.wormgear_recorded_encoder_count = count_encoder1; //print encoder count in the end

    analogWrite(ENABLE_A, 0);
  }

  delay(1000);
  if (X == 0) { //to damp the retraction motion
    for (int i = theta2in; i >= theta2; i--) {
      servo_midarm.write(i);
      delay(50);
    }
  }
  else {
    servo_midarm.write((int)theta2);
  }
  delay(1000);

  count_encoder1 = 0;
  theta1in = theta1;
  theta2in = theta2;
  debug_msg.servo_midarm = servo_midarm.read();
  debug_msg.servo_nozarm = servo_nozarm.read();
  
  debug_pub.publish(&debug_msg);
  nh.spinOnce();

  delay(1000);

}
