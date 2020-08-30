//##################################
//#### USER CONFIGURABLE VALUES ####
//##################################

//TODO: print out cycles on boot

//Each Intervalcycle all outputs will be switched consecutively
#define INTERVALCYCLE_0 1*60 //  Seconds. 00 / DIP 1=Off, DIP 2=Off
#define INTERVALCYCLE_1 10*60 // Seconds. 01 / DIP 1=Off, DIP 2=On
#define INTERVALCYCLE_2 30*60 // Seconds. 10 / DIP 1=On, DIP 2=Off
#define INTERVALCYCLE_3 60*60 // Seconds. 11 / DIP 1=On, DIP 2=On

#define OUTPUT_ON_TIME 10 //Seconds. How long each individual output stays on
#define TRIGGER_DELAY 1 //Seconds. Delay for trigger output after output activation
#define TRIGGER_ON_TIME 0.5 //Seconds. Length of the trigger pulse. Should be lower than OUTPUT_ON_TIME-TRIGGER_DELAY
#define OUTPUT_DELAY 2 //Seconds. Off time between output activations

#define TRIGGER_ACTIVE HIGH //Trigger output Active HIGH or Active LOW

uint8_t outputcount=32; //How many outputs to use


//############################
//#### END OF USER VALUES ####
//############################



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

boolean dualoutput; //use two relais as one output. gets set by dip switch 4

#define INFOINTERVAL 60 //Seconds. In run mode, how much time between time info messages when waiting

unsigned long intervalcycletime=1; //interval in seconds. maximum is 65535 seconds = 18 hours

 
uint16_t selectedOutput=0;

uint16_t cyclecount = 0; //just a counter
unsigned long lastCycleStart=0;
boolean firstRun=true;
unsigned long lastInfo=0;


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
  switchOffAllOutputs(); //TODO: assume maximum cards connected
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


  dualoutput=!digitalRead(PIN_DIP4);
  
  
  digitalWrite(PIN_LED, LOW);
  digitalWrite(LED_BUILTIN, LOW);

  
  if (dualoutput) {
    outputcount*=2;
    Serial.println("Dualoutput enabled");
  }
  Serial.print("Configured to use "); Serial.print(outputcount); Serial.println(" outputs.");
  
  Serial.println("Timing configuration:");
  Serial.print("OUTPUT_ON_TIME="); Serial.print(OUTPUT_ON_TIME); Serial.println(" s");
  Serial.print("TRIGGER_DELAY="); Serial.print(TRIGGER_DELAY); Serial.println(" s");
  Serial.print("TRIGGER_ON_TIME="); Serial.print(TRIGGER_ON_TIME); Serial.println(" s");
  Serial.print("OUTPUT_DELAY="); Serial.print(OUTPUT_DELAY); Serial.println(" s");

  if (!digitalRead(PIN_BUTTON)) { //button pressed on boot
    mode=2; //set test mode
    Serial.println("TESTMODE");
  }

  Serial.println("Waiting for user to start cycle. Press Button!");
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
      loopIdle();
      break;
    case 1:
      loopRun();
      break;
    case 2: //Output Test
      loopTest();
      break;
  }
  
}

void loopIdle()
{
  if (buttonFlag) { //button pressed
    //Read DIP switches
    Serial.print("DIP=");
    Serial.print(digitalRead(PIN_DIP1));
    Serial.print(digitalRead(PIN_DIP2));
    Serial.print(digitalRead(PIN_DIP3));
    Serial.println(digitalRead(PIN_DIP4));

    uint8_t intervalsel = !digitalRead(PIN_DIP2) + !digitalRead(PIN_DIP1)*2;
    Serial.print("interval selection = "); Serial.println(intervalsel);
    switch(intervalsel) {
      case 0:
        intervalcycletime=INTERVALCYCLE_0;
        break;
      case 1:
        intervalcycletime=INTERVALCYCLE_1;
        break;
      case 2:
        intervalcycletime=INTERVALCYCLE_2;
        break;
      case 3:
        intervalcycletime=INTERVALCYCLE_3;
        break;
    }
    Serial.print("intervalcycletime = "); Serial.print(intervalcycletime); Serial.println(" seconds");

    
    for (uint8_t x=0;x<10; x++) { //blink fast for some time
      digitalWrite(LED_BUILTIN, HIGH); delay(25); digitalWrite(LED_BUILTIN, LOW); delay(25);
    }
    delay(1000-300);
    //Blink Intervalselection number
    for (uint8_t b=0;b<intervalsel; b++) {
      delay(300);
      digitalWrite(LED_BUILTIN, HIGH); delay(300); digitalWrite(LED_BUILTIN, LOW);
    }
    delay(1000);
    
    for (uint8_t x=0;x<10; x++) { //blink fast for some time
      digitalWrite(LED_BUILTIN, HIGH); delay(25); digitalWrite(LED_BUILTIN, LOW); delay(25);
    }
    
    
    mode=1;
    firstRun=true;
    switchOffAllOutputs(); //for extra safety
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(PIN_LED, LOW);
    digitalWrite(PIN_TRIGGER, !TRIGGER_ACTIVE); //Off
    Serial.println("Starting Run Mode");
    delay(1000); //wait a bit

    if (intervalcycletime<= (outputcount/ ( dualoutput ? 2 : 1) )*(OUTPUT_ON_TIME+OUTPUT_DELAY)) { //cycletime not long enough to go through all outputs?
      Serial.println("Error: Intervalcycletime too short for all outputs!");
      Serial.print("Should be at least "); Serial.print((outputcount/ ( dualoutput ? 2 : 1) )*(OUTPUT_ON_TIME+OUTPUT_DELAY)); Serial.println(" Seconds");
      Serial.print("Current Intervalcycletime is "); Serial.print(intervalcycletime); Serial.println(" seconds");
      mode=0; //Do not start run mode
      for (uint8_t i=0;i<20; i++){
        digitalWrite(LED_BUILTIN, i%2==0); //fast blinking
        delay(200);
      }
    }
  }
}

void loopRun()
{
  digitalWrite(PIN_LED, ((millis()/1000)%2==0 ? HIGH : LOW)); //Slowly blink led to show waiting
  
  if (millis() - lastInfo > INFOINTERVAL*(unsigned long)1000) //wait until new cycle starts
  {
    Serial.print("Info: Waiting "); Serial.print((intervalcycletime*(unsigned long)1000 - (millis() - lastCycleStart))/1000 ); Serial.println(" s for next cycle");
    lastInfo=millis();
  }

  if (millis() - lastCycleStart > intervalcycletime*(unsigned long)1000 || firstRun) //wait until new cycle starts
  {
    firstRun=false;
    Serial.print("Starting cycle "); Serial.println(cyclecount);
    digitalWrite(PIN_LED, LOW); //led off
    lastCycleStart = millis();
    
    for (selectedOutput=0; selectedOutput<outputcount;selectedOutput+= (dualoutput ? 2 : 1)) { //go through all outputs
      Serial.print("output="); Serial.print(selectedOutput); 
      if (dualoutput) { Serial.print(","); Serial.print(selectedOutput+1); }
      Serial.print(" / "); Serial.println(outputcount-1);
      
      selectOutput(selectedOutput);
      digitalWrite(PIN_LED, HIGH); //LED On
      delay(TRIGGER_DELAY*(unsigned long)1000);
      digitalWrite(PIN_TRIGGER, TRIGGER_ACTIVE); //On
      digitalWrite(LED_BUILTIN, HIGH); //visual indicator
      delay(TRIGGER_ON_TIME*(unsigned long)1000);
      digitalWrite(PIN_TRIGGER, !TRIGGER_ACTIVE); //Off
      digitalWrite(LED_BUILTIN, LOW);
      delay((OUTPUT_ON_TIME-TRIGGER_ON_TIME-TRIGGER_DELAY)*(unsigned long)1000); //wait until turn off
      switchOffAllOutputs(); //all off
      digitalWrite(PIN_LED, LOW); //LED Off
  
      delay(OUTPUT_DELAY*(unsigned long)1000); //off time
      lastInfo=0; //force immediate info print
    }
    cyclecount++;
  }
}


void loopTest()
{
  dualoutput=false; //test only single outputs
  digitalWrite(PIN_LED, LOW); //led off, may be still on from button press
  
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

  if (!digitalRead(PIN_BUTTON)) {
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
    selectOutput(_output);
    for (uint8_t i=0;i<ARRAYSIZE; i++) {
      Serial.println(dataArray[i], BIN);
    }
    delay(1000);
  }
  Serial.println("All outputs off");
  switchOffAllOutputs();
  Serial.println();

  testcycles++;
}

void switchOffAllOutputs() {
  for (int j = 0; j < ARRAYSIZE; j++) { //for every byte
    dataArray[j]=0xFF; //reset. Active Low
  }
  updateShiftregister();
}

void selectOutput(uint16_t n) {
  for (int j = 0; j < ARRAYSIZE; j++) { //for every byte
    dataArray[j]=0xFF; //reset. Active Low
  }
  uint8_t byteIndex = n/8; //calculate byte
  dataArray[byteIndex] = ~(1<<(n%8)); //bit index at calculated byte

  
  if (dualoutput) { //switch on next output too
    uint8_t byteIndex = (n+1)/8; //calculate byte
    dataArray[byteIndex] &= ~(1<<((n+1)%8)); //bit index at calculated byte  
  }
  
  updateShiftregister();

  
}

void updateShiftregister() { //shift data from array to shiftregisters which activate the corresponding relais
  digitalWrite(PIN_LATCH, LOW); //hold last stored value on shift register output
  for (int j = 0; j < ARRAYSIZE; j++) { //for every byte
    shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, dataArray[ARRAYSIZE-1-j]); //send data
  }
  digitalWrite(PIN_LATCH, HIGH); //latch new valid values to shift register outputs
}
