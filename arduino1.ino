#include <SoftwareSerial.h>

SoftwareSerial arduino2(11, 10);

const int moistPin = A0;
const int gasPin = A1;
const int tempPin = A2;
const int ldrPin = A3;

int ldrValue = 0;
int tempValue = 0;
int moistValue = 0;
int gasValue = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(moistPin, INPUT);
  pinMode(gasPin, INPUT);
  pinMode(tempPin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(13, OUTPUT); 
  pinMode(12, OUTPUT); 
  
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);  

  Serial.println("PLANT COMMUNICATOR");
}

char variable;
void loop()
{
  ldrValue = analogRead(ldrPin);
  delay(500);
  moistValue = analogRead(moistPin);
  delay(500);
  tempValue = analogRead(tempPin);
  delay(500);
  gasValue = analogRead(gasPin);
  delay(500);
  
  float voltage = gasValue * (5.0 / 1023.0);  
  float ppm = 5000 * (voltage - 0.1) / 4.9;

  float temp_voltage = tempValue*4.68;
  temp_voltage /= 1024.0;
  float tempValueC = (temp_voltage-0.5)*100; 
  
  float rldr=(10000*(5-ldrPin))/ldrPin;
  float lux=(500/rldr);


  Serial.print("Light: ");
  Serial.println(ldrValue);
  
  Serial.print("Temperature: ");
  Serial.println(tempValueC);
          
  Serial.print("Moisture: ");
  Serial.println(moistValue);
  
  Serial.print("CO2 Level: ");
  Serial.println(ppm);
  
  delay(1000);
}