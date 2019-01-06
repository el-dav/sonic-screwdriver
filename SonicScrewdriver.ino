byte piezoPin = 9;                // pin for piezo. Long leg of piezo: pin 4, short leg: GND.
byte buttonPin = 10;              // pin for momentary switch (between Pin 10 and GND).
int sensorPin = A0;
const int RED_PIN = 8;
const int GREEN_PIN = 7;
const int BLUE_PIN = 6;
int sensorValue;

void setup()
{
  pinMode(piezoPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // set up buttonPin as input with internal pull-up resistor
}

void loop()
{
  sensorValue = analogRead(sensorPin);
  soundFX(800.0, 30 * (sensorValue / 5));
}

void soundFX(float amplitude, float period) {
  int uDelay = 2 + amplitude + amplitude * sin(millis() / period);
  for (int i = 0; i < 5; i++) {
    digitalWrite(piezoPin, HIGH);
    RGB(uDelay);
    delayMicroseconds(uDelay);
    digitalWrite(piezoPin, LOW);
    delayMicroseconds(uDelay);
  }

}

void RGB(int color)
{
  int redIntensity;
  int greenIntensity;
  int blueIntensity;

  color = constrain(color, 0, 767); // constrain the input value to a range of values from 0 to 767

  // if statement breaks down the "color" into three ranges:
  if (color <= 255)       // RANGE 1 (0 - 255) - red to green
  {
    redIntensity = 255 - color;    // red goes from on to off
    greenIntensity = color;        // green goes from off to on
    blueIntensity = 0;             // blue is always off
  }
  else if (color <= 511)  // RANGE 2 (256 - 511) - green to blue
  {
    redIntensity = 0;                     // red is always off
    greenIntensity = 511 - color;         // green on to off
    blueIntensity = color - 256;          // blue off to on
  }
  else                    // RANGE 3 ( >= 512)- blue to red
  {
    redIntensity = color - 512;         // red off to on
    greenIntensity = 0;                 // green is always off
    blueIntensity = 767 - color;        // blue on to off
  }

  // "send" intensity values to the Red, Green, Blue Pins using analogWrite()
  analogWrite(RED_PIN, redIntensity);
  analogWrite(GREEN_PIN, greenIntensity);
  analogWrite(BLUE_PIN, blueIntensity);
}

