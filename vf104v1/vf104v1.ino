/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

int ENCODER_PIN_A = 18;
int ENCODER_PIN_B = 19;
int LED_PINS[] = {2,3,4,5,6,7,8,9,10,11,12,13};
int SWITCH_PIN = 53;
int TAP_PIN = 21;
volatile byte TAP_STATE = HIGH; 
long DEBOUCE_DELAY = 50;
long LAST_DEBOUNCE_TIME = 0;
Encoder myEnc(ENCODER_PIN_A, ENCODER_PIN_B);

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test 2:");
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(TAP_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(TAP_PIN), tap, FALLING);
}

long oldPosition  = -999;
volatile byte state = LOW;

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    if (newPosition > 127) {
      myEnc.write(127);
      newPosition = 127;
    } else if (newPosition < 0) {
      myEnc.write(0);
      newPosition = 0;
    }
    oldPosition = newPosition;
    //Serial.println(newPosition);
  }
  
  if (digitalRead(SWITCH_PIN) == LOW){
    setLeds(0, LED_PINS, 12);
  } else {
    int brightness = getLedBrightness(newPosition);
    setLeds(brightness, LED_PINS, 12);
  }
  
  if (TAP_STATE == LOW && ((millis() - LAST_DEBOUNCE_TIME) > DEBOUCE_DELAY)){
    sendMidi();
    TAP_STATE = HIGH;
    LAST_DEBOUNCE_TIME = millis();
  }
  
}

int getLedBrightness(int midiValue) {
  int ledMax = 255;
  int midiMax = 127;
  return (midiValue / 127.0) * ledMax;
}

void setLeds(int brightness, int pins[], int size) {
  for (int idx=0; idx < size; idx++) {
    int pin = pins[idx];
    Serial.println(brightness);
    analogWrite(pin, brightness);
  }
}

void tap(){
  TAP_STATE = LOW;
}


void sendMidi() {
  Serial.write(0xB0); // cc Midi Command 
  Serial.write(114); // cc Parameter - Tap Tempo A
  Serial.write(10); // cc Value - any value should work
}

