#include <MaxMatrix.h>


// Inputs

const int buttonTopRedPin = A3;
const int buttonTopGreenPin = A2;
int buttonTopRedState = LOW;
int buttonTopGreenState = LOW;
int buttonTopRedPrevState = LOW;
int buttonTopGreenPrevState = LOW;
unsigned long buttonTopRedTime = 0;
unsigned long buttonTopGreenTime = 0;
bool buttonTopRedPressed;
bool buttonTopRedPressedPrev;

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
bool powerButtonPressed;
bool powerButtonPressedPrev;

const int xPin = 1;
const int yPin = 2;
const int switchStickPin = 3;
int xState = 0;
int yState = 0;
int switchStickState = 0;
bool hit = false;
bool victory = false;

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
bool switchBigPressed;
bool switchBigPressedPrev;

// Outputs

const int fanPin = 53;
int fanState = HIGH;

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

const unsigned char ledSignAll[] = {8, 8,
                                    B11111111,
                                    B11111111,
                                    B11111111,
                                    B11111111,
                                    B11111111,
                                    B11111111,
                                    B11111111,
                                    B11111111
                                   };


const unsigned char ledSignNone[] = {8, 8,
                                     B00000000,
                                     B00000000,
                                     B00000000,
                                     B00000000,
                                     B00000000,
                                     B00000000,
                                     B00000000,
                                     B00000000,
                                    };

const unsigned char ledSignSectionedFilled[] = {4, 4,
                                                B11111,
                                                B11111,
                                                B11111,
                                                B11111
                                               };

const unsigned char ledSignSectioned[] = {4, 4,
                                          B1111,
                                          B1001,
                                          B1001,
                                          B1111
                                         };

const unsigned char ledSignCircle1[] = {8, 8,
                                        B00000000,
                                        B00000000,
                                        B00000000,
                                        B00011000,
                                        B00011000,
                                        B00000000,
                                        B00000000,
                                        B00000000
                                       };

const unsigned char ledSignCircle2[] = {8, 8,
                                        B00000000,
                                        B00000000,
                                        B00011000,
                                        B00111100,
                                        B00111100,
                                        B00011000,
                                        B00000000,
                                        B00000000
                                       };

const unsigned char ledSignCircle3[] = {8, 8,
                                        B00000000,
                                        B00011000,
                                        B00111100,
                                        B01111110,
                                        B01111110,
                                        B00111100,
                                        B00011000,
                                        B00000000
                                       };

const unsigned char ledSignCircle4[] = {8, 8,
                                        B00011000,
                                        B00111100,
                                        B01111110,
                                        B11111111,
                                        B11111111,
                                        B01111110,
                                        B00111100,
                                        B00011000
                                       };

const unsigned char ledSignFireworks1[] = {8, 8,
                                           B00000000,
                                           B00000000,
                                           B00000000,
                                           B00011000,
                                           B00011000,
                                           B00000000,
                                           B00000000,
                                           B00000000
                                          };

const unsigned char ledSignFireworks2[] = {8, 8,
                                           B00000000,
                                           B00000000,
                                           B00100100,
                                           B00011000,
                                           B00011000,
                                           B00100100,
                                           B00000000,
                                           B00000000
                                          };

const unsigned char ledSignFireworks3[] = {8, 8,
                                           B00000000,
                                           B01000010,
                                           B00100100,
                                           B00000000,
                                           B00000000,
                                           B00100100,
                                           B01000010,
                                           B00000000
                                          };

const unsigned char ledSignFireworks4[] = {8, 8,
                                           B10000001,
                                           B01000010,
                                           B00000000,
                                           B00100100,
                                           B01000010,
                                           B00000000,
                                           B01000010,
                                           B10000001
                                          };

const unsigned char ledSignFireworks5[] = {8, 8,
                                           B10000001,
                                           B00000000,
                                           B01000010,
                                           B00000000,
                                           B01000010,
                                           B10000001,
                                           B00000000,
                                           B10000001
                                          };

// Puzzle logic

// -1: None
// 0: Normal
// 1: Fan
// 2: Side dp
// 3: Top dp
// 4: Brains
int operationState = 0;

int sideDpBootIndex;
bool sideDpOk;
bool topDpOk;
bool powerOn;
int powerIndex;
int bootFrames;
int victoryFrames;
int victoryTimer;

void setup()
{
  Serial.begin(9600);

  //pinMode(bigButtonPin, INPUT);
  pinMode(buttonTopGreenPin, INPUT_PULLUP);
  pinMode(buttonTopRedPin, INPUT_PULLUP);
  pinMode(buttonSideBluePin, INPUT_PULLUP);
  pinMode(buttonSideGreenPin, INPUT_PULLUP);
  pinMode(buttonPowerPin, INPUT_PULLUP);

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

  pinMode(fanPin, OUTPUT);

  ledsTop.init();
  ledsTop.setIntensity(15);
  ledsTop.writeSprite(0, 0, ledSignAll);
  ledsTop.writeSprite(8, 0, ledSignAll);
  delay(1000);
  resetAll();
}

void loop()
{
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

  /*
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
  */

  digitalWrite(fanPin, fanState);

  if (switch1State == LOW && switch2State == LOW && switch3State == LOW && switch4State == LOW) operationState = 0;
  else if (switch1State == HIGH && switch2State == LOW && switch3State == HIGH && switch4State == LOW) operationState = 1;
  else if (switch1State == HIGH && switch2State == LOW && switch3State == LOW && switch4State == HIGH) operationState = 2;
  else if (switch1State == LOW && switch2State == HIGH && switch3State == HIGH && switch4State == LOW) operationState = 3;
  else if (switch1State == HIGH && switch2State == HIGH && switch3State == HIGH && switch4State == HIGH) operationState = 4;
  else operationState = -1;

  if (buttonPowerState == HIGH != powerButtonPressedPrev)
  {
    powerButtonPressed = true;
    powerButtonPressedPrev = buttonPowerState == HIGH;
  }
  else
  {
    powerButtonPressed = false;
  }

  if (buttonTopRedState == HIGH != buttonTopRedPressedPrev)
  {
    buttonTopRedPressed = true;
    buttonTopRedPressedPrev = buttonTopRedState == HIGH;
  }
  else
  {
    buttonTopRedPressed = false;
  }

  if (switchBigState == HIGH != switchBigPressedPrev)
  {
    switchBigPressed = true;
    switchBigPressedPrev = switchBigState == HIGH;
  }
  else
  {
    switchBigPressed = false;
  }

  if (victory)
  {
    if (victoryTimer > 100)
    {
      victoryTimer = 0;
      victoryFrames++;
      if (victoryFrames > 4) victoryFrames = 0;
    }
    victoryTimer++;

    if (victoryFrames == 0)
    {
      ledsTop.writeSprite(0, 0, ledSignFireworks1);
      ledsTop.writeSprite(8, 0, ledSignFireworks1);
    }
    else if (victoryFrames == 1)
    {
      ledsTop.writeSprite(0, 0, ledSignFireworks2);
      ledsTop.writeSprite(8, 0, ledSignFireworks2);
    }
    else if (victoryFrames == 2)
    {
      ledsTop.writeSprite(0, 0, ledSignFireworks3);
      ledsTop.writeSprite(8, 0, ledSignFireworks3);
    }
    else if (victoryFrames == 3)
    {
      ledsTop.writeSprite(0, 0, ledSignFireworks4);
      ledsTop.writeSprite(8, 0, ledSignFireworks4);
    }
    else if (victoryFrames == 4)
    {
      ledsTop.writeSprite(0, 0, ledSignFireworks5);
      ledsTop.writeSprite(8, 0, ledSignFireworks5);
    }

    if (powerButtonPressed)
    {
      resetAll();
    }

    return;
  }

  switch (operationState)
  {
    case 0:
      if (powerButtonPressed)
      {
        resetAll();
      }
      break;

    case 1:
      if (buttonSideGreenState == HIGH)
      {
        fanState = switchBigState;
      }
      else
      {
        topDpOk = LOW;
        ledsTop.writeSprite(0, 0, ledSignNone);
        ledsTop.writeSprite(8, 0, ledSignNone);
      }
      break;

    case 2:
      if (buttonTopGreenState == HIGH && fanState == HIGH)
      {
        if (buttonTopRedPressed)
        {
          Serial.println("Side dp boot pressed");
          sideDpBootIndex++;

          if (sideDpBootIndex > 10) sideDpBootIndex = 0;
        }

        if (sideDpBootIndex >= 6 && sideDpBootIndex < 8)
        {
          Serial.println("Dp ok!");
          sideDpOk = true;
          ledsTop.writeSprite(0, 0, ledSignAll);
        }
        else
        {
          ledsTop.writeSprite(0, 0, ledSignNone);
          ledsTop.writeSprite(8, 0, ledSignNone);
          sideDpOk = false;
        }
      }
      else
      {
        sideDpBootIndex = 0;
      }
      break;

    case 3:

      if (sideDpOk)
      {
        ledsTop.writeSprite(0, 0, buttonTopRedState == HIGH ? ledSignSectionedFilled : ledSignSectioned);
        ledsTop.writeSprite(4, 0, buttonTopGreenState == HIGH ? ledSignSectionedFilled : ledSignSectioned);
        ledsTop.writeSprite(0, 4, buttonSideGreenState == HIGH ? ledSignSectionedFilled : ledSignSectioned);
        ledsTop.writeSprite(4, 4, buttonSideBlueState == HIGH ? ledSignSectionedFilled : ledSignSectioned);

        if (buttonTopRedState == HIGH && buttonTopGreenState == HIGH && buttonSideGreenState == HIGH && buttonSideBlueState == HIGH)
        {
          ledsTop.writeSprite(8, 0, ledSignAll);
          topDpOk = true;
        }
        else
        {
          ledsTop.writeSprite(8, 0, ledSignNone);
          topDpOk = false;
        }
      }

      break;

    case 4:
      if (!topDpOk)
        return;

      if (buttonTopGreenState == HIGH)
      {
        if (switchBigPressed)
        {
          Serial.println("Power increase");
          powerIndex++;
        }

        for (int i = 0; i < 8; ++i)
        {
          for (int j = 0; j < 8; ++j)
          {
            ledsTop.setDot(i, j, i <= powerIndex);
          }
        }

        if (powerIndex >= 8) powerIndex = 0;
        powerOn = powerIndex == 7;
      }

      if (powerOn)
      {
        if (buttonTopRedPressed) bootFrames++;
        if (bootFrames > 3) bootFrames = 0;

        if (bootFrames == 0) ledsTop.writeSprite(8, 0, ledSignCircle1);
        if (bootFrames == 1) ledsTop.writeSprite(8, 0, ledSignCircle2);
        if (bootFrames == 2) ledsTop.writeSprite(8, 0, ledSignCircle3);
        if (bootFrames == 3) ledsTop.writeSprite(8, 0, ledSignCircle4);

        if (bootFrames == 3 && buttonSideBlueState == LOW && buttonSideGreenState == LOW)
        {
          victory = true;
          return;
        }
      }
      else
      {
        ledsTop.writeSprite(8, 0, ledSignNone);
      }

      break;

    default:
      ledsTop.writeSprite(0, 0, ledSignNone);
      ledsTop.writeSprite(8, 0, ledSignNone);
      powerOn = false;
      powerIndex = 0;
      sideDpBootIndex = 0;
      bootFrames = 0;

      if (fanState == LOW)
      {
        sideDpOk = false;
      }

      if (!sideDpOk)
      {
        topDpOk = false;
      }

      if (sideDpOk)
      {
        ledsTop.writeSprite(0, 0, ledSignAll);
      }

      if (topDpOk)
      {
        ledsTop.writeSprite(8, 0, ledSignAll);
      }

      break;
  }
}

void resetAll()
{
  Serial.println("Reset all");
  fanState = LOW;
  ledsTop.writeSprite(0, 0, ledSignNone);
  ledsTop.writeSprite(8, 0, ledSignNone);
  sideDpBootIndex = 0;
  sideDpOk = false;
  topDpOk = false;
  powerOn = false;
  powerIndex = 0;
  bootFrames = 0;
  victory = false;
  victoryFrames = 0;
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
