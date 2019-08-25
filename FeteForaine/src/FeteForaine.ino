#include <Wire.h>
#include <SPI.h>
#include <FastLED.h>
#include <MD_YX5300.h>
#include <dcc_timer.h>
//#include <ssd1306.h>
//#include "nano_gfx.h"
#include "i2c_port.h"
#include "scenario.h"
#include "pixeltypes.h"

//#include "sova.h"


#define CURRENT_DETECT 41
// How many leds in your strip?
// Mas de cocagne 24+16, 12
#define NUM_LEDS1 52
// Palais des mirages (2) / Palais des glaces (3) + courone grande roue (12)
#define NUM_LEDS2 15
// grande roue gauche
#define NUM_LEDS3 26
// Grande roue droite
#define NUM_LEDS4 26
// Petit bandeau - 40 ?
#define NUM_LEDS5 57
// Grand bandeau 144
#define NUM_LEDS6 144

//#define NUM_LEDS7 50

#define FET1 45
#define FET2 44
#define FET3 43
#define FET4 42

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN1 22
#define DATA_PIN2 23
#define DATA_PIN3 24
#define DATA_PIN4 25
#define DATA_PIN5 26
#define DATA_PIN6 27
//#define DATA_PIN7 28

MD_YX5300 mp3(0,0);
bool bUseCallback = true; // use callbacks?
bool bUseSynch = false;   // use synchronous?

// Define 3 I2C extender
#define NB_I2C_PORT 4
I2c_Port i2c_ports[NB_I2C_PORT]= {I2c_Port(0x20), I2c_Port(0x21), I2c_Port(0x22), I2c_Port(0x23)};

uint8_t led1_cycle;
uint8_t led21_cycle;
uint8_t led22_cycle;
uint8_t led34_cycle;
uint8_t led5_cycle;
uint8_t led6_cycle;
uint8_t train_cycle;

// Define the array of leds
CRGB leds1[NUM_LEDS1];
CRGB leds2[NUM_LEDS2];
CRGB leds3[NUM_LEDS3];
CRGB leds4[NUM_LEDS4];
CRGB leds5[NUM_LEDS5];
CRGB leds6[NUM_LEDS6];
//CRGB leds7[NUM_LEDS7];

uint32_t current_time;

uint8_t current_color;

#include "helpers.h"
void setup() { 
	uint8_t i,ret;
	Wire.begin();
	// Turn Off Relays
	Wire.beginTransmission(0x20); // transmit to PCF8574
	Wire.write(0x00); // make sure we are not changing "input" pins
	Wire.endTransmission();

	pinMode(CURRENT_DETECT, INPUT);           // set pin to input for current detector
	digitalWrite(CURRENT_DETECT, HIGH);       // turn on pullup resistors

	Serial.begin(230400);
	timer3.end();
	// MP3 init
	mp3.begin();
	setCallbackMode(bUseCallback);
	setSynchMode(bUseSynch);

	Serial.println(F("\nScanning I2C bus"));
	for (i=1; i<127; i++) {
		// scan I2C bus
		Wire.beginTransmission(i); // transmit to PCF8574
		ret = Wire.endTransmission();
		if (ret == 0) {
			Serial.print(F("I2C dev at address : 0x"));
			Serial.println(i,16);
		}
	}
	Serial.println(F("Done"));

    // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<WS2812B, DATA_PIN1, GRB>(leds1, NUM_LEDS1);
    FastLED.addLeds<WS2812B, DATA_PIN2, GRB>(leds2, NUM_LEDS2);
    FastLED.addLeds<WS2812B, DATA_PIN3, GRB>(leds3, NUM_LEDS3);
    FastLED.addLeds<WS2812B, DATA_PIN4, RGB>(leds4, NUM_LEDS4);
    FastLED.addLeds<WS2812B, DATA_PIN5, RGB>(leds5, NUM_LEDS5);
    FastLED.addLeds<WS2812B, DATA_PIN6, RGB>(leds6, NUM_LEDS6);
//    FastLED.addLeds<WS2812B, DATA_PIN7, RGB>(leds7, NUM_LEDS7);

    leds1[0] = CRGB::Red;
    leds1[1] = CRGB::Green;
    leds1[2] = CRGB::Blue;
    leds2[0] = CRGB::Red;
    leds2[1] = CRGB::Green;
    leds2[2] = CRGB::Blue;
    leds3[0] = CRGB::Red;
    leds3[1] = CRGB::Green;
    leds3[2] = CRGB::Blue;
    leds4[0] = CRGB::Red;
    leds4[1] = CRGB::Green;
    leds4[2] = CRGB::Blue;
    leds5[0] = CRGB::Red;
    leds5[1] = CRGB::Green;
    leds5[2] = CRGB::Blue;
    leds6[0] = CRGB::Red;
    leds6[1] = CRGB::Green;
    leds6[2] = CRGB::Blue;
 	FastLED.show();

    delay(2000);

    for( uint16_t i=0; i<NUM_LEDS1; i++) {
    	leds1[i] = CRGB::Black;
    }
 	for( uint16_t i=0; i<NUM_LEDS2; i++) {
  	  leds2[i] = CRGB::Black;
  	}
    for( uint16_t i=0; i<NUM_LEDS3; i++) {
    	leds3[i] = CRGB::Black;
    	leds4[i] = CRGB::Black;
    }
    for( uint16_t i=0; i<NUM_LEDS5; i++) {
    	leds5[i] = CRGB::Black;
    }
    for( uint16_t i=0; i<NUM_LEDS6; i++) {
    	leds6[i] = CRGB::Black;
    }

 	FastLED.show();

 	current_color = 0;
 	FastLED.setBrightness(0xff);
 	/* Set button as input ports */
 	for( uint16_t i=0; i<5; i++) {
 	 	I2C_pinMode(10+i, INPUT);
 	 	I2C_pinMode(20+i, INPUT);
 	 	I2C_pinMode(30+i, INPUT);
  	}

 	for (uint8_t i = 0; i < NB_I2C_PORT; i++) {
 		i2c_ports[i].set_input_i2c();
 	}

 	current_time=0;
 	train_cycle = 0;

 	led_string1.init();
 	led_string21.init();
 	led_string22.init();
 	led_string34.init();
 	led_string5.init();
 	led_string6.init();

 	led_string1.enable(led1_cycle);
 	led_string21.enable(led21_cycle);
 	led_string22.enable(led22_cycle);
 	led_string34.enable(led34_cycle);
 	led_string5.enable(led5_cycle);
 	led_string6.enable(led6_cycle);
 	train_control.enable(train_cycle);

 	for (uint8_t hue=0; hue < 255; hue++) {
 		FastLED.showColor(CHSV(hue, 255, 180));
 		delay(10);
 	}
 	/* Turn on FET */
 	pinMode(FET1,OUTPUT);
 	pinMode(FET2,OUTPUT);
 	pinMode(FET3,OUTPUT);
 	pinMode(FET4,OUTPUT);
 	digitalWrite(FET1, LOW);
 	digitalWrite(FET2, HIGH);
 	digitalWrite(FET3, LOW);
 	digitalWrite(FET4, HIGH);

 	delay (1000);

}


void loop() { 
	uint16_t i;
	delay(20);
//	Serial.println('L');
	/* All the background processing */
	current_time = millis();
	// MP3 player
	mp3.check();

	// Update I2C ports vales
	for (i=0; i<NB_I2C_PORT; i++) {
//		Serial.println(i);
		i2c_ports[i].read_i2c();
		i2c_ports[i].write_i2c();
	}
	FastLED.show();

	/* end of "background tasks */
	led_string1.run();
	led_string21.run();
	led_string22.run();
	led_string34.run();
	led_string5.run();
	led_string6.run();
	train_control.run();

	for (i=0; i<5; i++) {
		if (I2C_digitalRead(10+i) == 0) {
			Serial.print(F("Button "));
			Serial.println(10+i);
			mp3.playTrackRepeat(i+6);
		}

		if (I2C_digitalRead(20+i) == 0) {
			Serial.print(F("Button "));
			Serial.println(20+i);
			I2C_digitalWrite(i+5, HIGH);
			mp3.playTrackRepeat(i+1);
		} else {
			I2C_digitalWrite(i+5, LOW);
		}
		if (I2C_digitalRead(30+i) == 0) {
			Serial.print(F("Button "));
			Serial.println(30+i);
			I2C_digitalWrite(i+5, HIGH);
			mp3.playTrackRepeat(i+1);
		} else {
			I2C_digitalWrite(i+1, LOW);
		}

	}


}
