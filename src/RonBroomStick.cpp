#include <Arduino.h>
#include <Wire.h>
#include <Timer.h>

#define IMU_ADDRESS 0x68
#define RED_LED 10
#define GYRO_FACTOR 2000

int32_t x_accel_offset = 0, y_accel_offset = 0, z_accel_offset = 0;
int32_t x_gyro_offset = 0, y_gyro_offset = 0, z_gyro_offset = 0;

int16_t x_gyro = 0, y_gyro = 0, z_gyro = 0;

int8_t event;

void setImuRegister(uint8_t reg, uint8_t value);
uint8_t readImu1Byte(uint8_t reg);
uint8_t readImu2Bytes(uint8_t reg);
void calibrateImu(uint32_t iterations);
int16_t scaleValue(int16_t value, int16_t factor);
void handleImuData();

Timer timer;

void setup()
{
  // begin i2c comunication
  Wire.begin();
  // initialization
  setImuRegister(0x6B, 0x00);
  // accelerometer configuration 16g
  setImuRegister(0x1C, 0x18);
  // gyroscope configuration 2000 deg/s
  setImuRegister(0x1B, 0x18);
  // calibrate imu
  calibrateImu(4000);
  // request the imu data every 100 ms
  timer.every(100, handleImuData);
}

void loop()
{
  timer.update();
}

void handleImuData()
{
  // Get the value from the sensor, scale it, convert from rad/s to deg/s
  // then multiply by 100 ms as we read from the sensor every 100 ms
  // This converts deg/s to deg
  x_gyro = degrees(scaleValue(readImu2Bytes(0x43), GYRO_FACTOR)) * 100;
  y_gyro = degrees(scaleValue(readImu2Bytes(0x45), GYRO_FACTOR)) * 100;

  // If the roll or the pitch exceeds 60 deg flash the red light
  if (abs(x_gyro) >= 60 || abs(y_gyro) >= 60)
  {
    event = timer.oscillate(RED_LED, 300, LOW);
  }
  else
  {
    // if not stop the flashing
    timer.stop(event);
  }
}

void setImuRegister(uint8_t reg, uint8_t value)
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t readImu1Byte(uint8_t reg)
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(IMU_ADDRESS, 1);
  while (Wire.available() < 1)
    ;
  return Wire.read();
}

uint8_t readImu2Bytes(uint8_t reg)
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(IMU_ADDRESS, 2);
  while (Wire.available() < 2)
    ;
  return Wire.read() << 8 | Wire.read();
}

void calibrateImu(uint32_t iterations)
{
  for (uint32_t i = 0; i < iterations; i++)
  {
    x_accel_offset += readImu2Bytes(0x3B);
    y_accel_offset += readImu2Bytes(0x3D);
    z_accel_offset += readImu2Bytes(0x3F);

    x_gyro_offset += readImu2Bytes(0x43);
    y_gyro_offset += readImu2Bytes(0x45);
    z_gyro_offset += readImu2Bytes(0x47);
  }

  x_accel_offset /= iterations;
  y_accel_offset /= iterations;
  z_accel_offset /= iterations;
  x_gyro_offset /= iterations;
  y_gyro_offset /= iterations;
  z_gyro_offset /= iterations;
}

int16_t scaleValue(int16_t value, int16_t factor)
{
  return (value * factor) / 32.767;
}