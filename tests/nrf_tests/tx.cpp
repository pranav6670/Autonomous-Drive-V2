
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

#define LED_PIN   2
#define LED_COUNT 1

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int command = 0;

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  strip.begin();
  strip.show();
  strip.setBrightness(50);
}

void forward() {
  const char text[] = "Forward";
  radio.write(&text, sizeof(text));
  strip.setPixelColor(0, 0, 255, 0);
  strip.show();
}

void reverse() {
  const char text[] = "Reverse";
  radio.write(&text, sizeof(text));
  strip.setPixelColor(0, 255, 255, 0);
  strip.show();
}

void left() {
  const char text[] = "Left";
  radio.write(&text, sizeof(text));
  strip.setPixelColor(0, 255, 0, 255);
  strip.show();
}

void right() {
  const char text[] = "Right";
  radio.write(&text, sizeof(text));
  strip.setPixelColor(0, 0, 255, 255);
  strip.show();
}

void stop(){
  const char text[] = "Stop";
  radio.write(&text, sizeof(text));
  strip.setPixelColor(0, 255, 0, 0);
  strip.show();
}

void send_command(int command) {
  switch (command) {
    case 0: stop(); break;
    case 1: forward(); break;
    case 2: reverse(); break;
    case 3: right(); break;
    case 4: left(); break;
    default: Serial.print("Invalid Command\n");
  }
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
  }
  send_command(command);
}


