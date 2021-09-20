#include <Timer.h>
#define PUSH_BUTTON 2
#define RED_LED 9
#define GREEN_LED 8
#define WHITE_LED 7

const unsigned long RED_TIMEOUT = 15UL * 60 * 1000; // 15 mins in ms
const unsigned long GREEN_TIME = 2UL * 60 * 1000;   // 2 mins in ms
const unsigned long WHITE_TIME1 = 5UL * 60 * 1000;  // 5 mins in ms
const unsigned long WHITE_TIME2 = 8UL * 60 * 1000;  // 8 mins in ms

Timer timer;
void ISR_Button();
void turnOffRedLed();
void blinkGreenLed();
void blinkWhiteLed();

void setup()
{
  attachInterrupt(digitalPinToInterrupt(PUSH_BUTTON), ISR_Button, HIGH);
}

void loop()
{
  timer.update();
}

void ISR_Button()
{
  // turn on red led
  digitalWrite(RED_LED, HIGH);
  // turn off red led after 15 mins
  timer.after(RED_TIMEOUT, turnOffRedLed);
  // blinks green led every 2 mins until red comes off
  timer.every(GREEN_TIME, blinkGreenLed, RED_TIMEOUT / GREEN_TIME);
  // flashes white led after 5 mins
  timer.after(WHITE_TIME1, blinkWhiteLed);
  // flashes white led after 8 mins
  timer.after(WHITE_TIME2, blinkWhiteLed);
}

void turnOffRedLed()
{
  digitalWrite(RED_LED, LOW);
}

// Flashes the green led for 5 seconds
void blinkGreenLed()
{
  timer.oscillate(GREEN_LED, 1000, LOW, 5);
}

// Flashes the white led for 10 seconds
void blinkWhiteLed()
{
  timer.oscillate(WHITE_LED, 1000, LOW, 10);
}
