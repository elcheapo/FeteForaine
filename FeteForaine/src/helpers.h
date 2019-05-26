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
	uint8_t i,j,k;
	for( i=0; i< NUM_LEDS1/12; i++) {
		for (j=0; j<12; j++) {
			if (i == start) {
				leds1[i*12+j] = CHSV(37,212,255);
			} else {
				k = abs( i - start);
				leds1[i*12+j] = CHSV(37,255 - (k*15),255);
			}

		}
	}
}

#if 0
void up1_led( uint8_t start) {
	uint8_t i;
	for( i=0; i< NUM_LEDS1; i++) {
		leds1[i] = CRGB::FairyLight; //HSV = 52,83,100
	}
	for( i=start; i<start + 12;  i++) {
		leds1[i] = CRGB::Orange;
	}

}
#endif
uint32_t update_led1(uint8_t &cycle) {
	uint8_t i;
	switch (cycle) {
	case 0:
		for (i=0; i<NUM_LEDS1; i++) {
			leds1[i] = CRGB::Black;
		}
		cycle = 1;
		return 1000;
		break;
	case 12:
		up1_led(12);
		cycle = 1;
		return 200;
		break;
	default:
		up1_led(cycle - 1);
		cycle ++;
		return 200;
		break;

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

uint32_t update_led2(uint8_t &cycle) {
	uint8_t i;
	switch (cycle) {
	case 0:
		for (i=0; i<NUM_LEDS2; i++) {
			leds2[i] = CRGB::Black;
		}
		cycle=1;
		return 500;
		break;
	case 12:
		up2_led(NUM_LEDS2-1);
		cycle = 1;
		return 500;
		break;
	default:
		up2_led(cycle-1);
		cycle++;
		return 500;
		break;
	}
return 0;
}

scenario led_string2(&update_led2);

/*********************************************************************************/

#if 0
void up3_led( uint8_t start) {
	uint8_t i;
	for( i=0; i<NUM_LEDS3 ; i++) {
		leds3[i] = CRGB::Black;
	}
	leds3[start] = CRGB::Red;
	if (start < NUM_LEDS3-2)
		leds3[(start+1) % NUM_LEDS3] = CRGB::Green;
	if (start < NUM_LEDS3-3)
		leds3[(start+2) % NUM_LEDS3] = CRGB::Blue;
}
#endif
#define HUE 150
void up3_led( uint8_t start) {
	uint8_t i,diff;
	for( i=0; i<NUM_LEDS3 ; i++) {
		diff = abs(i-start);
		leds3[i] = CHSV(HUE-diff,255,200);;
	}
}


uint32_t update_led3(uint8_t & cycle) {
	uint8_t i;
	switch (cycle) {
	case 0:
		for (i=0; i<NUM_LEDS3; i++) {
			leds3[i] = CRGB::Black;
		}
		cycle=1;
		return 80;
		break;
	case NUM_LEDS3:
		up3_led(NUM_LEDS3-1);
		cycle = 1;
		return 80;
		break;
	default:
		up3_led(cycle-1);
		cycle++;
		return 80;
		break;
	}
return 0;
}

scenario led_string3(&update_led3);

/*********************************************************************************/
// Handling of the train

uint16_t speed;

uint32_t train(uint8_t &cycle) {
//	Serial.print('T');
	switch (cycle) {
	case 0:
		speed = 0;
		timer3.begin();
		timer3.analog_set_speed_and_direction(speed,off);
		cycle=1;
		return 200;
		break;
	case 1:
		if (I2C_digitalRead(B_TRAIN) == LOW) {
			// button pressed, start the train
			Serial.print('S');
			speed = 200;
			timer3.analog_set_speed_and_direction(speed, backward);
			Serial.println(F("Train starts"));
			return 3000; // give it time to get out of detection zone
		}
		if (I2C_digitalRead(23) == LOW) {
			// button pressed, faster
			Serial.print('+');
			speed += 10;
			timer3.analog_set_speed_and_direction(speed, backward);
		}
		if (I2C_digitalRead(24) == LOW) {
			// button pressed, slower
			Serial.print('-');
			speed -= 10;
			timer3.analog_set_speed_and_direction(speed, backward);
		}
		if ((I2C_digitalRead(23) == LOW) & (I2C_digitalRead(24) == LOW)) {
			// button pressed, slower
			Serial.println('STOP');
			speed = 0;
			timer3.analog_set_speed_and_direction(speed, backward);
		}
		// If train goes in front of station, stop
		if (digitalRead(CURRENT_DETECT) == LOW) {
			cycle = 0;
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

/*********************************************************************************/

uint32_t manege1(uint8_t &cycle) {
	switch (cycle) {
	case 0:
		// Turn Off Manège
		I2C_digitalWrite(R_MANEGE1,LOW);
		cycle = 1;
		return 500;
		break;
	case 1:
		if (I2C_digitalRead(B_MANEGE1) == LOW) {
			I2C_digitalWrite(R_MANEGE1, HIGH);
			mp3.playTrackRepeat(6);
			cycle = 2;
		}
		return 500;
		break;
	case 2:
		cycle = 3;
		return MANEGE_DURATION;
	default:
		cycle = 1;
		I2C_digitalWrite(R_MANEGE1, LOW);
		return 500;
		break;
	}
return 0;
}

scenario op_manege_1(&manege1);


/*********************************************************************************/

uint32_t manege2(uint8_t &cycle) {
	switch (cycle) {
	case 0:
		// Turn Off Manège
		I2C_digitalWrite(R_MANEGE2,LOW);
		cycle = 1;
		return 500;
		break;
	case 1:
		if (I2C_digitalRead(B_MANEGE2) == LOW) {
			I2C_digitalWrite(R_MANEGE2, HIGH);
			mp3.playTrackRepeat(7);
			cycle = 2;
		}
		return 500;
		break;
	case 2:
		cycle = 3;
		return MANEGE_DURATION;
	default:
		cycle = 1;
		I2C_digitalWrite(R_MANEGE2, LOW);
		return 500;
		break;
	}
return 0;
}

scenario op_manege_2(&manege2);

/*********************************************************************************/

/*********************************************************************************/

uint32_t manege3(uint8_t &cycle) {
	switch (cycle) {
	case 0:
		// Turn Off Manège
		I2C_digitalWrite(R_MANEGE3,LOW);
		cycle = 1;
		return 500;
		break;
	case 1:
		if (I2C_digitalRead(B_MANEGE3) == LOW) {
			I2C_digitalWrite(R_MANEGE3, HIGH);
			mp3.playTrackRepeat(8);
			cycle = 2;
		}
		return 500;
		break;
	case 2:
		cycle = 3;
		return MANEGE_DURATION;
	default:
		cycle = 1;
		I2C_digitalWrite(R_MANEGE3, LOW);
		return 500;
		break;
	}
return 0;
}

scenario op_manege_3(&manege3);

/*********************************************************************************/

/*********************************************************************************/

uint32_t manege4(uint8_t &cycle) {
	switch (cycle) {
	case 0:
		// Turn Off Manège
		I2C_digitalWrite(R_MANEGE4,LOW);
		cycle = 1;
		return 500;
		break;
	case 1:
		if (I2C_digitalRead(B_MANEGE4) == LOW) {
			I2C_digitalWrite(R_MANEGE4, HIGH);
			mp3.playTrackRepeat(9);
			cycle = 2;
		}
		return 500;
		break;
	case 2:
		cycle = 3;
		return MANEGE_DURATION;
	default:
		cycle = 1;
		I2C_digitalWrite(R_MANEGE4, LOW);
		return 500;
		break;
	}
return 0;
}

scenario op_manege_4(&manege4);

/*********************************************************************************/

/*********************************************************************************/

uint32_t manege5(uint8_t &cycle) {
	switch (cycle) {
	case 0:
		// Turn Off Manège
		I2C_digitalWrite(R_MANEGE5,LOW);
		cycle = 1;
		return 500;
		break;
	case 1:
		if (I2C_digitalRead(B_MANEGE5) == LOW) {
			I2C_digitalWrite(R_MANEGE5, HIGH);
			mp3.playTrackRepeat(10);
			cycle = 2;
		}
		return 500;
		break;
	case 2:
		cycle = 3;
		return MANEGE_DURATION;
	default:
		cycle = 1;
		I2C_digitalWrite(R_MANEGE5, LOW);
		return 500;
		break;
	}
return 0;
}

scenario op_manege_5(&manege5);

/*********************************************************************************/
/*********************************************************************************/

uint32_t manege6(uint8_t &cycle) {
	switch (cycle) {
	case 0:
		// Turn Off Manège
		I2C_digitalWrite(R_WATERPARK,LOW);
		cycle = 1;
		return 500;
		break;
	case 1:
		if (I2C_digitalRead(B_WATERPARK) == LOW) {
			I2C_digitalWrite(R_WATERPARK, HIGH);
			mp3.playTrackRepeat(10);
			cycle = 2;
		}
		return 500;
		break;
	case 2:
		cycle = 3;
		return MANEGE_DURATION;
	default:
		cycle = 1;
		I2C_digitalWrite(R_WATERPARK, LOW);
		return 500;
		break;
	}
return 0;
}

scenario op_manege_6(&manege6);

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
