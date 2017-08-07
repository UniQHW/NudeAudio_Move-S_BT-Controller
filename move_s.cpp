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
 * The following file defines all functions prototyped in move_s.h

 */

#include <Interval.h>
#include "move_s.h"

/* --- struct speaker --- */

/* Returns High signal if volume has surpased filter value
 * For reference volume readings, see README.md */
bool speaker::sig(unsigned int filter) {
  for (int i = 0; i < SPK_NOISE_FILTERATION_ATTEMPTS; i++) {
    if (analogRead(pin) < filter) {
      return HIGH;
    }
  }

  return LOW;
}

/* Returns High signal if volume meets the
 * filter threshold and has been counted n times
 * For reference volume readings, see README.md */
bool speaker::sig(unsigned int lowest, unsigned int highest, int count) {
  int read;
  int min = 0;

  while(min < count) {
    int i;
    for (i = 0; i < SPK_NOISE_FILTERATION_ATTEMPTS; i++) {
      read = analogRead(pin);
      if (read > lowest && read < highest) {
        min++;
        break;
      }
    }

    if (i == SPK_NOISE_FILTERATION_ATTEMPTS) {
      return LOW;
    }
  }

  return HIGH;
}

/* --- struct led --- */
bool led::state() {
  return !digitalRead(pin); // Invertion due to pull-up resistor on input pin
}

/* --- struct move_s --- */

/* Check if device is paired */
bool move_s::paired() {
  timestamp stamp(&micros);

  stamp.setStamp(BT_LED_PAIRING_INTERVAL_USEC);

  while(bt_led->state() == HIGH) {
    if (stamp.expired())
      return true;
  }

  /* BT LED switched state before stamp has expired */
  return false;
}

/* BT LED in sleep mode */
bool move_s::pairing_sleepMode() {
  timestamp stamp(&micros);

  stamp.setStamp(BT_LED_PAIRING_INTERVAL_USEC);

  while(bt_led->state() == LOW) {
    if (stamp.expired())
      return true;
  }

  /* LED switched state before stamp has expired */
  return false;
}

/* BT LED in blinking mode */
bool move_s::pairing_blinkMode() {
  return (!paired() && !pairing_sleepMode());
}

/* Automatically determine bt mode */
move_s_bt_mode move_s::mode() {
  return (paired() ? paired_mode : (pairing_sleepMode() ? pair_sleep_mode : pair_blink_mode));
}
