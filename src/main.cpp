#include <Arduino.h>
#include <list>
using namespace std;

// put function declarations here:
int _diode = 13;
list<int> _list = {_diode, LED_BUILTIN};

void setup() {
  pinMode(_diode, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void blink(int diode) {
  digitalWrite(diode, HIGH);
  delay(1000);
  digitalWrite(diode, LOW);
  delay(1000);
}

void loop() {
  for (int i : _list) {
    blink(i);
  }
}

