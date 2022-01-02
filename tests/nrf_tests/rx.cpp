#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN   6
#define LED_COUNT 2

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  strip.begin();
  strip.show();
  strip.setBrightness(255);
}

void forward() {
  strip.setPixelColor(0, 0, 255, 0);
  strip.setPixelColor(1, 0, 255, 0);
  strip.show();
}

void reverse() {
  strip.setPixelColor(0, 255, 255, 0);
  strip.setPixelColor(1, 255, 255, 0);
  strip.show();
}
void left() {
  strip.setPixelColor(0, 255, 0, 255);
  strip.setPixelColor(1, 255, 0, 255);
  strip.show();
}
void right() {
  strip.setPixelColor(0, 0, 255, 255);
  strip.setPixelColor(1, 0, 255, 255);
  strip.show();
}

void stopp() {
  strip.setPixelColor(0, 255, 0, 0);
  strip.setPixelColor(1, 255, 0, 0);
  strip.show();
}

void loop() {
  if (radio.available()) {
    char text[32];
    radio.read(&text, sizeof(text));
    Serial.println(text);
    if (strcmp("Forward", text) == 0) {
      forward();
    }
    else if (strcmp("Reverse", text) == 0) {
      reverse();
    }
    else if (strcmp("Right", text) == 0) {
      right();
    }
    else if (strcmp("Left", text) == 0) {
      left();
    }
    else if (strcmp("Stop", text) == 0) {
      stopp();
    }
    else {
      Serial.print(text);
      Serial.print("Don't come here");
    }
  }
}