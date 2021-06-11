#include <Metro.h>
#include <Servo.h>
const int trig_pin = 10;
const int echo_pin = 11;
const int servo_pin = 3;

long duration;
double distance;
int angle = 170;

Servo servo;
Metro sensor_metro = Metro(0.1);

void setup() {
  // put your setup code here, to run once:
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  servo.attach(servo_pin);
  servo.write(125);
  Serial.begin(9600);
  delay(3000);
}

void loop() {
   //put your main code here, to run repeatedly:
 if (sensor_metro.check()) {
      calcular_distancia();
      if (distance <= 19) {
          Serial.println(distance);
      }
  }
  servo.write(115);
}

int  calcular_distancia () {
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(2);
    digitalWrite(trig_pin, LOW);
    
    duration = pulseIn(echo_pin, HIGH);
    distance = duration*0.034/2;
    return distance;
}
