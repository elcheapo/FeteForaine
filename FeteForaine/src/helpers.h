/*
 * helpers.h
 *
 *  Created on: Jan 3, 2019
 *      Author: francois
 */

#ifndef SRC_HELPERS_H_
#define SRC_HELPERS_H_

// I2C helpers
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
	uint8_t port = pin  / 10;
	uint8_t pin_mask = pin % 10;
	uint8_t data = i2c_ports[port].read();
#if 0
	Serial.print(F("I2C digital Read :"));
	Serial.print(port,16);
	Serial.print(F(" / "));
	Serial.print(pin_mask,16);
	Serial.print(F(" / "));
	Serial.print(data,16);
#endif
	data &= (1<<pin_mask);
#if 0
	Serial.print(F(" / "));
	Serial.println(data,16);
#endif
	if (data != 0) return HIGH; else return LOW;
}
void I2C_pinMode(uint8_t pin, uint8_t mode){
	uint8_t port = pin / 10;
	uint8_t pin_mask = pin % 10;
	if (mode != OUTPUT) {
		i2c_ports[port].set_input(1<<pin_mask);
	}
}

/*********************************************************************************/
// Mas de cocagne 40 + 12 / led1
void init1 (void){
	for (uint8_t i=0; i<NUM_LEDS1; i++) {
		leds1[i] = CRGB::Black;
	}
	led1_cycle=0;
}
void up1_led( uint8_t start) {
	uint8_t i;
	for( i=0; i<NUM_LEDS1 ; i++) {
		leds1[i] = CRGB::Black;
	}
	leds1[start] = CRGB::Red;
	if (start < NUM_LEDS1 - 1)
		leds1[(start+1) % NUM_LEDS1] = CRGB::Green;
	if (start < NUM_LEDS1 - 2)
		leds1[(start+2) % NUM_LEDS1] = CRGB::Blue;
}

uint32_t update_led1(void) {
	switch (led1_cycle) {
	case 0:
		break;
	case NUM_LEDS1:
		up1_led(NUM_LEDS1-1);
		led1_cycle = 1;
		return 300;
		break;
	default:
		up1_led(led1_cycle-1);
		led1_cycle++;
		return 300;
		break;
	}
return 0;
}

scenario led_string1(&init1, &update_led1);



/************************************************************************************************/
// Scenario for string 21 - Palais des mirages 2 LED leds2[0], leds2[1]

void init21(void) {
	leds2[0] = CRGB::Black;
	leds2[1] = CRGB::Black;
	led21_cycle=0;
}
uint32_t update_led21(void) {
	switch (led21_cycle) {
	case 0:
		break;
	case 1:
		leds2[0] = CRGB::Red;
		leds2[1] = CRGB::Yellow;
		led21_cycle ++;
		return 500;
		break;
	case 2:
		leds2[0] = CRGB::Yellow;
		leds2[1] = CRGB::Red;
		led21_cycle ++;
		return 500;
		break;
	case 3:
		leds2[0] = CRGB::Yellow;
		leds2[1] = CRGB::Green;
		led21_cycle ++;
		return 500;
		break;
	case 4:
		leds2[0] = CRGB::Green;
		leds2[1] = CRGB::Blue;
		led21_cycle ++;
		return 500;
		break;
	case 5:
		leds2[0] = CRGB::Blue;
		leds2[1] = CRGB::Cyan;
		led21_cycle ++;
		return 500;
		break;
	case 6:
		leds2[0] = CRGB::Cyan;
		leds2[1] = CRGB::OrangeRed;
		led21_cycle ++;
		return 500;
		break;
	case 7:
		leds2[0] = CRGB::OrangeRed;
		leds2[1] = CRGB::Orange;
		led21_cycle ++;
		return 500;
		break;
	case 8:
		leds2[0] = CRGB::Orange;
		leds2[1] = CRGB::Pink;
		led21_cycle ++;
		return 500;
		break;
	case 9:
		leds2[0] = CRGB::Pink;
		leds2[1] = CRGB::Azure;
		led21_cycle ++;
		return 500;
		break;
	default:
		leds2[0] = CRGB::Azure;
		leds2[1] = CRGB::Red;
		led21_cycle = 1;
		return 500;
		break;

	}
return 0;
}

scenario led_string21(&init21, &update_led21);

/************************************************************************************************/
// Scenario for string 2 - Palais des glaces 3

#define DELAY22 400

void init22(void) {
	leds2[2] = CRGB::Black;
	leds2[3] = CRGB::Black;
	leds2[4] = CRGB::Black;
	led22_cycle=0;
}
uint32_t update_led22(void) {
	switch (led22_cycle) {
	case 0:
		break;
	case 1:
		leds2[2] = CRGB::Blue;
		leds2[3] = CRGB::Blue;
		leds2[4] = CRGB::Blue;
		led22_cycle ++;
		return DELAY22;
		break;
	case 2:
		leds2[2] = CRGB::Cyan;
		leds2[3] = CRGB::Cyan;
		leds2[4] = CRGB::Cyan;
		led22_cycle ++;
		return DELAY22;
		break;
	case 3:
		leds2[2] = CRGB::AliceBlue;
		leds2[3] = CRGB::AliceBlue;
		leds2[4] = CRGB::AliceBlue;
		led22_cycle ++;
		return DELAY22;
		break;
	case 4:
		leds2[2] = CRGB::Aqua;
		leds2[3] = CRGB::Aqua;
		leds2[4] = CRGB::Aqua;
		led22_cycle ++;
		return DELAY22;
		break;
	case 5:
		leds2[2] = CRGB::CadetBlue;
		leds2[3] = CRGB::CadetBlue;
		leds2[4] = CRGB::CadetBlue;
		led22_cycle ++;
		return DELAY22;
		break;
	case 6:
		leds2[2] = CRGB::Aquamarine;
		leds2[3] = CRGB::Aquamarine;
		leds2[4] = CRGB::Aquamarine;
		led22_cycle ++;
		return DELAY22;
		break;
	case 7:
		leds2[2] = CRGB::DarkBlue;
		leds2[3] = CRGB::DarkBlue;
		leds2[4] = CRGB::DarkBlue;
		led22_cycle ++;
		return DELAY22;
		break;
	case 8:
		leds2[2] = CRGB::DarkCyan;
		leds2[3] = CRGB::DarkCyan;
		leds2[4] = CRGB::DarkCyan;
		led22_cycle ++;
		return DELAY22;
		break;
	case 9:
		leds2[2] = CRGB::BlueViolet;
		leds2[3] = CRGB::BlueViolet;
		leds2[4] = CRGB::BlueViolet;
		led22_cycle ++;
		return DELAY22;
		break;
	case 10:
		leds2[2] = CRGB::DarkSlateBlue;
		leds2[3] = CRGB::DarkSlateBlue;
		leds2[4] = CRGB::DarkSlateBlue;
		led22_cycle ++;
		return DELAY22;
		break;
	case 11:
		leds2[2] = CRGB::Lavender;
		leds2[3] = CRGB::Lavender;
		leds2[4] = CRGB::Lavender;
		led22_cycle ++;
		return DELAY22;
		break;
	case 12:
		leds2[2] = CRGB::LavenderBlush;
		leds2[3] = CRGB::LavenderBlush;
		leds2[4] = CRGB::LavenderBlush;
		led22_cycle ++;
		return DELAY22;
		break;
	default:
		leds2[2] = CRGB::LightCyan;
		leds2[3] = CRGB::LightCyan;
		leds2[4] = CRGB::LightCyan;
		led22_cycle =1;
		return DELAY22;
		break;

	}
return 0;
}

scenario led_string22(&init22, &update_led22);


/*********************************************************************************/
// Grande roue Gauche led3/led4
// Grande roue Droite
// Courone sur led2 5--17

uint8_t hue34;

void init34 (void) {
	for (uint8_t i=0; i<NUM_LEDS3; i++) {
		leds3[i] = CRGB::Black;
		leds4[i] = CRGB::Black;
	}
	for (uint8_t i=0; i<NUM_LEDS2-5; i++) {
		leds2[i+5] = CRGB::Black;
	}
	led34_cycle=0;
	hue34  = 0;
}
void up34_led( uint8_t start) {
	uint8_t i;
	for( i=0; i<NUM_LEDS2 ; i++) {
		leds2[i] = CRGB::Black;
	}
	leds2[start] = CRGB::Red;
}


uint32_t update_led34(void) {
	switch (led34_cycle) {
	case 0:
		break;
	case 1:
		for (uint8_t i = 0; i<26; i++) {
			leds3[]
		}
		leds3[]
		led34_cycle ++;
		return 500;
		break;

	case 12:
		up34_led(NUM_LEDS2-1);
		led34_cycle = 1;
		return 500;
		break;
	default:
		up34_led(led34_cycle-1);
		led34_cycle++;
		return 500;
		break;
	}
	return 0;
}

scenario led_string34(&init34, &update_led34);

/*********************************************************************************/
// Petit Bandeau / led5
void init5(void) {
	for (uint8_t i=0; i<NUM_LEDS5; i++) {
		leds5[i] = CRGB::Black;
	}
	led5_cycle=0;

}
void up5_led( uint8_t start) {
	uint8_t i;
	for( i=0; i<NUM_LEDS5 ; i++) {
		leds5[i] = CRGB::Blue;
	}
	leds5[start]=CRGB::Red;
}

uint32_t update_led5(void) {
	switch (led5_cycle) {
	case 0:
		break;
	case NUM_LEDS5:
		up5_led(NUM_LEDS5-1);
		led5_cycle = 1;
		return 300;
		break;
	default:
		up5_led(led5_cycle-1);
		led5_cycle++;
		return 300;
		break;
	}
return 0;
}

scenario led_string5(&init5, &update_led5);

/*********************************************************************************/
// Grand bandeau / led6
void init6 (void) {
	for (uint8_t i=0; i<NUM_LEDS6; i++) {
		leds6[i] = CRGB::Black;
	}
	led6_cycle=0;
}

void up6_led( uint8_t start) {
	uint8_t i;
	for( i=0; i<NUM_LEDS6 ; i++) {
		leds6[i] = CRGB::White;
	}
	leds6[start] = CRGB::Red;
}

uint32_t update_led6(void) {
	switch (led6_cycle) {
	case 0:
		break;
	case NUM_LEDS6:
		up6_led(NUM_LEDS6-1);
		led6_cycle = 1;
		return 300;
		break;
	default:
		up6_led(led6_cycle-1);
		led6_cycle++;
		return 300;
		break;
	}
return 0;
}

scenario led_string6(&init6, &update_led6);


/*********************************************************************************/
// Handling of the train

uint16_t speed;
void train_init(void) {
	speed = 0;
	timer3.begin();
	timer3.analog_set_speed_and_direction(speed,off);
	train_cycle=0;
}
uint32_t train(void) {
//	Serial.print('T');
	switch (train_cycle) {
	case 0:
		// Stop Train
		timer3.analog_set_speed_and_direction(speed,off);
		return 200;
		break;
	case 1:
		if (I2C_digitalRead(10) == LOW) {
			// button pressed, start the train
			Serial.print('S');
			speed = 200;
			timer3.analog_set_speed_and_direction(speed, forward);
			Serial.println(F("Train starts"));
			return 3000; // give it time to get out of detection zone
		}
		if (I2C_digitalRead(11) == LOW) {
			// button pressed, faster
			Serial.print('+');
			speed += 10;
			timer3.analog_set_speed_and_direction(speed, forward);
		}
		if (I2C_digitalRead(12) == LOW) {
			// button pressed, slower
			Serial.print('-');
			speed -= 10;
			timer3.analog_set_speed_and_direction(speed, forward);
		}
		// If train goes in front of station, stop
		if (digitalRead(CURRENT_DETECT) == LOW) {
			train_cycle = 0;
			return 0;
		}
		return 200;
		break;
	default:
		return 200;
		break;
	}
return 0;
}

scenario train_control(&train_init, &train);


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
  Serial.println(status->data, HEX);
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



#endif /* SRC_HELPERS_H_ */
