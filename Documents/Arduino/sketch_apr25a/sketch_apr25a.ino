int trigPinR = 13;
int echoPinR = 12;

int trigPinL = 11;
int echoPinL = 10;

int wait;

int smoothR[2];
int smoothL[2];

long avgR;
long avgL;

long durationR;
long durationL;

#include <Wire.h>
//#include <drivLF.h>
#define uchar unsigned char

int spiggidy = 150;


#define leftP 3
#define left1 4
#define left2 5
#define right1 6
#define right2 7
#define rightP 9



uchar t;
//void send_data(short a1,short b1,short c1,short d1,short e1,short f1);
uchar data[16];

void drividy(float LD, float RD) {

  analogWrite(leftP, abs(LD));
  analogWrite(rightP, abs(RD));

  if (LD > 0) {

    digitalWrite(left1, HIGH);
    digitalWrite(left2, LOW);

  } else {


    digitalWrite(left1, LOW);
    digitalWrite(left2, HIGH);

  }

  if (RD > 0) {

    digitalWrite(right1, LOW);
    digitalWrite(right2, HIGH);

  } else {


    digitalWrite(right1, HIGH);
    digitalWrite(right2, LOW);

  }

}

void driveF() {


  Wire.requestFrom(9, 16);    // request 16 bytes from slave device #9
  while (Wire.available())   // slave may send less than requested
  {
    data[t] = Wire.read(); // receive a byte as character
    if (t < 15)
      t++;
    else
      t = 0;
  }
  Serial.print("data[0]:");
  Serial.print(data[0]);
  Serial.print("data[2]:");
  Serial.print(data[2]);
  Serial.print("data[4]:");
  Serial.print(data[4]);
  Serial.print("data[6]:");
  Serial.print(data[6]);
  Serial.print("data[8]:");
  Serial.print(data[8]);
  Serial.print("data[10]:");
  Serial.print(data[10]);
  Serial.print("data[12]:");
  Serial.print(data[12]);
  Serial.print("data[14]:");
  Serial.println(data[14]);

  //if(wait<1) {

  if (avgL < 650) {

    spiggidy = 0;


  } else if (avgL <= 1600) {

    spiggidy = map(avgL, 650, 1800, 0, 150);

  } else {

    spiggidy = 150;



  }

  if ((data[0] < 90 || data[2] < 90) && (data[12] < 90 || data[14] < 90)) {

    drividy(0, 0);


  } else if (data[0] < 90) {

    drividy(spiggidy, -spiggidy);

  } else if (data[8] < 90 || data[6] < 90 || data[4] < 90 || data[2] < 90) {

    drividy(-spiggidy * .85, spiggidy * .8);



  } else if (data[10] < 90) {

    drividy(-spiggidy * .1, spiggidy * .85);

  } else if (data[12] < 90) {

    drividy(spiggidy * .4, spiggidy * .85);

  } else if (data[14] < 90) {

    drividy(spiggidy * 1.1, spiggidy * 1.1);

  } else {

    drividy(spiggidy, spiggidy * .63);

  }

  /* } else if(wait<66 && wait>5) {

    drividy(spiggidy*.9, spiggidy*.57);


    } else if (wait<5) {

    drividy(spiggidy*.8,spiggidy*.9);


    }

    wait--;*/

  //  }

}

void ultraSonicL() {

  digitalWrite(trigPinL, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);

  //measures time for ultrasonic pulse to return
  pinMode(echoPinL, INPUT);
  durationL = pulseIn(echoPinL, HIGH);

  //Serial.println(avgL);

  avgL = 0; //resets the average

  for (int i = 0; i < 2; i++) { //for loop runs 16 times

    smoothL[i] = {smoothL[i + 1]}; //each smooth value is set to the smooth value taken before it.

    avgL = avgL + smoothL[i]; //the average adds up all of these values.

  }

  smoothL[1] = {durationL}; // new value is set

  avgL = (avgL + smoothL[1]) / 2; //final average in calculated

  // Serial.println(avgL);

  delay(60); //delay so it won't be too crazy.

}


/*void ultraSonicR() {

  digitalWrite(trigPinR, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);

  //measures time for ultrasonic pulse to return
  pinMode(echoPinR, INPUT);
  durationR = pulseIn(echoPinR, HIGH);

  Serial.println(avgR);

  avgR = 0; //resets the average

  for(int i = 0; i < 3; i++) { //for loop runs 16 times

    smoothR[i] = {smoothR[i + 1]}; //each smooth value is set to the smooth value taken before it.

    avgR = avgR + smoothR[i]; //the average adds up all of these values.

  }

  smoothR[2] = {durationR}; // new value is set

  avgR = (avgR + smoothR[2]) / 3; //final average in calculated

  Serial.println(avgR);

  delay(60); //delay so it won't be too crazy.

  }*/






void setup() {

  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  pinMode(trigPinL, OUTPUT); //trig pin is output
  pinMode(echoPinL, OUTPUT); //echo pin is output
  pinMode(trigPinR, OUTPUT); //trig pin is output
  pinMode(echoPinR, OUTPUT); //echo pin is output

  t = 0;

  /*pinMode(trigPinL, OUTPUT); //trig pin is output
    pinMode(echoPinL, OUTPUT); //echo pin is output
    pinMode(trigPinR, OUTPUT); //trig pin is output
    pinMode(echoPinR, OUTPUT); //echo pin is output*/

}


void loop() {

  //ultraSonicR();
  ultraSonicL();


  driveF();




}
