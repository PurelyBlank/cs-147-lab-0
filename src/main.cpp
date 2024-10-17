#include <Arduino.h>

const int LIGHT_SENSOR = 13;
const int LED_PIN = 15;
const int BAUDRATE = 9600;

int maxLight = 0, minLight = 4095;
int light_value;
int counter = 0;

void setup() {
  Serial.begin(BAUDRATE);

  pinMode(LED_PIN, OUTPUT);
  pinMode(LIGHT_SENSOR, INPUT);
}

void loop() {
  light_value = analogRead(LIGHT_SENSOR);
  minLight = min(minLight, light_value);
  maxLight = max(maxLight, light_value);

  Serial.print("Light Value: ");
  Serial.println(light_value);

  Serial.print("Min Light: ");
  Serial.println(minLight);

  Serial.print("Max Light: ");
  Serial.println(maxLight);
  Serial.println();

  if (counter % 2 == 0) {
    analogWrite(LED_PIN, HIGH);
  } else {
    analogWrite(LED_PIN, LOW);
  }
  
  ++counter;
  delay(1000);
}
