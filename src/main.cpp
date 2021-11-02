#include <Arduino.h>

HardwareSerial Serial_im920(2);

hw_timer_t* timer;

void setup()
{
  Serial.begin(115200);
	Serial_im920.begin(19200, SERIAL_8N1, 16, 17);
  
  Serial_im920.setTimeout(100);

  timer = timerBegin(0, 80, true);
  timerStart(timer);

  delay(500);
  Serial_im920.print("srst\r\n");
  delay(500);
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

  // send data
  if (timerReadMicros(timer) > 2e5) {
    //from 0002
    // Serial_im920.print("txdu,0001,a2\r\n");
    //from 0003
    Serial_im920.print("txdu,0001,a3\r\n");
    Serial.println("sended message");

    timerWrite(timer, 0);
  }
}