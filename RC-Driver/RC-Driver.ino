/*
* Receiver Code for RC Driver (RC Car)
* Written by Christopher Lai
* 
* Last Updated: 11/18/2022
* 
* 3x12: Arduino Workshop (CPP Hyperloop)
* The following codebase utilizes a simple manual control loop in order to receive data
* from the controller (RF Moduli Mini) as an input, and control the car's motors as an output.
* The code below is mostly complete, but has some missing parts. Determine what is missing in
* order to successfully drive your vehicle.
* 
* --- Task Log ---
* 1) Receive a packet of controller data from the transmitter (Channel = Team Number)
* 2) Write down a plan of how you want the RC Car to drive depending on your controls
* 3) Write output signals to the motor drivers in order to calibrate the RC car motion
* 4) Write functions to drive the RC car in 4 directions (Forward, Backward, Rotate Left, Rotate Right)
* 5) Use conditional statements to drive the RC car (using functions) when the controller packet has a certain value
* 
* Upon completing the tasks listed above, you will notice that the RC Car drives well, but there are
* a few flaws. Here are some optimization/integration ideas to improve the RC Car (You may choose
* to implement your own!) [Hint: The easier it is for your car to drive/make turns, the faster you will
* be able to complete the race!]
* 
* --- RC Car Optimization ---
* 1) What happens if the RC Car loses communication with the controller? Implement a failsafe to prevent disasters (UGV)
* 2) Implement a motor speed PWM control system to allow the car to drift around corners (Agility++)
* 3) Use the potentiometer inputs to modify speed using PWM
* 4) Use the switch inputs to create a state machine to allow the RC Car to drive using user-defined modes
* 5) Creaet precise pre-defined actions for the RC Car and have it be activated by button presses / switch presses
* 6) And more! Be creative!
* 
* Fun Fact (from Harris): Many high schools participate in FRC, and this is very similar to that competition.
* The solution to winning racecar competitions is driver practice!
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00501";
const uint8_t  channel = ___; // [TODO]: Replace this blank with your team number

// Pin Definitions
#define in1L 0  // Left L298N, Pin IN1
#define in2L 1  // Left L298N, Pin IN2
#define in3L 2  // Left L298N, Pin IN3
#define in4L 3  // Left L298N, Pin IN4
#define in1R 4  // Right L298N, Pin IN1
#define in2R 5  // Right L298N, Pin IN2
#define in3R 6  // Right L298N, Pin IN3
#define in4R 9  // Right L298N, Pin IN4
#define en 10   // Both L298N, Pin ENA/B

// Max size 32 bytes because of buffer limit
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
  // Set Up Serial Comms - Debug
  Serial.begin(9600);

  // [TODO]: Set up GPIO Pins (OUTPUT or INPUT?)
  pinMode(in1L, ___);
  pinMode(in2L, ___);
  pinMode(in3L, ___);
  pinMode(in4L, ___);
  pinMode(in1R, ___);
  pinMode(in2R, ___);
  pinMode(in3R, ___);
  pinMode(in4R, ___);
  pinMode(en, ___);


  // Set up default state (On startup, none of the motors should be on!)
  digitalWrite(in1L, LOW);
  digitalWrite(in2L, LOW);
  digitalWrite(in3L, LOW);
  digitalWrite(in4L, LOW);
  digitalWrite(in1R, LOW);
  digitalWrite(in2R, LOW);
  digitalWrite(in3R, LOW);
  digitalWrite(in4R, LOW);

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
  
  /* 
   *  [Tips & Hints]
   *  1) List down all the outputs that must be sent from the Arduino to power the motors.
   *  2) Write a motor calibration function that tests for the direction in which each motor turns.
   *  2.5) What kind of signals does the L298 motor driver accept in order to drive the motors? (Digital or Analog?)
   *  3) Where is the controller data stored within the RC car after the RF transciever code is complete?
   *  4) How should we use the controller data numerically to provide conditions on the car to drive it
   *  forward, backward, have rotations, drift around corners, etc?
  */
  
  if (radio.available()) {
    radio.read(&packet, sizeof(packet));

    // Used to test the motor orientation (calibration)
    // motor_test();

    // [TODO]: Replace this series of conditional statements to use the
    // commands from the packet to drive the RC Car. For example, which
    // control should drive the racecar forward?
    if (___) {
      forward();
    }
    else if (___) {
      backward();
    }
    else if (___) {
      rotate_CW();
    }
    else if (___) {
      rotate_CCW();
    }
    else {
      stopnow();
    }

    // [TODO]: Implement extra functionalities for the RC Car. What methods
    // or operations can you use to make the car more agile? What about stability?
    // Can you modify the speed using PWM (on the enable pins) in order to make the
    // RC car go faster or slower through turns?

    delay(5);
  }
  else{
    resetCMD();
    delay(5); 
  }
}

// [TODO]: Implement a function that will make the car drive forward
void forward() {
  
}

// [TODO]: Implement a function that will make the car drive backward
void backward() {
  
}

// [TODO]: Implement a function that will make the car rotate clockwise
void rotate_CW() {
  
}

// [TODO]: Implement a function that will make the car rotate counterclockwise
void rotate_CCW() {
  
}

// [TODO]: Implement extra functions here to optimize car driving

// [TODO]: Implement a function that will stop the car
void stopnow() {
  
}

// [TODO]: Implement a function that will test the motors for orientation.
// This is primarily a troubleshooting function and will not be used in the end product
void motor_test() {
  
}

// [TODO]: Implement a function that will reset the packet of information to default values
// if the controller were to ever lose connection with the RC Car mid-travel (Failsafe)
void resetCMD() {
  
}
