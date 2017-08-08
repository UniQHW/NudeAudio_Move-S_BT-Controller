# Nude Audio Move S Readable Bluetooth Controller

With The provided code, an arduino and a bit of tinkering (the see wiki/circuitry), you can turn your Nude Audio Move S circuit into an
low-key read-only arduino bluetooth controller.

The controller provides the arduino with a variaty of signals which can be interpreted and trigger a certain event.

For instance, using the sound volume signal (```move_s.spk->sig(volume))```), the arduino may be controlled trough bluetooth with the use of sound.   

![Setup](img/MoveS_BT-Controller_bb.png)
Image made using Fritzing

### Wiki
To keep things tidy, all documentation is available on the wiki.

### Q&A

Q: Will I able able to write bluetooth signals?

A: No, as the title mentiones, the code only provides readable data. To put this into perspective, you may
   connect your device to the Move S circuit and transmit sound data. The arduino can read this sound data and can act according to it.
   However, the arduino cannot respond to the paired device (at least not using this library) as it has no control over the Move S circuit whatsoever
