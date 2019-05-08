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
	uint8_t port = pin / 10;
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

/************************************************************************************************/
// Scenario for string 1

void up1_led( uint8_t start) {
	uint8_t i;
	for( i=0; i< NUM_LEDS1; i++) {
		leds1[i] = CRGB::FairyLight;
	}
	for( i=start; i<start + 12;  i++) {
		leds1[i] = CRGB::Orange;
	}

}

uint32_t update_led1(void) {
	uint8_t i;
	switch (led1_cycle) {
	case 0:
		for (i=0; i<NUM_LEDS1; i++) {
			leds1[i] = CRGB::Black;
		}
		led1_cycle=1;
		return 500;
		break;
	case 1:
		up1_led(0);
		led1_cycle++;
		return 500;
		break;
	case 2:
		up1_led(12);
		led1_cycle++;
		return 500;
		break;
	case 3:
		up1_led(24);
		led1_cycle++;
		return 500;
		break;
	case 4:
		up1_led(36);
		led1_cycle++;
		return 500;
		break;
	case 5:
		up1_led(48);
		led1_cycle++;
		return 500;
		break;
	case 6:
		up1_led(60);
		led1_cycle++;
		return 500;
		break;
	case 7:
		up1_led(72);
		led1_cycle++;
		return 500;
		break;
	case 8:
		up1_led(84);
		led1_cycle++;
		return 500;
		break;
	case 9:
		up1_led(96);
		led1_cycle++;
		return 500;
		break;
	case 10:
		up1_led(108);
		led1_cycle++;
		return 500;
		break;
	case 11:
		up1_led(120);
		led1_cycle = 3;
		return 500;
		break;
	case 12:
		up1_led(132);
		led1_cycle = 1;
		return 500;
		break;
	default:
		led1_cycle=0;
		return 0;
	}
return 0;
}

scenario led_string1(&update_led1);

/*********************************************************************************/

void up2_led( uint8_t start) {
	uint8_t i;
	for( i=0; i<NUM_LEDS2 ; i++) {
		leds2[i] = CRGB::Black;
	}
	leds2[start] = CRGB::Red;
}

uint32_t update_led2(void) {
	uint8_t i;
	switch (led2_cycle) {
	case 0:
		for (i=0; i<NUM_LEDS2; i++) {
			leds2[i] = CRGB::Black;
		}
		led2_cycle=1;
		return 500;
		break;
	case 12:
		up2_led(NUM_LEDS2-1);
		led2_cycle = 1;
		return 500;
		break;
	default:
		up2_led(led2_cycle-1);
		led2_cycle++;
		return 500;
		break;
	}
return 0;
}

scenario led_string2(&update_led2);

/*********************************************************************************/

void up3_led( uint8_t start) {
	uint8_t i;
	for( i=0; i<NUM_LEDS3 ; i++) {
		leds3[i] = CRGB::Black;
	}
	leds3[start] = CRGB::Red;
	if (start < 83)
		leds3[(start+1) % 85] = CRGB::Green;
	if (start < 82)
		leds3[(start+2) % 85] = CRGB::Blue;
}

uint32_t update_led3(void) {
	uint8_t i;
	switch (led3_cycle) {
	case 0:
		for (i=0; i<NUM_LEDS3; i++) {
			leds3[i] = CRGB::Black;
		}
		led3_cycle=1;
		return 300;
		break;
	case 85:
		up3_led(NUM_LEDS3-1);
		led3_cycle = 1;
		return 300;
		break;
	default:
		up3_led(led3_cycle-1);
		led3_cycle++;
		return 300;
		break;
	}
return 0;
}

scenario led_string3(&update_led3);

/*********************************************************************************/
// Handling of the train

uint16_t speed;

uint32_t train(void) {
//	Serial.print('T');
	switch (train_cycle) {
	case 0:
		speed = 0;
		timer3.begin();
		timer3.analog_set_speed_and_direction(speed,off);
		train_cycle=1;
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

scenario train_control(&train);


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
