// Motor A connections
#include <Servo.h> 
int enA = D2;
int in1 = D1;
int in2 = D0;


Servo servot;

void setup() {
    Serial.begin(9600);
  // put your setup code here, to run once:
  servot.attach(D3, 544, 2400);

  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);


  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(enA, LOW);

}

void turn(int deg) {
  servot.write(deg);
}


void forwards(int spd) {
  analogWrite(enA, spd);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}
void backwrds (int spd) {
  analogWrite(enA, spd);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void loop() {

turn(120);
Serial.println("left");
delay(3000);
turn(-120);
Serial.println("right");
delay(3000);


}
