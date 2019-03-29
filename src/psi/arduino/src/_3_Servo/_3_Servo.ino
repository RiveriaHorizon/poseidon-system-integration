#include "math.h"
#include <Servo.h> //Servo library

Servo servo_midarm; //initialize a servo object for the connected servo
Servo servo_nozarm;
String Xin = "";
String Yin = "";
String Yplatein = "";
String Theta1in = "";

//values of arm (worm arm L1, mid arm L2, nozzle arm L3, dist worm to edge D)
double L1 = 375; //length of worm arm
double L2 = 400; //length of mid arm
double L3 = 110; //length of nozzle arm
double D1 = 50;  //distance from worm to edge
double D2 = 75;  //distance from edge to noz arm servo at home state

double pi = 3.141592654;
double a = 15;                //angle for mid arm at home state
double arad = (pi / 180) * a; //radian angle
double b = 20;                //angle for nozzle arm when horizontal (degree)
double brad = (pi / 180) * b; //acute fixed angle (radian)

float theta3; //noz arm angle
float theta2; //mid arm angle
float theta1; //worm arm angle

//values of heights (wheel height WH, component height CH, effective stroke ES)
double WH = 260; //ground to wheel height
double CH = 480; //base of robot to component height
double ES = 800; //effective stroke lenght of linear actuator
                 //current height of plate wrt component, Yplate height to be obtained

void setup()
{

    Serial.begin(9600);

    servo_midarm.attach(40); // attach the signal pin of servo to pin of arduino
    servo_nozarm.attach(41);
    servo_midarm.write(15);  // home state of mid arm servo
    servo_nozarm.write(120); // home state of noz arm servo
}

void loop()
{

    Serial.print("Servo Mid Arm Angle : ");
    Serial.print(servo_midarm.read()); //check state of mid arm
    Serial.println(" ");
    Serial.print("Servo Nozzle Arm Angle : ");
    Serial.print(servo_nozarm.read()); //check state of noz arm
    Serial.println(" ");

    int v;
    inputvalues(v); //prompt user to input X and Y values

    //run check of X value and obtain corresponding required values
    //run check of Y value and obtain required distance for actuator to move
    checkvalue(v);

    //trigger motion only if no error and to show error if above the limits
}

void inputvalues(int v)
{
    Serial.println("Enter INPUT X (mm)");

    while (Serial.available() == 0)
    {
    }
    Xin = Serial.readString(); //Reading Input from Serial port.

    Serial.println("-------------------------------------"); //Showing the details
    Serial.println("INPUT X: " + Xin);
    //convert readString to a number
    //tabulate, check value and return result
    //checkvalue()

    Serial.println("~~~~~~~~~~~~~~~"); //Showing the details
}

void checkvalue(int v)
{
    //obtain input value from inputvalues()
    //convert readString to a number
    float X = Xin.toDouble();
    Serial.println(X);

    //calculation
    //check X value
    //check if X<=75
    //if yes, obtain required values for X=0

    if (X <= 75)
    {
        Serial.println("ERROR, HOME STATE");
        //Angles
        theta1 = 90;  //worm arm angle at rest (degree)
        theta2 = 15;  //mid arm angle at rest (degree)
        theta3 = 120; //noz arm angle at rest (degree)
    }
    else if (X <= 185)
    {
        theta1 = 90;                                    //worm arm angle at rest (degree)
        theta2 = 15;                                    //mid arm angle at rest (degree)
        float theta3rad = arad + (acos((X - D2) / L3)); //noz arm angle varies (degree)
        theta3 = (180 / pi) * theta3rad;
    }
    else if (X <= 460)
    {
        theta1 = 90;                                //worm arm angle at rest (degree)
        float theta2rad = asin((X - L3 + D1) / L2); //mid arm angle varies (radian)
        theta2 = (180 / pi) * theta2rad;            //mid arm angle varies (degree)
        theta3 = theta2 + 5;                        //noz arm angle varies wrt to mid arm angle (at rest 15, 20) (degree)
    }
    else if (X <= 835)
    {
        float theta1rad = acos((X - L3 - L2 + D1) / L1); //worm arm angle varies (radian)
        theta1 = (180 / pi) * theta1rad;                 //worm arm angle varies (degree)
        theta2 = 90 + theta1;                            //mid arm angle varies (degree)
        theta3 = 90;                                     //no200z arm angle at rest (degree)
    }

    Serial.println(theta1);
    Serial.println(theta2);
    Serial.println(theta3);

    servo_nozarm.write(theta3);
    servo_midarm.write(theta2);

    Serial.print("Servo Mid Arm Angle : ");
    Serial.print(servo_midarm.read()); //check state of mid arm
    Serial.println(" ");
    Serial.print("Servo Nozzle Arm Angle : ");
    Serial.print(servo_nozarm.read()); //check state of noz arm
    Serial.println(" ");

    Serial.println("-------------------------------------"); //Showing the details

    delay(1000);
}