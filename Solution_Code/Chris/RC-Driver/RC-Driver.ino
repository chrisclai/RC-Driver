/*
* Receiver Code for RC Driver
* Written by Christopher Lai
* For loklokfafa
* 
* Last Updated: 11/16/2022
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00501";
const uint8_t  channel = 102;

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

bool conn = false;

// Max size 32 bytes because of buffer limit
struct CMD_Packet {
  byte leftstickx;
  byte leftsticky;
  byte rightstickx;
  byte rightsticky;
  byte btnleft;
  byte btnright;
  byte potleft;
  byte potright;
  byte modeSW;
  byte leftSW;
  byte rightSW;
};

CMD_Packet packet;

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

  // Set up default state
  stop();

  // Set up Radio
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW,0);
  radio.setChannel(channel);
  Serial.println("Starting Radio"); 

  //to recieve
  radio.startListening();
}

void loop() {  
  if (radio.available()) {
    conn = true;
    radio.read(&packet, sizeof(packet));
    delay(50);

    if (packet.leftsticky > 175) {
      forward();
    }
    else if (packet.leftsticky < 100) {
      backward();
    }
    else if (packet.rightstickx > 175 && packet.rightsticky > 175) {
      drift_right_fw();
    }
    else if (packet.rightstickx < 100 && packet.rightsticky > 175) {
      drift_left_fw();
    }
    else if (packet.rightstickx < 100 && packet.rightsticky < 100) {
      drift_left_bw();
    }
    else if (packet.rightstickx > 175 && packet.rightsticky < 100) {
      drift_right_bw();
    }
    else if (packet.leftstickx > 175) {
      rotate_CW();
    }
    else if (packet.leftstickx < 100) {
      rotate_CCW();
    }
    else {
      stop();
    }

  }
  else{
    // delay(5); 
  }
}

void forward() {
  digitalWrite(in1L, LOW);
  digitalWrite(in2L, HIGH);
  digitalWrite(in3L, LOW);
  digitalWrite(in4L, HIGH);
  digitalWrite(in1R, LOW);
  digitalWrite(in2R, HIGH);
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
  digitalWrite(in3R, HIGH);
  digitalWrite(in4R, LOW);
}

void rotate_CCW() {
  digitalWrite(in1L, HIGH);
  digitalWrite(in2L, LOW);
  digitalWrite(in3L, HIGH);
  digitalWrite(in4L, LOW);
  digitalWrite(in1R, LOW);
  digitalWrite(in2R, HIGH);
  digitalWrite(in3R, LOW);
  digitalWrite(in4R, HIGH);
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

void motor_test() {
  if (packet.leftstickx > 175) {
      digitalWrite(in1L, LOW);
      digitalWrite(in2L, HIGH);
    }
    else if (packet.leftstickx < 75) {
      digitalWrite(in1L, HIGH);
      digitalWrite(in2L, LOW);
    }
    else
    {
      digitalWrite(in1L, LOW);
      digitalWrite(in2L, LOW);
    }

    if (packet.leftsticky > 175) {
      digitalWrite(in3L, LOW);
      digitalWrite(in4L, HIGH);
    }
    else if (packet.leftsticky < 75) {
      digitalWrite(in3L, HIGH);
      digitalWrite(in4L, LOW);
    }
    else
    {
      digitalWrite(in3L, LOW);
      digitalWrite(in4L, LOW);
    }

    if (packet.rightstickx > 175) {
      digitalWrite(in1R, LOW);
      digitalWrite(in2R, HIGH);
    }
    else if (packet.rightstickx < 75) {
      digitalWrite(in1R, HIGH);
      digitalWrite(in2R, LOW);
    }
    else
    {
      digitalWrite(in1R, LOW);
      digitalWrite(in2R, LOW);
    }

    if (packet.rightsticky > 175) {
      digitalWrite(in3R, LOW);
      digitalWrite(in4R, HIGH);
    }
    else if (packet.rightsticky < 75) {
      digitalWrite(in3R, HIGH);
      digitalWrite(in4R, LOW);
    }
    else
    {
      digitalWrite(in3R, LOW);
      digitalWrite(in4R, LOW);
    }
}

void resetCMD() {
  packet.leftstickx=127;
  packet.leftsticky=127;
  packet.rightstickx=127;
  packet.rightsticky=127;
  packet.btnleft=1;
  packet.btnright=1;
  packet.potleft=0;
  packet.potright=0;
  packet.modeSW=1;
  packet.leftSW=1;
  packet.rightSW=1;
}
