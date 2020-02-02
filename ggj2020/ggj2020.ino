#include <MaxMatrix.h>
//#include <I2Cdev.h>
//#include <MPU9250.h>

// Inputs
//const int bigButtonPin = -1;
//int bigButtonState = 0;

const int buttonTopRedPin = A3;
const int buttonTopGreenPin = A2;
int buttonTopRedState = LOW;
int buttonTopGreenState = LOW;
int buttonTopRedPrevState = LOW;
int buttonTopGreenPrevState = LOW;
unsigned long buttonTopRedTime = 0;
unsigned long buttonTopGreenTime = 0;

const int buttonSideBluePin = A1;
const int buttonSideGreenPin = A0;
int buttonSideBlueState = LOW;
int buttonSideGreenState = LOW;
int buttonSideBluePrevState = LOW;
int buttonSideGreenPrevState = LOW;
unsigned long buttonSideBlueTime = 0;
unsigned long buttonSideGreenTime = 0;

const int buttonPowerPin = 52;
int buttonPowerState = LOW;
int buttonPowerPrevState = LOW;
unsigned long buttonPowerTime = 0;

/*const int buttonStickPin = -1;
const int axisXPositivePin = -1;
const int axisXNegativePin = -1;
const int axisYPositivePin = -1;
const int axisNegativePin = -1;
int buttonStickState = 0;
int axisXPositiveState = 0;
int axisXNegativeState = 0;
int axisYPositiveState = 0;
int axisYNegativeState = 0;*/
const int xPin = 1;
const int yPin = 2;
const int switchStickPin = 3;
int xState = 0;
int yState = 0;
int switchStickState = 0;
bool hit = false;

const int switch1Pin1 = A4;
const int switch1Pin2 = A5;
const int switch2Pin1 = A6;
const int switch2Pin2 = A7;
const int switch3Pin1 = A8;
const int switch3Pin2 = A9;
const int switch4Pin1 = A10;
const int switch4Pin2 = A11;
int switch1State = 0;
int switch2State = 0;
int switch3State = 0;
int switch4State = 0;

const int switchBigPin1 = DAC0;
const int switchBigPin2 = DAC1;
int switchBigState = 0;
/*
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
*/

// Outputs
const int fanPin = 53;
int fanState = HIGH;

/*
const int heaterPin = -1;
int heaterState = 0;
*/
const int ledsTopDin = 50;
const int ledsTopCs = 48;
const int ledsTopClk = 46;
int ledsMaxInUse = 2;
MaxMatrix ledsTop(ledsTopDin, ledsTopCs, ledsTopClk, ledsMaxInUse); 

const unsigned char ledSignA[] = {4, 8,
            B01111110,
            B00010001,
            B00010001,
            B01111110,
           };

 const unsigned char ledSignSmile[] = {8, 8,
        B00111100,
        B01000010,
        B10010101,
        B10100001,
        B10100001,
        B10010101,
        B01000010,
        B00111100
       };

//const int digitalNumberPin = -1;
//int digitalNumberState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //pinMode(bigButtonPin, INPUT);
  pinMode(buttonTopGreenPin, INPUT_PULLUP);
  pinMode(buttonTopRedPin, INPUT_PULLUP);
  pinMode(buttonSideBluePin, INPUT_PULLUP);
  pinMode(buttonSideGreenPin, INPUT_PULLUP);
  pinMode(buttonPowerPin, INPUT_PULLUP);
  
  /*pinMode(buttonStickPin, INPUT);
  pinMode(axisXPositivePin, INPUT);
  pinMode(axisXNegativePin, INPUT);
  pinMode(axisYPositivePin, INPUT);
  pinMode(axisNegativePin, INPUT);*/
  /*pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(switchStickPin, INPUT);*/

  pinMode(switch1Pin1, INPUT_PULLUP);
  pinMode(switch2Pin1, INPUT_PULLUP);
  pinMode(switch3Pin1, INPUT_PULLUP);
  pinMode(switch4Pin1, INPUT_PULLUP);
  pinMode(switch1Pin2, INPUT_PULLUP);
  pinMode(switch2Pin2, INPUT_PULLUP);
  pinMode(switch3Pin2, INPUT_PULLUP);
  pinMode(switch4Pin2, INPUT_PULLUP);
  pinMode(switchBigPin1, INPUT_PULLUP);
  pinMode(switchBigPin2, INPUT_PULLUP);
  
  /*pinMode(sensorLightPin, INPUT);
  pinMode(sensorSoundPin, INPUT);
  pinMode(sensorMotionPin, INPUT);
  pinMode(heaterPin, INPUT);
  pinMode(ledsTopPin, INPUT);
  pinMode(ledsSidePin, INPUT);
  pinMode(digitalNumberPin, INPUT);*/

  pinMode(fanPin, OUTPUT);

  ledsTop.init(); // MAX7219 initialization
  ledsTop.setIntensity(15);
  //ledsTop.setDot(6,2,true); 
  ledsTop.writeSprite(0, 0, ledSignSmile);
  ledsTop.writeSprite(8, 0, ledSignSmile);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  /*xState = analogRead(xPin);
  yState = analogRead(yPin);
  switchStickState = digitalRead(switchStickPin);

  joystickAxis();
  joystickSwitch();*/

  /*buttonPowerState = digitalRead(buttonPowerPin);

  buttonPower();

  buttonSideGreenState = digitalRead(buttonSideGreenPin);
  buttonSideGreen();

  delay(250);*/
  //Serial.println("Hello");
  //buttonSideGreenState = digitalRead(buttonSideGreenPin);
  //buttonSideGreen();

  //buttonTopRedState = digitalRead(buttonTopRedPin);
  //buttonTopRed();

  buttonPress(buttonTopRedPin, buttonTopRedState, buttonTopRedPrevState, buttonTopRedTime);
  buttonPress(buttonTopGreenPin, buttonTopGreenState, buttonTopGreenPrevState, buttonTopGreenTime);
  buttonPress(buttonSideBluePin, buttonSideBlueState, buttonSideBluePrevState, buttonSideBlueTime);
  buttonPress(buttonSideGreenPin, buttonSideGreenState, buttonSideGreenPrevState, buttonSideGreenTime);
  buttonPress(buttonPowerPin, buttonPowerState, buttonPowerPrevState, buttonPowerTime);

  switchBigState = digitalRead(switchBigPin1) > digitalRead(switchBigPin2) ? LOW : HIGH;
  switch1State = digitalRead(switch1Pin1) > digitalRead(switch1Pin2) ? LOW : HIGH;
  switch2State = digitalRead(switch2Pin1) > digitalRead(switch2Pin2) ? LOW : HIGH;
  switch3State = digitalRead(switch3Pin1) > digitalRead(switch3Pin2) ? LOW : HIGH;
  switch4State = digitalRead(switch4Pin1) > digitalRead(switch4Pin2) ? LOW : HIGH;

  if(buttonTopRedState == HIGH) Serial.println("buttonTopRed press");
  if(buttonTopGreenState == HIGH) Serial.println("buttonTopGreen press");
  if(buttonSideBlueState == HIGH) Serial.println("buttonSideBlue press");
  if(buttonSideGreenState == HIGH) Serial.println("buttonSideGreen press");
  if(buttonPowerState == HIGH) Serial.println("buttonPower press");

  if(switchBigState == HIGH) Serial.println("switchBig toggled");
  if(switch1State == HIGH) Serial.println("switch1 toggled");
  if(switch2State == HIGH) Serial.println("switch2 toggled");
  if(switch3State == HIGH) Serial.println("switch3 toggled");
  if(switch4State == HIGH) Serial.println("switch4 toggled");

  //Serial.println(switch4State);
  //Serial.println("Hello");

    digitalWrite(fanPin, fanState);
}

void buttonPress(int pin, int &state, int &prev, unsigned long &time)
{
    int reading = digitalRead(pin);

    if (reading == HIGH && prev == LOW && millis() - time > 200)
    {
        if (state == HIGH)
        {
            state = LOW;
        }
        else
        {
            state = HIGH;
        }

        time = millis();
    }

    prev = reading;
}

/*void joystickAxis()
{
    // -Y direction
    if (xState >= 0 && yState <= 10)
    {
        Serial.println("X-axis: " + xState);
        Serial.println("Y-axis: " + yState);
    }
    // -X direction
    if (xState <= 10 && yState >= 500)
    {
        Serial.println("X-axis: " + xState);
        Serial.println("Y-axis: " + yState);
    }
    // +X direction
    if (xState >= 1020 && yState >= 500)
    {
        Serial.println("X-axis: " + xState);
        Serial.println("Y-axis: " + yState);
    }
    // +Y direction
    if (xState >= 500 && yState >= 1020)
    {
        Serial.println("X-axis: " + xState);
        Serial.println("Y-axis: " + yState);
    }
}

void joystickSwitch()
{
    if (switchStickState == HIGH)
    {
        if (hit)
        {
            hit = false;
            switchStickState == HIGH;
        }
        else
        {
            hit = true;
            switchStickState == LOW;
        }

        Serial.println("Switch pressed");
    }
}*/

/*void buttonPower()
{
    if (buttonPowerState == HIGH)
    {
        Serial.println("Power button turned on");
    }
    if (buttonPowerState == LOW)
    {
        Serial.println("Power button turned off");
    }
}*/

void buttonSideGreen()
{
    if (buttonSideGreenState == HIGH)
    {
        Serial.println("Side green button turned on");
    }
    if (buttonSideGreenState == LOW)
    {
        Serial.println("Side green button turned off");
    }
}


void buttonTopRed()
{
    if (buttonTopRedState == HIGH)
    {
        Serial.println("Top red button turned on");
    }
    if (buttonTopRedState == LOW)
    {
        Serial.println("Top red button turned off");
    }
}
