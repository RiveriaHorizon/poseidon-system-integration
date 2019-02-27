#include <PID_v1.h>
#include <MPU9250.h>
#include <L298N.h>

#define EN_LEFT 12
#define EN_RIGHT 9
#define IN1 11
#define IN2 10
#define IN3 8
#define IN4 7

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

double set_point, input, output;
double kp = 8,
       ki = 4,
       kd = 2;

int default_speed = 150;

MPU9250 mpu;
PID pid(&input, &output, &set_point, kp, ki, kd, DIRECT);
L298N motor_left(EN_LEFT, IN1, IN2);
L298N motor_right(EN_RIGHT, IN3, IN4);

void setup()
{
    Serial.begin(115200);

    Wire.begin();

    delay(2000);
    mpu.setup();

    input = 0;
    set_point = 0;
    pid.SetMode(AUTOMATIC);
    pid.SetOutputLimits(-255, 255);

    motor_left.setSpeed(default_speed);
    motor_right.setSpeed(default_speed);
}

void loop()
{
    motor_left.forward();
    motor_right.forward();

    mpu.update();
    Serial.println(mpu.getAcc())
    input = mpu.getGyro(Z_AXIS);
    pid.Compute();

    Serial.print(input);
    Serial.print('\t');
    Serial.println(output);

    motor_right.setSpeed(default_speed + output);
    motor_left.setSpeed(default_speed - output);
}