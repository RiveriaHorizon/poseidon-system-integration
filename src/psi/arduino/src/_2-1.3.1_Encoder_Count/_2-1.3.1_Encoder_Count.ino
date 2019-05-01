// Written by Nur Farzana

String Ecin = "";
String Tto = "";
String Tin = "";
unsigned long prev_ms = 0;
#define enA 9
#define Motor1 6
#define Motor2 7

int Encoder1 = 10;
int Encoder2 = 12; //white

int count_encoder1 = 0;
int count_encoder2 = 0;
int x;
int Ec;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(Motor1, OUTPUT);
  pinMode(Motor2, OUTPUT);
  pinMode(Encoder1, INPUT);
  pinMode(Encoder2, INPUT);
  pinMode(enA, OUTPUT);
}

void loop()
{
  Serial.println("Enter INPUT no of rev.");

  while (Serial.available() == 0)
  {
  }
  Tin = Serial.readString(); //Reading Input from Serial port.

  //  Serial.println("Enter DESIRED THETA (deg).");
  //
  //  while (Serial.available()==0)
  //  {
  //    //Wait for user input
  //  }
  //  Tto=Serial.readString();

  float Thetain = Tin.toDouble();
  //  double Thetato=Tto.toDouble();

  //  double Wgr=Thetain-Thetato;
  //  double Wr=abs(Wgr)*(0.002777778); //rev for worm wheel (1rev-360deg)
  float Gr = Thetain;
  float Re = Gr / 3;
  int Ec = Re * 64 * 2;
  Serial.println(Gr);
  Serial.println(Re);
  Serial.println(Ec);

  count_encoder1 = 0;
  Serial.println(count_encoder1);

  delay(5000);

  while (count_encoder1 <= Ec)
  {
    analogWrite(enA, 100);
    digitalWrite(Motor1, LOW);
    digitalWrite(Motor2, HIGH);
    //
    //     count_encoder1 = digitalRead(Encoder1);
    //
    if (digitalRead(Encoder1))
    {
      count_encoder1 = count_encoder1 + 1;
    }
    Serial.println(count_encoder1);
  }

  analogWrite(enA, 0);

  //count_encoder1=0;
  //     if (count_encoder1>100){
  //      analogWrite(enA, 0); // Send PWM signal to L298N Enable pin (0-255 - control speed of motor)
  //     }
}
