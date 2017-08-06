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
 * The following file provides the application with device data and
 * device structures to obtain signals from the Move S.
 * These signals can be intepreted and call a certain event.

 * A user may obtain the following information using the provided signal functions :

 * The device mode :
 * Whether the device is in pairing mode with no bluetooth led blinking (aka sleep mode)
 * Whether the device is in pairing mode with bluetooth LED blinking
 * Whether the device has been paired

 * Audio input :
 * Whether the volume exceeds a certain level
 * Whether the volume matches a certain threshold

 * With the provided signals, the Move S chip can be used as a low speed bluetooth controller

 */

/* Blinking interval of LED during pairing mode
 * The interval lies at 204 545 usec, however, as various
 * attributes may result in slight reading errors,
 * we'll give it a total of 210 000 usec
 */
#define BT_LED_PAIRING_INTERVAL_USEC  210000

/* During the pairing interval, the LED state is switched for a total of 880 times *
 * This measurement includes both On and Off states
 */
#define BT_LED_PAIRING_INTERVAL_COUNT 880

/* After simple calculation and additional measuring, the paring
 * interval takes a total of 3 minutes, or simply a total of 180 000 000 usec.
 */
#define BT_LED_PAIRING_INTERVAL_TOTAL_USEC 180000000

/* Makes work simpler as invertion is required due to pull-up resistor
 * see schematic for more details */
#define BT_LED_OFF HIGH
#define BT_LED_ON  LOW

/* Sound volume parameters */
#define SPK_NOISE_FILTERATION_ATTEMPTS 500 // Search volume pool of 500 analog reads
#define SPK_NOISE_LEVEL_HIGH           850 // Reads above this value can be considered as "loud" tones

#ifdef DEVICE_PINS_GT_BYTE  // Device has more than 256 pins
typedef unsigned int pin_t;
#else                       // Pin count under 256
typedef uint8_t pin_t;
#endif

/* Bluetooth States */
enum move_s_bt_mode {
  pair_sleep_mode,
  pair_blink_mode,
  paired_mode
};

/* Speaker Input */
struct speaker {
  speaker(pin_t pin) : pin(pin) {};

  /* Returns High signal if volume has surpased filter value
   * For reference volume readings, see README.md */
  bool sig(unsigned int filter);

  /* Returns High signal if volume meets the
   * filter threshold and has been counted n times
   * For reference volume readings, see README.md */
  bool sig(unsigned int lowest, unsigned int highest, int count = 1);

private:
  pin_t pin;
};

/* LED Input */
struct led {
  led(pin_t pin) : pin(pin) {};
  bool state();

private:
  pin_t pin;
};

/* Mai ndevice structure */
struct MoveS {
  MoveS(pin_t bt_led, pin_t pwr_led, pin_t spk) :
  bt_led(new led(bt_led)), pwr_led(new led(pwr_led)),
  spk(new speaker(spk)) {
    pinMode(bt_led, INPUT);
    pinMode(pwr_led, INPUT);
    pinMode(spk, INPUT);
  };

  ~MoveS() {
    delete bt_led;
    delete pwr_led;
    delete spk;
  }

  led *bt_led;
  led *pwr_led;
  speaker *spk;

  bool paired();            // Check if device is paired
  bool pairing_sleepMode(); // BT LED in sleep mode
  bool pairing_blinkMode(); // BT LED in blinking mode

  move_s_bt_mode mode();    // Automatically determine bt mode
};
