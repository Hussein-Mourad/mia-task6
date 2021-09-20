
#define ENCODER1_PINA 2 // signal from channel A of encoder 1
#define ENCODER1_PINB 3 // signal from channel B of encoder 1

#define ENCODER2_PINA 18 // signal from channel A of encoder 2
#define ENCODER2_PINB 19 // signal from channel B of encoder 2

#define ENCODER3_PINA 20 // signal from channel A of encoder 3
#define ENCODER3_PINB 21 // signal from channel B of encoder 3

#define PPR 2048 // pulses per revolution for encoder

#define GREEN_LED 10

long long counter1 = 0; // counter of encoder 1
long long counter2 = 0; // counter of encoder 2
long long counter3 = 0; // counter of encoder 3

byte deg1 = 0;
byte deg2 = 0;
byte deg3 = 0;

void ISR_A1();
void ISR_B1();
void ISR_A2();
void ISR_B2();
void ISR_A3();
void ISR_B3();
void channelA(long long &counter, byte signalA, byte signalB);
void channelB(long long &counter, byte signalA, byte signalB);

void setup()
{
  pinMode(ENCODER1_PINA, INPUT_PULLUP);
  pinMode(ENCODER1_PINB, INPUT_PULLUP);
  pinMode(ENCODER2_PINA, INPUT_PULLUP);
  pinMode(ENCODER2_PINB, INPUT_PULLUP);
  pinMode(ENCODER3_PINA, INPUT_PULLUP);
  pinMode(ENCODER3_PINB, INPUT_PULLUP);
  pinMode(GREEN_LED, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENCODER1_PINA), ISR_A1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER1_PINB), ISR_B1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER2_PINA), ISR_A2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER2_PINB), ISR_B2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER3_PINA), ISR_A3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER3_PINB), ISR_B3, CHANGE);
}

void loop()
{
  deg1 = (counter1 / (PPR * 4)) * 360 % 360;
  deg2 = (counter2 / (PPR * 4)) * 360 % 360;
  deg3 = (counter3 / (PPR * 4)) * 360 % 360;

  if (deg1 == 37)
    digitalWrite(GREEN_LED, HIGH);
  if (deg2 == 10)
    digitalWrite(GREEN_LED, HIGH);
  if (deg3 == 54)
    digitalWrite(GREEN_LED, HIGH);

  delay(100);

  digitalWrite(GREEN_LED, LOW);
}

void channelA(long long &counter, byte signalA, byte signalB)
{
  if (digitalRead(signalA) != digitalRead(signalB))
    counter++;
  else
    counter--;
}

void channelB(long long &counter, byte signalA, byte signalB)
{
  if (digitalRead(signalA) == digitalRead(signalB))
    counter1++;
  else
    counter1--;
}

void ISR_A1() { channelA(counter1, ENCODER1_PINA, ENCODER1_PINB); }

void ISR_B1() { channelB(counter1, ENCODER1_PINA, ENCODER1_PINB); }

void ISR_A2() { channelA(counter2, ENCODER2_PINA, ENCODER2_PINB); }

void ISR_B2() { channelB(counter2, ENCODER2_PINA, ENCODER2_PINB); }

void ISR_A3() { channelA(counter3, ENCODER3_PINA, ENCODER3_PINB); }

void ISR_B3() { channelB(counter3, ENCODER3_PINA, ENCODER3_PINB); }