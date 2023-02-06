void setup() {
  pinMode(D8, OUTPUT);
}

void loop() {
  digitalWrite(D8, HIGH);
  delay(1000);
  digitalWrite(D8, LOW);
  delay(1000);
}


  if(currentTime - previousTime > 6000)
  {
    mover_servo_2();
    apagar_boquilla();
  }

    if (currentTime - previousTime >= 6000) {
    mover_servo_1();
    encender_boquilla();
    previousTime = currentTime;    
  }
