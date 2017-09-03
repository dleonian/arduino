#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

const char* ssid = "ENTER YOUT SSID HERE";
const char* password = "ENTER YOUR WIFI PASS HERE";

// Set these to run example.
#define FIREBASE_HOST ".firebaseio.com"
#define FIREBASE_AUTH "INSERT FIREBASE AUTH KEY"

int ledPin = 13;
int ledPin2 = 5;
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("disp1/luzPin", 0);
  Firebase.set("disp1/luzPin2", 0);
  Serial.println("Firebase OK");
}

int fbLedValue = 0;
void loop() {
  int val = Firebase.getInt("disp1/luzPin");
  Serial.println(val);

  if(val == 0)
  {
    digitalWrite(ledPin, LOW);
  }
  else
  {
    digitalWrite(ledPin, HIGH);
  }
  val = Firebase.getInt("disp1/luzPin2");
  Serial.println(val);

  if(val == 0)
  {
    digitalWrite(ledPin2, LOW);
  }
  else
  {
    digitalWrite(ledPin2, HIGH);
  }  
  delay(1000);
}
 
