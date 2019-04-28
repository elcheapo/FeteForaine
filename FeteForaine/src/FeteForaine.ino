#include <Wire.h>
#include <SPI.h>
#include <FastLED.h>
#include <MD_YX5300.h>
#include <dcc_timer.h>
#include <ssd1306.h>
#include "nano_gfx.h"
#include "i2c_port.h"
#include "scenario.h"
#include "pixeltypes.h"

//#include "sova.h"

// How many leds in your strip?
#define NUM_LEDS1 144
#define NUM_LEDS2 12
#define NUM_LEDS3 1
#define NUM_LEDS4 1
#define NUM_LEDS5 1
#define NUM_LEDS6 1
#define NUM_LEDS7 1


// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN1 22
#define DATA_PIN2 23
#define DATA_PIN3 24
#define DATA_PIN4 25
#define DATA_PIN5 26
#define DATA_PIN6 27
#define DATA_PIN7 28

MD_YX5300 mp3(0,0);
bool bUseCallback = true; // use callbacks?
bool bUseSynch = false;   // use synchronous?

// Define 3 I2C extender
#define NB_I2C_PORT 3
I2c_Port i2c_ports[NB_I2C_PORT]= {I2c_Port(0x20), I2c_Port(0x21), I2c_Port(0x22)};


// Define the array of leds
CRGB leds1[NUM_LEDS1];
CRGB leds2[NUM_LEDS2];
CRGB leds3[NUM_LEDS3];
CRGB leds4[NUM_LEDS4];
CRGB leds5[NUM_LEDS5];
CRGB leds6[NUM_LEDS6];
CRGB leds7[NUM_LEDS7];

uint32_t current_time;
uint8_t led1_cycle;
uint8_t led2_cycle;
uint8_t led3_cycle;
uint8_t led4_cycle;
uint8_t led5_cycle;
uint8_t led6_cycle;
uint8_t led7_cycle;
uint8_t led8_cycle;

uint8_t current_color;

#include "helpers.h"

void setup() { 
	uint8_t i,ret;
	Serial.begin(230400);
	timer3.end();
	// MP3 init
	mp3.begin();
	setCallbackMode(bUseCallback);
	setSynchMode(bUseSynch);

	Serial.println(F("\nScanning I2C bus"));
	Wire.begin();
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

	// LCD Init
	/* Select the font to use with menu and all font functions */
    ssd1306_128x64_i2c_init();
    ssd1306_flipVertical(1);
    ssd1306_flipHorizontal(1);
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_clearScreen();
    ssd1306_printFixed(0,  8, "Normal text", STYLE_NORMAL);
    ssd1306_printFixed(0, 16, "Bold text", STYLE_BOLD);
    ssd1306_printFixed(0, 24, "Italic text", STYLE_ITALIC);
    ssd1306_negativeMode();
    ssd1306_printFixed(0, 32, "Inverted bold", STYLE_BOLD);
    ssd1306_positiveMode();
    delay(1000);

    // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<WS2812B, DATA_PIN1, RGB>(leds1, NUM_LEDS1);
    FastLED.addLeds<WS2812B, DATA_PIN2, GRB>(leds2, NUM_LEDS2);
    FastLED.addLeds<WS2812B, DATA_PIN3, RGB>(leds3, NUM_LEDS3);
    FastLED.addLeds<WS2812B, DATA_PIN4, RGB>(leds4, NUM_LEDS4);
    FastLED.addLeds<WS2812B, DATA_PIN5, RGB>(leds5, NUM_LEDS5);
    FastLED.addLeds<WS2812B, DATA_PIN6, RGB>(leds6, NUM_LEDS6);
    FastLED.addLeds<WS2812B, DATA_PIN7, RGB>(leds7, NUM_LEDS7);

    for( uint16_t i=0; i<NUM_LEDS1; i++) {
    	leds1[i] = CRGB::Black;
    }
 	for( uint16_t i=0; i<NUM_LEDS2; i++) {
  	  leds2[i] = CRGB::FairyLight;
  	}
 	FastLED.show();

 	current_color = 0;
 	FastLED.setBrightness(0xff);
 	/* Set button as input ports */
 	for( uint16_t i=0; i<5; i++) {
 	 	I2C_pinMode(10+i, INPUT);
 	 	I2C_pinMode(20+i, INPUT);
  	}
 	current_time=0;
 	led1_cycle = 0;
 	led2_cycle = 0;
 	led3_cycle = 0;
 	led4_cycle = 0;
 	led5_cycle = 0;
 	led6_cycle = 0;
 	led7_cycle = 0;
 	led8_cycle = 0;
 	led_string1.enable();
 	led_string2.enable();

 	for (uint8_t hue=0; hue < 255; hue++) {
 		FastLED.showColor(CHSV(hue, 255, 100));
 		delay(100);
 	}
 	for (uint8_t sat=0; sat < 255; sat++) {
 		FastLED.showColor(CHSV(0, sat, 100));
 		delay(100);
 	}
 	for (uint8_t bri=0; bri < 255; bri++) {
 		FastLED.showColor(CHSV(0, 255, bri));
 		delay(100);
 	}

}


void loop() { 
	uint16_t i;
	delay(500);
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
	led_string2.run();

	for (i=0; i<5; i++) {
		if (I2C_digitalRead(10+i) == 0) {
			Serial.print(F("Button "));
			Serial.println(10+i);
			I2C_digitalWrite(i, HIGH);
		} else {
			I2C_digitalWrite(i, LOW);
		}

		if (I2C_digitalRead(20+i) == 0) {
			Serial.print(F("Button "));
			Serial.println(20+i);
			I2C_digitalWrite(i+5, HIGH);
		} else {
			I2C_digitalWrite(i+5, LOW);
		}

	}


}
