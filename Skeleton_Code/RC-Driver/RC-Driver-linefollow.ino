/*
* Receiver Code for RC Driver - Line Follower Edition
* Written by Christopher Lai
* For loklokfafa
* 
* Last Updated: 11/16/2022
*/

// Pin Definitions
#define in1L 0
#define in2L 1
#define in3L 2
#define in4L 3
#define in1R 4
#define in2R 5
#define in3R 6
#define in4R 9
#define en 10

#define trig A0
#define echo A1
#define IR1 A2
#define IR2 A3

long duration;
double distance;
int ir1_data;
int ir2_data;



void setup() {
  // Set Up Serial Comms - Debug
  Serial.begin(9600);

  // Set up GPIO Pins
  pinMode(in1L, OUTPUT);
  pinMode(in2L, OUTPUT);
  pinMode(in3L, OUTPUT);
  pinMode(in4L, OUTPUT);
  pinMode(in1R, OUTPUT);
  pinMode(in2R, OUTPUT);
  pinMode(in3R, OUTPUT);
  pinMode(in4R, OUTPUT);

  // Set up sensors
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  // Set up default state
  stop();
}

void loop() 
{ 
  
  //put line following logic here!
  // digital reads? when should you go forward()?

}


double getDistance()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2; // 0.034 constant from speed of sound
  Serial.println(distance);
  return distance;
}

void forward() {
  digitalWrite(in1L, HIGH);
  digitalWrite(in2L, LOW);
  digitalWrite(in3L, HIGH);
  digitalWrite(in4L, LOW);
  digitalWrite(in1R, HIGH);
  digitalWrite(in2R, LOW);
  digitalWrite(in3R, LOW);
  digitalWrite(in4R, HIGH);
}

void backward() {
  digitalWrite(in1L, HIGH);
  digitalWrite(in2L, LOW);
  digitalWrite(in3L, HIGH);
  digitalWrite(in4L, LOW);
  digitalWrite(in1R, HIGH);
  digitalWrite(in2R, LOW);
  digitalWrite(in3R, HIGH);
  digitalWrite(in4R, LOW);
}

void rotate_CW() {
  digitalWrite(in1L, LOW);
  digitalWrite(in2L, HIGH);
  digitalWrite(in3L, LOW);
  digitalWrite(in4L, HIGH);
  digitalWrite(in1R, HIGH);
  digitalWrite(in2R, LOW);
  digitalWrite(in3R, LOW);
  digitalWrite(in4R, HIGH);
}

void rotate_CCW() {
  digitalWrite(in1L, HIGH);
  digitalWrite(in2L, LOW);
  digitalWrite(in3L, HIGH);
  digitalWrite(in4L, LOW);
  digitalWrite(in1R, LOW);
  digitalWrite(in2R, HIGH);
  digitalWrite(in3R, HIGH);
  digitalWrite(in4R, LOW);
}

void drift_right_fw() {
  digitalWrite(in1L, LOW);
  digitalWrite(in2L, HIGH);
  digitalWrite(in3L, LOW);
  digitalWrite(in4L, HIGH);
  digitalWrite(in1R, LOW);
  digitalWrite(in2R, LOW);
  digitalWrite(in3R, LOW);
  digitalWrite(in4R, LOW);
}

void drift_left_fw() {
  digitalWrite(in1L, LOW);
  digitalWrite(in2L, LOW);
  digitalWrite(in3L, LOW);
  digitalWrite(in4L, LOW);
  digitalWrite(in1R, LOW);
  digitalWrite(in2R, HIGH);
  digitalWrite(in3R, LOW);
  digitalWrite(in4R, HIGH);
}

void drift_right_bw() {
  digitalWrite(in1L, HIGH);
  digitalWrite(in2L, LOW);
  digitalWrite(in3L, HIGH);
  digitalWrite(in4L, LOW);
  digitalWrite(in1R, LOW);
  digitalWrite(in2R, LOW);
  digitalWrite(in3R, LOW);
  digitalWrite(in4R, LOW);
}

void drift_left_bw() {
  digitalWrite(in1L, LOW);
  digitalWrite(in2L, LOW);
  digitalWrite(in3L, LOW);
  digitalWrite(in4L, LOW);
  digitalWrite(in1R, HIGH);
  digitalWrite(in2R, LOW);
  digitalWrite(in3R, HIGH);
  digitalWrite(in4R, LOW);
}

void stop() {
  digitalWrite(in1L, LOW);
  digitalWrite(in2L, LOW);
  digitalWrite(in3L, LOW);
  digitalWrite(in4L, LOW);
  digitalWrite(in1R, LOW);
  digitalWrite(in2R, LOW);
  digitalWrite(in3R, LOW);
  digitalWrite(in4R, LOW);
}
