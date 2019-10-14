#include <FastLED.h>
// fast led constants
#define DATA_PIN    3
#define RED_PIN   6   // red output strip
#define GREEN_PIN   12   // green output strip
#define BLUE_PIN  10  // blue output strip    
#define COLOR_ORDER GRB      // if colors are mismatched; change this
#define MAX_POINTS    16       // change to the number of LEDs in your strip
#define amountOfLeds 37 //refers to the amount of leds circling around each hole
#define LED_TYPE    WS2812B
#define BRIGHTNESS          50


// change WS2812B to match your type of LED, if different
// list of supported types is here:
// https://github.com/FastLED/FastLED/wiki/Overview
int LEDbrightness;
int midSensor = 2;                        // the pin that the midSensor is atteched to
int leftSensor = 4;
int rightSensor = 5;
int state[MAX_POINTS] = {LOW};              // by default, no motion detected
int midState[MAX_POINTS] = {0};             // variable to store the midSensor status (value)
int leftState[MAX_POINTS] = {0};           // variable to Store the leftSensor status (value)
int rightState[MAX_POINTS] = {0};            // variable to store the rightSensor status (value)
int LedFlag = 0;
int index = 0;
int circlingIndex[3] = {0, 1, 2};
int prevIndex[3] = {0, 0, 0};

// this creates an LED array to hold the values for each led in your strip
CRGB pointLeds[MAX_POINTS];
CRGB midLeds[amountOfLeds];
CRGB leftLeds[amountOfLeds];
CRGB rightLeds[amountOfLeds];
CRGB colors[3] = {CRGB :: Red, CRGB :: Green, CRGB :: Blue};

void setup()
{

  // the wiki features a much more basic setup line:

  // initalize LED as an output
  pinMode(midSensor, INPUT);    // initialize midSensor as an input
  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(pointLeds, MAX_POINTS);
  FastLED.addLeds<LED_TYPE, RED_PIN, COLOR_ORDER>(midLeds, amountOfLeds);
  FastLED.addLeds<LED_TYPE, BLUE_PIN, COLOR_ORDER>(rightLeds, amountOfLeds);
  FastLED.addLeds<LED_TYPE, GREEN_PIN, COLOR_ORDER>(leftLeds, amountOfLeds);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));

}

void addPoint(int colorState[], CRGB color) {
  pointLeds[index] = color;
  colorState[index] = LOW;
  FastLED.show();
  delay(4000);
  index = index + 1;
}

void shuffleColors() {
  // Random number generator

  for (int i = 0; i < 3; i++) {
    int randomPosition = random(3);
    CRGB temp = colors[i]; //test, should be CRGB
    colors[i] = colors[randomPosition];
    colors[randomPosition] = temp;
  }
}

void fireInDaHole(CRGB color) {
  for (int i = 0; i < amountOfLeds; i++) {
    midLeds[i] = color;
    leftLeds[i] = color;
    rightLeds[i] = color;
  }
  FastLED.show();
  shuffleColors();
  delay(800);
}

void updateLights() {
  for (int i = amountOfLeds - 1; i > amountOfLeds - 3; i--) {
    midLeds[i] = 0;
    leftLeds[i] = 0;
    rightLeds[i] = 0;
  }
  for (int i = 0; i < 3; i++) {
    midLeds[prevIndex[i]] = 0;
    rightLeds[prevIndex[i]] = 0;
    leftLeds[prevIndex[i]] = 0;
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
      midLeds[circlingIndex[i]] = colors[0];
      leftLeds[circlingIndex[i]] = colors[1];
      rightLeds[circlingIndex[i]] = colors[2];
      circlingIndex[i] = circlingIndex[i] + 3;
    }
  }
  FastLED.show();
  delay(200);
}

void loop()
{
  //updateLights();
  midState[index] = digitalRead(midSensor);   // read midSensor value
  rightState[index] = digitalRead(rightSensor); // read rightSensor value
  leftState[index] = digitalRead(leftSensor); // read leftSensor value
  if ((midState[index] == HIGH || leftState[index] == HIGH || rightState[index] == HIGH) && state[index] == LOW) {
    state[index] = HIGH;       // update the current individual led state to HIGH
  } else {
    updateLights();
  }

  if (state[index] == HIGH) {
    if (midState[index] == HIGH) {
      CRGB prevColor = colors[0];
      fireInDaHole(prevColor);
      addPoint(midState, prevColor);
    }
    if (leftState[index] == HIGH) {
      CRGB prevColor = colors[1];
      fireInDaHole(prevColor);
      addPoint(leftState, prevColor);
    }
    if (rightState[index] == HIGH) {
      CRGB prevColor = colors[2];
      fireInDaHole(prevColor);
      addPoint(rightState, prevColor);
    }
  }

  if (index == MAX_POINTS) {
    for (int i = 0; i < MAX_POINTS; i++) {
      pointLeds[i] = 0;
      index = 0;
    }
  }
}
