/*
* Transmitter Code for RF Moduli Mini
* Written by Christopher Lai
* For loklokfafa
* 
* Last Updated: 11/14/2022
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00501";
const uint8_t  channel = 102;

int lowmap = 10;
int highmap = 250;

// Define the digital inputs
#define lBTN 9  // Joystick button 1
#define rBTN 10  // Joystick button 2
#define switchL 0 // Left Switch
#define switchR 1 // Right Switch
#define switchMode 5 // Mode Switch

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

//Make command packet
CMD_Packet packet;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW,0);
  radio.setChannel(channel);
  radio.stopListening();
  Serial.println("Sending");

  // Check for OLED Availability
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("LOADING...");
  display.setCursor(0, 20);
  display.println("Setting Up");
  display.setCursor(0, 40);
  display.println("RF Moduli");
  display.display(); 
  delay(2500);
  
  //Set Up Controls
  pinMode(lBTN, INPUT_PULLUP);
  pinMode(rBTN, INPUT_PULLUP);
  pinMode(switchL, INPUT_PULLUP);
  pinMode(switchR, INPUT_PULLUP);
  pinMode(switchMode, INPUT_PULLUP);
}

void loop() {
  
  // Read all analog inputs and map them to one Byte value
  //Gather Left Stick Values
  packet.leftstickx = map(analogRead(A1),0,1023,lowmap,highmap);
  packet.leftsticky = map(analogRead(A0),0,1023,highmap,lowmap);
  
  //Gather Right Stick Values
  packet.rightstickx = map(analogRead(A3),0,1023,lowmap,highmap);
  packet.rightsticky = map(analogRead(A2),0,1023,highmap,lowmap);
  
  // Read all digital inputs
  packet.btnleft = digitalRead(lBTN);
  packet.btnright = digitalRead(rBTN);
  packet.modeSW = digitalRead(switchMode);
  packet.leftSW = digitalRead(switchL);
  packet.rightSW = digitalRead(switchR);

  // Read potentiometer values and assign them to packet
  packet.potleft = map(analogRead(A6),0,1023,highmap,lowmap);
  packet.potright = map(analogRead(A7),0,1023,highmap,lowmap);

  // Send the whole data from the structure to the receiver
  radio.write(&packet, sizeof(packet));

  // debug();
  OLED_display();
  
  delay(5);
}

void OLED_display()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(15,0);
  display.println("CONTROLS");
  display.setTextSize(1);
  display.setCursor(0,20);
  display.println("LX: " + String(packet.leftstickx));
  display.setCursor(0,30);
  display.println("LY: " + String(packet.leftsticky));
  display.setCursor(0,40);
  display.println("RX: " + String(packet.rightstickx));
  display.setCursor(0,50);
  display.println("RY: " + String(packet.rightsticky));
  display.setCursor(64,20);
  display.println("BTN: " + String(packet.btnleft) + " | " + String(packet.btnright));
  display.setCursor(64,30);
  display.println("SW: " + String(packet.leftSW) + " | " + String(packet.rightSW));
  display.setCursor(64,40);
  display.println("POTL: " + String(packet.potleft));
  display.setCursor(64,50);
  display.println("POTR: " + String(packet.potright));
  display.display();
}

void debug() {
      //THIS IS FOR DEBUG
      delay(5);
}
