#include <Arduino.h>
#include <Wire.h>

#include <tones.h>
#include <HX711.h>
#include <notes.h>

#include <M5UnitSynth.h>
String inputString = "";         // a string to hold incoming data
String inputString2 = "";         // a string to hold incoming data

FingerEncoder fingerEncoder;
FingerEncoder::Finger finger;
ToneEncoder toneEncoder;

#define HX711_PIN_DOUT 5
#define HX711_PIN_SCK 6
HX711 scale;

#define TOP_BORDER 1600000
#define LOWER_BORDER 1100000


Octa octa = FOUR;
Octa lastOcta = FOUR;

M5UnitSynth synth;


int instrument = 3; //11; //10; //25;

int tempo = 80;


	// synth.setInstrument(0, 0, instrument);
	// synth.setNoteOn(0, melody[thisNote], 127); //noteDuration * 0.9);
  //   // Wait for the specief duration before playing the next note.
  //   delay(noteDuration);
  //   // stop the waveform generation before the next note.
  //   synth.setNoteOff(0, melody[thisNote], 127);

std::string octaToString(Octa octa) {
    switch (octa) {
        case THREE: return "THREE";
        case FOUR: return "FOUR";
        case T_F: return "T_F";
        default: return "UNKNOWN";
    }
}

void playTone(int tone) {
  synth.setInstrument(0, 0, 74);
  if (tone == -1) {
    synth.setNoteOff(0, NOTE_C4, 127);
  } else {
    synth.setNoteOn(0, tone, 127);
  }
}

void setup() {
  Wire.begin();
  USBSerial.begin(9600);

  scale.begin(HX711_PIN_DOUT, HX711_PIN_SCK);

  synth.begin(&Serial1, UNIT_SYNTH_BAUD, 1, 2);
  synth.setInstrument(0, 0, 74);
  synth.setNoteOn(0, NOTE_C4, 127);
  delay(1000);
  synth.setNoteOff(0, NOTE_C4, 127);
}

void loop() {
  if (scale.is_ready()) {
    long reading = scale.read();
    // USBSerial.println(reading);
    if (reading < LOWER_BORDER) {
      octa = THREE;
    } else if (reading > TOP_BORDER) {
      octa = FOUR;
    } else {
      octa = T_F;
    }
  }

  inputString = "";
  Wire.requestFrom(0x08, 2);
  while (Wire.available()) {
    char c = Wire.read();
    for (int i = 7; i >= 0; --i) {
      //USBSerial.print((c >> i) & 1);
      inputString += String((c >> i) & 1);
    }
  }

  if (inputString != inputString2 || lastOcta != octa) {
    finger = fingerEncoder.encode(inputString);

    int tone = toneEncoder.encodeToTone(finger, octa);
    static int lastTone = -1;
    synth.setNoteOff(0, lastTone, 127);
    lastTone = tone;

    playTone(tone);

    USBSerial.print("Tone: ");
    USBSerial.println(tone);
    
    USBSerial.print("l1: ");
    USBSerial.print(finger.l1);
    USBSerial.print(" l2: ");
    USBSerial.print(finger.l2);
    USBSerial.print(" l3: ");
    USBSerial.print(finger.l3);
    USBSerial.print(" l4: ");
    USBSerial.print(finger.l4);
    USBSerial.print(" l5: ");
    USBSerial.print(finger.l5);
    USBSerial.print(" r2: ");
    USBSerial.print(finger.r2);
    USBSerial.print(" r3: ");
    USBSerial.print(finger.r3);
    USBSerial.print(" r4: ");
    USBSerial.print(finger.r4);
    USBSerial.print(" r5_1: ");
    USBSerial.print(finger.r5_1);
    USBSerial.print(" r5_2: ");
    USBSerial.print(finger.r5_2);
    USBSerial.print(" r5_3: ");
    USBSerial.println(finger.r5_3);

    inputString2 = inputString;
    // USBSerial.println(inputString);
    inputString = "";

    USBSerial.print("Octa: ");
    USBSerial.println(octaToString(octa).c_str());
    lastOcta = octa;
  }
  delay(10);
}
