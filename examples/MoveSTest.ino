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
 * Example program for the Nude Audio Move S Readable BT Controller Library

 */

#include <move_s_r.h>

move_s_r *mvs_r;
move_s_bt_mode mode;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  /* Initialize with BT LED on pin 2 and speaker on pin a5 */
  mvs_r = new move_s_r(2, A5);
}

void loop() {
  /* Evaluate device mode */
  switch(mvs_r->mode()) {

    /* Device is paired */
    case paired_mode :
      Serial.println("Device has been paired");

      while(mvs_r->mode() == paired_mode) {
        /* If volume signal reaches below 10, receive high signal */
        if(mvs_r->spk->sig(SPK_NOISE_LEVEL_HIGH)) {
          digitalWrite(LED_BUILTIN, HIGH);
          while(mvs_r->spk->sig(SPK_NOISE_LEVEL_HIGH));
          digitalWrite(LED_BUILTIN, LOW);
        }
      }

      Serial.println("Device disconnected");
      break;

    /* Device is in pairing mode and is blinking */
    case pair_blink_mode :
      Serial.println("Awaiting device");
      while(mvs_r->mode() == pair_blink_mode);
      break;

    /* Device is in pairing mode, but isn't blinking */
    case pair_sleep_mode :
      Serial.println("Entered sleep mode");
      Serial.println("Awaiting device");
      while(mvs_r->mode() == pair_sleep_mode);
  }
}
