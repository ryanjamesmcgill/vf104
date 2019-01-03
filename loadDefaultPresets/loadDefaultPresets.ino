#include <EEPROM.h>

int LED_PARAM_PINS_LENGTH = 8;
int LED_PRESET_PINS_LENGTH = 3;
int MIDI_DATA[3][3][8] = {
  // bank A
  {
    {32,127,50,64,64,0,0,0},
    {70,127,50,64,64,0,0,0},
    {120,127,50,64,64,0,0,0},
  },
  // bank B
  {
    {13,127,0,64,64,16,54,31},
    {70,127,50,64,64,16,50,10},
    {120,127,50,64,64,16,50,8},
  },
  // bank C
  {
    {28,127,0,64,78,16,85,13},
    {31,127,0,64,127,32,84,102},
    {14,0,0,64,127,32,81,60}, // 6ths square
  }
};

void setup() {
  // put your setup code here, to run once:
  write_eeprom();
}

void write_eeprom() {
  // writes MIDI_DATA to eeprom
  int bank_count = 3;
  int preset_count = LED_PRESET_PINS_LENGTH;
  int parameter_count = LED_PARAM_PINS_LENGTH;
  int address = 0;
  //LED_SAVE.On().Update();
  for (int bankIdx = 0; bankIdx < bank_count; bankIdx++) {
    for (int presetIdx = 0; presetIdx < preset_count; presetIdx++) {
      for (int parameterIdx = 0; parameterIdx < parameter_count; parameterIdx++) {
        EEPROM.update(address, MIDI_DATA[bankIdx][presetIdx][parameterIdx]);
        address++;
      }
    }
  }
  //stopSaveIndicator();
}

void loop() {
  // put your main code here, to run repeatedly:

}
