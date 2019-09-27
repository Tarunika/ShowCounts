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
int fsrAnalogPin = 0; // FSR is connected to analog 0
int LEDpin = 11;      // connect Red LED to pin 11 (PWM pin)
int fsrReading;      // the analog reading from the FSR resistor divider
int LEDbrightness;



// this creates an LED array to hold the values for each led in your strip
CRGB leds[NUM_LEDS];

void setup()
{
  
  // the wiki features a much more basic setup line:
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(LEDpin, OUTPUT);
  Serial.begin(9600);


}
void loop() 
{
    fsrReading = analogRead(fsrAnalogPin);
  Serial.print("Analog reading = ");
  Serial.println(fsrReading);
 
  // we'll need to change the range from the analog reading (0-1023) down to the range
  // used by analogWrite (0-255) with map!
  //LEDbrightness = map(fsrReading, 0, 1023, 0, 255);
  // LED gets brighter the harder you press
  //analogWrite(LEDpin, LEDbrightness);
  leds[0] = CRGB :: Green;
 
  //delay(10);

  if(fsrReading > 0){
    for( int i = 1; i<7; i++){
      
      leds[i] = CRGB :: Green;
    }
   // EVERY_N_SECONDS( 10 ) { nextPattern(); }
  

  }
  else {
    for( int i = 0; i<7; i++){
      
      leds[i] = 0;
    }
    
  }
  
  
  
//  leds[0] = CRGB::Red;
//  leds[1] = CRGB::Red;
//
//  leds[2] = CRGB::Green;
//  leds[3] = CRGB::Blue;

  FastLED.show();

 // delay(50);
}
void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  int i=0;
  for(i=0;i<7;i++)
  {
    if(leds[i].r){
      leds[i] = CRGB::Green;
    }
    else if(leds[i].g){
      leds[i] = CRGB::Blue;
    }
    else{
      leds[i] = CRGB::Red;
  }
  }
  
}
