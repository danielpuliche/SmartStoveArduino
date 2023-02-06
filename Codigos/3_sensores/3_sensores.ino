#define TRIGGER_PIN D8
#define ECHO_PIN D9

#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN D11

DHT dht(DHTPIN, DHTTYPE);

int sensorPin = A0;

void setup() {
  
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);

 
  dht.begin();  
  
  pinMode(sensorPin, INPUT);
  
}

void loop() {
  Sensor_ultrasonido();
  Sensor_temperatura();
  Sensor_gas();
  Serial.println("-------------");
}

void Sensor_ultrasonido() {
 
  Serial.println("Sensor de ultrasonido");

  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(2000);
  
}

void Sensor_temperatura(){
  
  Serial.println("Sensor de temperatura");
 float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Error al leer del sensor DHT11");
    return;
  }

  
  Serial.print("Temperatura: ");
  Serial.print(t);


  delay(2000);
}

void Sensor_gas(){
  int sensorValue = analogRead(sensorPin);
  Serial.println("Sensor de gas");
  Serial.println(sensorValue);
  Serial.println("");
  delay(2000);
}
 



