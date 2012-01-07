/*
 Arduino Busstop Light
 
 Idea by Christian Leu (www.leumund.ch)
 
 Adaptions made by Bastian Widmer (bastianwidmer.ch)
 
 This sketch connects to a PHP Script which parses Data from fahrplan.search.ch
 
 According to this data the LED's connected to Pin 5 and Pin 6 Display wether or not catching the next bus
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * LEDS attached to pins 5,6
 
 created 07 January 2012
 by Bastian Widmer
 
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte server[] = {
  82,195,224,126}; // Webserver

EthernetClient client;
String currentLine = "";            // string to hold the text from server

#define DATA_INTERVAL 30000         //miliseconds wait until fetching new data from webservice

void setup() {

  // Output LEDS
  pinMode(5, OUTPUT);     // RED LED
  pinMode(6, OUTPUT);     // GREEN LED

  // start the serial library:
  Serial.begin(9600);
  Serial.println("- Busstop Light Initialising -");

  Serial.println("Bringing Network up...");
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
}

void loop()
{
  static unsigned long getPrevTime = 0;


  if (millis() - getPrevTime > DATA_INTERVAL){                   // if time is bigger than our wait interval - connect
    getPrevTime = millis();                                      //  Reset the wait counter
    Serial.println("Getting Data ...");


    if (client.connect(server, 80)) {                            // Connect to Server
      Serial.println("Connected ...");

      Serial.println("Getting Data ...");
      client.println("GET /arduino_busstop/ HTTP/1.0");          // Make a HTTP request
      client.println("HOST: temp.dasrecht.net");                 // If you'r server runs on a Shared hosting send the Hostname along the Request
      client.println();
    } 
  }


  while(client.available() > 0)                                  // write the incomming bytes to our buffer
  {
    char c = client.read();
    currentLine += c;
    Serial.print(c);

    int ledGreen = 6;
    int ledRed = 5;

    if (c == '\n') {
      //   Serial.println(currentLine);

      if ( currentLine.startsWith("off",0)) {                  // if the webservice is signaling an off event turn off the leds
        Serial.println("OFF");
        digitalWrite(ledRed, LOW);
        digitalWrite(ledGreen, LOW);
        client.stop();
        Serial.println("stop");  
      }


      if ( currentLine.startsWith("green",0)) {                // if the webservice signals a green event push a HIGH to the green led pin
        Serial.println("GREEN");
        digitalWrite(ledRed, LOW);
        digitalWrite(ledGreen, HIGH);
        client.stop();
        Serial.println("stop");  
      }

      if ( currentLine.startsWith("red",0)) {                  // if the webservice signals a red event push a HIGH to the red led pin
        Serial.println("RED");
        digitalWrite(ledRed, HIGH);
        digitalWrite(ledGreen, LOW);
        client.stop();
        Serial.println("stop");  
      }
      if ( currentLine.startsWith("error",0)) {                // if we get an error ... turn off the leds
        Serial.println("ERROR");
        digitalWrite(ledRed, LOW);
        digitalWrite(ledGreen, LOW);

        client.stop();
        Serial.println("stop");  
      }
      currentLine = "";                                        // clear our linebuffer for the next run
    }
  }

  if (!client.connected()) {
    client.stop();
  }
}

