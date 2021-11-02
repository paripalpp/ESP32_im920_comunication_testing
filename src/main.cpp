#include <Arduino.h>

#define sending_rate_us 250e3

#define nn0003

HardwareSerial Serial_im920(2);

hw_timer_t* timer;

uint32_t timer_countor = 0;

void setup()
{
  Serial.begin(115200);
	Serial_im920.begin(115200, SERIAL_8N1, 16, 17);
  
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
  #ifdef nn0002
  if (timerRead(timer) > sending_rate_us * timer_countor) {
    Serial_im920.print("txdu,0001,a2\r\n");
    Serial.println("sended message");

    timer_countor++;
  }
  #endif
  #ifdef nn0003
  if (timerRead(timer) > sending_rate_us * timer_countor) {
    Serial_im920.print("txdu,0001,a3\r\n");
    Serial.println("sended message");

    timer_countor++;
  }
  #endif
}