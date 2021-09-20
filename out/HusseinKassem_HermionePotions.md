# Herminoe Potions

First we define components pins
```cpp
#define PUSH_BUTTON 2
#define RED_LED 9
#define GREEN_LED 8
#define WHITE_LED 7
```
Then we define time needed for each task
```cpp
const unsigned long RED_TIMEOUT = 15UL * 60 * 1000; // 15 mins in ms
const unsigned long GREEN_TIME = 2UL * 60 * 1000;   // 2 mins in ms
const unsigned long WHITE_TIME1 = 5UL * 60 * 1000;  // 5 mins in ms
const unsigned long WHITE_TIME2 = 8UL * 60 * 1000;  // 8 mins in ms
```
Then we attach an interrupt with the push button on change that starts the routine
```cpp
void setup()
{
  attachInterrupt(digitalPinToInterrupt(PUSH_BUTTON), ISR_Button, CHANGE);
}
```
Then we call this function when the interupt happens
```cpp
void ISR_Button()
{
  // we turn on the red len
  digitalWrite(RED_LED, HIGH);
  // we close it after 15 mins
  timer.after(RED_TIMEOUT, closeRedLed);
  // blinks green led every 2 mins until red comes off
  timer.every(GREEN_TIME, blinkGreenLed, RED_TIMEOUT / GREEN_TIME);
  // blinks white led after 5 mins
  timer.after(WHITE_TIME1, blinkWhiteLed);
  // blinks white led after 8 mins
  timer.after(WHITE_TIME2, blinkWhiteLed);
}

// closes the red led
void closeRedLed()
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
```