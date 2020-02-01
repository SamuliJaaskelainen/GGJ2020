#include <MaxMatrix.h>
#include <I2Cdev.h>
#include <MPU9250.h>

// Inputs
const int bigButtonPin = -1;
int bigButtonState = 0;

const int buttonTopGreenPin = -1;
const int buttonTopRedPin = -1;
int buttonTopGreenState = 0;
int buttonTopRedState = 0;

const int buttonSideBluePin = -1;
const int buttonSideRedPin = -1;
int buttonSideBlueState = 0;
int buttonSideRedState = 0;

const int buttonPowerPin = -1;
int buttonPowerState = 0;

const int buttonStickPin = -1;
const int axisXPositivePin = -1;
const int axisXNegativePin = -1;
const int axisYPositivePin = -1;
const int axisNegativePin = -1;
int buttonStickState = 0;
int axisXPositiveState = 0;
int axisXNegativeState = 0;
int axisYPositiveState = 0;
int axisYNegativeState = 0;

const int switch1Pin = -1;
const int switch2Pin = -1;
const int switch3Pin = -1;
const int switch4Pin = -1;
int switch1State = 0;
int switch2State = 0;
int switch3State = 0;
int switch4State = 0;

const int switchBigPin = -1;
int switchBigState = 0;

const int sensorLightPin = -1;
int sensorLightState = 0;

const int sensorSoundPin = -1;
int sensorSoundState = 0;

const int sensorMotionPin = -1;
int sensorMotionGyroStateX = 0;
int sensorMotionGyroStateY = 0;
int sensorMotionGyroStateZ = 0;
int sensorMotionAccStateX = 0;
int sensorMotionAccStateY = 0;
int sensorMotionAccStateZ = 0;
int sensorMotionMagStateX = 0;
int sensorMotionMagStateY = 0;
int sensorMotionMagStateZ = 0;

// Outputs
const int fanPin = -1;
int fanState = 0;

const int heaterPin = -1;
int heaterState = 0;

const int ledsTopPin = -1;
int ledsTopState = 0;

const int ledsSidePin = -1;
int ledsSideState = 0;

const int digitalNumberPin = -1;
int digitalNumberState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(bigButtonPin, INPUT);
  pinMode(buttonTopGreenPin, INPUT);
  pinMode(buttonTopRedPin, INPUT);
  pinMode(buttonSideBluePin, INPUT);
  pinMode(buttonSideRedPin, INPUT);
  pinMode(buttonPowerPin, INPUT);
  pinMode(buttonStickPin, INPUT);
  pinMode(axisXPositivePin, INPUT);
  pinMode(axisXNegativePin, INPUT);
  pinMode(axisYPositivePin, INPUT);
  pinMode(axisNegativePin, INPUT);
  pinMode(switch1Pin, INPUT);
  pinMode(switch2Pin, INPUT);
  pinMode(switch3Pin, INPUT);
  pinMode(switch4Pin, INPUT);
  pinMode(switchBigPin, INPUT);
  pinMode(sensorLightPin, INPUT);
  pinMode(sensorSoundPin, INPUT);
  pinMode(sensorMotionPin, INPUT);
  pinMode(fanPin, INPUT);
  pinMode(heaterPin, INPUT);
  pinMode(ledsTopPin, INPUT);
  pinMode(ledsSidePin, INPUT);
  pinMode(digitalNumberPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Hellou");

  delay(250);
}
