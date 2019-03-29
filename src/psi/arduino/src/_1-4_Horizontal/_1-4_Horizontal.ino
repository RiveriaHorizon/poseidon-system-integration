  #include "math.h"
  #include <Servo.h> //servo library
  
  String Xin= "";
  String Yin= "";
  String Yplatein= "";
  String Theta1in= "";

  //values of arm (worm arm L1, mid arm L2, nozzle arm L3, dist worm to edge D)
  double L1=384; //length of worm arm
  double L2=400; //length of mid arm
  double L3=112; //length of nozzle arm
  double D=44; //distance from worm to edge
  double pi=3.141592654;
  double arad=asin(D/L2); //acute fixed angle (radian)
  double a=(180/pi)*arad; //acute fixed angle (degree)

  //values of heights (wheel height WH, component height CH, effective stroke ES)
  double WH=260; //ground to wheel height
  double CH=480; //base of robot to component height
  double ES=800; //effective stroke lenght of linear actuator
  //current height of plate wrt component, Yplate height to be obtained

  unsigned long prev_ms = 0;
  int Encoder1 = 10;
  int Encoder2 = 11;

  int count_encoder1 = 0;
  int count_encoder2 = 0;

  #define enA 9
  #define Motor1 6
  #define Motor2 7
  int rotDirection = 0;

void setup() {
  Serial.begin(9600);

  pinMode(Motor1, OUTPUT);
  pinMode(Motor2, OUTPUT);
  pinMode(Encoder1, INPUT);
  pinMode(Encoder2, INPUT);
  pinMode(enA, OUTPUT);
  
}

void loop() { 
  inputvalues(); //prompt user to input X and Y values

  //run check of X value and obtain corresponding required values
  //run check of Y value and obtain required distance for actuator to move
  checkvalue();

  //trigger motion only if no error and to show error if above the limits
}

void inputvalues(){
  Serial.println("Enter INPUT X (mm).");

  while (Serial.available()==0)
  {
  }
  Xin=Serial.readString(); //Reading Input from Serial port.

  Serial.println("Enter INPUT Y (mm).");

  while (Serial.available()==0)
  {
    //Wait for user input
  }
  Yin=Serial.readString();

  Serial.println("Enter Yplate (mm).");

  while (Serial.available()==0)
  {
    //Wait for user input
  }
  Yplatein=Serial.readString();

  Serial.println("Enter Theta1 (degree).");

  while (Serial.available()==0)
  {
    //Wait for user input
  }
  Theta1in=Serial.readString();

  Serial.println("-------------------------------------"); //Showing the details
  Serial.println("INPUT X: "+Xin);
  Serial.println("INPUT Y: "+Yin);
  Serial.println("INPUT Yplate: "+Yplatein);
  Serial.println("INPUT Theta1: "+Theta1in);

  //convert readString to a number
  //tabulate, check value and return result
  //checkvalue()
  
  Serial.println("~~~~~~~~~~~~~~~"); //Showing the details
}

void checkvalue(){
  //obtain input value from inputvalues()
  //convert readString to a number
  double X=Xin.toDouble();
  double Y=Yin.toDouble();
  double Yplate=Yplatein.toDouble(); //current height of plate wrt component, Yplate height to be obtained
  double theta1in=Theta1in.toDouble(); //input theta1, from rest, theta1in is 90deg

  //calculation
  //check X value
  //check if X=0
  //if yes, obtain required values for X=0
  if(X==0){
    //Angles
    double theta1=90; //worm arm angle at rest (degree)
    double theta1rad=(pi/180)*theta1; //worm arm angle at rest (radian)
    double theta2=270-a; //mid arm angle at rest (degree)
    double theta2rad=(pi/180)*theta2; //mid arm angle at rest (radian)
    double theta3=90+a; //nozzle arm angle at rest (degree)
    double theta3rad=(pi/180)*theta3; //nozzle arm angle at rest(radian)

    //Height wrt Plate
    double Hworm=L1*sin(theta1rad); //VH plate to tip of worm arm
    double Hmid=L2*(cos((1.5*pi)-theta2rad)); //VH tip of worm arm to tip of mid arm
    double Hnozzle=L3*(sin(theta3rad-arad)); //VH tip of mid arm to tip of nozzle arm

    //tabulate Corresponding Yvalue
    double Yworm=L1; //tip of worm arm wrt plate
    double Ymid=L1-Hmid; //tip of mid arm wrt plate
    double Ynozzle=L1-Hmid-Hnozzle; //tip of nozzle wrt plate

    double Y1= CH+Ynozzle+Yplate; //corresponding arm height (nozzle tip to origin), Yplate to be obtained
    double Y2= Y-CH; //distance from component height to tip of nozzle
  
    //check Y1 and Y
    double Hplate=Y-Y1; //distance or height that the plate has to move

    double Yplatenew=Yplate+Hplate; //new height of plate wrt component 
    
    //check value Y input
    if (Yplatenew <0){
      Serial.println("ERROR, MIN VERTICAL VALUE");
    }
    else if (Y>(ES+CH+Ynozzle)){
      Serial.println("ERROR, MAX VERTICAL VALUE");
    }
    else {
      Serial.println("INPUT X AND Y IS ACCEPTABLE");
      Serial.println(" ");
      Serial.print("Height of Nozzle Tip from Base: "); Serial.print(Y1,5);
      Serial.println(" ");
      Serial.print("Plate to move at distance of: "); Serial.print(Hplate,5);
      Serial.println(" ");
      Serial.print("New Height of Plate wrt Component: "); Serial.print(Yplatenew,5);
      Serial.println(" ");
      Serial.print("Height of Nozzle Tip wrt Plate: "); Serial.print(Ynozzle,5);
      Serial.println(" ");
      Serial.print("Height of Nozzle Tip from Component: "); Serial.print(Y2,3);
      Serial.println(" ");
      Serial.print("New Height of Nozzle Tip from Base: "); Serial.print(Y,3);
      Serial.println(" ");

      //MoveMotor
      //obtain theta values from checkvalue()
      if (theta1 == theta1in){
        Serial.println(" ");
        Serial.println("ARM GEAR MOTOR WILL NOT RUN");
      }
      else {
        double Wgr=theta1in-theta1; //angle which gearmotor is to move
        Serial.print("New Worm Wheel Angle: "); Serial.print(theta1,3);
        Serial.println(" ");
        Serial.print("Worm Wheel to turn at an angle of: "); Serial.print(Wgr,5);

        double Wr=abs(Wgr)*(0.002777778); //rev for worm wheel (1rev-360deg)
        double Gr= Wr*50; //rev for worm gear (gear ratio=50)
        double Tg= (0.12)*Gr; //rev to motor time (500rpm)
        Serial.println(" ");
        Serial.print("Arm Gear Motor will run for (seconds): "); Serial.print(Tg,3);
        Serial.println(" ");

        if (Wgr>0){
          Serial.println(" ");
          Serial.println("Arm Gear Motor will turn CLOCKWISE");

          while(millis() - prev_ms > Tg){
                //motor to turn clockwise for Tg seconds (on for Tg sec, off after Tg sec)
                digitalWrite(Motor1, LOW);
                digitalWrite(Motor2, HIGH);
               
                if (digitalRead(Encoder1)) {
                  count_encoder1=count_encoder1+1;
                  Serial.println(count_encoder1);
                 }
              
                if (digitalRead(Encoder2)) {
                  count_encoder2=count_encoder2+1;
                  Serial.println(count_encoder2);
                 }
                
                prev_ms=millis();
          }
        }
        else{
          Serial.println(" ");
          Serial.println("Arm Gear Motor will turn ANTI-CLOCKWISE");

          while (millis() - prev_ms > Tg){
                //motor to turn anticlockwise for Tg seconds (on for Tg sec, off after Tg sec)
                digitalWrite(Motor1, HIGH);
                digitalWrite(Motor2, LOW);
                
                if (digitalRead(Encoder1)) {
                  count_encoder1=count_encoder1+1;
                  Serial.println(count_encoder1);
                }
             
                if (digitalRead(Encoder2)) {
                  count_encoder2=count_encoder2+1;
                  Serial.println(count_encoder2);
                }
                
                prev_ms=millis();
          }
        }
      }
    }
  }
  //no, check if X<=112
  //if yes, obtain required values for X<=112
  else if (X<=112){
    //Angles
    double theta1=90; //worm arm angle at rest (degree)
    double theta1rad=(pi/180)*theta1; //worm arm angle at rest (radian)
    double theta2=270-a; //mid arm angle at rest (degree)
    double theta2rad=(pi/180)*theta2; //mid arm angle at rest (radian)
    double theta3rad=arad+(acos(X/L3)); //nozzle arm angle at rest (degree)
    double theta3=(180/pi)*theta3rad; //nozzle arm angle at rest(radian)

    //Height wrt Plate
    double Hworm=L1*sin(theta1rad); //VH plate to tip of worm arm
    double Hmid=L2*(cos((1.5*pi)-theta2rad)); //VH tip of worm arm to tip of mid arm
    double Hnozzle=L3*(sin(theta3rad-arad)); //VH tip of mid arm to tip of nozzle arm

    //tabulate Corresponding Yvalue
    double Yworm=L1; //tip of worm arm wrt plate
    double Ymid=L1-Hmid; //tip of mid arm wrt plate
    double Ynozzle=L1-Hmid-Hnozzle; //tip of nozzle wrt plate

    double Y1= CH+Ynozzle+Yplate; //corresponding arm height (nozzle tip to origin), Yplate to be obtained
    double Y2= Y-CH; //distance from component height to tip of nozzle
  
    //check Y1 and Y
    double Hplate=Y-Y1; //distance or height that the plate has to move

    double Yplatenew=Yplate+Hplate; //new height of plate wrt component 

    //check value Y input
    if (Yplatenew <0){
      Serial.println("ERROR, MIN VERTICAL VALUE");
    }
    else if (Y>(ES+CH+Ynozzle)){
      Serial.println("ERROR, MAX VERTICAL VALUE");
    }
    else {
      Serial.println("INPUT X AND Y IS ACCEPTABLE");
      Serial.println(" ");
      Serial.print("Height of Nozzle Tip from Base: "); Serial.print(Y1,5);
      Serial.println(" ");
      Serial.print("Plate to move at distance of: "); Serial.print(Hplate,5);
      Serial.println(" ");
      Serial.print("New Height of Plate wrt Component: "); Serial.print(Yplatenew,5);
      Serial.println(" ");
      Serial.print("Height of Nozzle Tip wrt Plate: "); Serial.print(Ynozzle,5);
      Serial.println(" ");
      Serial.print("Height of Nozzle Tip from Component: "); Serial.print(Y2,3);
      Serial.println(" ");
      Serial.print("New Height of Nozzle Tip from Base: "); Serial.print(Y,3);
      Serial.println(" "); 
      
      //MoveMotor
      //obtain theta values from checkvalue()
      if (theta1 == theta1in){
        Serial.println(" ");
        Serial.println("ARM GEAR MOTOR WILL NOT RUN");
      }
      else {
        double Wgr=theta1in-theta1; //angle which gearmotor is to move
        Serial.print("New Worm Wheel Angle: "); Serial.print(theta1,3);
        Serial.println(" ");
        Serial.print("Worm Wheel to turn at an angle of: "); Serial.print(Wgr,5);

        double Wr=abs(Wgr)*(0.002777778); //rev for worm wheel (1rev-360deg)
        double Gr= Wr*50; //rev for worm gear (gear ratio=50)
        double Tg= (0.12)*Gr; //rev to motor time (500rpm)
        Serial.println(" ");
        Serial.print("Arm Gear Motor will run for (seconds): "); Serial.print(Tg,3);
        Serial.println(" ");

        if (Wgr>0){
          Serial.println(" ");
          Serial.println("Arm Gear Motor will turn CLOCKWISE");

          while(millis() - prev_ms > Tg){
                //motor to turn clockwise for Tg seconds (on for Tg sec, off after Tg sec)
                digitalWrite(Motor1, LOW);
                digitalWrite(Motor2, HIGH);
               
                if (digitalRead(Encoder1)) {
                  int count_encoder1=count_encoder1+1;
                  Serial.println(count_encoder1);
                }

                if (digitalRead(Encoder2)) {
                  int count_encoder2=count_encoder2+1;
                  Serial.println(count_encoder2);
                }
                
                prev_ms=millis();
          }
        }
        else{
          Serial.println(" ");
          Serial.println("Arm Gear Motor will turn ANTI-CLOCKWISE");

          while(millis() - prev_ms > Tg){
                //motor to turn anticlockwise for Tg seconds (on for Tg sec, off after Tg sec)
                digitalWrite(Motor1, HIGH);
                digitalWrite(Motor2, LOW);

                if (digitalRead(Encoder1)) {
                  int count_encoder1=count_encoder1+1;
                  Serial.println(count_encoder1);
                }
               
                if (digitalRead(Encoder2)) {
                  int count_encoder2=count_encoder2+1;
                  Serial.println(count_encoder2);
                }
               
                prev_ms=millis();
          }

        }
      
      }
    
    }
  }
  
  //no, check if X<=468
  //if yes, obtain required values for X<=468
  else if (X<=468){
    //Angles
    double theta1=90; //worm arm angle at rest (degree)
    double theta1rad=(pi/180)*theta1; //worm arm angle at rest (radian)
    double theta3rad=(asin((X-L3+D)/L2)); //nozzle arm angle at rest (degree)
    double theta3=(180/pi)*theta3rad; //nozzle arm angle at rest(radian)
    double theta2=270-theta3; //mid arm angle at rest (degree)
    double theta2rad=(pi/180)*theta2; //mid arm angle at rest (radian)

    //Height wrt Plate
    double Hworm=L1*sin(theta1rad); //VH plate to tip of worm arm
    double Hmid=L2*(cos((1.5*pi)-theta2rad)); //VH tip of worm arm to tip of mid arm
    double Hnozzle=L3*(sin(((270-theta2)-theta3)*(pi/180))); //VH tip of mid arm to tip of nozzle arm

    //tabulate Corresponding Yvalue
    double Yworm=L1; //tip of worm arm wrt plate
    double Ymid=L1-Hmid; //tip of mid arm wrt plate
    double Ynozzle=L1-Hmid-Hnozzle; //tip of nozzle wrt plate

    double Y1= CH+Ynozzle+Yplate; //corresponding arm height (nozzle tip to origin), Yplate to be obtained
    double Y2= Y-CH; //distance from component height to tip of nozzle
  
    //check Y1 and Y
    double Hplate=Y-Y1; //distance or height that the plate has to move

    double Yplatenew=Yplate+Hplate; //new height of plate wrt component 

    //check value Y input
    if (Yplatenew <0){
      Serial.println("ERROR, MIN VERTICAL VALUE");
    }
    else if (Y>(ES+CH+Ymid)){
      Serial.println("ERROR, MAX VERTICAL VALUE");
    }
    else {
      Serial.println("INPUT X AND Y IS ACCEPTABLE");
      Serial.println(" ");
      Serial.print("Height of Nozzle Tip from Base: "); Serial.print(Y1,5);
      Serial.println(" ");
      Serial.print("Plate to move at distance of: "); Serial.print(Hplate,5);
      Serial.println(" ");
      Serial.print("New Height of Plate wrt Component: "); Serial.print(Yplatenew,5);
      Serial.println(" ");
      Serial.print("Height of Nozzle Tip wrt Plate: "); Serial.print(Ynozzle,5);
      Serial.println(" ");
      Serial.print("Height of Nozzle Tip from Component: "); Serial.print(Y2,3);
      Serial.println(" ");
      Serial.print("New Height of Nozzle Tip from Base: "); Serial.print(Y,3);
      Serial.println(" ");  

      //MoveMotor
      //obtain theta values from checkvalue()
      if (theta1 == theta1in){
        Serial.println(" ");
        Serial.println("ARM GEAR MOTOR WILL NOT RUN");
      }
      else {
        double Wgr=theta1in-theta1; //angle which gearmotor is to move
        Serial.print("New Worm Wheel Angle: "); Serial.print(theta1,3);
        Serial.println(" ");
        Serial.print("Worm Wheel to turn at an angle of: "); Serial.print(Wgr,5);

        double Wr=abs(Wgr)*(0.002777778); //rev for worm wheel (1rev-360deg)
        double Gr= Wr*50; //rev for worm gear (gear ratio=50)
        double Tg= (0.12)*Gr; //rev to motor time (500rpm)
        Serial.println(" ");
        Serial.print("Arm Gear Motor will run for (seconds): "); Serial.print(Tg,3);
        Serial.println(" ");
        
        if (Wgr>0){
          Serial.println(" ");
          Serial.println("Arm Gear Motor will turn CLOCKWISE");

          while(millis() - prev_ms > Tg){
                //motor to turn clockwise for Tg seconds (on for Tg sec, off after Tg sec)
                digitalWrite(Motor1, LOW);
                digitalWrite(Motor2, HIGH);

                if (digitalRead(Encoder1)) {
                  int count_encoder1=count_encoder1+1;
                  Serial.println(count_encoder1);
                }

                if (digitalRead(Encoder2)) {
                  int count_encoder2=count_encoder2++;
                  Serial.println(count_encoder2);
                }
                
                prev_ms=millis();
          }
        }
        else{
          Serial.println(" ");
          Serial.println("Arm Gear Motor will turn ANTI-CLOCKWISE");
                //motor to turn anticlockwise for Tg seconds (on for Tg sec, off after Tg sec)
                digitalWrite(Motor1, HIGH);
                digitalWrite(Motor2, LOW);

                if (digitalRead(Encoder1)) {
                  int count_encoder1=count_encoder1+1;
                  Serial.println(count_encoder1);
                }

                if (digitalRead(Encoder2)) {
                  int count_encoder2=count_encoder2+1;
                  Serial.println(count_encoder2);
                }

                prev_ms=millis();
        }
      }
      
    }

  }
  
  //no, check if X<=852
  //if yes, obtain required values for X<=852
  else if (X<=852){
    //Angles
    double theta1rad=acos((X-L3-L2+D)/L1); //worm arm angle at rest (degree)
    double theta1=(180/pi)*theta1rad; //worm arm angle at rest (radian)
    double theta2=90+theta1; //mid arm angle at rest (degree)
    double theta2rad=(pi/180)*theta2; //mid arm angle at rest (radian)
    double theta3=90; //nozzle arm angle at rest (degree)
    double theta3rad=(pi/180)*theta3; //nozzle arm angle at rest(radian)

    //Height wrt Plate
    double Hworm=L1*sin(theta1rad); //VH plate to tip of worm arm
    double Hmid=0; //VH tip of worm arm to tip of mid arm
    double Hnozzle=L3*sin((theta2rad-theta1rad)-theta3rad); //VH tip of mid arm to tip of nozzle arm

    //tabulate Corresponding Yvalue
    double Yworm=Hworm; //tip of worm arm wrt plate
    double Ymid=Yworm-Hmid; //tip of mid arm wrt plate
    double Ynozzle=Yworm-Hmid-Hnozzle; //tip of nozzle wrt plate

    double Y1= CH+Ynozzle+Yplate; //corresponding arm height (nozzle tip to origin), Yplate to be obtained
    double Y2= Y-CH; //distance from component height to tip of nozzle
  
    //check Y1 and Y
    double Hplate=Y-Y1; //distance or height that the plate has to move

    double Yplatenew=Yplate+Hplate; //new height of plate wrt component 

    //check value Y input
    if (Yplatenew <0){
      Serial.println("ERROR, MIN VERTICAL VALUE");
    }
    else if (Y>(ES+CH+Ymid)){
      Serial.println("ERROR, MAX VERTICAL VALUE");
    }
    else {
      Serial.println("INPUT X AND Y IS ACCEPTABLE");
      Serial.println(" ");
      Serial.print("Height of Nozzle Tip from Base: "); Serial.print(Y1,5);
      Serial.println(" ");
      Serial.print("Plate to move at distance of: "); Serial.print(Hplate,5);
      Serial.println(" ");
      Serial.print("New Height of Plate wrt Component: "); Serial.print(Yplatenew,5);
      Serial.println(" ");
      Serial.print("Height of Nozzle Tip wrt Plate: "); Serial.print(Ynozzle,5);
      Serial.println(" ");
      Serial.print("Height of Nozzle Tip from Component: "); Serial.print(Y2,3);
      Serial.println(" ");
      Serial.print("New Height of Nozzle Tip from Base: "); Serial.print(Y,3);
      Serial.println(" ");

      //MoveMotor
      //obtain theta values from checkvalue()
      if (theta1 == theta1in){
        Serial.println(" ");
        Serial.println("ARM GEAR MOTOR WILL NOT RUN");
      }
      else {
        double Wgr=theta1in-theta1; //angle which gearmotor is to move
        Serial.print("New Worm Wheel Angle: "); Serial.print(theta1,3);
        Serial.println(" ");
        Serial.print("Worm Wheel to turn at an angle of: "); Serial.print(Wgr,5);

        double Wr=abs(Wgr)*(0.002777778); //rev for worm wheel (1rev-360deg)
        double Gr= Wr*50; //rev for worm gear (gear ratio=50)
        double Tg= (0.12)*Gr; //rev to motor time (500rpm)
        Serial.println(" ");
        Serial.print("Arm Gear Motor will run for (seconds): "); Serial.print(Tg,3);
        Serial.println(" ");

        if (Wgr>0){
          Serial.println(" ");
          Serial.println("Arm Gear Motor will turn CLOCKWISE");

          while(millis() - prev_ms > Tg){
                //motor to turn clockwise for Tg seconds (on for Tg sec, off after Tg sec)
                digitalWrite(Motor1, LOW);
                digitalWrite(Motor2, HIGH);
                
                if (digitalRead(Encoder1)) {
                  count_encoder1=count_encoder1+1;
                  Serial.println(count_encoder1);
               }
                if (digitalRead(Encoder2)) {
                  count_encoder2=count_encoder2+1;
                  Serial.println(count_encoder2);
                }
                
                prev_ms=millis();
          }
        }
        else{
          Serial.println(" ");
          Serial.println("Arm Gear Motor will turn ANTI-CLOCKWISE");
                //motor to turn anticlockwise for Tg seconds (on for Tg sec, off after Tg sec)
                digitalWrite(Motor1, HIGH);
                digitalWrite(Motor2, LOW);

                if (digitalRead(Encoder1)) {
                  int count_encoder1=count_encoder1+1;
                  Serial.println(count_encoder1);
               }
                if (digitalRead(Encoder2)) {
                  int count_encoder2=count_encoder2+1;
                  Serial.println(count_encoder2);
                }

                prev_ms=millis();
        }
        
        }
      }
    }
  //no, show ERROR, Max Horizontal Value
  else {
    Serial.println("ERROR, MAX HORIZONTAL VALUE");
  }
  
  Serial.println("-------------------------------------"); //Showing the details

  }



