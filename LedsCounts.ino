#include <FastLED.h>

// fast led constants
#define DATA_PIN    3
#define RED_PIN   6   // red output strip
#define GREEN_PIN   12   // green output strip
#define BLUE_PIN  10  // blue output strip    
#define COLOR_ORDER GRB      // if colors are mismatched; change this
#define MAX_POINTS    16       // change to the number of LEDs in your strip
#define amountOfLeds 37 //refers to the amount of leds circling around each hole


// change WS2812B to match your type of LED, if different
// list of supported types is here:
// https://github.com/FastLED/FastLED/wiki/Overview
#define LED_TYPE    WS2812B
#define BRIGHTNESS          50
int LEDbrightness;
int redSensor = 2;                        // the pin that the redSensor is atteched to
int greenSensor = 4;
int blueSensor = 5;
int state[MAX_POINTS] = {LOW};              // by default, no motion detected
int redState[MAX_POINTS] = {0};             // variable to store the redSensor status (value)
int greenState[MAX_POINTS] = {0};           // variable to Store the greenSensor status (value)
int blueState[MAX_POINTS] = {0};            // variable to store the blueSensor status (value)
int LedFlag = 0;
int index = 0;
int circlingIndex[3] = {0, 1, 2};
int prevIndex[3] = {0, 0, 0};

// this creates an LED array to hold the values for each led in your strip
CRGB pointLeds[MAX_POINTS];
CRGB redLeds[amountOfLeds];
CRGB greenLeds[amountOfLeds];
CRGB blueLeds[amountOfLeds];

void setup()
{

  // the wiki features a much more basic setup line:

  // initalize LED as an output
  pinMode(redSensor, INPUT);    // initialize redSensor as an input
  pinMode(greenSensor, INPUT);
  pinMode(blueSensor, INPUT);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(pointLeds, MAX_POINTS);
  FastLED.addLeds<LED_TYPE, RED_PIN, COLOR_ORDER>(redLeds, amountOfLeds);
  FastLED.addLeds<LED_TYPE, BLUE_PIN, COLOR_ORDER>(blueLeds, amountOfLeds);
  FastLED.addLeds<LED_TYPE, GREEN_PIN, COLOR_ORDER>(greenLeds, amountOfLeds);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(9600);

}

void addPoint(int colorState[], CRGB color) {
  pointLeds[index] = color;
  colorState[index] = LOW;
  FastLED.show();
  delay(4000);
  index = index + 1;
}

void fireInDaHole(CRGB color) {
  Serial.println(color);
  for (int i = 0; i < amountOfLeds; i++) {
    redLeds[i] = color;
    greenLeds[i] = color;
    blueLeds[i] = color;
  }
  FastLED.show();
  delay(800);
}

void updateLights() {
  for (int i = amountOfLeds - 1; i > amountOfLeds - 3; i--) {
    redLeds[i] = 0;
    greenLeds[i] = 0;
    blueLeds[i] = 0;
  }
  for (int i = 0; i < 3; i++) {
    redLeds[prevIndex[i]] = 0;
    blueLeds[prevIndex[i]] = 0;
    greenLeds[prevIndex[i]] = 0;
  }

  prevIndex[0] = circlingIndex[0];
  prevIndex[1] = circlingIndex[1];
  prevIndex[2] = circlingIndex[2];

  if (circlingIndex[0] + 5 >= amountOfLeds) {
    circlingIndex[0] = 0;
    circlingIndex[1] = 1;
    circlingIndex[2] = 2;
  } else {
    for (int i = 0; i < 3; i++) {
      redLeds[circlingIndex[i]] = CRGB :: Red;
      blueLeds[circlingIndex[i]] = CRGB :: Blue;
      greenLeds[circlingIndex[i]] = CRGB :: Green;
      circlingIndex[i] = circlingIndex[i] + 3;
    }
  }
  FastLED.show();
  delay(200);
}

void loop()
{
  //updateLights();
  redState[index] = digitalRead(redSensor);   // read redSensor value
  blueState[index] = digitalRead(blueSensor); // read blueSensor value
  greenState[index] = digitalRead(greenSensor); // read greenSensor value
  if ((redState[index] == HIGH || greenState[index] == HIGH || blueState[index] == HIGH) && state[index] == LOW) {
    state[index] = HIGH;       // update the current individual led state to HIGH
  } else {
    updateLights();
  }

  if (state[index] == HIGH) {
    if (redState[index] == HIGH) {
      fireInDaHole(CRGB :: Red);
      addPoint(redState, CRGB :: Red);
    }
    if (greenState[index] == HIGH) {
      fireInDaHole(CRGB :: Green);
      addPoint(greenState, CRGB :: Green);
    }
    if (blueState[index] == HIGH) {
      fireInDaHole(CRGB :: Blue);
      addPoint(blueState, CRGB :: Blue);
    }
  }

  if (index == MAX_POINTS) {
    for (int i = 0; i < MAX_POINTS; i++) {
      pointLeds[i] = 0;
      index = 0;
    }
  }
}
