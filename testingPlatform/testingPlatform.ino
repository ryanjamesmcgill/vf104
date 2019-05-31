void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // output to computer monitor
  Serial1.begin(31250); // output to computer monitor
  Serial.println("Waiting for VF-104 preset...");
}


char MIDI_CC = 0xB0;
int STATE_PARMETER_SEQUENCE = 0;

void loop() {
  
  if (Serial1.available() >= 3) {
    byte inByte1 = Serial1.read();
    byte inByte2 = Serial1.read();
    byte inByte3 = Serial1.read();
    
    Serial.print(inByte1, HEX);
    Serial.print("-");
    Serial.print(inByte2, DEC);
    Serial.print("-");
    Serial.print(inByte3, DEC);
    Serial.println(" ");

    if (checkForPreset_VF104(inByte1, inByte2, inByte3)) {
      Serial.println("Detected VF-104 Preset!");
      STATE_PARMETER_SEQUENCE = 0;
    }
  }
}

bool checkForPreset_VF104(byte inByte1, byte inByte2, byte inByte3) {
  bool valid = true;
  byte ccMidi = 0xB0;
  
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

  // is first byte a ccMessage?
  if (inByte1 != ccMidi) { 
    valid = false;
    STATE_PARMETER_SEQUENCE = 0;
  }

  // is the second byte the exected CC number?
  if (valid && inByte2 != parameters[STATE_PARMETER_SEQUENCE]) {
    valid = false;
    STATE_PARMETER_SEQUENCE = 0;
  }

  // if still valid then we can inncrement the parameter sequecne
  if (valid) {
    STATE_PARMETER_SEQUENCE++;
  }

  // Have we recieved an entire preset of 8 CC messages?
  if (valid && STATE_PARMETER_SEQUENCE != 8) {
    valid = false;
  }

  return valid;
}