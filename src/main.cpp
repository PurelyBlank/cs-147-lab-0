#include <Arduino.h>
#include <Servo.h>

const int LIGHT_SENSOR = 13;
const int LED_PIN = 15;
const int SERVO_PIN = 17;
const int BAUD_RATE = 9600;
const int CALIBRATION_DELAY = 10000;

int maxLight = 0, minLight = 4095;
int light_value;
int rotateValue = 0;

Servo myServo;

void calibrate(){
  unsigned long startTime = millis();
  int counter = 0;
  while(millis() - startTime < CALIBRATION_DELAY) {
    analogWrite(LED_PIN, HIGH);
    sleep(1);
    light_value = analogRead(LIGHT_SENSOR);
    minLight = min(minLight, light_value);
    maxLight = max(maxLight, light_value);
    Serial.println("SLEEP");
    
    analogWrite(LED_PIN, LOW);
    sleep(1);
    ++counter;
  }
}

void setup() {
  Serial.begin(BAUD_RATE);

  pinMode(LED_PIN, OUTPUT);
  pinMode(LIGHT_SENSOR, INPUT);
  calibrate();
  myServo.attach(SERVO_PIN);

  Serial.print("Min Light: ");
  Serial.println(minLight);

  Serial.print("Max Light: ");
  Serial.println(maxLight);
  Serial.println();
}

void loop() {
  int lightLevel = analogRead(LIGHT_SENSOR);
  Serial.println(lightLevel);
  if (lightLevel <= minLight + 200) {
    myServo.write(0);
  } else if (lightLevel >= maxLight - 200) {
    myServo.write(179);
  }else
  {
    int value = (light_value)/(maxLight) * 179;
    myServo.write(value);
  }
  delay(1000);
}
