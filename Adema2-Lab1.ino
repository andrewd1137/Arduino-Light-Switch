//Andrew DeMarco
const int BLUEpin = 2;
const int REDpin = 3;
const int GREENpin = 4;
const int BUTTONpin = 5;
const int SHOCKpin = 6;

int buttonCounter = 0;
int lastButtonState = 0;

const long interval = 500;  //amount of time for blinking light
unsigned long previousMillis = 0; //clock starts off at 0
int ledState = LOW; //led starts off

void setup() {
  // put your setup code here, to run once:
  //configure the pin direction

  pinMode(BLUEpin, OUTPUT);
  pinMode(REDpin, OUTPUT);
  pinMode(GREENpin, OUTPUT);

  //start with leds off
  digitalWrite(REDpin, LOW);
  digitalWrite(GREENpin, LOW);
  digitalWrite(BLUEpin, LOW);

  pinMode(BUTTONpin, INPUT);
  digitalWrite(BUTTONpin, LOW);

  pinMode(SHOCKpin, INPUT);
  digitalWrite(SHOCKpin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonStatus = digitalRead(BUTTONpin);
  int shockStatus = digitalRead(SHOCKpin);
  
  unsigned long currentMillis = millis();  //counts the miliseconds that goes by during loop

//code checks to see if button state changes and adds 1 to the counter if the state changes
 if(buttonStatus != lastButtonState){
    if(buttonStatus == LOW){
      buttonCounter++;
    }
  }
  lastButtonState = buttonStatus;

  //the red led turns on
  if(buttonCounter == 1){
    digitalWrite(REDpin, HIGH);
    digitalWrite(GREENpin, LOW);
    digitalWrite(BLUEpin, LOW);
  }else if(buttonCounter == 2){ //button is pressed again, red led turns off and green led flashes
    digitalWrite(REDpin, LOW);
    if (currentMillis - previousMillis >= interval) {  //checks to see if the time interval set is met before executing code inside
      previousMillis = currentMillis;

    //changes the state of the led so it flashes on and off
    if (ledState == LOW) {  
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(GREENpin, ledState);
  }

  //turns the green led on for good
  }else if(buttonCounter == 3){
    digitalWrite(REDpin, LOW);
    digitalWrite(GREENpin, HIGH);
    digitalWrite(BLUEpin, LOW);
  }

   //if the shock sensor goes off at any time, it shuts off all leds and sets the button counter back to 0 to reset code
 if(shockStatus == HIGH){
    digitalWrite(REDpin, LOW);
    digitalWrite(GREENpin, LOW);
    digitalWrite(BLUEpin, LOW);
    buttonCounter = 0; 
  }
}
