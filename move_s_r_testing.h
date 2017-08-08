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
 * The following file provides the application with
 * functions to measure and observe Move S signals.

 */

#include <Interval.h>
#include "move_s_r.h"

#define BT_LED_PIN 0x2 // Read LED state on pin D2
#define SPK_PIN    A5  // Read Speaker values on pin A5

void measurePairingBlink();         // Measure time of interval in usec
int measurePairingBlinks();         // Measure ammount of blinks
time_us measurePairingBlinkTotal(); // Measure total interval time in usec

int measureSpeakerSig();            // Measure volume output (NOTE: Volume output is very noisy, filtering will help)
