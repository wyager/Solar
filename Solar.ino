#include <Adafruit_ADXL345_U.h>
#include <Adafruit_TSL2561_U.h>
#include <pgmspace.h>
#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial ss(4,5); // (rx, tx)
// TSL2561_ADDR_FLOAT is the I2C address of the light sensor if the ADDR pin is floating (disconnected)
// 0xBEEF is the sensor's unique ID, with respect to Adafruit's "Adafruit_Sensor" library,
// which I guess allows you to log from a bunch of sensors or something.
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 0xBEEF);

// 0xF00D is the accelerometer's unique ID
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(0xF00D);
 
void setup() {
  Wire.begin(12,13); // (sda,scl)

  Serial.begin(115200); // Hardware serial
  
  ss.begin(9600); // Virtual serial

  tsl.enableAutoRange(true); // Light sensor auto-selects between 1x and 16x gain
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS); // Fast integration, low resolution

  accel.setRange(ADXL345_RANGE_2_G); // 2G max accel
  accel.setDataRate(ADXL345_DATARATE_50_HZ); // 50Hz refresh rate
  
  
  
  delay(10); // Let things settle (probably not necessary)

}

 
void loop() {
  // Light sensor stuff
  sensors_event_t event; // The sensor event (see Adafruit's sensor library)
  tsl.getEvent(&event); // Read an event from the light sensor
  if (event.light != 0) {
    Serial.print(event.light); Serial.println(" lux");
  } else { // 0 light means probable overload
    Serial.println("Light sensor overload.");
  }

  // Accelerometer stuff
  sensors_event_t accel_event;
  accel.getEvent(&accel_event);
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  
  
  delay(500);

  // Soft serial stuff
//  while(!ss.available()){};
//  char result = ss.read();
//  Serial.print(result);
}
