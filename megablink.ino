#define ledUP 2
#define ledDown 3
#define buttOnZ 6

unsigned long lastPress;
unsigned long lastBlink;

bool pressFlag = false;
bool rgbIsRuning = false;
int ledLegs = 1;
int stepFlag = 5;

int redColorCount = 0;
int greenColorCount = 0;
int blueColorCount = 0;
int ColorCount = 0;

int redPin = 5;
int greenPin = 9;
int bluePin = 11;

unsigned long test;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledUP, OUTPUT);
  pinMode(ledDown, OUTPUT);
  pinMode(buttOnZ, INPUT);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  Serial.begin(9600); 
  blueColorCount=255; 
}

void rgbRound() {
  //if (rgbIsRuning) { // мигаем туда 
/*    if (digitalRead(redPin)==LOW && digitalRead(greenPin)==LOW && digitalRead(bluePin)==LOW) {
       digitalWrite(redPin, HIGH);
    }*/
    ColorCount+=stepFlag;
    
    if (rgbIsRuning){
      if(stepFlag!=5){
        ColorCount-=1;
      }
      stepFlag=5;
    }
    else{
      if(stepFlag!=-5){
        ColorCount+=1;
      }
      stepFlag=-5;
    }
    
    
    Serial.print("R/G/B   ");
    Serial.print(redColorCount);
    Serial.print("/");
    Serial.print(greenColorCount);
    Serial.print("/");
    Serial.println(blueColorCount);

    if(ColorCount>=0 && ColorCount<=255){redColorCount+=stepFlag;}      //красный +
    if(ColorCount>=256 && ColorCount<=510){redColorCount-=stepFlag;}    //красный -
    
    if(ColorCount>=256 && ColorCount<=510){greenColorCount+=stepFlag;}  //зеленый +
    if(ColorCount>=511 && ColorCount<=765){greenColorCount-=stepFlag;}  //зеленый -
    
    if(ColorCount>=511 && ColorCount<=765){blueColorCount+=stepFlag;}   //голубой +
    if(ColorCount>=0 && ColorCount<=255){blueColorCount-=stepFlag;}     //голубой -

    if(redColorCount<0){redColorCount=0;}
    if(greenColorCount<0){greenColorCount=0;}
    if(blueColorCount<0){blueColorCount=0;}
    
    if(redColorCount>255){redColorCount=255;}
    if(greenColorCount>255){greenColorCount=255;}
    if(blueColorCount>255){blueColorCount=255;}

    if (rgbIsRuning){
      if(ColorCount==754||ColorCount==765||ColorCount==756){ColorCount=0;}
    }
    else{
      if(ColorCount==-1||ColorCount==0||ColorCount==1){ColorCount=765;}
    }

    analogWrite(redPin, redColorCount);
    analogWrite(greenPin, greenColorCount);
    analogWrite(bluePin, blueColorCount);
    
    /*
    if (redColorCount!=0 && greenColorCount!=255) {
      /*Serial.print(" кр-зел   ");
      Serial.print(redColorCount);
      Serial.print("---");
      Serial.println(greenColorCount);*//*
      analogWrite(redPin, (redColorCount-=15));
      analogWrite(greenPin, (greenColorCount+=15));
      if(blueColorCount==255){blueColorCount=0;}
    }
    if (greenColorCount!=0 && blueColorCount!=255) {
      /*Serial.print("зел-гол   ");
      Serial.print(greenColorCount);
      Serial.print("---");
      Serial.println(blueColorCount);*//*
      analogWrite(greenPin, greenColorCount-=15);
      analogWrite(bluePin, blueColorCount+=15);
      if(redColorCount==255){redColorCount=0;}
    }
    if (blueColorCount!=0 && redColorCount!=255) {
      /*Serial.print("гол-кр    ");
      Serial.print(blueColorCount);
      Serial.print("---");
      Serial.println(redColorCount);*//*
      analogWrite(bluePin, blueColorCount-=15);
      analogWrite(redPin, redColorCount+=15);
      if(greenColorCount==255){greenColorCount=0;}
    }*/
    
    /*
    if (digitalRead(redPin)==HIGH) {
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, HIGH);
    }
    else if (digitalRead(greenPin)==HIGH) {
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, HIGH);
    }
    else if (digitalRead(bluePin)==HIGH) {
      digitalWrite(bluePin, LOW);
      digitalWrite(redPin, HIGH);
    }
    else {
      digitalWrite(redPin, HIGH);
    }
   /*  digitalWrite(redPin, LOW);
     digitalWrite(greenPin, LOW);
     digitalWrite(bluePin, LOW);*/
  //}
 /* if (!rgbIsRuning) {// мигаем сюда
    if (digitalRead(redPin)==HIGH) {
      digitalWrite(redPin, LOW);
      digitalWrite(bluePin, HIGH);
    }
    else if (digitalRead(bluePin)==HIGH) {
      digitalWrite(bluePin, LOW);
      digitalWrite(greenPin, HIGH);
    }
    else if (digitalRead(greenPin)==HIGH) {
      digitalWrite(greenPin, LOW);
      digitalWrite(redPin, HIGH);
    }
    else {
      digitalWrite(redPin, HIGH);
    }
  }*/
}

void loop() {
 if (millis() - lastBlink > 100) {
   rgbRound();
   lastBlink = millis();
 }
  
  test = millis() - lastPress;
  if ((digitalRead(buttOnZ) == LOW) && (test >400) && (!pressFlag)) {
    lastPress = millis();
  
    if (digitalRead(ledUP) == LOW) {
     Serial.println("ЗАЖИГАЕМ");
     digitalWrite(ledUP, HIGH);
     digitalWrite(ledDown, LOW);
     rgbIsRuning = true;
    }
    else if (digitalRead(ledUP) == HIGH){
      Serial.println("ГАСИМ");
     digitalWrite(ledUP, LOW); 
     digitalWrite(ledDown, HIGH);
     rgbIsRuning = false;
    }
     pressFlag = true;
  }
 
   if (digitalRead(buttOnZ) == HIGH) {
   pressFlag = false;
   }
}
