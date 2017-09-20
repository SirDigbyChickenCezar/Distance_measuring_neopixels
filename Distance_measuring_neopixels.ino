#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

#include <FastLED.h>
#define LED_PIN     2
#define NUM_LEDS    60
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

long a;
int b;

void setup() {
   delay( 3000 ); // power-up safety delay
   FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
   FastLED.setBrightness(  BRIGHTNESS );
   Serial.begin(9600);
   for (int i = 0; i<NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
   }
   delay(1000);
}

void loop() {
   a=sr04.Distance();
   Serial.println(a);
   //Serial.println("cm");
   a = int(a);

   
   if (a>NUM_LEDS) {
       b = a - NUM_LEDS;
       if (b>NUM_LEDS) {
        b = NUM_LEDS;
       }
       for (int i = 0; i<b; i++) {
        leds[i] = CRGB::Red;
       }
       if (b<NUM_LEDS) {
           for (int i = b; i<NUM_LEDS; i++) {
            leds[i] = CRGB::Blue;
           }
       }
   }
   else {
       for( int i = a; i < NUM_LEDS; i++) {
          leds[i] = CRGB::Black;
       }
       for( int i = 0; i < a; i++) {
          leds[i] = CRGB::Blue;
       }
   }
   FastLED.show();
   delay(10);
   
   }
