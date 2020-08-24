#define PIN_LATCH 8 //74HC595 Pin 12 ST_CP (Latch) connected to Arduino D8
#define PIN_CLOCK 12 //74HC595 Pin 11 SH_CP (clock) connected to Arduino D12
#define PIN_DATA 11 //74HC595 Pin 14 DS (data) connected to Arduino D11

byte data;
#define ARRAYSIZE 2
byte dataArray[ARRAYSIZE];

uint16_t selectedOutput=0;

void setup() {
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_CLOCK, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  switchOffAllRelais();
}

void loop() {

/*
  dataArray[0]=0x00;
  dataArray[1]=0x00;
  updateShiftregister();
  Serial.println("off");
  digitalWrite(LED_BUILTIN, LOW);

  delay(1000);

  dataArray[0]=0xFF;
  dataArray[1]=0xFF;

  updateShiftregister();
  
  Serial.println("on");
  digitalWrite(LED_BUILTIN, HIGH);

  delay(1000);
  */

  

  Serial.print("output="); Serial.println(selectedOutput);
  selectRelais(selectedOutput);
  Serial.println(dataArray[0], BIN);
  Serial.println(dataArray[1], BIN);
  delay(1000);

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
