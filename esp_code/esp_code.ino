#include <ESP8266WiFi.h>
 
const char* ssid = "WIFIROUTER";            //type your wifi router ssid
const char* password = "******";     //type your wifi router password

//name your ssid, passowrd
const char* ht_ssid = "NAME";             //type your ESP hotspot ssid
const char* ht_password = "PASSWORD";       //type your ESP hotspot password


 
int ledPin = 2; // GPIO2 of ESP8266
WiFiServer server(80);



void print(String msg)
{
 //  Serial.println(msg);
}

void print(const char* msg)
{
   // Serial.println(msg);
}
 
void setup() {
  Serial.begin(9600);
  delay(10);
 
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
   
  // Connect to WiFi network
  print("Connecting to ");
  print(ssid);
   
  WiFi.begin(ssid, password);
  
  WiFi.softAP(ht_ssid,ht_password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
   print(".");
   }
  print("WiFi connected");
   
  // Start the server
  server.begin();
  print("Server started");
 
  // Print the IP address
  print("Use this URL to connect: ");
  print("http://");
  //print(WiFi.localIP());
  print("/");
    
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
   
  // Wait until the client sends some data
  print("new client");
  while(!client.available()){
    delay(1);
  }
   
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  print(request);
  client.flush();
   
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    Serial.print("1ONS");
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF") != -1){
    digitalWrite(ledPin, LOW);
    Serial.print("1OFFS");
    value = LOW;
  }
 
// Set ledPin according to the request
 // digitalWrite(ledPin, value);
   
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html><body width='100%'>");
   
  client.print("Led pin is now: ");
   
  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<button><a href=\"/LED=ON\">Turn On</a></button><br>");
  client.println("<button><a href=\"/LED=OFF\">Turn Off</a></button><br>");
  client.println("</body></html>");
 
  delay(1);
  print("Client disonnected");
  print("");
 
}
