#include <DHT.h>
#include <stdio.h>
#include <stdlib.h>
#include <Stepper.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <Adafruit_Sensor.h>

#define STEPS  15

const int waterBuzzer = 7;
int redWavelength = 6;
int blueWavelength = 4;
int greenWavelength = 5;
int waterPin = A0;
int waterValue = 0;
int IRSensor = 3;
const int IRLed = 2;
int homeLights = 13;
int  StepsToTake;

IRrecv receiver(IRSensor);
decode_results results;
Stepper small_stepper(STEPS, 8, 10, 9, 11);

class primaryArduino {

  public:

    void setup() {
      pinMode(IRLed, OUTPUT);
      pinMode(homeLights, OUTPUT);
      pinMode(redWavelength, OUTPUT);
      pinMode(blueWavelength, OUTPUT);
      pinMode(greenWavelength, OUTPUT);

      receiver.enableIRIn();
      Serial.begin(9600);
    }

    void loop() {

      char id = Serial.read();
      waterValue = analogRead(waterPin);

      if (waterValue < 400) {
        digitalWrite(redWavelength, HIGH);
        digitalWrite(blueWavelength, LOW);
        digitalWrite(greenWavelength, LOW);

        Serial.println(waterValue);
        Serial.println("LOW WATER RESERVES");

        delay(5000);

        tone(waterBuzzer, 1000);
        delay(1000);
        noTone(waterBuzzer);
        delay(2000);

        tone(waterBuzzer, 1000);
        delay(1000);
        noTone(waterBuzzer);
        delay(2000);
      }

      if (waterValue >= 400 && waterValue <= 500) {
        digitalWrite(blueWavelength, HIGH);
        digitalWrite(redWavelength, LOW);
        digitalWrite(greenWavelength, LOW);

        Serial.println(waterValue);
        Serial.println("MID WATER RESERVES");
      }

      if (waterValue > 500) {
        digitalWrite(greenWavelength, HIGH);
        digitalWrite(blueWavelength, LOW);
        digitalWrite(redWavelength, LOW);

        Serial.println(waterValue);
        Serial.println("HIGH WATER RESERVES");
      }

      if (waterValue == 0) {
        digitalWrite(greenWavelength, HIGH);
        digitalWrite(blueWavelength, LOW);
        digitalWrite(redWavelength, HIGH);

        Serial.println("VALUES NAN !!!");
        Serial.println("SENSOR ERROR !!!");
      }

      if (id == 'A') {
        digitalWrite(homeLights, HIGH);
      }

      if (id == 'B') {
        digitalWrite(homeLights, LOW);
      }

      if (receiver.decode(&results))

      {
        switch (results.value)

        {

          case 0xFFA857:
            digitalWrite(IRLed, HIGH);
            small_stepper.setSpeed(500);
            StepsToTake  =  512 
            ;
            small_stepper.step(StepsToTake);
            digitalWrite(IRLed, LOW);
            Serial.println(results.value, HEX);
            Serial.println("DOOR OPEN");
            //delay(2000);
            break;

          case 0xFFE01F:
            digitalWrite(IRLed, HIGH);
            small_stepper.setSpeed(500);
            StepsToTake  =  -512;
            small_stepper.step(StepsToTake);
            digitalWrite(IRLed, LOW);
            Serial.println(results.value, HEX);
            Serial.println("DOOR CLOSED");
            //delay(2000);
            break;

        }

        receiver.resume();
      }
    }
};

primaryArduino primaryArduinoActivated;
