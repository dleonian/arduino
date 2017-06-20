#include <SoftwareSerial.h>
SoftwareSerial esp8266(3, 2); // RX | TX

void setup()
  {  Serial.begin(115200);
     esp8266.begin(115200);
  }

void loop()
  {
     // Repetir lo recibido por el ESP8266 hacia el monitor serial
     if (esp8266.available())
         { char c = esp8266.read() ;
           Serial.print(c);
         }

     // Repetir lo recibido por el monitor serial hacia el ESP8266
     if (Serial.available())
         {  char c = Serial.read();
            esp8266.print(c);
         }
   }
