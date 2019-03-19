#include <Arduino.h>
#include <ArduinoSTL.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <SPI.h>
#include <Wire.h>
#include <MPU9250.h>
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/MagneticField.h>
#include <sensor_msgs/Range.h>
#include <psi/JoystickInput.h>

// Imu sensor
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2
#define GRAVITY_CONSTANT 9.80665

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
ros::Publisher compass_pub("/psi/sensors/compass", &compass_msg);
ros::Publisher range_left_outer_pub("/psi/sensors/range/left_outer", &range_msg);
ros::Publisher range_left_inner_pub("/psi/sensors/range/left_inner", &range_msg);
ros::Publisher range_right_outer_pub("/psi/sensors/range/right_outer", &range_msg);
ros::Publisher range_right_inner_pub("/psi/sensors/range/right_inner", &range_msg);

MPU9250 mpu;
float orientation_covariance[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Need to find out how to obtain this
float angular_velocity_covariance[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
float linear_acceleration_covariance[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
float magnetic_field_covariance[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

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

ros::Subscriber<psi::JoystickInput> joystick_input_sub("/psi/drive/joystick_input", &joystick_input_cb);

void setup()
{
  // ROS initialization
  nh.initNode();
  nh.advertise(imu_pub);
  nh.advertise(compass_pub);
  nh.advertise(range_left_outer_pub);
  nh.advertise(range_left_inner_pub);
  nh.advertise(range_right_outer_pub);
  nh.advertise(range_right_inner_pub);
  nh.subscribe(joystick_input_sub);

  // Arduino initialization
  Wire.begin();
  SPI.begin();

  // Imu sensor initialization
  imu_msg.header.frame_id = "imu_link";
  compass_msg.header.frame_id = "compass_link";
  std::copy(orientation_covariance, orientation_covariance + 9, imu_msg.orientation_covariance);
  std::copy(angular_velocity_covariance, angular_velocity_covariance + 9, imu_msg.angular_velocity_covariance);
  std::copy(linear_acceleration_covariance, linear_acceleration_covariance + 9, imu_msg.linear_acceleration_covariance);
  std::copy(magnetic_field_covariance, magnetic_field_covariance + 9, compass_msg.magnetic_field_covariance);
  mpu.setup();
  mpu.calibrateAccelGyro();

  // Range sensor initialization
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.field_of_view = 0.0174533;
  range_msg.min_range = MIN_RANGE;
  range_msg.max_range = MAX_RANGE;
  pinMode(TRIG_PIN_LEFT_OUTER, OUTPUT);
  pinMode(ECHO_PIN_LEFT_OUTER, INPUT);
  pinMode(TRIG_PIN_LEFT_INNER, OUTPUT);
  pinMode(ECHO_PIN_LEFT_INNER, INPUT);
  pinMode(TRIG_PIN_RIGHT_OUTER, OUTPUT);
  pinMode(ECHO_PIN_RIGHT_OUTER, INPUT);
  pinMode(TRIG_PIN_RIGHT_INNER, OUTPUT);
  pinMode(ECHO_PIN_RIGHT_INNER, INPUT);

  // Digital potentiometer initialization
  pinMode(CS, OUTPUT);
}

void loop()
{
  // static uint32_t prev_ms = millis();
  //
  // if ((millis() - prev_ms) > 50)
  // {
  //   mpu.update();
  //   imu_msg.header.stamp = nh.now();
  //   imu_msg.orientation.x = mpu.getRoll();
  //   imu_msg.orientation.y = mpu.getPitch();
  //   imu_msg.orientation.z = mpu.getYaw();
  //   imu_msg.orientation.w = 1.0;
  //   imu_msg.angular_velocity.x = mpu.getGyro(X_AXIS);
  //   imu_msg.angular_velocity.y = mpu.getGyro(Y_AXIS);
  //   imu_msg.angular_velocity.z = mpu.getGyro(Z_AXIS);
  //   imu_msg.linear_acceleration.x = mpu.getAcc(X_AXIS) * GRAVITY_CONSTANT;
  //   imu_msg.linear_acceleration.y = mpu.getAcc(Y_AXIS) * GRAVITY_CONSTANT;
  //   imu_msg.linear_acceleration.z = mpu.getAcc(Z_AXIS) * GRAVITY_CONSTANT;
  //   imu_pub.publish(&imu_msg);

  //   compass_msg.header.stamp = nh.now();
  //   compass_msg.magnetic_field.x = mpu.getMag(X_AXIS);
  //   compass_msg.magnetic_field.y = mpu.getMag(Y_AXIS);
  //   compass_msg.magnetic_field.z = mpu.getMag(Z_AXIS);
  //   compass_pub.publish(&compass_msg);

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
  //   prev_ms = millis();
  // }

  digitalPotWrite(address_x_input, x_input);
  digitalPotWrite(address_y_input, y_input);

  nh.spinOnce();
}