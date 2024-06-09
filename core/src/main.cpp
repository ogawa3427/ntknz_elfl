#include <Arduino.h>
#include <Wire.h>

#include <tones.h>
#include <HX711.h>

String inputString = "";         // a string to hold incoming data
String inputString2 = "";         // a string to hold incoming data

FingerEncoder fingerEncoder;
FingerEncoder::Finger finger;

#define HX711_PIN_DOUT 5
#define HX711_PIN_SCK 6
HX711 scale;

#define TOP_BORDER 1600000
#define LOWER_BORDER 1100000

enum Octa {
  THREE, T_F, FOUR
};

Octa octa = FOUR;
Octa lastOcta = FOUR;


void setup() {
  Wire.begin();
  USBSerial.begin(9600);

  scale.begin(HX711_PIN_DOUT, HX711_PIN_SCK);


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
    USBSerial.println(inputString);
    inputString = "";

    USBSerial.print("Octa: ");
    USBSerial.println(octa);
    lastOcta = octa;
  }
  delay(10);
}
