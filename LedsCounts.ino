#include <FastLED.h>

// fast led constants
#define DATA_PIN    3        // change to your data pin
#define COLOR_ORDER GRB      // if colors are mismatched; change this
#define NUM_LEDS    16       // change to the number of LEDs in your strip

// change WS2812B to match your type of LED, if different
// list of supported types is here:
// https://github.com/FastLED/FastLED/wiki/Overview
#define LED_TYPE    WS2812B
#define BRIGHTNESS          50
int LEDbrightness;
int redSensor = 2;              // the pin that the redSensor is atteched to
int greenSensor = 4;
int blueSensor = 5;
int state[NUM_LEDS] = {LOW};              // by default, no motion detected
int redState[NUM_LEDS] = {0};             // variable to store the redSensor status (value)
int greenState[NUM_LEDS] = {0};           // variable to Store the greenSensor status (value)
int blueState[NUM_LEDS] = {0};            // variable to store the blueSensor status (value)
int LedFlag = 0;
int index = 0;

// this creates an LED array to hold the values for each led in your strip
CRGB leds[NUM_LEDS];

void setup()
{

  // the wiki features a much more basic setup line:

  // initalize LED as an output

  pinMode(redSensor, INPUT);    // initialize redSensor as an input
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(DATA_PIN, OUTPUT);
  Serial.begin(9600);

}

void turnOn(int colorState[], CRGB color) {
  leds[index] = color; 
  colorState[index] = LOW;
  FastLED.show();
  delay(4000);
  index = index + 1;
}

void loop()
{
  redState[index] = digitalRead(redSensor);   // read redSensor value
  blueState[index] = digitalRead(blueSensor); // read blueSensor value
  greenState[index] = digitalRead(greenSensor); // read greenSensor value
  if ((redState[index] == HIGH || greenState[index] == HIGH || blueState[index] == HIGH) && state[index] == LOW) {
    state[index] = HIGH;       // update the current individual led state to HIGH
  }

  if (state[index] == HIGH) {
    if (redState[index] == HIGH) turnOn(redState, CRGB :: Red);
    if (greenState[index] == HIGH) turnOn(greenState, CRGB :: Green);
    if (blueState[index] == HIGH) turnOn(blueState, CRGB :: Blue);
  }

  if (index + 1 == NUM_LEDS) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = 0;
      index = 0;
    }
  }
}
