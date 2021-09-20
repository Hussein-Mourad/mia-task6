# Harry Maze

First we define the components pins
```cpp
#define MOTOR_LEFT1 2 // +ve
#define MOTOR_LEFT2 3 // -ve
#define MOTOR_LEFT_SPEED 10

#define MOTOR_RIGHT1 5 // +ve
#define MOTOR_RIGHT2 4 // -ve
#define MOTOR_RIGHT_SPEED 11

#define IR_RIGHT A0
#define IR_MIDDLE A1
#define IR_LEFT A2
```

Then we set pinMode of components and we set motor speed
```cpp
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
``` 

```cpp
void loop()
{
  // If all the sensors doesn't read any line then we are at a wrong edge and we need to go backwards
  if ((digitalRead(IR_LEFT) == 0) && (digitalRead(IR_MIDDLE) == 0) && (digitalRead(IR_RIGHT) == 0))
  {
    moveBackward();
  }

  // If the middle sensors only is reading then we are on the line and need to go forward
  if ((digitalRead(IR_LEFT) == 0) && (digitalRead(IR_MIDDLE) == 1) && (digitalRead(IR_RIGHT) == 0))
  {
    moveForward();
  }

  // If the left and and middle sensors are reading then we need to turn left
  if ((digitalRead(IR_LEFT) == 1) && (digitalRead(IR_MIDDLE) == 1) && (digitalRead(IR_RIGHT) == 0))
  {
    rotate90Left();
  }

  // This handles the case if the line is curved, as only the left sensor is reading so we need to go left
  if ((digitalRead(IR_LEFT) == 1) && (digitalRead(IR_MIDDLE) == 0) && (digitalRead(IR_RIGHT) == 0))
  {
    rotate90Left();
  }

  // If the right and and middle sensors are reading then we need to turn right
  if ((digitalRead(IR_LEFT) == 0) && (digitalRead(IR_MIDDLE) == 1) && (digitalRead(IR_RIGHT) == 1))
  {
    rotate90right();
  }

// This handles the case if the line is curved, as only the right sensor is reading so we need to go right
  if ((digitalRead(IR_LEFT) == 0) && (digitalRead(IR_MIDDLE) == 0) && (digitalRead(IR_RIGHT) == 1))
  {
    rotate90right();
  }

  // if all sensors are reading then we reached our destination, then we need to stop
  if ((digitalRead(IR_LEFT) == 1) && (digitalRead(IR_MIDDLE) == 1) && (digitalRead(IR_RIGHT) == 1))
  {
    stop();
  }
}

// makes the motors spin cw
void moveForward()
{
  digitalWrite(MOTOR_LEFT1, LOW);
  digitalWrite(MOTOR_LEFT2, HIGH);
  digitalWrite(MOTOR_RIGHT1, LOW);
  digitalWrite(MOTOR_RIGHT2, HIGH);
}

// makes the motors ccw
void moveBackward()
{
  digitalWrite(MOTOR_LEFT1, HIGH);
  digitalWrite(MOTOR_LEFT2, LOW);
  digitalWrite(MOTOR_RIGHT1, HIGH);
  digitalWrite(MOTOR_RIGHT2, LOW);
}

// stops the right motor so we can go right
void rotate90right()
{
  digitalWrite(MOTOR_LEFT1, LOW);
  digitalWrite(MOTOR_LEFT2, HIGH);
  digitalWrite(MOTOR_RIGHT1, LOW);
  digitalWrite(MOTOR_RIGHT2, LOW);
}

// stops the left motor so we can go left
void rotate90Left()
{
  digitalWrite(MOTOR_LEFT1, LOW);
  digitalWrite(MOTOR_LEFT2, LOW);
  digitalWrite(MOTOR_RIGHT1, LOW);
  digitalWrite(MOTOR_RIGHT2, HIGH);
}

// stops the rotation of the two motors
void stop()
{
  digitalWrite(MOTOR_LEFT1, LOW);
  digitalWrite(MOTOR_LEFT2, LOW);
  digitalWrite(MOTOR_RIGHT1, LOW);
  digitalWrite(MOTOR_RIGHT2, LOW);
}

```