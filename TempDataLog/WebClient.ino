/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen
 
 */

#include <SPI.h>
#include <Ethernet.h>

float tempC;
int tempPin = 0;

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x98, 0xAD};
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "data.sparkfun.com";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192,168,0,177);

unsigned long nextRun = 0;


// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
 // Open serial communications and wait for port to open:
 
  pinMode(7,OUTPUT);
  Serial.begin(57600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    while(true){};
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");
 
  doStuff();
  
}
void loop(){
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
//  if (!client.connected() ) {
//    Serial.println();
//    Serial.println("disconnecting.");
//    client.stop();
  
  
  if (!client.connected() && millis() > nextRun) {
    client.stop();
    doStuff();
    nextRun = millis()+1.2e+6;
  }
}

  
  void doStuff(){
    if (client.connect(server, 80)) {
    Serial.println("connected");
      tempC = analogRead(tempPin);
      tempC = (5.0*tempC*100.0)/1024.0;
  Serial.println((byte)tempC);
  
  if((byte)tempC == 72  || (byte)tempC == 73 || (byte)tempC == 74){   
    digitalWrite(7,HIGH); 
  }else{
    digitalWrite(7,LOW);
  }
  delay(1000);
    // Make a HTTP request:
    client.print("GET /input/LQV28480qNhOzVpMnwRj?private_key=A1g7AyA2vGcxK27Gd9Rb&temp=");
    client.print((byte)tempC);
    client.println(" HTTP/1.1");
    client.println("Host: data.sparkfun.com");
    client.println("Connection: close");
    client.println();
  }  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}
  

  
  


