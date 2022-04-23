#include <M5Core2.h>
#include <FastLED.h>
#include <SCServo.h>
#define RX 32
#define TX 33
#define NUM_LEDS 14
#define INPUT_PINS 36
#define DATA_PIN 26

SMS_STS st;

unsigned short speed = 2500;
unsigned char acc = 50;
char str[128];

// Define the array of leds
CRGB leds[NUM_LEDS];

uint8_t beginHue = 0;
uint8_t deltaHue = 30;
uint8_t brightness = 100;
uint16_t rawADC = 0;
uint16_t degree = 0;

void setup()
{
  M5.begin();
  //M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextFont(7);
  M5.Lcd.setTextColor(WHITE,BLACK);
  Serial1.begin(1000000, SERIAL_8N1, RX, TX);
  st.pSerial = &Serial1;
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  delay(1000);
  pinMode(36, INPUT);
  fill_rainbow(leds, NUM_LEDS, beginHue, deltaHue); 
  st.unLockEprom(1);
  st.WheelMode(1);
  st.LockEprom(1);
}

void loop()
{
  rawADC = analogRead(INPUT_PINS);
  brightness = map(rawADC, 0, 4095, 0, 255);
  degree = map(rawADC, 0, 4095, 0, 360);
  FastLED.setBrightness(brightness);
  FastLED.show();
  M5.Lcd.fillRect(0, 0, 200, 150, BLACK);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.printf("%d",degree);
  st.RegWritePosEx(1, rawADC, speed, acc);
  st.RegWriteAction();
  delay(100);
}
