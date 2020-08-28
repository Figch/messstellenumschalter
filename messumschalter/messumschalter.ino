#define PIN_LATCH 8 //74HC595 Pin 12 ST_CP (Latch) connected to Arduino D8
#define PIN_CLOCK 12 //74HC595 Pin 11 SH_CP (clock) connected to Arduino D12
#define PIN_DATA 11 //74HC595 Pin 14 DS (data) connected to Arduino D11
#define PIN_ENABLE 9 //74HC595 Pin 13 OE (output enable) connected to Arduino D9

#define PIN_BUTTON A0
#define PIN_LED A1

#define PIN_TRIGGER 10 //Trigger Signal Output. Arduino Pin D2

#define PIN_DIP1 7
#define PIN_DIP2 6
#define PIN_DIP3 5
#define PIN_DIP4 4

unsigned long last_button_down = 0;
#define BUTTON_DEBOUNCETIME 200

byte data;
#define ARRAYSIZE 8 //set to maximum possible relais modules. One array covers 8 channels.
byte dataArray[ARRAYSIZE];
 
uint16_t selectedOutput=0;

#define TRIGGER_ACTIVE HIGH


uint8_t mode = 0; // 0=idle, 1=running, 2=output test
boolean buttonFlag;

uint16_t testcycles = 0; //for test mode

void setup() {
  //Initialize Inputs and Outputs and set default startup values
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_CLOCK, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_ENABLE, OUTPUT);
  digitalWrite(PIN_ENABLE, HIGH); //disable shift register outputs
  switchOffAllRelais(); //TODO: assume maximum cards connected
  digitalWrite(PIN_ENABLE, LOW); //enable outputs

  pinMode(PIN_TRIGGER, OUTPUT); digitalWrite(PIN_TRIGGER, !TRIGGER_ACTIVE); //Initialize Trigger Output

  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT); digitalWrite(PIN_LED, HIGH);
  pinMode(LED_BUILTIN, OUTPUT); digitalWrite(LED_BUILTIN, HIGH);
  
  pinMode(PIN_DIP1, INPUT_PULLUP);
  pinMode(PIN_DIP2, INPUT_PULLUP);
  pinMode(PIN_DIP3, INPUT_PULLUP);
  pinMode(PIN_DIP4, INPUT_PULLUP);
  
  Serial.begin(9600);
  Serial.println("Booting");
  Serial.print("DIP=");
  Serial.print(digitalRead(PIN_DIP1));
  Serial.print(digitalRead(PIN_DIP2));
  Serial.print(digitalRead(PIN_DIP3));
  Serial.println(digitalRead(PIN_DIP4));

  
  
  digitalWrite(PIN_LED, LOW);
  digitalWrite(LED_BUILTIN, LOW);

  if (!digitalRead(PIN_BUTTON)) { //button pressed on boot
    mode=2; //set test mode
    Serial.println("TESTMODE");
  }
}

void loop() {

  buttonFlag = false;
  if (!digitalRead(PIN_BUTTON)) { //button pressed
    digitalWrite(PIN_LED, HIGH); //led on
    if (millis() - last_button_down > BUTTON_DEBOUNCETIME) {
      buttonFlag = true;
    }
    last_button_down=millis();
  }
  else {
    digitalWrite(PIN_LED, LOW); //led off
  }

  switch(mode) {
    case 0:
      break;
    case 1:
      break;
    case 2: //Output Test
      loopTest();
      break;
  }

  if (buttonFlag) {
    Serial.println("Button!");
    
  }
  

  

  
  
}


void loopTest()
{
  Serial.print("Testcycle="); Serial.println(testcycles);
  Serial.print("DIP=");
  Serial.print(digitalRead(PIN_DIP1));
  Serial.print(digitalRead(PIN_DIP2));
  Serial.print(digitalRead(PIN_DIP3));
  Serial.println(digitalRead(PIN_DIP4));

  delay(500);
  Serial.println();
  Serial.println("button test...");
  delay(1000);

  if (buttonFlag) {
    Serial.println("Button Pressed");
  }else{
    Serial.println("Button Not Pressed");
  }

  
  Serial.println();
  delay(500);
  Serial.println("Testing LED_BUILTIN");
  delay(1000);
  Serial.println("LED_BUILTIN Off");
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  Serial.println("LED_BUILTIN On");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  Serial.println("LED_BUILTIN Off");
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println();
  delay(500);
  Serial.println("Testing LED");
  delay(1000);
  Serial.println("LED Off");
  digitalWrite(PIN_LED, LOW);
  delay(1000);
  Serial.println("LED On");
  digitalWrite(PIN_LED, HIGH);
  delay(1000);
  Serial.println("LED Off");
  digitalWrite(PIN_LED, LOW);

  Serial.println();
  delay(500);
  Serial.println("Testing Trigger");
  Serial.print("Trigger is set to active "); Serial.println((TRIGGER_ACTIVE ? "HIGH" : "LOW"));
  delay(1000);
  Serial.println("Trigger Off");
  digitalWrite(PIN_TRIGGER, !TRIGGER_ACTIVE);
  delay(1000);
  Serial.println("Trigger Active");
  digitalWrite(PIN_TRIGGER, TRIGGER_ACTIVE);
  delay(1000);
  Serial.println("Trigger Off");
  digitalWrite(PIN_TRIGGER, !TRIGGER_ACTIVE);

  delay(500);
  Serial.println();
  Serial.print("Testing "); Serial.print(ARRAYSIZE*8); Serial.println(" outputs...");

  delay(1000);

  for (uint16_t _output=0; _output<(ARRAYSIZE*8);_output++) {
    Serial.print("output="); Serial.print(_output); Serial.print(" / "); Serial.println((ARRAYSIZE*8));
    selectRelais(_output);
    for (uint8_t i=0;i<ARRAYSIZE; i++) {
      Serial.println(dataArray[i], BIN);
    }
    delay(1000);
  }
  Serial.println("All outputs off");
  switchOffAllRelais();
  Serial.println();

  testcycles++;
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
