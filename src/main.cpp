#include <Arduino.h>
#include <list>
#include <map>

using namespace std;
#define YELLOW_DIODE 12
#define GREEN_DIODE 13
#define BUTTON 14
#define DEFAULT_DELAY 250
// put function declarations here:
void blink(int);
std::map<int, int> _startup = {
  {GREEN_DIODE, OUTPUT}, 
  {YELLOW_DIODE, OUTPUT}, 
  {LED_BUILTIN, OUTPUT}, 
  {BUTTON, INPUT_PULLUP}
};

int buttonState = 0;
long int lastTick = 0;
int currentDiode = GREEN_DIODE;
uint8_t currentPower;

void setup()
{
  for (auto kv : _startup)
  {
    pinMode(kv.first, kv.second);
  }

  lastTick = millis();
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
  long int time = millis();
  int lastButtonState = buttonState;
  buttonState = digitalRead(BUTTON);
  if (buttonState != lastButtonState)
  {
    digitalWrite(currentDiode, LOW);
    lastButtonState = buttonState;
    currentDiode = buttonState == LOW ? YELLOW_DIODE : GREEN_DIODE;
  }

  if (time - lastTick < DEFAULT_DELAY)
  {
    return;
  }
  lastTick = time;
  currentPower = currentPower == HIGH ? LOW : HIGH;
  digitalWrite(currentDiode, currentPower);
  // Serial.println("Button state: " + String(buttonState));
  // blink(buttonState == HIGH ? GREEN_DIODE : YELLOW_DIODE);
}