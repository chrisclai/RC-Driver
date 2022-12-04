/*
* Transmitter Code for RF Moduli Mini (Controller)
* Written by Christopher Lai
* 
* Last Updated: 11/18/2022
* 
* 3x12: Arduino Workshop (CPP Hyperloop)
* The following codebase transmits a packet of information containing data
* such as joystick inputs from the user, potentiometer inputs, and switch
* inputs. The code below is mostly complete, but has missing parts. Determine
* what is missing in order to perform the following tasks with the controller:
* 
* 1) Wirelessly send data to a receiver listening on the same channel (Channel = Team Number)
* 2) Display controller inputs onto the OLED as reading from the analog pins
* 3) Implement a struct to contain data and to use as a reference
* 4) Implement some debug code in order to troubleshoot inputs from the Serial Monitor
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
const uint8_t  channel = __; // [TODO]: Replace this blank with your team number

// Define the digital inputs
#define lBTN 9  // Joystick button 1 defined on pin D9
#define rBTN 10  // Joystick button 2 defined on pin D10
#define switchL 0 // Left Switch defined on pin D0
#define switchR 1 // Right Switch defined on pin D1
#define switchMode 5 // Mode Switch defined on pin D5
#define LJoyX A1 // Left Joystick defined on pin A1
#define LJoyY A0 // Left Joystick defined on pin A0
#define RJoyX A3 // Right Joystick defined on pin A3
#define RJoyY A2 // Right Joystick defined on pin A2
#define LPot A6 // Left Potentiometer defined on pin A6
#define RPot A7 // Right Potentiometer defined on pin A7

// Data structure used to store packet of input information from the controller
struct CMD_Packet {
  byte leftstickx;    // Left Joystick X-Axis
  byte leftsticky;    // Left Joystick Y-Axis
  byte rightstickx;   // Right Joystick X-Axis
  byte rightsticky;   // Right Joystick Y-Axis
  byte btnleft;       // Left Button
  byte btnright;      // Right Button
  byte potleft;       // Left Potentiometer
  byte potright;      // Right Potentiometer
  byte modeSW;        // Mode Switch (Bottom Left Corner)
  byte leftSW;        // Left Switch (Top Left Corner)
  byte rightSW;       // Right Switch (Top Right Corner)
};

// Define the struct as a packet of code
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

  //Set Up Default Controls
  pinMode(lBTN, INPUT_PULLUP);
  pinMode(rBTN, INPUT_PULLUP);
  pinMode(switchL, INPUT_PULLUP);
  pinMode(switchR, INPUT_PULLUP);
  pinMode(switchMode, INPUT_PULLUP);
}

void loop() {

  /* 
   *  [Tips & Hints]
   *  1) List down all the inputs that the user will use for the controller.
   *  2) Determine if the input mechanism provides a binary or analog input into the Arduino.
   *  3) Which function should we use to read from a binary input?
   *  4) Which function should we use to read from an analog input?
  */
  
  // [TODO]: Write code that will read from each input device on the controller
  // and store the value inside the struct
  
  //Gather Left Stick Values
  packet.leftstickx = ___;
  packet.leftsticky = ___;
  
  //Gather Right Stick Values
  packet.rightstickx = ___;
  packet.rightsticky = ___;
  
  // Read all digital inputs
  packet.btnleft = ___;
  packet.btnright = ___;
  packet.modeSW = ___;
  packet.leftSW = ___;
  packet.rightSW = ___;

  // Read potentiometer values and assign them to packet
  packet.potleft = ___;
  packet.potright = ___;

  // Send the whole data from the structure to the receiver
  radio.write(&packet, sizeof(packet));

  // [TODO]: Write some code that will print out the packet information
  // to the serial monitor upon running the code.
  // debug();
  
  /* Debug functions are only used for troubleshooting! Remove this function 
   * (or comment it out) at the end of your work else you will slow down your code!
   */

  // [TODO]: Write some code that will display the packet information
  // to the OLED Display
  OLED_display();
  
  delay(5);
}

void OLED_display()
{
  // [TODO]: You can use the following template or design your own interface!
  display.clearDisplay(); // Blank out the display after every loop so new pixels don't overwrite old ones
  display.setTextSize(2); // Text Size = 2
  display.setTextColor(WHITE); // Doesn't really do anything since the OLEDs already have pre-defined color
  display.setCursor(15,0); // Position Cursor on specific pixel line 
  display.println("CONTROLS"); // Write message to screen
  display.setTextSize(1);
  display.setCursor(0,20);
  display.println("LX: " + ___);
  display.setCursor(0,30);
  display.println("LY: " + ___);
  display.setCursor(0,40);
  display.println("RX: " + ___);
  display.setCursor(0,50);
  display.println("RY: " + ___);
  display.setCursor(64,20);
  display.println("BTN: " + ___ + " | " + ___);
  display.setCursor(64,30);
  display.println("SW: " + ___ + " | " + ___);
  display.setCursor(64,40);
  display.println("POTL: " + ___);
  display.setCursor(64,50);
  display.println("POTR: " + ___);
  display.display(); // Display Message
}

void debug() {
      //THIS IS FOR DEBUG
      Serial.println("Hello World!");
      delay(5);
}
