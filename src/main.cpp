#include <Arduino.h>

HardwareSerial Serial_im920(1);
void setup()
{
  Serial.begin(115200);
	Serial_im920.begin(19200, SERIAL_8N1, 26, 27);
  
  Serial_im920.setTimeout(100);
}

void loop()
{

  //data from im920 to pc
  if (Serial_im920.available()){
	  String str = Serial_im920.readStringUntil('\r');
    Serial_im920.readStringUntil('\n');
    Serial.println(str);

    // Serial.print(Serial_im920.read());
  }
  
  //data from pc to im920
  if (Serial.available()){
    Serial.print("> ");
    
    String str = Serial.readStringUntil('\r');
    Serial.readStringUntil('\n');
    Serial.println(str);
    Serial_im920.println(str);
  }
}