#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

#define LED_PIN   2
#define LED_COUNT 1

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int time = 1;
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

void forward(int time) {
  const char text[] = "Forward";
  radio.write(&text, sizeof(text));
  strip.setPixelColor(0, 0, 255, 0);
  strip.show();
  delay(time);
}

void reverse(int time) {
  const char text[] = "Reverse";
  radio.write(&text, sizeof(text));
  strip.setPixelColor(0, 255, 255, 0);
  strip.show();
  delay(time);
}

void left(int time) {
  const char text[] = "Left";
  radio.write(&text, sizeof(text));
  strip.setPixelColor(0, 255, 0, 255);
  strip.show();
  delay(time);
}

void right(int time) {
  const char text[] = "Right";
  radio.write(&text, sizeof(text));
  strip.setPixelColor(0, 0, 255, 255);
  strip.show();
  delay(time);
}

void stop(int time){
  const char text[] = "Stop";
  radio.write(&text, sizeof(text));
  strip.setPixelColor(0, 255, 0, 0);
  strip.show();
  delay(time);
}

void send_command(int command, int time) {
  switch (command) {
    case 0: stop(time); break;
    // single command
    case 1: forward(time); break;
    case 2: reverse(time); break;
    case 3: right(time); break;
    case 4: left(time); break;
    default: Serial.print("Invalid Command\n");
  }
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
  }
  send_command(command, time);
}


