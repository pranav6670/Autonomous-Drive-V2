#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_NeoPixel.h>
#include <LcdBarGraphRobojax.h>

#define in1 3
#define in2 4
#define in3 5
#define in4 6
#define ena 10
#define enb 9

#define LED_PIN   2
#define LED_COUNT 2

Adafruit_NeoPixel pixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd(0x27, 16, 2);
LcdBarGraphRobojax a_0(&lcd, 8, 2, 0);  //lcd obj, length of bar graph, start(column), line(row)
LcdBarGraphRobojax a_1(&lcd, 8, 2, 1);

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pixel.begin();
  pixel.show();
  pixel.setBrightness(255);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  delay(1000);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
}

void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  pixel.setPixelColor(0, 0, 255, 0);
  pixel.setPixelColor(1, 0, 255, 0);
  pixel.show();
}

void reverse() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  pixel.setPixelColor(0, 255, 255, 0);
  pixel.setPixelColor(1, 255, 255, 0);
  pixel.show();
}
void left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(16, HIGH);
  pixel.setPixelColor(0, 255, 0, 255);
  pixel.setPixelColor(1, 255, 0, 255);
  pixel.show();
}
void right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(14, HIGH);
  pixel.setPixelColor(0, 0, 255, 255);
  pixel.setPixelColor(1, 0, 255, 255);
  pixel.show();
}

void stopp() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  pixel.setPixelColor(0, 255, 0, 0);
  pixel.setPixelColor(1, 255, 0, 0);
  pixel.show();
}

int speeda = 150;
int speedb = 100;

void loop() {
  int a = analogRead(A0);
  int b = analogRead(A1);
  a_0.drawValue(a, 1024);
  a_1.drawValue(b, 1024);
  float val1 = map(a, 0, 1023, 0, 255);
  float val2 = map(b, 0, 1023, 0, 255);
  analogWrite(ena, val1);
  analogWrite(enb, val2);
  lcd.setCursor (0, 0);
  lcd.print("A:");
  lcd.setCursor (0, 1);
  lcd.print("B:");
  lcd.setCursor (11, 0);
  lcd.print(val1);
  lcd.setCursor (11, 1);
  lcd.print(val2);
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