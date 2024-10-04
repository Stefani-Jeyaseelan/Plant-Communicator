#include <SoftwareSerial.h>
#include <DHT.h>

SoftwareSerial bluetooth(11, 10); // RX, TX

const int moistPin = A0;
const int gasPin = A1;
const int tempPin = A2;
const int ldrPin = A3;
const int motorPin = 7;

#define DHTPIN A2 // DHT11 sensor connected to analog pin A2
#define DHTTYPE DHT11 // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);

int ldrValue = 0;
float tempValueC = 0;
int moistValue = 0;
int gasValue = 0;

float moistPercent;
float voltage;
float ppm;
float rldr;
float lux;

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600); 

  pinMode(moistPin, INPUT);
  pinMode(gasPin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(motorPin, OUTPUT);
  dht.begin();

  Serial.println("PLANT COMMUNICATOR");
}

void loop()
{
  ldrValue = analogRead(ldrPin);
  delay(500);
  moistValue = analogRead(moistPin);
  delay(500);
  tempValueC = dht.readTemperature();
  delay(500);
  gasValue = analogRead(gasPin);
  delay(500);
  char ch = bluetooth.read();
  switch(ch) {
    case 'a':
      moistPercent = moistValue / 1023.0 * 100;

      voltage = gasValue * (5.0 / 1023.0);  
      ppm = 5000 * (voltage - 0.1) / 4.9;

      rldr=(10000*(5-ldrPin))/ldrPin;
      lux=(500/rldr);

      Serial.print("Light: ");
      Serial.print(ldrValue);
      Serial.println(" lux");
      Serial.print("Temp: ");
      Serial.print(tempValueC);
      Serial.println(" °C");
      Serial.print("CO2 Level: ");
      Serial.print(ppm);
      Serial.println(" ppm");
      Serial.print("Soil Dryness: ");
      Serial.print(moistPercent);
      Serial.println(" %");
      if(moistPercent > 90) {
        digitalWrite(motorPin, LOW);
        delay(5000);
        digitalWrite(motorPin, HIGH);
      }
      
      bluetooth.print(ldrValue);
      bluetooth.print(" lux");
      bluetooth.print(",");
      bluetooth.print(tempValueC);
      bluetooth.print(" °C");
      bluetooth.print(",");
      bluetooth.print(ppm);
      bluetooth.print(" ppm");
      bluetooth.print(",");
      bluetooth.print(moistPercent);
      bluetooth.print(" %");
      bluetooth.println();
      delay(1000);
      break;
    
    case 'b':
      ldrValue = analogRead(ldrPin);
      delay(500);
      moistValue = analogRead(moistPin);
      delay(500);
      tempValueC = dht.readTemperature();
      delay(500);
      gasValue = analogRead(gasPin);
      delay(500);
      
      moistPercent = moistValue/ 1023.0 * 100;

      voltage = gasValue * (5.0 / 1023.0);  
      ppm = 5000 * (voltage - 0.1) / 4.9;

      rldr=(10000*(5-ldrPin))/ldrPin;
      lux=(500/rldr);

      Serial.print("Light: ");
      Serial.print(ldrValue);
      Serial.println(" lux");
      Serial.print("Temp: ");
      Serial.print(tempValueC);
      Serial.println(" °C");
      Serial.print("CO2 Level: ");
      Serial.print(ppm);
      Serial.println(" ppm");
      Serial.print("Soil Dryness: ");
      Serial.print(moistPercent);
      Serial.println(" %");
      digitalWrite(motorPin, HIGH);
      
      bluetooth.print(ldrValue);
      bluetooth.print(" lux");
      bluetooth.print(",");
      bluetooth.print(tempValueC);
      bluetooth.print(" °C");
      bluetooth.print(",");
      bluetooth.print(ppm);
      bluetooth.print(" ppm");
      bluetooth.print(",");
      bluetooth.print(moistPercent);
      bluetooth.print(" %");
      bluetooth.println();
      break;
  }
}