#include <SoftwareSerial.h>
#define analog_i A0
#define digital_i 9 //D9 pin
#define rxPin 6
#define txPin 7

//Setting up Global Variables
//Control Variables
int cnt = 0;
const int check = 100;
int mx_noise = 0;
const int buf_noise = 7;
//Constant Variable to signal to send data
int Signal=0;
int timer=0;

// Set up a new SoftwareSerial object
SoftwareSerial mySerial =SoftwareSerial(rxPin, txPin);

void setup() {
  //Setting up the pin for Software Serial 
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(digital_i, INPUT);   // Set the sensorPin as an input pin
  Serial.begin(9600);
  //Message to indicate start of Serial Monitor
  Serial.println("Testing Software Serial Monitor");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
}
void loop() 
  { 
  int val_i = analogRead(analog_i);
  int val2_i = digitalRead(digital_i);
  if(val_i){
    if (cnt<check){
      if (val_i>mx_noise){
        mx_noise = val_i;
      }
      Serial.print("Calibrating.... \n");
      cnt++;
    }
    else{
      if(val2_i){
      Serial.println("Detect Vibration");
      if (val_i > mx_noise+buf_noise )
      {
        Serial.println(val_i);
        mySerial.write("ON\n");
      }
      }
    }
  }
}