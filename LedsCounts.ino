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
void loop()
{

  for (int i = 0; i < NUM_LEDS; ) {
    redState[i] = digitalRead(redSensor);   // read redSensor value
    blueState[i] = digitalRead(blueSensor); // read blueSensor value
    greenState[1] = digitalRead(greenSensor); // read greenSensor value
    if ((redState[i] == HIGH || greenState[i] == HIGH || blueState[i] == HIGH) && state[i] == LOW) {
       /*Serial.println("Motion detected!");*/
       state[i] = HIGH;       // update the current individual led state to HIGH
      }

    if (redState[i] == HIGH && state[i] == HIGH) {
      leds[i].r = 50;
      redState[i] = LOW; 
      FastLED.show();
      delay(2000);
      i = i + 1;
    } else if (greenState[i] == HIGH && state[i] == HIGH) {
      Serial.println("Green detected");
      leds[i].g = 100; 
      greenState[i] = LOW;
      delay(2000);
      FastLED.show();
      i = i + 1;
    } else if (blueState[i] == HIGH && state[i] == HIGH) {
      leds[i].b = 150;
      blueState[1] = LOW; 
      FastLED.show();
      delay(2000);
      i = i + 1;
    }

    /*FastLED.show();
    delay(2000);
    */

  /*  if (digitalRead(redSensor) == HIGH || digitalRead(greenSensor) == HIGH || digitalRead(blueSensor) == HIGH) {
      i = i + 1;
      Serial.print(i);
    }*/


  }

  for ( int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = 0;
  }


}
