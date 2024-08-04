#include <Servo.h>
// Ultrasonic sonar.
// read distance, Theta.
// convert to X,Y careasian coords
// send data over seial. 

// Sensor IO
#define TRIG_PIN_1 10
#define ECHO_PIN_1 9
// Function Primatives:
int getDistance(int triggerPin, int echoPin);

//const float PI = 3.14159265358979323846;
// Guess I dont have to define it
Servo myservo;  // Servo object on pin 11
int pos = 0;    // servo position

void setup() {
  Serial.begin(115200);
  myservo.attach(11); 
  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  }
/* polar conversion:
r, theta = 
theta in DEG convert to RAD:
theta = (pos*pi)/180
x=distance * cos(pos)
y=distance * sin(pos *
*/
float x;
float y;
float theta;
int r; // distance from sensor
void loop() {
  
  for (pos = 0; pos <= 180; pos += 1) { 
    myservo.write(pos);               
    delay(5); // Travel time        
    theta = (pos*PI)/180;
    r = getDistance(TRIG_PIN_1, ECHO_PIN_1);
    x = r * cos(theta);
    y = r * sin(theta);
    Serial.print(x);
    Serial.print(",");
    Serial.println(y);              
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);              
    delay(5); // Travel time  
    theta = (pos*PI)/180;
    r = getDistance(TRIG_PIN_1, ECHO_PIN_1);
    x = r * cos(theta);
    y = r * sin(theta);
    Serial.print(x);
    Serial.print(",");
    Serial.println(y);                  
  }
}
int getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.017;
  return distance;
}
