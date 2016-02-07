#include <SoftwareSerial.h>

SoftwareSerial ss(4,5);
 
void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  delay(10);

}

 
void loop() {
  while(!ss.available()){};
  char result = ss.read();
  
  Serial.print(result);
}
