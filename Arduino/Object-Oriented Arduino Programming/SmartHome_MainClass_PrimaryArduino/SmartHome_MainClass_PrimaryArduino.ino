#include <DHT.h>
#include <Wire.h>
#include <stdio.h>
#include <stdlib.h>
#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>

#define DHTPIN A0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float humidityValue = A0;
const int temperatureBuzzer = 13;
float temperatureValue = A0;
int redWavelength = 10;
int blueWavelength = 8;
int greenWavelength = 9;
const int fanPin = 6;

byte iceChar[] = {
  B00100,
  B10101,
  B01110,
  B11111,
  B11111,
  B01110,
  B10101,
  B00100
};

byte heatChar[] = {
  B00001,
  B00001,
  B00101,
  B00101,
  B10101,
  B10101,
  B11111,
  B11111
};

byte ACOnChar[] = {
  B11111,
  B11000,
  B00001,
  B00010,
  B10100,
  B11000,
  B00011,
  B11111
};

byte arrowUpChar[] = {
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B01110,
  B01110,
  B01110
};

byte arrowDownChar[] = {
  B01110,
  B01110,
  B01110,
  B01110,
  B11111,
  B11111,
  B01110,
  B00100
};

byte hyphenChar[] = {
  B00000,
  B11111,
  B11111,
  B01110,
  B01110,
  B11111,
  B11111,
  B00000
};

byte warmChar[] = {
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000
};

byte noACOnChar[] = {
  B11111,
  B10001,
  B01010,
  B00100,
  B01010,
  B10001,
  B11111,
  B11111
};

class primaryArduino {

  public:

    void setup() {
      dht.begin();
      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.print("    POWER ON    ");
      lcd.setCursor(0, 1);
      lcd.print(" SYSTEM BOOT UP ");
      delay(10000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("      POST      ");
      lcd.setCursor(0, 1);
      lcd.print(" COMPONENT TEST ");
      delay(10000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("       .       ");
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("       ..      ");
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("       ...     ");
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("      ... L    ");
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("     ... LO    ");
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    ... LOA    ");
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   ... LOAD    ");
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  ... LOADI    ");
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" ... LOADIN    ");
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("... LOADING    ");
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("... LOADING .  ");
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("... LOADING .. ");
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("... LOADING ...");
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("... LOADING ...");
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("... LOADING ...");
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" POWERED BY LIA ");
      lcd.setCursor(0, 1);
      lcd.print("OPERATING SYSTEM");
      delay(10000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   SMART HOME   ");
      lcd.setCursor(0, 1);
      lcd.print("===BY N.ELMER===");
      lcd.createChar(0, iceChar);
      lcd.createChar(1, heatChar);
      lcd.createChar(2, ACOnChar);
      lcd.createChar(3, noACOnChar);
      lcd.createChar(4, arrowUpChar);
      lcd.createChar(5, arrowDownChar);
      lcd.createChar(6, hyphenChar);
      lcd.createChar(7, warmChar);
      lcd.home();
      
      pinMode(fanPin, OUTPUT);
      pinMode(redWavelength, OUTPUT);
      pinMode(greenWavelength, OUTPUT);
      pinMode(blueWavelength, OUTPUT);
      delay(10000);
    }

    void RGB_color(int red, int green, int blue) {
      #ifdef COMMON_ANODE
            red = 255 - red;
            green = 255 - green;
            blue = 255 - blue;
      #endif

      analogWrite(redWavelength, red);
      analogWrite(greenWavelength, green);
      analogWrite(blueWavelength, blue);
    }

    void loop() {
      humidityValue = dht.readHumidity();
      temperatureValue = dht.readTemperature();

      if (temperatureValue >= 27) {
        digitalWrite(fanPin, HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("HOT ");
        lcd.write((byte)4);
        lcd.print(" TEMP ");
        lcd.write((byte)1);
        lcd.setCursor(0, 1);
        lcd.print("COOLING AC ON ");
        lcd.write((byte)2);

        RGB_color(255, 0, 0);

        delay(5000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("TEMP... = ");
        lcd.print(temperatureValue, 1);
        lcd.print((char)223);
        lcd.print("C");
        lcd.setCursor(0, 1);
        lcd.print("HUMI... = ");
        lcd.print(humidityValue);
        lcd.print("%");

        tone(temperatureBuzzer, 3000);
        delay(500);
        noTone(temperatureBuzzer);
        delay(500);

        tone(temperatureBuzzer, 3000);
        delay(500);
        noTone(temperatureBuzzer);
        delay(500);
      }

      else if (temperatureValue >= 26 && temperatureValue < 27) {
        digitalWrite(fanPin, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("WARM ");
        lcd.write((byte)6);
        lcd.print(" TEMP ");
        lcd.write((byte)7);
        lcd.setCursor(0, 1);
        lcd.print("NO AC ON ");
        lcd.write((byte)3);

        RGB_color(0, 255, 0);

        delay(5000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("TEMP... = ");
        lcd.print(temperatureValue, 1);
        lcd.print((char)223);
        lcd.print("C");
        lcd.setCursor(0, 1);
        lcd.print("HUMI... = ");
        lcd.print(humidityValue);
        lcd.print("%");
      }

      else if (temperatureValue < 26) {
        digitalWrite(fanPin, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("COLD ");
        lcd.write((byte)5);
        lcd.print(" TEMP ");
        lcd.write((byte)0);
        lcd.setCursor(0, 1);
        lcd.print("HEATING AC ON ");
        lcd.write((byte)2);

        RGB_color(0, 0, 255);

        delay(5000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("TEMP... = ");
        lcd.print(temperatureValue, 1);
        lcd.print((char)223);
        lcd.print("C");
        lcd.setCursor(0, 1);
        lcd.print("HUMI... = ");
        lcd.print(humidityValue);
        lcd.print("%");
        
        tone(temperatureBuzzer, 1000);
        delay(500);
        noTone(temperatureBuzzer);
        delay(500);

        tone(temperatureBuzzer, 1000);
        delay(500);
        noTone(temperatureBuzzer);
        delay(500);
      }

      else {
        digitalWrite(fanPin, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("VALUES ");
        lcd.print("NAN ");
        lcd.write((byte)8);
        lcd.setCursor(0, 1);
        lcd.print("SENSOR ERROR ");
        lcd.write((byte)8);

        RGB_color(255, 204, 33);

        delay(5000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("TEMP... = ");
        lcd.print(temperatureValue, 1);
        lcd.print((char)223);
        lcd.print("C");
        lcd.setCursor(0, 1);
        lcd.print("HUMI... = ");
        lcd.print(humidityValue);
        lcd.print("%");
      }
      
      delay(5000);
    }
};

primaryArduino primaryArduinoActivated;
