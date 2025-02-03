#include <Arduino.h>
#include <list>
#include <map>

using namespace std;
#define YELLOW_DIODE 12
#define GREEN_DIODE 13
#define BUTTON 14

// put function declarations here:
void blink(int);
std::map<int, int> _startup = {
  {GREEN_DIODE, OUTPUT}, 
  {YELLOW_DIODE, OUTPUT}, 
  {LED_BUILTIN, OUTPUT}, 
  {BUTTON, INPUT_PULLUP}
};

int buttonState = 0;

void setup()
{
  for (auto kv : _startup)
  {
    pinMode(kv.first, kv.second);
  }

  Serial.begin(115200);
}

void blinkMode(int diode, int time, bool high)
{
  digitalWrite(diode, high ? HIGH : LOW);
  delay(time);
}

void blink(int diode)
{
  // Serial.println("Turning on diode: " + String(diode));
  blinkMode(diode, 250, true);
  // Serial.println("Turning off diode: " + String(diode));
  blinkMode(diode, 250, false);
}

void loop()
{
  buttonState = digitalRead(BUTTON);
  Serial.println("Button state: " + String(buttonState));
  blink(buttonState == HIGH ? GREEN_DIODE : YELLOW_DIODE);
}