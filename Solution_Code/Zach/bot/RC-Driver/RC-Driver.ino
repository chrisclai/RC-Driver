/*
* Receiver Code for RC Driver
* Written by Christopher Lai
* For loklokfafa
* 
* Last Updated: 11/25/2022 -
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00501";
const uint8_t  channel = 169;

// Pin Definitions
// edited 11/25/2022 - zach
// changed to const int for easy usage in parameters
// which ended up being pointless anyways because i have to create
// my own motor object thanks to how L298's handle polarity
const int in1L = 0;
const int in2L = 1;
const int in3L = 2;
const int in4L = A0;
const int in1R = 4;
const int in2R = A1;
const int in3R = A2;
const int in4R = A3;

//added 11/25/2022 - zach
//the hard way, you could easily get away with running speed control channels A & B for each side through one signal
//it would free up two analog ports for other activities, but this is more "correct". 
#define en_L 3
#define en_R 5


bool conn = false;

// Max size 32 bytes because of buffer limit
struct CMD_Packet {
  //edited 11/25/2022 - zach
  //passing ints because i was too lazy to do mapping on hte bot code
  int leftstickx;
  int leftsticky;
  int rightstickx;
  int rightsticky;
  byte btnleft;
  byte btnright;
  byte potleft;
  byte potright;
  byte modeSW;
  byte leftSW;
  byte rightSW;
};

//added 11/25/2022 - zach
//LA CREATURA~!!!
class Motor{ //i hate you L298 i hate you i hate you i hateyou
  private:
    //inheret pins
    int en; //analog
    int fwd;
    int rev;

  public:
    void kill(){
      analogWrite(en, 0);
    }

    Motor(int en_, int fwd_, int rev_){ //constructor

      en = en_;
      fwd = fwd_;
      rev = rev_;
      pinMode(en, OUTPUT);
      pinMode(fwd, OUTPUT);
      pinMode(rev, OUTPUT);

      kill();
    }

    void set(int speed){

      analogWrite(en, abs(speed));
      // Serial.print("ESC at ");
      // Serial.print(en);
      // Serial.print(" outputting ");
      // Serial.println(speed);
      
      if(speed < 0){ //this is why i hate L298's. what is the fuckin 70's with this pin polarity madge
        digitalWrite(fwd, LOW);
        digitalWrite(rev, HIGH);
      }
      else{
        digitalWrite(fwd, HIGH);
        digitalWrite(rev, LOW);
      }
    }
};

CMD_Packet packet;
//added 11/25/2022 - zach
//OOP users shaking my smh
Motor fL(en_L, in1L, in2L);
Motor rL(en_L, in3L, in4L);
Motor fR(en_R, in1R, in2R);
Motor rR(en_R, in3R, in4R);  

void setup() {
  // Set Up Serial Comms - Debug
  //Serial.begin(9600); //comment out on live

  // Set up Radio
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW,0);
  radio.setChannel(channel);
  radio.startListening();

}

void loop() {  
  if (radio.available()) {
    conn = true;
    radio.read(&packet, sizeof(packet));

    //added 11/25/2022 - zach
    //control mixing algo
    // -> make one of the switches switch between tank/arcade?
    // -> or rather one-stick/two-stick arcade. tank drive users are ontologically evil
    fL.set(packet.leftsticky + packet.rightstickx);
    fR.set(packet.leftsticky - packet.rightstickx);
    rL.set(packet.leftsticky + packet.rightstickx);
    rR.set(packet.leftsticky - packet.rightstickx);

  }
  else{

    //edited 11/25/2022 - zach
    // delay(5);
    //failsafe


  }
}

//deleted unused functions 11/25/2022 - zach