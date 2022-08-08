#include <Wire.h>

#define relayPin 1
//#define SLAVE_ADDR 9

int data;
//int relayPin = 1;

void setup() {
  Wire.begin(9);
  pinMode(relayPin, OUTPUT);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  Serial.println("AUXILIARY TEST");
}

void receiveEvent() {
  while (1 < Wire.available()) {
    data = Wire.read();
    Serial.println(data);
  }
}

void loop() {
  Wire.requestFrom(9, 2);
  
  if (data > 25) {
    digitalWrite(relayPin, HIGH);
    Serial.println(data);
    Serial.println("It is getting hot: FAN ACTIVE");
  }

  else if (data < 25) {
    digitalWrite(relayPin, LOW);
    Serial.println(data);
    Serial.println("It is getting cold: FAN INACTIVE");
  }

  delay(5000);
}
