#include "Arduino.h"
#include <FastLED.h>
#include <MD_YX5300.h>

#include "i2c_port.h"
#include "scenario.h"
#include "actions.h"

const uint8_t action0 PROGMEM = 0;
const uint8_t action1 PROGMEM = 0;
const uint8_t action2 PROGMEM = 0;
const uint8_t action3 PROGMEM = 0;
const uint8_t action4 PROGMEM = 0;
const uint8_t action5 PROGMEM = 0;
const uint8_t action6 PROGMEM = 0;
const uint8_t action7 PROGMEM = 0;
const uint8_t action8 PROGMEM = 0;
const uint8_t action9 PROGMEM = 0;
const uint8_t action10 PROGMEM = 0;
const uint8_t action11 PROGMEM = 0;
const uint8_t action12 PROGMEM = 0;

const uint8_t * actions[]={&action1,&action2,&action3,&action4,&action5,&action6,&action7,&action8,&action9,&action10,&action11,&action12};

#define NB_SCENARIO 12

scenario scenarii[] = {scenario(&action0), scenario(&action1), scenario(&action2), scenario(&action3), scenario(&action4),
		scenario(&action5),	scenario(&action6), scenario(&action7), scenario(&action8), scenario(&action9), scenario(&action10),
		scenario(&action11), scenario(&action12)};

#define LED_STRING_COUNT 5

// How many leds in your strips?

#define LED_COUNT_0 144
#define LED_COUNT_1 26
#define LED_COUNT_2 26
#define LED_COUNT_3 12
#define LED_COUNT_4 50

const uint8_t led_count[] = {LED_COUNT_0, LED_COUNT_1, LED_COUNT_2, LED_COUNT_3, LED_COUNT_4};

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.

#define LED_PIN_0 3
#define LED_PIN_1 4
#define LED_PIN_2 50
#define LED_PIN_3 51
#define LED_PIN_4 52

const uint8_t led_pins[] = {LED_PIN_0, LED_PIN_1, LED_PIN_2, LED_PIN_3, LED_PIN_4};

// Define 2 I2C extender
I2c_Port i2c_ports[2]= {I2c_Port(0x20), I2c_Port(0x21)};

void I2C_digitalWrite(uint8_t pin, uint8_t value){
	uint8_t port = pin / 10;
	uint8_t pin_mask = pin % 10;
	if (value == HIGH){
		i2c_ports[port].set_mask(1<<pin_mask);
	} else {
		i2c_ports[port].clear_mask(1<<pin_mask);
	}
}
uint8_t I2C_digitalRead(uint8_t pin){
	uint8_t port = pin / 10;
	uint8_t pin_mask = pin % 10;
	uint8_t data = i2c_ports[port].read();
	data &= (1<<pin_mask);
	if (data != 0) return HIGH; else return LOW;
}
void I2C_pinMode(uint8_t pin, uint8_t mode){
	uint8_t port = pin / 10;
	uint8_t pin_mask = pin % 10;
	if (mode != OUTPUT) {
		i2c_ports[port].set_input(1<<pin_mask);
	}
}

#define NB_COLOR (sizeof(led_colors)/4)
uint8_t current_color;

// Define the array of led strings

CRGB leds0[LED_COUNT_0];
CRGB leds1[LED_COUNT_1];
CRGB leds2[LED_COUNT_2];
CRGB leds3[LED_COUNT_3];
CRGB leds4[LED_COUNT_4];

CRGB * led_array[] = {&leds0[0], &leds1[0], &leds2[0], &leds3[0], &leds4[0]};


void setup() {
      // Uncomment/edit one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
      FastLED.addLeds<WS2812B, LED_PIN_0, RGB>(leds0, LED_COUNT_0);
      FastLED.addLeds<WS2812B, LED_PIN_1, RGB>(leds1, LED_COUNT_1);
      FastLED.addLeds<WS2812B, LED_PIN_2, RGB>(leds2, LED_COUNT_2);
      FastLED.addLeds<WS2812B, LED_PIN_3, RGB>(leds3, LED_COUNT_3);
      FastLED.addLeds<WS2812B, LED_PIN_4, RGB>(leds4, LED_COUNT_4);
  	  // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
      // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);

      // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, RGB>(leds, NUM_LEDS);

      // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);


  	for( uint8_t i=0; i<LED_STRING_COUNT; i++) {
  		for (uint8_t j=0; j < led_count[i]; j++) {
  			*(led_array[i]+j) = CRGB::Black;

  		}
  	FastLED.show();
  	}
}
void loop() {
	for (uint8_t i=0; i<NB_SCENARIO; i++) {
		scenarii[i].run();

	}

}
