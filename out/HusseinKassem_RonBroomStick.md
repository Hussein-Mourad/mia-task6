# RonBroomStick

- Begin i2c communication
- Initialize Imu
- configure accelerometer and gyroscope
- calibrate the Imu
- request the date from the sensor every 100ms by using timer library
- read the roll value from the register 
- scale the roll value from int value to the correct reading: (reading*fullScaleRange)/ max int16 value
- multiply the scaled value by 100 ms to covert from deg/s to deg
- repeat last 3 steps from pitch value
- If the roll or the pitch >= 60 flash the red led, else stop the led