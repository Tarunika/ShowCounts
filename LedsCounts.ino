#include <FastLED.h>
#define DATA_PIN    3 
#define DATA_PIN1   6   //hole 1
#define DATA_PIN2   9   //hole 2 
#define DATA_PIN3   10  //hole 3     
#define COLOR_ORDER GRB       
#define NUM_LEDS   16              //The number of LEDs in the strip for count
#define NUM1_LEDS  20             //The number of LEDs in the strip for hole
#define NUM2_LEDS  20 
#define NUM3_LEDS  20 
#define LED_TYPE    WS2812B         
#define BRIGHTNESS          50     
int LEDbrightness;
int redSensor = 2;             
int greenSensor = 4;
int blueSensor = 5;
int state[NUM_LEDS] = {LOW};             
int redState[NUM_LEDS] = {0};            
int greenState[NUM_LEDS] = {0};          
int blueState[NUM_LEDS] = {0};         
int LedFlag = 0;
int index = 0;
CRGB leds[NUM_LEDS];
CRGB leds1[NUM1_LEDS];
CRGB leds2[NUM2_LEDS];
CRGB leds3[NUM3_LEDS];
void setup()
{
  pinMode(redSensor, INPUT);  
  pinMode(greenSensor, INPUT);   
  pinMode(blueSensor, INPUT);   
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.addLeds<LED_TYPE, DATA_PIN1, COLOR_ORDER>(leds1, NUM1_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.addLeds<LED_TYPE, DATA_PIN2, COLOR_ORDER>(leds2, NUM2_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.addLeds<LED_TYPE, DATA_PIN3, COLOR_ORDER>(leds3, NUM3_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(DATA_PIN1, OUTPUT);
  pinMode(DATA_PIN2, OUTPUT);
  pinMode(DATA_PIN3, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  redState[index] = digitalRead(redSensor);  
  blueState[index] = digitalRead(blueSensor);
  greenState[index] = digitalRead(greenSensor); 
  
  if ((redState[index] == HIGH ) && state[index] == LOW)            //hole 1
  {
    for(int x=80;x>=0;x--)
    {
    for(int i=0;i<20;i++)
    leds1[i] = CRGB ::Red;
    FastLED.show();  
    FastLED.setBrightness(x);
    delay(20);
    }
    state[index] = HIGH;       // update the current individual led state to HIGH
  }
if (( greenState[index] == HIGH ) && state[index] == LOW)              //hole 2
  {
      for(int x=80;x>=0;x--)
    {
    for(int i=0;i<20;i++)
    leds1[i] = CRGB ::Green;
    FastLED.show();  
    FastLED.setBrightness(x);
    delay(20);
    }
    state[index] = HIGH;       // update the current individual led state to HIGH
  }
 
if ((blueState[index] == HIGH) && state[index] == LOW)               //hole 3
  {
    for(int x=80;x>=0;x--)
    {
    for(int i=0;i<20;i++)
    leds1[i] = CRGB ::Blue;
    FastLED.show();  
    FastLED.setBrightness(x);
    delay(20);
    }
    state[index] = HIGH;       // update the current individual led state to HIGH
  }

  if (state[index] == HIGH) 
  {
    if (redState[index] == HIGH) 
    turnOn(redState, CRGB :: Red);
    if (greenState[index] == HIGH)
    turnOn(greenState, CRGB :: Green);
    if (blueState[index] == HIGH) 
    turnOn(blueState, CRGB :: Blue);
  }

  if (index + 1 == NUM_LEDS) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = 0;
      index = 0;
    }
  }
}




void turnOn(int colorState[], CRGB color) 
{
  leds[index] = color; 
  colorState[index] = LOW;
  FastLED.show();
  delay(4000);
  index = index + 1;
}
