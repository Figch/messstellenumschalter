#define PIN_LATCH 8 //74HC595 Pin 12 ST_CP (Latch) connected to Arduino D8
#define PIN_CLOCK 12 //74HC595 Pin 11 SH_CP (clock) connected to Arduino D12
#define PIN_DATA 11 //74HC595 Pin 14 DS (data) connected to Arduino D11

#define PIN_BUTTON A0
#define PIN_LED A1

#define PIN_DIP1 7
#define PIN_DIP2 6
#define PIN_DIP3 5
#define PIN_DIP4 4

unsigned long last_button_down = 0;
#define BUTTON_DEBOUNCETIME 200

byte data;
#define ARRAYSIZE 2
byte dataArray[ARRAYSIZE];

uint16_t selectedOutput=0;

void setup() {
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_CLOCK, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);

  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT); digitalWrite(PIN_LED, HIGH);
  pinMode(LED_BUILTIN, OUTPUT); digitalWrite(LED_BUILTIN, HIGH);
  
  pinMode(PIN_DIP1, INPUT_PULLUP);
  pinMode(PIN_DIP2, INPUT_PULLUP);
  pinMode(PIN_DIP3, INPUT_PULLUP);
  pinMode(PIN_DIP4, INPUT_PULLUP);
  
  Serial.begin(9600);

  switchOffAllRelais();
  
  digitalWrite(PIN_LED, LOW);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {

  boolean buttonFlag = false;
  if (!digitalRead(PIN_BUTTON)) { //button pressed
    digitalWrite(PIN_LED, HIGH);
    if (millis() - last_button_down > BUTTON_DEBOUNCETIME) {
      buttonFlag = true;
    }
    last_button_down=millis();
  }
  else {
    digitalWrite(PIN_LED, LOW);
  }

  if (buttonFlag) {
    Serial.println("Button!");
    Serial.println(digitalRead(PIN_DIP1));
    Serial.println(digitalRead(PIN_DIP2));
    Serial.println(digitalRead(PIN_DIP3));
    Serial.println(digitalRead(PIN_DIP4));
  }
  

  
  Serial.print("output="); Serial.println(selectedOutput);
  selectRelais(selectedOutput);
  Serial.println(dataArray[0], BIN);
  Serial.println(dataArray[1], BIN);
  delay(100);

  selectedOutput++,
  selectedOutput = selectedOutput % 16;

  
  
}

void switchOffAllRelais() {
  for (int j = 0; j < ARRAYSIZE; j++) { //for every byte
    dataArray[j]=0xFF; //reset. Active Low
  }
  updateShiftregister();
}

void selectRelais(uint16_t n) {
  for (int j = 0; j < ARRAYSIZE; j++) { //for every byte
    dataArray[j]=0xFF; //reset. Active Low
  }
  uint8_t byteIndex = n/8; //calculate byte
  dataArray[byteIndex] = ~(1<<(n%8)); //bit index at calculated byte
  updateShiftregister();
}

void updateShiftregister() { //shift data from array to shiftregisters which activate the corresponding relais
  digitalWrite(PIN_LATCH, LOW); //hold last stored value on shift register output
  for (int j = 0; j < ARRAYSIZE; j++) { //for every byte
    shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, dataArray[ARRAYSIZE-1-j]); //send data
  }
  digitalWrite(PIN_LATCH, HIGH); //latch new valid values to shift register outputs
}
