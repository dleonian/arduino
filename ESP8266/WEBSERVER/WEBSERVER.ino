#include <SoftwareSerial.h>
 // arduino Rx (pin 2) ---- ESP8266 Tx
 // arduino Tx (pin 3) ---- ESP8266 Rx
SoftwareSerial esp8266(3,2); 

void setup()
{
  Serial.begin(115200);  // monitor serial del arduino
  esp8266.begin(115200); // baud rate del ESP8255
 
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  Serial.println("SETUPPING...");
  sendData("AT+RST\r\n",2000);      // resetear módulo
  sendData("AT+CWMODE=1\r\n",1000); // configurar como cliente
  sendData("AT+CWJAP=\"UAI-FI\",\"AccesosUAI\"\r\n",8000); //SSID y contraseña para unirse a red 
 // sendData("AT+CWJAP=\"DiegoL\",\"diego0610\"\r\n",8000); //SSID y contraseña para unirse a red 
  sendData("AT+CIFSR\r\n",1000);    // obtener dirección IP
  sendData("AT+CIPMUX=1\r\n",1000); // configurar para multiples conexiones
  sendData("AT+CIPSERVER=1,80\r\n",1000);         // servidor en el puerto 80
}

void loop()
{
 //Serial.println("looop");
 if(esp8266.available())   // revisar si hay mensaje del ESP8266
 {
   Serial.println("Available !");
   if(esp8266.find("+IPD,")) // revisar si el servidor recibio datos
   {
     Serial.println("Hay IPD!");
     delay(1500); // esperar que lleguen los datos hacia el buffer
     int conexionID = esp8266.read()-48; // obtener el ID de la conexión para poder responder
     
     esp8266.find("led="); // bucar el texto "led="
     int state = (esp8266.read()-48); // Obtener el estado del pin a mostrar
     Serial.println("Estado: " + String(state));
     if(state == 0)
     {
      digitalWrite(13, LOW); // Cambiar estado del pin
     }
     else
     {
      digitalWrite(13, HIGH);
     }
    
     
     while(esp8266.available()){
      char c = esp8266.read();
      Serial.print(c);
     }
     
     //responder y cerrar la conexión para que el navegador no se quede cargando 
     // página web a enviar
     String webpage = "";
     if (state==1) webpage += "<h1>LED_13 = encendido!</h1>";
     else { webpage += "<h1>LED_13 = apagado!</h1>";}
     
     // comando para enviar página web
     String comandoWebpage = "AT+CIPSEND=";
     comandoWebpage+=conexionID;
     comandoWebpage+=",";
     comandoWebpage+=webpage.length();
     comandoWebpage+="\r\n";
     sendData(comandoWebpage,1000);
     sendData(webpage,1000);
     
     // comando para terminar conexión
     String comandoCerrar = "AT+CIPCLOSE=";
     comandoCerrar+=conexionID;
     comandoCerrar+="\r\n";
     sendData(comandoCerrar,3000);
   }
 }
 else
  {
    int val = digitalRead(13);
   // Serial.print(val);
  }
}

/*
Enviar comando al esp8266 y verificar la respuesta del módulo, todo esto dentro del tiempo timeout
*/
void sendData(String comando, const int timeout)
{
 long int time = millis(); // medir el tiempo actual para verificar timeout
 
 esp8266.print(comando); // enviar el comando al ESP8266
 
 while( (time+timeout) > millis()) //mientras no haya timeout
 {
   while(esp8266.available()) //mientras haya datos por leer
   { 
     // Leer los datos disponibles
     char c = esp8266.read(); // leer el siguiente caracter
     Serial.print(c);
   }
 } 
 return;
}
