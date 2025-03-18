#include <Arduino.h>
#include <BleKeyboard.h>
#include <map>

BleKeyboard bleKeyboard;

const uint8_t SWITCH_PIN_LEFT = 4;
const uint8_t SWITCH_PIN_MIDDLE = 16;
const uint8_t SWITCH_PIN_RIGHT = 17;

const uint8_t LED_PIN_LEFT = 13;
const uint8_t LED_PIN_MIDDLE = 12;
const uint8_t LED_PIN_RIGHT = 14;

std::map<uint8_t, uint8_t> ledMap = {
  {SWITCH_PIN_LEFT, LED_PIN_LEFT},
  {SWITCH_PIN_MIDDLE, LED_PIN_MIDDLE},
  {SWITCH_PIN_RIGHT, LED_PIN_RIGHT}
};

std::map<uint8_t, char> keyMap = {
  {SWITCH_PIN_LEFT, 'A'},
  {SWITCH_PIN_MIDDLE, 'B'},
  {SWITCH_PIN_RIGHT, 'C'},
};

// Put function declarations here:
int kbdSwitchPin(uint8_t switchPin);

// Setup the code
// This function is called once at the start of the program
// or when the microcontroller is reset
void setup() {
  pinMode(SWITCH_PIN_LEFT, INPUT_PULLUP);
  pinMode(SWITCH_PIN_MIDDLE, INPUT_PULLUP);
  pinMode(SWITCH_PIN_RIGHT, INPUT_PULLUP);

  pinMode(LED_PIN_LEFT, OUTPUT);
  pinMode(LED_PIN_MIDDLE, OUTPUT);
  pinMode(LED_PIN_RIGHT, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  bleKeyboard.begin();

  Serial.println("Ready to connect!");
  Serial.println("Plug in the switches for pins 4, 16, and 17 to GND.");
  Serial.println("4: A, 16: B, 17: C");
}

// The following function is called repeatedly
void loop() {
  if(!bleKeyboard.isConnected()) {
      digitalWrite(LED_BUILTIN, HIGH);
      goto waitDelay;
  }

  digitalWrite(LED_BUILTIN, LOW);
  kbdSwitchPin(SWITCH_PIN_LEFT);
  kbdSwitchPin(SWITCH_PIN_MIDDLE);
  kbdSwitchPin(SWITCH_PIN_RIGHT);
  
waitDelay:
  delay(25);
  return;
}


// Put function definitions here:
int kbdSwitchPin(uint8_t switchPin) {
  int switchState = digitalRead(switchPin); // Read pin state
  uint8_t key = keyMap[switchPin];
  uint8_t ledPin = ledMap[switchPin];

  if (key == 0 || ledPin == 0) {
    return -1;
  }

  if (switchState == LOW) {  // Switch pressed (connected to GND)
      digitalWrite(ledPin, HIGH);  // Turn on LED
      bleKeyboard.press(key);
  } else {
      digitalWrite(ledPin, LOW);  // Turn off LED
      bleKeyboard.release(key);
  }

  return switchState;
}
