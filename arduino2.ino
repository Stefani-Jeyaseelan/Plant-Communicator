#include <Arduino.h>
#include <Wire.h>
#include <OV7670.h>
 
OV7670 camera;
 
void setup() {
  Serial.begin(9600);
  camera.begin();
  camera.setResolution(OV7670_320x240);
}
 
void loop() {
  // Capture image
  camera.takePicture();
 
  // Send image data over serial
  uint16_t pixelCount = camera.getWidth() * camera.getHeight();
  uint8_t buffer[pixelCount * 2];  // 2 bytes per pixel (RGB565 format)
 
  for (uint16_t i = 0; i < pixelCount; i++) {
    uint16_t pixel = camera.readData();
    buffer[i * 2] = (uint8_t)(pixel >> 8);    // High byte
    buffer[i * 2 + 1] = (uint8_t)(pixel);     // Low byte
  }
 
  Serial.write(buffer, sizeof(buffer));
 
  // Delay between captures
  delay(1000);
}