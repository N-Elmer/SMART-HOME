#include "DHT.h"
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>


#define DHTPIN 0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int digPin = 1;

byte iceChar[] = {
  B00100,
  B10101,
  B01110,
  B11111,
  B01110,
  B10101,
  B00100,
  B00000
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

byte onChar[] = {
  B11111,
  B11000,
  B00001,
  B00010,
  B10100,
  B11000,
  B00011,
  B11111
};

byte offChar[] = {
  B11111,
  B10001,
  B01010,
  B00100,
  B01010,
  B10001,
  B11111,
  B11111
};

void setup() {
  lcd.begin(16, 2);
  lcd.print("---SMART HOME---");
  lcd.setCursor(0, 1);
  lcd.print("---BY N.ELMER---");
  lcd.createChar(0, iceChar);
  lcd.createChar(1, heatChar);
  lcd.createChar(2, onChar);
  lcd.createChar(3, offChar);
  lcd.home();
  dht.begin();
  pinMode(digPin, OUTPUT);
  delay(10000);
}

void loop() {
  float humidite = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (temperature > 26.5) {
    digitalWrite(digPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GETTING HOT ");
    lcd.write((byte)1);
    lcd.setCursor(0, 1);
    lcd.print("AC ACTIVATED ");
    lcd.write((byte)2);
    
    Serial.println("GETTING HOT !!!");
    Serial.println("AC ACTIVATED !!!");

    delay(5000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TEMP... = ");
    lcd.print(temperature, 1);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("HUMI... = ");
    lcd.print(humidite);
    lcd.print("%");
  }

  else if (temperature <= 26.5) {
    digitalWrite(digPin, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GETTING COLD ");
    lcd.write((byte)0);
    lcd.setCursor(0, 1);
    lcd.print("AC DEACTIVATED ");
    lcd.write((byte)3);
    
    Serial.println("GETTING HOT !!!");
    Serial.println("AC DEACTIVATED !!!");

    delay(5000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TEMP... = ");
    lcd.print(temperature, 1);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("HUMI... = ");
    lcd.print(humidite);
    lcd.print("%");
  }

  delay(5000);
}
