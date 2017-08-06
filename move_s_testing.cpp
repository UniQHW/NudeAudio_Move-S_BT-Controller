/*
 * Copyright 2017 Patrick Pedersen <ctx.xda@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *

 * Author :
 * Patrick Pedersen <ctx.xda@gmail.com>

 * DESCRIPTION :
 * The following file defines all functions prototyped in move_s_testing.h

 */

#include <Arduino.h>
#include "move_s_testing.h"


/* Measure time of blink in usec */
void measurePairingBlink() {
  timestamp stamp(&micros);
  bool stat = true;

  /* Wait for interval start */
  Serial.println("Waiting for interval");
  while(digitalRead(BT_LED_PIN) == BT_LED_OFF);
  Serial.println("Measuring...");

  while(true) {
    if (stat != digitalRead(BT_LED_PIN)) {
      Serial.println(stamp.timeSinceStamp());
      stamp.setStamp();
      stat = !stat;
    }
  }
}

/* Measure ammount of blinks */
int measurePairingBlinks() {
  int intervals = 0;
  bool stat = true;
  timestamp stamp(&micros);

  /* Wait for interval start */
  Serial.println("Waiting for interval");
  while(digitalRead(BT_LED_PIN) == BT_LED_OFF);
  Serial.println("Measuring...");

  /* Set "initial" time stamp */
  stamp.setStamp(BT_LED_PAIRING_INTERVAL_USEC);

  /* Continue counting until blinking is over, aka. device enters sleep mode? */
  while(!stamp.expired()) {
    if (stat != digitalRead(BT_LED_PIN)) {
      stat = !stat;
      stamp.setStamp(BT_LED_PAIRING_INTERVAL_USEC);
      intervals++;
    }
  }

  return intervals;
}

/* Measure total time of inteval in usec */
time_us measurePairingBlinkTotal() {
  bool stat = true;
  timestamp stamp(&micros);

  /* Wait for interval start */
  Serial.println("Waiting for interval");
  while(digitalRead(BT_LED_PIN) == BT_LED_OFF);
  Serial.println("Measuring...");

  /* Start measuring total time */
  timestamp ret(&micros);

  /* Set "initial" time stamp */
  stamp.setStamp(BT_LED_PAIRING_INTERVAL_USEC);

  /* Continue counting until blinking is over, aka. device enters sleep mode? */
  while(!stamp.expired()) {
    if (stat != digitalRead(BT_LED_PIN)) {
      stat = !stat;
      stamp.setStamp(BT_LED_PAIRING_INTERVAL_USEC);
    }
  }

  return ret.timeSinceStamp();
}

int measureSpeakerSig() {
  return analogRead(SPK_PIN);
}
