#include "EspMQTTClient.h"
#include <Servo.h> 

const byte mSpeed = 4;
const byte mDir = 2;
int spd;

int dir;

int pot = A0;
int potval = 0;

Servo servot;

// Gamla sättet
/*EspMQTTClient client(
 "Nätverksnamn",           // Wifi ssid
  "password",           // Wifi password
  "maqiatto.com",  // MQTT broker ip
  1883,             // MQTT broker port
  "användarnamn på maqiatton",            // MQTT username
  "password",       // MQTT password
  "klientnamn",          // Client name
  onConnectionEstablished, // Connection established callback
  true,             // Enable web updater
  true              // Enable debug messages
);*/
// Nya sättet!
//configuring mqtt client
EspMQTTClient client(
    "ABBgym_2.4",
    "mittwifiarsabra",
    "aedes-broker.cloud.mustini.se",
    "",
    "",
    "broker",
    9696
    );




void setup()
{
Serial.begin(9600);

 servot.attach(D3, 544, 2400);

  servot.write(90);


  pinMode(mDir, OUTPUT);
  digitalWrite(mDir, HIGH);


  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output

  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true

}

void turn(int deg) {
  servot.write(90+deg);
}


void forwards(int spd) {
    analogWrite(mSpeed, spd);
    digitalWrite(mDir, HIGH);
}
void backwards (int spd) {
    analogWrite(mSpeed, spd);
    digitalWrite(mDir, LOW);
}
//when conected to the broker cleint subscribes to the topics dir and spd, and sends these values back to the broker in the arspeed and ardir topic
void onConnectionEstablished()
{
  Serial.println("conected");
  client.subscribe("seb/dir", [](const String &payload)
                   {
                     Serial.println(payload);
                     dir = payload.toInt();
                     turn(dir);
                   });
  client.subscribe("seb/spd", [](const String &payload)
                   {
                     Serial.println(payload);
                     spd = payload.toInt();
                     if (spd > 0) {
                      forwards(spd);
                     }
                     else {
                      backwards(-spd);
                     }
                 
                   });

  client.publish("seb/arSpd", "spd");

  client.publish("seb/arDir", "dir");
}

void loop()
{
  // put your main code here, to run repeatedly:

  //loops the mqtt client
  client.loop();

}
