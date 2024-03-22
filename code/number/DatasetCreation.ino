#include "Wire.h" // library that allows to communicate with I2C devices

// pins for the flex sensors
const int flexSensor1Pin = A0;
const int flexSensor2Pin = A1;
const int flexSensor3Pin = A2;
const int flexSensor4Pin = A3;
const int flexSensor5Pin = A4;

// I2C address of the MPU-6050 
// can be determined by running Files > Examples > Wire > i2c_scanner
const int MPU_ADDR = 0x68; 

// variables for accelerometer raw data
int16_t accelerometer_x, accelerometer_y, accelerometer_z; 

// variables for gyro raw data
int16_t gyro_x, gyro_y, gyro_z; 

// variable for temperature data
int16_t temperature; 

// temporary variable used in convert function
char tmp_str[7]; 

// function to convert int16 to string
char* convert_int16_to_str(int16_t i) { 
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {
  Serial.begin(9600);

  // Initializes the I2C communication
  Wire.begin();
  
  // Starts a transmission to the device with the specified address
  Wire.beginTransmission(MPU_ADDR); 
  
  // Sends data to the device that have been started a transmission to
  Wire.write(0x6B); 
  
  // set to zero (wakes up the MPU-6050)
  Wire.write(0); 

  // Ends the transmission and sends the buffered data to the device
  Wire.endTransmission(true);
}

void loop() {
  // Starts a transmission to the device with the specified address
  Wire.beginTransmission(MPU_ADDR);
  
  // starting with register 0x3B (ACCEL_XOUT_H) 
  Wire.write(0x3B); 
  
  // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.endTransmission(false); 
  
  // request a total of 7*2=14 registers
  Wire.requestFrom(MPU_ADDR, 7*2, true); 
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_x = Wire.read()<<8 | Wire.read();

  // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_y = Wire.read()<<8 | Wire.read(); 
  
  // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read();

  // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  temperature = Wire.read()<<8 | Wire.read(); 
  
  // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); 
  
  // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); 
  
  // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); 
  
  int flexSensor1Value = analogRead(flexSensor1Pin);
  int flexSensor2Value = analogRead(flexSensor2Pin);
  int flexSensor3Value = analogRead(flexSensor3Pin);
  int flexSensor4Value = analogRead(flexSensor4Pin);
  int flexSensor5Value = analogRead(flexSensor5Pin);

  // print out data
  // Thumb
  Serial.print(flexSensor1Value);
  Serial.print(",");
  // IndexFinger
  Serial.print(flexSensor2Value);
  Serial.print(",");
  // MiddleFinger
  Serial.print(flexSensor3Value);
  Serial.print(",");
  // RingFinger
  Serial.print(flexSensor4Value);
  Serial.print(",");
  // LittleFinger
  Serial.print(flexSensor5Value);
  Serial.print(",");
  
  Serial.print(convert_int16_to_str(accelerometer_x));
  Serial.print(",");
  Serial.print(convert_int16_to_str(accelerometer_y));
  Serial.print(",");
  Serial.print(convert_int16_to_str(accelerometer_z));
  Serial.print(",");
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
  Serial.print(temperature/340.00+36.53);
  Serial.print(",");
  Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(",");
  Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(",");
  Serial.print(convert_int16_to_str(gyro_z));
  Serial.print(",");
  Serial.println();
  
  // delay
  delay(1000);
}
