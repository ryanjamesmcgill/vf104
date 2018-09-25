#include <Encoder.h>
#include <JC_Button.h>

int ENCODER_A_PIN = 18;
int ENCODER_B_PIN = 19;
Encoder ENCODER(ENCODER_B_PIN, ENCODER_A_PIN);
long ENCODER_POSITION = -999;
int ENCODER_MAX_POSITION = 127;
int ENCODER_MIN_POSITION = 0;
int LED_PARAM_PINS[] = {32, 33, 34, 35, 36, 37, 38, 39};
int LED_PARAM_PINS_LENGTH = 8;
int LED_SAVE_PIN = 29;
int LED_ENCODER_PINS[] = {A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, 44, 45, 46};
int LED_ENCODER_PINS_LENGTH = 15;
float LED_ENCODER_STEP_POSITION = (ENCODER_MAX_POSITION - ENCODER_MIN_POSITION) / LED_ENCODER_PINS_LENGTH;
int LED_CURVE[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05,
0x05, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x08, 0x08, 0x08, 0x09, 0x09, 0x0A, 0x0A, 0x0B, 0x0B,
0x0C, 0x0C, 0x0D, 0x0D, 0x0E, 0x0F, 0x0F, 0x10, 0x11, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x26, 0x27, 0x29, 0x2B, 0x2C,
0x2E, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3A, 0x3C, 0x3E, 0x40, 0x43, 0x45, 0x47, 0x4A, 0x4C, 0x4F,
0x51, 0x54, 0x57, 0x59, 0x5C, 0x5F, 0x62, 0x64, 0x67, 0x6A, 0x6D, 0x70, 0x73, 0x76, 0x79, 0x7C,
0x7F, 0x82, 0x85, 0x88, 0x8B, 0x8E, 0x91, 0x94, 0x97, 0x9A, 0x9C, 0x9F, 0xA2, 0xA5, 0xA7, 0xAA,
0xAD, 0xAF, 0xB2, 0xB4, 0xB7, 0xB9, 0xBB, 0xBE, 0xC0, 0xC2, 0xC4, 0xC6, 0xC8, 0xCA, 0xCC, 0xCE,
0xD0, 0xD2, 0xD3, 0xD5, 0xD7, 0xD8, 0xDA, 0xDB, 0xDD, 0xDE, 0xDF, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5,
0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xED, 0xEE, 0xEF, 0xEF, 0xF0, 0xF1, 0xF1, 0xF2,
0xF2, 0xF3, 0xF3, 0xF4, 0xF4, 0xF5, 0xF5, 0xF6, 0xF6, 0xF6, 0xF7, 0xF7, 0xF7, 0xF8, 0xF8, 0xF8,
0xF9, 0xF9, 0xF9, 0xF9, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFC,
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD,
0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF
};
int PARAM_BUTTON_PIN = 30;
int SAVE_BUTTON_PIN = 28;
int BANK_A_BUTTON_PIN = 40;
int BANK_B_BUTTON_PIN = 41;
int BANK_C_BUTTON_PIN = 42;

Button PARAM_BUTTON(PARAM_BUTTON_PIN, 100);
Button BANK_A_BUTTON(BANK_A_BUTTON_PIN);
Button BANK_B_BUTTON(BANK_B_BUTTON_PIN);
Button BANK_C_BUTTON(BANK_C_BUTTON_PIN);

char STATE_BANK = 'A'; // A,B,C indicating current preset bank
int STATE_PRESET = 1; // 1-3 indicating current preset
int STATE_PARAMETER = 1; // 1-8 indicating current parameter
bool STATE_SAVE_INDICATOR = false; // indicates if save led should be blinking

void setup() {
  Serial.begin(9600);
  intializePins();
  PARAM_BUTTON.begin();
  BANK_A_BUTTON.begin();
  BANK_B_BUTTON.begin();
  BANK_C_BUTTON.begin();
  turnOnLeds();
}

void loop() {
  updateEncoderPosition();
  updateStates();
  
  setEncoderLeds();
  setParameterLeds();
}

void updateStates() {
  // update bank
  BANK_A_BUTTON.read();
  BANK_B_BUTTON.read();
  BANK_C_BUTTON.read();
  if ( BANK_C_BUTTON.isPressed() ) {
    STATE_BANK = 'C';
  } else if ( BANK_B_BUTTON.isPressed() ) {
    STATE_BANK = 'B';
  } else {
    STATE_BANK = 'A';
  }
  Serial.println(STATE_BANK);
  
  // update preset
  
  // update parameter
  PARAM_BUTTON.read();
  if ( PARAM_BUTTON.wasPressed() ) {
    nextParam();
  }
}

void nextParam() {
  STATE_PARAMETER = STATE_PARAMETER + 1;
  if (STATE_PARAMETER > LED_PARAM_PINS_LENGTH) {
    STATE_PARAMETER = 1;
  }
}

void setParameterLeds() {
  for (int idx = 0; idx < LED_PARAM_PINS_LENGTH; idx++) {
    if (idx + 1 == STATE_PARAMETER) {
      digitalWrite(LED_PARAM_PINS[idx], HIGH);
    } else {
      digitalWrite(LED_PARAM_PINS[idx], LOW);
    }
  }
}

void setEncoderLeds() {
 for (int idx = 0; idx < LED_ENCODER_PINS_LENGTH; idx++) {
  float max_position = (idx+1) * LED_ENCODER_STEP_POSITION;
  float min_position = idx * LED_ENCODER_STEP_POSITION;
  setEncoderLed(LED_ENCODER_PINS[idx], ENCODER_POSITION, min_position, max_position);
 }
}

void setEncoderLed(int pin, long encoder_position, float led_min_posiiton, float led_max_positon) {
  int ledBrightness;
  int ledMaxBrghtness = 255;
  float fraction;
  if (encoder_position >= led_max_positon) {
    ledBrightness = LED_CURVE[ledMaxBrghtness];
  } else if (encoder_position <= led_min_posiiton) {
    ledBrightness = LED_CURVE[0];
  } else {
    fraction = ((encoder_position - led_min_posiiton) / (led_max_positon - led_min_posiiton));
    int index = fraction * ledMaxBrghtness;
    ledBrightness = LED_CURVE[index];
  }
  analogWrite(pin, ledBrightness);
}

void updateEncoderPosition() {
  long newPosition = ENCODER.read();
  if (newPosition != ENCODER_POSITION) {
    if (newPosition > ENCODER_MAX_POSITION) {
      ENCODER.write(ENCODER_MAX_POSITION);
      newPosition = ENCODER_MAX_POSITION;
    } else if (newPosition < ENCODER_MIN_POSITION) {
      ENCODER.write(ENCODER_MIN_POSITION);
      newPosition = ENCODER_MIN_POSITION;
    }
    ENCODER_POSITION = newPosition;
  }
}

void intializePins () {
  pinMode(LED_SAVE_PIN, OUTPUT);
  for (int idx = 0; idx < LED_PARAM_PINS_LENGTH; idx++) {
    pinMode(LED_PARAM_PINS[idx], OUTPUT);
  }
  for (int idx = 0; idx < LED_ENCODER_PINS_LENGTH; idx++) {
    pinMode(LED_ENCODER_PINS[idx], OUTPUT);
  }
  pinMode(PARAM_BUTTON_PIN, INPUT_PULLUP);
}

void turnOnLeds () {
  digitalWrite(LED_SAVE_PIN, HIGH);
}