#include <Arduino.h>
#include <ArduinoSTL.h>
#include <SPI.h>
#include <Wire.h>
#include <MPU9250.h>
#include <AccelStepper.h>
#include <ros.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/MagneticField.h>
#include <sensor_msgs/Range.h>
#include <psi/ArmControl.h>
#include <psi/JoystickInput.h>
#include <math.h>

// Imu sensor
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2
#define GRAVITY_PULL_CONSTANT 9.80665

// AccelStepper motors
#define AC_RIGHT_STEP 30
#define AC_RIGHT_DIRECTION 31
#define AC_LEFT_STEP 8
#define AC_LEFT_DIRECTION 9
#define STEPPER_ACCELERATION 20000
#define STEPPER_SPEED 2000
#define INITIALIZE_POSITION 0
#define SINGLE_REV_DISTANCE 10
#define QUARTER_REV_STEPS 200
#define FULL_REV_STEPS 800

// Sonar sensor
#define TRIG_PIN_LEFT_OUTER 22
#define ECHO_PIN_LEFT_OUTER 23
#define TRIG_PIN_LEFT_INNER 24
#define ECHO_PIN_LEFT_INNER 25
#define TRIG_PIN_RIGHT_OUTER 28
#define ECHO_PIN_RIGHT_OUTER 29
#define TRIG_PIN_RIGHT_INNER 26
#define ECHO_PIN_RIGHT_INNER 27
#define MAX_RANGE 4
#define MIN_RANGE 0.02

// ROS initialization
sensor_msgs::Imu imu_msg;
sensor_msgs::MagneticField compass_msg;
sensor_msgs::Range range_msg;
ros::NodeHandle nh;
ros::Publisher imu_pub("/psi/sensors/imu", &imu_msg);
// ros::Publisher compass_pub("/psi/sensors/compass", &compass_msg);
// ros::Publisher range_left_outer_pub("/psi/sensors/range/left_outer", &range_msg);
// ros::Publisher range_left_inner_pub("/psi/sensors/range/left_inner", &range_msg);
// ros::Publisher range_right_outer_pub("/psi/sensors/range/right_outer", &range_msg);
// ros::Publisher range_right_inner_pub("/psi/sensors/range/right_inner", &range_msg);

MPU9250 mpu;
float orientation_covariance[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Need to find out how to obtain this
float angular_velocity_covariance[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
float linear_acceleration_covariance[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
float magnetic_field_covariance[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

// Vertical motion stepper motors initialization
AccelStepper stepper_right(AccelStepper::FULL2WIRE, 30, 31);
AccelStepper stepper_left(AccelStepper::FULL2WIRE, 8, 9);
float y_plate_0 = 100;
float y = 1000;
float vertical_input = 100;
double height = 480;

// Joystick input initialization
int x_input = 125,
    y_input = 125;

byte address_x_input = B00010000,
     address_y_input = B00000000;
int CS = 53; // Slave select pin

float getSonarSensorData(int trig_pin, int echo_pin)
{
  // Clear trig_pin
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  // Sets the trig_pin on HIGH state for 10 micro seconds
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  // Reads the echo_pin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echo_pin, HIGH);
  // Calculating the distance
  return (float)duration * 0.034 / 200; // Obtained in metres
}

int digitalPotWrite(byte address, int value)
{
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}

void joystick_input_cb(const psi::JoystickInput &msg)
{
  x_input = msg.x_input;
  y_input = msg.y_input;
}

void update_range_msg(int trig_pin, int echo_pin)
{
  range_msg.header.stamp = nh.now();
  range_msg.range = getSonarSensorData(trig_pin, echo_pin);
}

void arm_control_cb(const psi::ArmControl &msg)
{
  vertical_input = msg.vertical_distance;
  prepare_vertical_motion();
}

long calculate_steps(long y_2)
{
  //Calculates how many revolutions/steps required for the distance
  //0.25 revolutions is 200 steps as defined on the driver.
  //Convert distance ot the number of revolutions
  //1 revolution is 10mm
  long stepper_revolution = abs(y_2) / SINGLE_REV_DISTANCE;
  long stepper_steps = FULL_REV_STEPS * stepper_revolution;

  return stepper_steps;
}

void prepare_vertical_motion()
{
  float y_in = vertical_input; //current height of plate wrt component, Yplate height to be obtained
  long y_2 = y_plate_0 - y_in; //Yin to change Y1
  long target_steps = 0;
  if (y_in < 100)
  {
    nh.logerror("Input given less than minimum vertical value. Please check your input again.");
  }
  else if (y_in > 860)
  {
    nh.logerror("Input given more than maximum vertical value. Please check your input again.");
  }
  else
  {
    nh.loginfo("Input given is within acceptable range. Proceeding.");
    target_steps = calculate_steps(y_2);
    stepper_right.setSpeed(STEPPER_SPEED); // To spin upwards, send a positive value
    stepper_left.setSpeed(STEPPER_SPEED);  // To spin downwards, send a negative value

    if (y_in < y_plate_0)
    {
      // A negative value was received
      stepper_right.moveTo(-target_steps);
      stepper_left.moveTo(-target_steps);
    }
    else
    {
      stepper_right.moveTo(target_steps);
      stepper_left.moveTo(target_steps);
    }
  }
}

ros::Subscriber<psi::JoystickInput> joystick_input_sub("/psi/drive/joystick_input", &joystick_input_cb);
ros::Subscriber<psi::ArmControl> arm_control_sub("/psi/arm/control", &arm_control_cb);

void setup()
{
  // ROS initialization
  nh.initNode();
  nh.advertise(imu_pub);
  // nh.advertise(compass_pub);
  // nh.advertise(range_left_outer_pub);
  // nh.advertise(range_left_inner_pub);
  // nh.advertise(range_right_outer_pub);
  // nh.advertise(range_right_inner_pub);
  nh.subscribe(joystick_input_sub);
  nh.subscribe(arm_control_sub);

  // Arduino initialization
  Wire.begin();
  SPI.begin();

  // Imu sensor initialization
  imu_msg.header.frame_id = "imu_link";
  compass_msg.header.frame_id = "compass_link";
  std::copy(orientation_covariance, orientation_covariance + 9, imu_msg.orientation_covariance);
  std::copy(angular_velocity_covariance, angular_velocity_covariance + 9, imu_msg.angular_velocity_covariance);
  std::copy(linear_acceleration_covariance, linear_acceleration_covariance + 9, imu_msg.linear_acceleration_covariance);
  // std::copy(magnetic_field_covariance, magnetic_field_covariance + 9, compass_msg.magnetic_field_covariance);
  mpu.setup();
  mpu.calibrateAccelGyro();

  // Note that both stepper moves at 200 steps per 0.25 revolution
  // Change the number of steps using the switches on the driver itself
  stepper_left.setCurrentPosition(INITIALIZE_POSITION);
  stepper_left.setAcceleration(STEPPER_ACCELERATION);
  stepper_right.setCurrentPosition(INITIALIZE_POSITION);
  stepper_right.setAcceleration(STEPPER_ACCELERATION);

  // // Range sensor initialization
  // range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  // range_msg.field_of_view = 0.0174533;
  // range_msg.min_range = MIN_RANGE;
  // range_msg.max_range = MAX_RANGE;
  // pinMode(TRIG_PIN_LEFT_OUTER, OUTPUT);
  // pinMode(ECHO_PIN_LEFT_OUTER, INPUT);
  // pinMode(TRIG_PIN_LEFT_INNER, OUTPUT);
  // pinMode(ECHO_PIN_LEFT_INNER, INPUT);
  // pinMode(TRIG_PIN_RIGHT_OUTER, OUTPUT);
  // pinMode(ECHO_PIN_RIGHT_OUTER, INPUT);
  // pinMode(TRIG_PIN_RIGHT_INNER, OUTPUT);
  // pinMode(ECHO_PIN_RIGHT_INNER, INPUT);

  // Digital potentiometer initialization
  pinMode(CS, OUTPUT);
}

void loop()
{
  while (stepper_right.distanceToGo() > 0 || stepper_right.distanceToGo() < 0)
  {
    stepper_left.run();
    stepper_right.run();
  }

  static uint32_t prev_ms = millis();

  if ((millis() - prev_ms) > 100)
  {
    mpu.update();
    imu_msg.header.stamp = nh.now();
    imu_msg.orientation.x = mpu.getRoll();
    imu_msg.orientation.y = mpu.getPitch();
    imu_msg.orientation.z = mpu.getYaw();
    imu_msg.orientation.w = 1.0;
    imu_msg.angular_velocity.x = mpu.getGyro(X_AXIS);
    imu_msg.angular_velocity.y = mpu.getGyro(Y_AXIS);
    imu_msg.angular_velocity.z = mpu.getGyro(Z_AXIS);
    imu_msg.linear_acceleration.x = mpu.getAcc(X_AXIS) * GRAVITY_PULL_CONSTANT;
    imu_msg.linear_acceleration.y = mpu.getAcc(Y_AXIS) * GRAVITY_PULL_CONSTANT;
    imu_msg.linear_acceleration.z = mpu.getAcc(Z_AXIS) * GRAVITY_PULL_CONSTANT;
    imu_pub.publish(&imu_msg);

    // compass_msg.header.stamp = nh.now();
    // compass_msg.magnetic_field.x = mpu.getMag(X_AXIS);
    // compass_msg.magnetic_field.y = mpu.getMag(Y_AXIS);
    // compass_msg.magnetic_field.z = mpu.getMag(Z_AXIS);
    // compass_pub.publish(&compass_msg);

    //   range_msg.header.frame_id = "sonar_base_left_outer_link";
    //   update_range_msg(TRIG_PIN_LEFT_OUTER, ECHO_PIN_LEFT_OUTER);
    //   range_left_outer_pub.publish(&range_msg);
    //   range_msg.header.frame_id = "sonar_base_left_inner_link";
    //   update_range_msg(TRIG_PIN_LEFT_INNER, ECHO_PIN_LEFT_INNER);
    //   range_left_inner_pub.publish(&range_msg);
    //   range_msg.header.frame_id = "sonar_base_right_outer_link";
    //   update_range_msg(TRIG_PIN_RIGHT_OUTER, ECHO_PIN_RIGHT_OUTER);
    //   range_right_outer_pub.publish(&range_msg);
    //   range_msg.header.frame_id = "sonar_base_right_inner_link";
    //   update_range_msg(TRIG_PIN_RIGHT_INNER, ECHO_PIN_RIGHT_INNER);
    //   range_right_inner_pub.publish(&range_msg);

    digitalPotWrite(address_x_input, x_input);
    digitalPotWrite(address_y_input, y_input);

    prev_ms = millis();
  }

  nh.spinOnce();
}