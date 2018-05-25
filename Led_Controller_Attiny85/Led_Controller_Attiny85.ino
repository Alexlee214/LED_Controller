const byte ledOn = 0;
const byte photocell = A2;
const byte mode1Btn = 1;
const byte mode2Btn = 2;
const int led = 3;

bool mode = true; //true means mode 1 and false mean mode 2
bool ledIsOn = false;

unsigned long lastBtnSwitch = 0;
const short debounceTime = 500;

short ledOnly = 0;
short darkPhoto = 0;
const byte photoTolerance = 50;
const byte offMargin = 30;

unsigned long prevDimTime = 0;
bool dimStart = false;

void setup() {
  // put your setup code here, to run once:  
  pinMode(ledOn, OUTPUT);
  pinMode(photocell, INPUT);
  pinMode(mode1Btn, INPUT);
  pinMode(mode2Btn, INPUT);
  pinMode(led, OUTPUT);
  initializePhotocell();
}

void loop() {
  //if in mode 2 and mode 1 button pressed, switch to mode 1
  if(digitalRead(mode1Btn) == HIGH && mode == false){
    mode = true;
    digitalWrite(led, LOW);
  }
  
  //if in mode 1 and mode 1 button pressed, switch to mode 2
  if(digitalRead(mode2Btn) == HIGH && mode == true){
    mode = false;
    digitalWrite(led, HIGH);
  }

  if(mode == true){
    manualMode();
  }else if(mode == false){
    autoMode();
  }
}



//pressing the button turns led on and off
void manualMode(){
  if(digitalRead(mode1Btn) == HIGH && millis() - lastBtnSwitch >= debounceTime){
    if (ledIsOn == true){
      turnLEDOff();
    }
    else{
      turnLEDOn();
    }
    lastBtnSwitch = millis();
  }

}

void autoMode(){
  //when the light is on
  if(abs(analogRead(photocell) -  photoTolerance) > darkPhoto && ledIsOn == false){
    turnLEDOn();
    
  //when light turns off  
  }else if(ledIsOn == true && analogRead(photocell) - ledOnly < offMargin){
    /*
    if(dimStart = false){
      dimStart = true;
      prevDimTime = millis();
    }

    //after 5 seconds, if still dim, turn off led
    if(millis() - prevDimTime > 5000){
      if(analogRead(photocell) - ledOnly < photoTolerance)
        turnLEDOff();
      dimStart = false;  
    }
  */
    turnLEDOff();
    delay(500);
  }
  
}


//initializes the brightness that the room is in when only the led is on
void initializePhotocell(){
  delay(1000);
  
  digitalWrite(ledOn, LOW);
  int sumPhotocell = 0;
  for(byte countInit = 0; countInit < 20; countInit++){
    sumPhotocell = sumPhotocell + analogRead(photocell);
    delay(100);
  }
  darkPhoto = (int)(sumPhotocell / 20);
  
  digitalWrite(ledOn, HIGH);
  sumPhotocell = 0;

  delay(1000);

  for(byte countInit = 0; countInit < 20; countInit++){
    sumPhotocell = sumPhotocell + analogRead(photocell);
    delay(100);
  }
  ledOnly = (int)(sumPhotocell / 20);
  digitalWrite(ledOn, LOW);

  delay(5000);
}


void turnLEDOn(){
  ledIsOn = true;
  for(byte countBrightness = 0; countBrightness < 255; countBrightness = countBrightness = countBrightness + 5){
    analogWrite(ledOn, countBrightness);
    delay(30);
  }
  digitalWrite(ledOn, HIGH);
}

void turnLEDOff(){
    ledIsOn = false;
    for(byte countBrightness = 255; countBrightness > 0; countBrightness = countBrightness = countBrightness - 5){
      analogWrite(ledOn, countBrightness);
      delay(30);
    }
    digitalWrite(ledOn, LOW);
}

