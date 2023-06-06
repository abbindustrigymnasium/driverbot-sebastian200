#include "EspMQTTClient.h"
#include <Servo.h>

int enA = D2;
int in1 = D1;
int in2 = D0;
int spd;

int dir;

Servo servot;
// hello
//  Gamla sättet
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
// configuring mqtt client
EspMQTTClient client(

    "Almesbo_wifi",   // Wifi ssid
    "KottenAlmesbo",  // Wifi password
    "192.168.50.218", // MQTT broker ip
    "ESP8266",        // Client name
    1884);

void setup()
{
  Serial.begin(9600);

  servot.attach(D3, 544, 2400);

  servot.write(90);

  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(enA, LOW);

  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output

  client.enableLastWillMessage("TestClient/lastwill", "I am going offline"); // You can activate the retain flag by setting the third parameter to true
}

void turn(int deg)
{
  servot.write(90 + deg);
}

void forwards(int spd)
{
  analogWrite(enA, spd);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}
void backwrds(int spd)
{
  analogWrite(enA, spd);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

// when conected to the broker cleint subscribes to the topics dir and spd, and sends these values back to the broker in the arspeed and ardir topic
void onConnectionEstablished()
{
  Serial.println("conected");
  client.subscribe("dir", [](const String &payload)
                   {
                     Serial.println(payload);
                     dir = payload.toInt();
                     turn(dir); });
  client.subscribe("spd", [](const String &payload)
                   {
                     Serial.println(payload);
                     spd = payload.toInt();
                     if (spd > 0)
                     {
                       forwards(spd);
                     }
                     else
                     {
                       backwards(-spd);
                     } });

  client.publish("arSpd", "spd");

  client.publish("arDir", "dir");
}

void loop()
{
  // put your main code here, to run repeatedly:

  // loops the mqtt client
  client.loop();
}
