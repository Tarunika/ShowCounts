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
int sensor = 2;              // the pin that the sensor is atteched to
int state[NUM_LEDS] = {LOW};             // by default, no motion detected
int val[NUM_LEDS] = {0};                 // variable to store the sensor status (value)
int LedFlag = 0;

// this creates an LED array to hold the values for each led in your strip
CRGB leds[NUM_LEDS];

void setup()
{

  // the wiki features a much more basic setup line:

  // initalize LED as an output

  pinMode(sensor, INPUT);    // initialize sensor as an input
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(DATA_PIN, OUTPUT);
  Serial.begin(9600);


}
void loop()
{

  for (int i = 0; i < NUM_LEDS; ) {
    val[i] = digitalRead(sensor);   // read sensor value
    if (val[i] == HIGH && state[i] == LOW) {
      Serial.println("Motion detected!");
      state[i] = HIGH;       // update variable state to HIGH
    }
    if (val[i] == HIGH && state[i] == HIGH) {           // check if the sensor is HIGH
      leds[i] = CRGB:: Green;   // turn LED ON
    }
    
    FastLED.show();
    delay(2000);

   if ( digitalRead(sensor) == HIGH){
    i = i+1;
    Serial.print(i);
   }
  

  }

  for( int i=0;i<NUM_LEDS;i++)
  {
    leds[i]= 0;
  }


}
