#include <Wire.h>
#include <SPI.h>
#include <FastLED.h>
#include <MD_YX5300.h>
#include <dcc_timer.h>
#include <ssd1306.h>
#include "nano_gfx.h"
#include "i2c_port.h"
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

// Define 5 I2C extender
I2c_Port i2c_port1(0x20);
I2c_Port i2c_port2(0x21);
I2c_Port i2c_port3(0x22);

void cbResponse(const MD_YX5300::cbData *status)
// Used to process device responses either as a library callback function
// or called locally when not in callback mode.
{
  if (bUseCallback)
    Serial.print(F("\nCback status: "));
  else
    Serial.print(F("\nSync Status: "));

  switch (status->code)
  {
  case MD_YX5300::STS_OK:         Serial.print(F("STS_OK"));         break;
  case MD_YX5300::STS_TIMEOUT:    Serial.print(F("STS_TIMEOUT"));    break;
  case MD_YX5300::STS_VERSION:    Serial.print(F("STS_VERSION"));    break;
  case MD_YX5300::STS_CHECKSUM:   Serial.print(F("STS_CHECKSUM"));    break;
  case MD_YX5300::STS_TF_INSERT:  Serial.print(F("STS_TF_INSERT"));  break;
  case MD_YX5300::STS_TF_REMOVE:  Serial.print(F("STS_TF_REMOVE"));  break;
  case MD_YX5300::STS_ERR_FILE:   Serial.print(F("STS_ERR_FILE"));   break;
  case MD_YX5300::STS_ACK_OK:     Serial.print(F("STS_ACK_OK"));     break;
  case MD_YX5300::STS_FILE_END:   Serial.print(F("STS_FILE_END"));   break;
  case MD_YX5300::STS_INIT:       Serial.print(F("STS_INIT"));       break;
  case MD_YX5300::STS_STATUS:     Serial.print(F("STS_STATUS"));     break;
  case MD_YX5300::STS_EQUALIZER:  Serial.print(F("STS_EQUALIZER"));  break;
  case MD_YX5300::STS_VOLUME:     Serial.print(F("STS_VOLUME"));     break;
  case MD_YX5300::STS_TOT_FILES:  Serial.print(F("STS_TOT_FILES"));  break;
  case MD_YX5300::STS_PLAYING:    Serial.print(F("STS_PLAYING"));    break;
  case MD_YX5300::STS_FLDR_FILES: Serial.print(F("STS_FLDR_FILES")); break;
  case MD_YX5300::STS_TOT_FLDR:   Serial.print(F("STS_TOT_FLDR"));   break;
  default: Serial.print(F("STS_??? 0x")); Serial.print(status->code, HEX); break;
  }

  Serial.print(F(", 0x"));
  Serial.print(status->data, HEX);
}


void setCallbackMode(bool b)
{
  bUseCallback = b;
  Serial.print(F("\n>Callback "));
  Serial.print(b ? F("ON") : F("OFF"));
  mp3.setCallback(b ? cbResponse : nullptr);
}

void setSynchMode(bool b)
{
  bUseSynch = b;
  Serial.print(F("\n>Synchronous "));
  Serial.print(b ? F("ON") : F("OFF"));
  mp3.setSynchronous(b);
}


// Define the array of leds
CRGB leds1[NUM_LEDS1];
CRGB leds2[NUM_LEDS2];
CRGB leds3[NUM_LEDS3];
CRGB leds4[NUM_LEDS4];
CRGB leds5[NUM_LEDS5];
CRGB leds6[NUM_LEDS6];
CRGB leds7[NUM_LEDS7];

CRGB::HTMLColorCode led_colors[]= {
        CRGB::AliceBlue,
        CRGB::Amethyst,
        CRGB::AntiqueWhite,
        CRGB::Aqua,
        CRGB::Aquamarine,
        CRGB::Azure,
        CRGB::Beige,
        CRGB::Bisque,
        CRGB::Black,
        CRGB::BlanchedAlmond,
        CRGB::Blue,
        CRGB::BlueViolet,
        CRGB::Brown,
        CRGB::BurlyWood,
        CRGB::CadetBlue,
        CRGB::Chartreuse,
        CRGB::Chocolate,
        CRGB::Coral,
        CRGB::CornflowerBlue,
        CRGB::Cornsilk,
        CRGB::Crimson,
        CRGB::Cyan,
        CRGB::DarkBlue,
        CRGB::DarkCyan,
        CRGB::DarkGoldenrod,
        CRGB::DarkGray,
        CRGB::DarkGrey,
        CRGB::DarkGreen,
        CRGB::DarkKhaki,
        CRGB::DarkMagenta,
        CRGB::DarkOliveGreen,
        CRGB::DarkOrange,
        CRGB::DarkOrchid,
        CRGB::DarkRed,
        CRGB::DarkSalmon,
        CRGB::DarkSeaGreen,
        CRGB::DarkSlateBlue,
        CRGB::DarkSlateGray,
        CRGB::DarkSlateGrey,
        CRGB::DarkTurquoise,
        CRGB::DarkViolet,
        CRGB::DeepPink,
        CRGB::DeepSkyBlue,
        CRGB::DimGray,
        CRGB::DimGrey,
        CRGB::DodgerBlue,
        CRGB::FireBrick,
        CRGB::FloralWhite,
        CRGB::ForestGreen,
        CRGB::Fuchsia,
        CRGB::Gainsboro,
        CRGB::GhostWhite,
        CRGB::Gold,
        CRGB::Goldenrod,
        CRGB::Gray,
        CRGB::Grey,
        CRGB::Green,
        CRGB::GreenYellow,
        CRGB::Honeydew,
        CRGB::HotPink,
        CRGB::IndianRed,
        CRGB::Indigo,
        CRGB::Ivory,
        CRGB::Khaki,
        CRGB::Lavender,
        CRGB::LavenderBlush,
        CRGB::LawnGreen,
        CRGB::LemonChiffon,
        CRGB::LightBlue,
        CRGB::LightCoral,
        CRGB::LightCyan,
        CRGB::LightGoldenrodYellow,
        CRGB::LightGreen,
        CRGB::LightGrey,
        CRGB::LightPink,
        CRGB::LightSalmon,
        CRGB::LightSeaGreen,
        CRGB::LightSkyBlue,
        CRGB::LightSlateGray,
        CRGB::LightSlateGrey,
        CRGB::LightSteelBlue,
        CRGB::LightYellow,
        CRGB::Lime,
        CRGB::LimeGreen,
        CRGB::Linen,
        CRGB::Magenta,
        CRGB::Maroon,
        CRGB::MediumAquamarine,
        CRGB::MediumBlue,
        CRGB::MediumOrchid,
        CRGB::MediumPurple,
        CRGB::MediumSeaGreen,
        CRGB::MediumSlateBlue,
        CRGB::MediumSpringGreen,
        CRGB::MediumTurquoise,
        CRGB::MediumVioletRed,
        CRGB::MidnightBlue,
        CRGB::MintCream,
        CRGB::MistyRose,
        CRGB::Moccasin,
        CRGB::NavajoWhite,
        CRGB::Navy,
        CRGB::OldLace,
        CRGB::Olive,
        CRGB::OliveDrab,
        CRGB::Orange,
        CRGB::OrangeRed,
        CRGB::Orchid,
        CRGB::PaleGoldenrod,
        CRGB::PaleGreen,
        CRGB::PaleTurquoise,
        CRGB::PaleVioletRed,
        CRGB::PapayaWhip,
        CRGB::PeachPuff,
        CRGB::Peru,
        CRGB::Pink,
        CRGB::Plaid,
        CRGB::Plum,
        CRGB::PowderBlue,
        CRGB::Purple,
        CRGB::Red,
        CRGB::RosyBrown,
        CRGB::RoyalBlue,
        CRGB::SaddleBrown,
        CRGB::Salmon,
        CRGB::SandyBrown,
        CRGB::SeaGreen,
        CRGB::Seashell,
        CRGB::Sienna,
        CRGB::Silver,
        CRGB::SkyBlue,
        CRGB::SlateBlue,
        CRGB::SlateGray,
        CRGB::SlateGrey,
        CRGB::Snow,
        CRGB::SpringGreen,
        CRGB::SteelBlue,
        CRGB::Tan,
        CRGB::Teal,
        CRGB::Thistle,
        CRGB::Tomato,
        CRGB::Turquoise,
        CRGB::Violet,
        CRGB::Wheat,
        CRGB::White,
        CRGB::WhiteSmoke,
        CRGB::Yellow,
        CRGB::YellowGreen,

        // LED RGB color that roughly approximates
        // the color of incandescent fairy lights,
        // assuming that you're using FastLED
        // color correction on your LEDs (recommended).
        CRGB::FairyLight,
        // If you are using no color correction, use this
        CRGB::FairyLightNCC

};
#define NB_COLOR (sizeof(led_colors)/4)
uint8_t current_color;

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
    delay(3000);

      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
      FastLED.addLeds<WS2812B, DATA_PIN1, RGB>(leds1, NUM_LEDS1);
      FastLED.addLeds<WS2812B, DATA_PIN2, RGB>(leds2, NUM_LEDS2);
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
}

void loop() { 
	mp3.check();
	uint16_t i;

	for (i=0; i<NUM_LEDS1; i++) {
		leds1[i] = led_colors[i+(current_color % NB_COLOR)];
	}
	current_color += NUM_LEDS1;
	current_color %= NB_COLOR;
	FastLED.show();
	for (i=0; i<NUM_LEDS1; i++) {
		leds1[i] = CRGB::FairyLightNCC;
		FastLED.show();
	}


	delay(1000);
  	for( i=0; i<NUM_LEDS1; i++) {
  	  leds1[i] = CRGB::Black;
  	}
  	FastLED.show();

	for (i=0; i<NUM_LEDS1; i++) {
			leds1[i] = CRGB::FairyLightNCC;
			if (i>0) leds1[i-1] = CRGB::Black;
			FastLED.show();
			delay(50);
		}
	delay(1000);
  	for( i=0; i<NUM_LEDS1; i++) {
  	  leds1[i] = CRGB::Black;
  	}
  	FastLED.show();
	delay(1000);

	uint32_t j;
	for (j=0; j<255; j++) {
		for( i=0; i<NUM_LEDS1; i++) {
			leds1[i] = 0x000000+j;
		}
		FastLED.show();
	}
	for (j=0; j<255; j++) {
		for( i=0; i<NUM_LEDS1; i++) {
			leds1[i] = 0x000000+(j<<8);
		}
		for (i=0; i<NUM_LEDS1; i++) {
			leds1[i] = 0x00ff00-(j<<8);
		}
		FastLED.show();
	}
	for (j=0; j<255; j++) {
		for( i=0; i<NUM_LEDS1; i++) {
			leds1[i] = 0x000000+(j<<16);
		}
		FastLED.show();
	}


  	for(i=0; i< NB_COLOR; i++) {
  	  	for( j=0; j<NUM_LEDS1; j++) {
  	  	  leds1[j] = led_colors[i];
  	  	}
  	  	FastLED.show();
  	  	delay(100);
  	}
  	for( i=0; i<NUM_LEDS1; i++) {
  	  leds1[i] = CRGB::Black;
  	}
  	FastLED.show();

}
