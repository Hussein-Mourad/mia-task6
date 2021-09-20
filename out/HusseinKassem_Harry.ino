#include <Arduino.h>

#define MOTOR_LEFT1 2 // +ve
#define MOTOR_LEFT2 3 // -ve
#define MOTOR_LEFT_SPEED 10

#define MOTOR_RIGHT1 5 // +ve
#define MOTOR_RIGHT2 4 // -ve
#define MOTOR_RIGHT_SPEED 11

#define IR_RIGHT A0
#define IR_MIDDLE A1
#define IR_LEFT A2

void moveForward();
void moveBackward();
void rotate90right();
void rotate90Left();
void moveBackward();

void setup()
{
  pinMode(MOTOR_RIGHT2, OUTPUT);
  pinMode(MOTOR_RIGHT1, OUTPUT);
  pinMode(MOTOR_LEFT1, OUTPUT);
  pinMode(MOTOR_LEFT2, OUTPUT);
  pinMode(MOTOR_RIGHT_SPEED, OUTPUT);
  pinMode(MOTOR_LEFT_SPEED, OUTPUT);

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_MIDDLE, INPUT);
  pinMode(IR_RIGHT, INPUT);

  analogWrite(MOTOR_LEFT_SPEED, 150);
  analogWrite(MOTOR_RIGHT_SPEED, 150);
  delay(200);
}
void loop()
{
  if ((digitalRead(IR_LEFT) == 0) && (digitalRead(IR_MIDDLE) == 0) && (digitalRead(IR_RIGHT) == 0))
  {
    moveBackward();
  }

  if ((digitalRead(IR_LEFT) == 0) && (digitalRead(IR_MIDDLE) == 1) && (digitalRead(IR_RIGHT) == 0))
  {
    moveForward();
  }

  if ((digitalRead(IR_LEFT) == 1) && (digitalRead(IR_MIDDLE) == 1) && (digitalRead(IR_RIGHT) == 0))
  {
    rotate90Left();
  }

  if ((digitalRead(IR_LEFT) == 1) && (digitalRead(IR_MIDDLE) == 0) && (digitalRead(IR_RIGHT) == 0))
  {
    rotate90Left();
  }

  if ((digitalRead(IR_LEFT) == 0) && (digitalRead(IR_MIDDLE) == 1) && (digitalRead(IR_RIGHT) == 1))
  {
    rotate90right();
  }

  if ((digitalRead(IR_LEFT) == 0) && (digitalRead(IR_MIDDLE) == 0) && (digitalRead(IR_RIGHT) == 1))
  {
    rotate90right();
  }

  if ((digitalRead(IR_LEFT) == 1) && (digitalRead(IR_MIDDLE) == 1) && (digitalRead(IR_RIGHT) == 1))
  {
    stop();
  }
}

void moveForward()
{
  digitalWrite(MOTOR_LEFT1, LOW);
  digitalWrite(MOTOR_LEFT2, HIGH);
  digitalWrite(MOTOR_RIGHT1, LOW);
  digitalWrite(MOTOR_RIGHT2, HIGH);
}

void moveBackward()
{
  digitalWrite(MOTOR_LEFT1, HIGH);
  digitalWrite(MOTOR_LEFT2, LOW);
  digitalWrite(MOTOR_RIGHT1, HIGH);
  digitalWrite(MOTOR_RIGHT2, LOW);
}

void rotate90right()
{
  digitalWrite(MOTOR_LEFT1, LOW);
  digitalWrite(MOTOR_LEFT2, HIGH);
  digitalWrite(MOTOR_RIGHT1, LOW);
  digitalWrite(MOTOR_RIGHT2, LOW);
}

void rotate90Left()
{
  digitalWrite(MOTOR_LEFT1, LOW);
  digitalWrite(MOTOR_LEFT2, LOW);
  digitalWrite(MOTOR_RIGHT1, LOW);
  digitalWrite(MOTOR_RIGHT2, HIGH);
}

void stop()
{
  digitalWrite(MOTOR_LEFT1, LOW);
  digitalWrite(MOTOR_LEFT2, LOW);
  digitalWrite(MOTOR_RIGHT1, LOW);
  digitalWrite(MOTOR_RIGHT2, LOW);
}