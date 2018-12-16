#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 288
#define NUM_LEDS1 24

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define DATA_PIN1 4
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];
CRGB leds1[NUM_LEDS1];

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
      // Uncomment/edit one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
      FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
      FastLED.addLeds<WS2812B, DATA_PIN1, RGB>(leds1, NUM_LEDS1);
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
  	for( uint16_t i=0; i<NUM_LEDS; i++) {
  	  leds[i] = CRGB::Black;
  	  FastLED.show();
  	}
 	for( uint16_t i=0; i<NUM_LEDS1; i++) {
  	  leds1[i] = CRGB::Black;
  	  FastLED.show();
  	}

 	current_color = 0;
 	FastLED.setBrightness(0x80);
}

void loop() { 
	uint16_t i;

	for (i=0; i<NUM_LEDS1; i++) {
		leds1[i] = led_colors[i+(current_color % NB_COLOR)];
	}
	current_color += NUM_LEDS1;
	current_color %= NB_COLOR;
	FastLED.show();
	for (i=0; i<NUM_LEDS; i++) {
		leds[i] = CRGB::FairyLightNCC;
		FastLED.show();
	}


	delay(1000);
  	for( i=0; i<NUM_LEDS; i++) {
  	  leds[i] = CRGB::Black;
  	}
  	FastLED.show();

	for (i=0; i<NUM_LEDS; i++) {
			leds[i] = CRGB::FairyLightNCC;
			if (i>0) leds[i-1] = CRGB::Black;
			FastLED.show();
			delay(50);
		}
	delay(1000);
  	for( i=0; i<NUM_LEDS; i++) {
  	  leds[i] = CRGB::Black;
  	}
  	FastLED.show();
	delay(1000);

	uint32_t j;
	for (j=0; j<255; j++) {
		for( i=0; i<NUM_LEDS; i++) {
			leds[i] = 0x000000+j;
		}
		for (i=0; i<NUM_LEDS1; i++) {
			leds1[i] = 0x0000ff-j;
		}
		FastLED.show();
	}
	for (j=0; j<255; j++) {
		for( i=0; i<NUM_LEDS; i++) {
			leds[i] = 0x000000+(j<<8);
		}
		for (i=0; i<NUM_LEDS1; i++) {
			leds1[i] = 0x00ff00-(j<<8);
		}
		FastLED.show();
	}
	for (j=0; j<255; j++) {
		for( i=0; i<NUM_LEDS; i++) {
			leds[i] = 0x000000+(j<<16);
		}
		for (i=0; i<NUM_LEDS1; i++) {
			leds1[i] = 0xff0000-(j<<24);
		}

		FastLED.show();
	}


  	for(i=0; i< NB_COLOR; i++) {
  	  	for( j=0; j<NUM_LEDS; j++) {
  	  	  leds[j] = led_colors[i];
  	  	}
  	  	for( j=0; j<NUM_LEDS1; j++) {
  	  	  leds1[j] = led_colors[i];
  	  	}
  	  	FastLED.show();
  	  	delay(100);
  	}
  	for( i=0; i<NUM_LEDS; i++) {
  	  leds[i] = CRGB::Black;
  	}
  	FastLED.show();

}
