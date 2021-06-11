 #include <Metro.h>
#include <Servo.h>

Servo servo;
Metro sensor_metro = Metro(0.1);

const int trig_pin = 10;
const int echo_pin = 11;
const int servo_pin = 6;

const int u_max = 170;
const int u_min = 80; 

const double setpoint = 13;
const double tau = 0.1e-3;

const double Kp = -4.46;
const double Ki = -1.48;
const double Kd = -4.46;

double P = 0;
double I = 0;
double D = 0;
double angle;

long duration;
double distance;
double error_prev = 0;
double error_actual;

void setup() {
  // put your setup code here, to run once:
  servo.attach(servo_pin);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  servo.write(140);
  delay(1000);
  Serial.begin(9600);
}

void loop() {
  if (sensor_metro.check()) {
    distance = calcular_distancia();
  }
  if (distance < 25 && distance >= 0){
      error_actual = setpoint - distance;
      
      P = Kp*(error_actual);
      I = I + tau*Ki*error_actual;
      D = Kd*(error_actual-error_prev);
      
      error_prev = error_actual;
      angle = P + I + D;
      Serial.print(distance);
      Serial.print(" ");
      Serial.print(error_actual);
      angle = map(angle,-105,105,u_min,u_max);
      Serial.print(" ");
      Serial.print(angle);
      Serial.print("\n");
      
      if (angle > u_max) {
          angle = u_max;
          servo.write(angle);
          delay(1);
      } else if (angle < u_min) {
          angle = u_min;
          servo.write(angle);   
          delay(1);
      } else if (angle <= u_max && angle >= u_min) {
          servo.write(angle);
          delay(1);
      }
  }
}

double  calcular_distancia () {
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(1);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(1);
    digitalWrite(trig_pin, LOW);
    
    duration = pulseIn(echo_pin, HIGH);
    double distance_output = duration*0.034/2;
    return distance_output;
}
