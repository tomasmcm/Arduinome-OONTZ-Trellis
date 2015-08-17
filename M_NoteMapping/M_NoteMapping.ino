//

#include <Wire.h>
#include <Adafruit_Trellis.h>
#include <Adafruit_OONTZ.h>

#define LED     13
#define CHANNEL 1

Adafruit_Trellis T[4];
OONTZ            oontz(&T[0], &T[1], &T[2], &T[3]);
const uint8_t    addr[] = { 0x70, 0x71, 0x72, 0x73 };

#define WIDTH     ((sizeof(T) / sizeof(T[0])) * 2)
#define N_BUTTONS ((sizeof(T) / sizeof(T[0])) * 16)
#define SHIFTNOTE 4
#define LOWNOTE   (((128 + (SHIFTNOTE*2)) - N_BUTTONS) / 2)

uint8_t       heart        = 0;
unsigned long prevReadTime = 0L;

//const uint8_t notes[]={12, 14, 16, 17, 24, 26, 28, 29, 36, 38, 40, 41, 48, 50, 52, 53, 19, 21, 23, 120, 31, 33, 35, 121, 43, 45, 47, 122, 55, 57, 59, 123, 60, 62, 64, 65, 72, 74, 76, 77, 84, 86, 88, 89, 96, 98, 100, 101, 67, 69, 71, 124, 79, 81, 83, 125, 91, 93, 95, 126, 103, 105, 107, 127};
const uint8_t notes[]={96, 98, 100, 101, 84, 86, 88, 89, 72, 74, 76, 77, 60, 62, 64, 65, 103, 105, 107, 108, 91, 93, 95, 96, 79, 81, 83, 84, 67, 69, 71, 72, 48, 50, 52, 53, 36, 38, 40, 41, 24, 26, 28, 29, 12, 14, 16, 17, 55, 57, 59, 60, 43, 45, 47, 48, 31, 33, 35, 36, 19, 21, 23, 24};

void setup() {
  pinMode(LED, OUTPUT);
  oontz.begin(addr[0], addr[1], addr[2], addr[3]);
#ifdef __AVR__
  TWBR = 12;
#endif
  oontz.clear();
  oontz.writeDisplay();
}

void loop() {
  unsigned long t = millis();
  if((t - prevReadTime) >= 20L) {
    if(oontz.readSwitches()) {
      for(uint8_t i=0; i<N_BUTTONS; i++) {
        uint8_t note= notes[i];
        if(oontz.justPressed(i)) {
          usbMIDI.sendNoteOn(note, 127, CHANNEL);
          oontz.setLED(i);
        } else if(oontz.justReleased(i)) {
          usbMIDI.sendNoteOff(note, 0, CHANNEL);
          oontz.clrLED(i);
        }
      }
      oontz.writeDisplay();
    }
    prevReadTime = t;
    digitalWrite(LED, ++heart & 32);
  }
  while(usbMIDI.read());
}