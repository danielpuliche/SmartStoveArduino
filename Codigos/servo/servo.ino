#include <Servo.h>

Servo myservo;

void setup() {
  myservo.attach(D8);
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i <= 180; i++) {
    myservo.write(i);
    Serial.println(i);
    delay(15);
  }
  for (int i = 180; i >= 0; i--) {
    myservo.write(i);
    Serial.println(i);
    delay(15);
  }
}
