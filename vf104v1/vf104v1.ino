#include <Encoder.h>
#include <JC_Button.h>
#include <jled.h>
#include <EEPROM.h>

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

int MIDI_DATA[3][3][8] = {
  // bank A
  {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
  },
  // bank B
  {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
  },
  // bank C
  {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
  }
};
int ACTIVE_MIDI_DATA[8] = {0,0,0,0,0,0,0,0};
int ACTIVE_MIDI_DATA_LENGTH = 8;

int ENCODER_A_PIN = 18;
int ENCODER_B_PIN = 19;
Encoder ENCODER(ENCODER_B_PIN, ENCODER_A_PIN);
int ENCODER_MAX_POSITION = 127;
int ENCODER_MIN_POSITION = 0;
int LED_PARAM_PINS[] = {32, 33, 34, 35, 36, 37, 38, 39};
int LED_PARAM_PINS_LENGTH = 8;
int LED_PRESET_PINS[] = {23, 25, 27};
int LED_PRESET_PINS_LENGTH = 3;
int BUTTON_PRESET_PINS[] = {22, 24, 26};
int LED_SAVE_PIN = 29;
int LED_ENCODER_PINS[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 44, 45, 46};
int LED_ENCODER_PINS_LENGTH = 15;
float LED_ENCODER_STEP_POSITION = (ENCODER_MAX_POSITION - ENCODER_MIN_POSITION) / LED_ENCODER_PINS_LENGTH;
int PARAM_BUTTON_PIN = 30;
int SAVE_BUTTON_PIN = 28;
int BANK_A_BUTTON_PIN = 40;
int BANK_B_BUTTON_PIN = 41;
int BANK_C_BUTTON_PIN = 42;

int ENCODER_LED_MAX_BRIGHTNESS = 255; // 0-255
int MIDI_DELAY_BETWEEN_PARAMETERS_MS = 10; // delay time between each parameter when sending a preset via midi

int STATE_BANK = 0; // 0,1,2 indicating current preset bank
int STATE_PRESET = 0; // 0,1,2indicating current preset
int STATE_PARAMETER = 0; // 0-7 indicating current parameter
bool STATE_SAVE_INDICATOR = false; // indicates if save led should be blinking

// special case parameters with descrete settings
int PARAMETER_DELAY_MODE = 1;
int PARAMETER_LFO_WAVEFORM = 5;

Button PARAM_BUTTON(PARAM_BUTTON_PIN, 100);
Button BANK_A_BUTTON(BANK_A_BUTTON_PIN);
Button BANK_B_BUTTON(BANK_B_BUTTON_PIN);
Button BANK_C_BUTTON(BANK_C_BUTTON_PIN);
Button PRESET_0_BUTTON(BUTTON_PRESET_PINS[0]);
Button PRESET_1_BUTTON(BUTTON_PRESET_PINS[1]);
Button PRESET_2_BUTTON(BUTTON_PRESET_PINS[2]);
Button SAVE_BUTTON(SAVE_BUTTON_PIN);
JLed LED_SAVE = JLed(LED_SAVE_PIN);

void setup() {
  Serial.begin(31250);
  initializePins();
  PARAM_BUTTON.begin();
  BANK_A_BUTTON.begin();
  BANK_B_BUTTON.begin();
  BANK_C_BUTTON.begin();
  PRESET_0_BUTTON.begin();
  PRESET_1_BUTTON.begin();
  PRESET_2_BUTTON.begin();
  SAVE_BUTTON.begin();
  setParameterLeds();
  setPresetLeds();
  read_eeprom();
  loadActiveMidiData();
  sendMidiPreset();
  setEncoderToCurrentParameter();
}

void loop() {
  updateBanks();
  updatePresets();
  updateParameters();
  updateEncoderPosition();
  updateSave();
  updateLeds();
}

void updateLeds() {
  LED_SAVE.Update();
}

void startSaveIndicator(){
  if (STATE_SAVE_INDICATOR == false) {
    STATE_SAVE_INDICATOR = true;
    LED_SAVE.Blink(500,500).Forever();
  }
}

void stopSaveIndicator(){
  STATE_SAVE_INDICATOR = false;
  LED_SAVE.Stop();
}

void updateSave() {
  SAVE_BUTTON.read();
  if ( SAVE_BUTTON.wasPressed() ) {
    writeActiveMidiData();
    write_eeprom();
  }
}

void updateBanks() {
  BANK_A_BUTTON.read();
  BANK_B_BUTTON.read();
  BANK_C_BUTTON.read();
  if ( BANK_C_BUTTON.isPressed() && STATE_BANK != 2 ) {
    STATE_BANK = 2;
    loadActiveMidiData();
    sendMidiPreset();
    setEncoderToCurrentParameter();
  } else if ( BANK_B_BUTTON.isPressed() && STATE_BANK != 1 ) {
    STATE_BANK = 1;
    loadActiveMidiData();
    sendMidiPreset();
    setEncoderToCurrentParameter();
  } else if ( BANK_A_BUTTON.isPressed() && STATE_BANK != 0 ){
    STATE_BANK = 0;
    loadActiveMidiData();
    sendMidiPreset();
    setEncoderToCurrentParameter();
  }
}
  
void updatePresets() {
  PRESET_0_BUTTON.read();
  PRESET_1_BUTTON.read();
  PRESET_2_BUTTON.read();
  if ( PRESET_0_BUTTON.wasPressed() ) {
    STATE_PRESET = 0;
    loadActiveMidiData();
    sendMidiPreset();
    setPresetLeds();
    setEncoderToCurrentParameter();
  } else if ( PRESET_1_BUTTON.wasPressed() ) {
    STATE_PRESET = 1;
    loadActiveMidiData();
    sendMidiPreset();
    setPresetLeds();
    setEncoderToCurrentParameter();
  } else if ( PRESET_2_BUTTON.wasPressed() ) {
    STATE_PRESET = 2;
    loadActiveMidiData();
    sendMidiPreset();
    setPresetLeds();
    setEncoderToCurrentParameter();
  }
}

void updateParameters() {
  // update parameter
  PARAM_BUTTON.read();
  if ( PARAM_BUTTON.wasPressed() ) {
    nextParam();
    setEncoderToCurrentParameter();
    setParameterLeds();
  }
}

void nextParam() {
  // only called when "next param" button is pressed
  STATE_PARAMETER = STATE_PARAMETER + 1;
  if (STATE_PARAMETER >= LED_PARAM_PINS_LENGTH) {
    STATE_PARAMETER = 0;
  }
}

void setPresetLeds() {
  // only called when a preset footswitch is pressed
  for (int idx = 0; idx < LED_PRESET_PINS_LENGTH; idx++) {
    if (idx == STATE_PRESET) {
      digitalWrite(LED_PRESET_PINS[idx], HIGH);
      // write encoder value for current bank, preset, param
    } else {
      digitalWrite(LED_PRESET_PINS[idx], LOW);
    }
  }
}

void setParameterLeds() {
  for (int idx = 0; idx < LED_PARAM_PINS_LENGTH; idx++) {
    if (idx == STATE_PARAMETER) {
      digitalWrite(LED_PARAM_PINS[idx], HIGH);
      // write encoder value for current bank, preset, param
    } else {
      digitalWrite(LED_PARAM_PINS[idx], LOW);
    }
  }
}

void setEncoderLeds() {
  if (STATE_PARAMETER == PARAMETER_DELAY_MODE) {
    int delayModeCCValue = ACTIVE_MIDI_DATA[STATE_PARAMETER];
    for (int idx = 0; idx < LED_ENCODER_PINS_LENGTH; idx++) {
      int ledBrightness = 0;
      if(idx == 0 && delayModeCCValue < 64) {
        ledBrightness = ENCODER_LED_MAX_BRIGHTNESS;
      }
      if (idx == 1 && delayModeCCValue >= 64) {
        ledBrightness = ENCODER_LED_MAX_BRIGHTNESS;
      }
      int pin = LED_ENCODER_PINS[idx];
      analogWrite(pin, ledBrightness);
    } 
  } else if (STATE_PARAMETER == PARAMETER_LFO_WAVEFORM) {
    int waveformCCValue = ACTIVE_MIDI_DATA[STATE_PARAMETER];
    for (int idx = 0; idx < LED_ENCODER_PINS_LENGTH; idx++) {
      int ledBrightness = 0;
      if(idx == 9 && waveformCCValue <= 15) { // sine
        ledBrightness = ENCODER_LED_MAX_BRIGHTNESS;
      }
      if (idx == 10 && waveformCCValue >= 16 && waveformCCValue <= 31) { // triangle
        ledBrightness = ENCODER_LED_MAX_BRIGHTNESS;
      }
      if (idx == 11 && waveformCCValue >= 32 && waveformCCValue <= 47) { // square
        ledBrightness = ENCODER_LED_MAX_BRIGHTNESS;
      }
      if (idx == 12 && waveformCCValue >= 48 && waveformCCValue <= 63) { // saw
        ledBrightness = ENCODER_LED_MAX_BRIGHTNESS;
      }
      if (idx == 13 && waveformCCValue >= 64 && waveformCCValue <= 79) { // ramp
        ledBrightness = ENCODER_LED_MAX_BRIGHTNESS;
      }
      if (idx == 14 && waveformCCValue >= 80 && waveformCCValue <= 95) { // s&h
        ledBrightness = ENCODER_LED_MAX_BRIGHTNESS;
      }
      int pin = LED_ENCODER_PINS[idx];
      analogWrite(pin, ledBrightness);
    }
  } else
    for (int idx = 0; idx < LED_ENCODER_PINS_LENGTH; idx++) {
      float max_position = (idx+1) * LED_ENCODER_STEP_POSITION;
      float min_position = idx * LED_ENCODER_STEP_POSITION;
      setEncoderLed(LED_ENCODER_PINS[idx], ACTIVE_MIDI_DATA[STATE_PARAMETER], min_position, max_position);
    }
}

void setEncoderLed(int pin, int encoder_position, float led_min_positon, float led_max_positon) {
  int ledBrightness;
  int ledMaxBrghtness = ENCODER_LED_MAX_BRIGHTNESS;
  float fraction;
  if (encoder_position >= led_max_positon) {
    ledBrightness = LED_CURVE[ledMaxBrghtness];
  } else if (encoder_position <= led_min_positon) {
    ledBrightness = LED_CURVE[0];
  } else {
    fraction = ((encoder_position - led_min_positon) / (led_max_positon - led_min_positon));
    int index = fraction * ledMaxBrghtness;
    ledBrightness = LED_CURVE[index];
  }
  analogWrite(pin, ledBrightness);
}

void updateEncoderPosition() {
  int newPosition = int(ENCODER.read());
  if (newPosition != ACTIVE_MIDI_DATA[STATE_PARAMETER]) {
    if (newPosition > getEncoderMaxPosition()) {
      ENCODER.write(long(getEncoderMaxPosition()));
      newPosition = getEncoderMaxPosition();
    } else if (newPosition < getEncoderMinPosition()) {
      ENCODER.write(long(getEncoderMinPosition()));
      newPosition = getEncoderMinPosition();
    }
    ACTIVE_MIDI_DATA[STATE_PARAMETER] = newPosition;
    setEncoderLeds();
    sendMidiParameter(STATE_PARAMETER);
    startSaveIndicator();
  }
}

int getEncoderMaxPosition() {
  if (STATE_PARAMETER == PARAMETER_DELAY_MODE) {
    return 80;
  } else if (STATE_PARAMETER == PARAMETER_LFO_WAVEFORM) {
    return 95;
  } else {
    return ENCODER_MAX_POSITION;
  }
}

int getEncoderMinPosition() {
  if (STATE_PARAMETER == PARAMETER_DELAY_MODE) {
    return 50;
  } else if (STATE_PARAMETER == PARAMETER_LFO_WAVEFORM) {
    return 0;
  } else {
    return ENCODER_MIN_POSITION;
  }
}

void initializePins () {
  pinMode(LED_SAVE_PIN, OUTPUT);
  for (int idx = 0; idx < LED_PARAM_PINS_LENGTH; idx++) {
    pinMode(LED_PARAM_PINS[idx], OUTPUT);
  }
  for (int idx = 0; idx < LED_PRESET_PINS_LENGTH; idx++) {
    pinMode(LED_PRESET_PINS[idx], OUTPUT);
  }
  for (int idx = 0; idx < LED_ENCODER_PINS_LENGTH; idx++) {
    pinMode(LED_ENCODER_PINS[idx], OUTPUT);
  }
}

void setEncoderToCurrentParameter() {
  ENCODER.write(long(ACTIVE_MIDI_DATA[STATE_PARAMETER]));
  setEncoderLeds();
}

void read_eeprom() {
  // loads MIDI_DATA from eeprom
  int bank_count = 3;
  int preset_count = LED_PRESET_PINS_LENGTH;
  int parameter_count = LED_PARAM_PINS_LENGTH;
  int address = 0;
  for (int bankIdx = 0; bankIdx < bank_count; bankIdx++) {
    for (int presetIdx = 0; presetIdx < preset_count; presetIdx++) {
      for (int parameterIdx = 0; parameterIdx < parameter_count; parameterIdx++) {
        MIDI_DATA[bankIdx][presetIdx][parameterIdx] = EEPROM.read(address);
        address++;
      }
    }
  }
}

void write_eeprom() {
  // writes MIDI_DATA to eeprom
  int bank_count = 3;
  int preset_count = LED_PRESET_PINS_LENGTH;
  int parameter_count = LED_PARAM_PINS_LENGTH;
  int address = 0;
  LED_SAVE.On().Update();
  for (int bankIdx = 0; bankIdx < bank_count; bankIdx++) {
    for (int presetIdx = 0; presetIdx < preset_count; presetIdx++) {
      for (int parameterIdx = 0; parameterIdx < parameter_count; parameterIdx++) {
        EEPROM.update(address, MIDI_DATA[bankIdx][presetIdx][parameterIdx]);
        address++;
      }
    }
  }
  stopSaveIndicator();
}

void loadActiveMidiData() {
  // loads MIDI_DATA[bank][preset] => CURRENT_PREST
  for (int idx = 0; idx < ACTIVE_MIDI_DATA_LENGTH; idx++) {
    ACTIVE_MIDI_DATA[idx] = MIDI_DATA[STATE_BANK][STATE_PRESET][idx];
  }
  stopSaveIndicator();
}

void writeActiveMidiData() {
  // writes ACTIVE_MIDI_DATA => MIDI_DATA[bank][preset]
  for (int idx = 0; idx < ACTIVE_MIDI_DATA_LENGTH; idx++) {
    MIDI_DATA[STATE_BANK][STATE_PRESET][idx] = ACTIVE_MIDI_DATA[idx];
  }
}

int getMidiCcParameter(int index) {
  // returns midi cc parameter coresponding to index of ACTIVE_MIDI_DATA array
  int parameters[] = {
    12, // delay time
    86, // short or long delay mode
    13, // feedback
    7,  // output level
    14, // mix
    102,// lfo waveform
    15, // lfo rate
    16, // lfo amount
  };
  return parameters[index];
}

void sendMidiPreset() {
  // Sends entire midi preset in ACTIVE_MIDI_DATA
  char ccMidi = 0xB0;

  sendMidiParameter(0);
  delay(MIDI_DELAY_BETWEEN_PARAMETERS_MS);
  sendMidiParameter(1);
  delay(MIDI_DELAY_BETWEEN_PARAMETERS_MS);
  sendMidiParameter(2);
  delay(MIDI_DELAY_BETWEEN_PARAMETERS_MS);
  sendMidiParameter(3);
  delay(MIDI_DELAY_BETWEEN_PARAMETERS_MS);
  sendMidiParameter(4); // send mix setting last to mute glitch sounds
  delay(MIDI_DELAY_BETWEEN_PARAMETERS_MS);
  sendMidiParameter(5);
  delay(MIDI_DELAY_BETWEEN_PARAMETERS_MS);
  sendMidiParameter(6);
  delay(MIDI_DELAY_BETWEEN_PARAMETERS_MS);
  sendMidiParameter(7);
}

void sendMidiParameter(int parameter) {
  // Sends only STATE_PARMAETER in ACTIVE_MIDI_DATA
  noInterrupts();
  char ccMidi = 0xB0;
  Serial.write(ccMidi);
  Serial.write(getMidiCcParameter(parameter));
  Serial.write(ACTIVE_MIDI_DATA[parameter]);
  interrupts();
}