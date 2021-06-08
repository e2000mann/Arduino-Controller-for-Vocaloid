// Arduino Controller for Vocaloid by Emma Mann

// external libraries
#include <LiquidCrystal.h>

// global variables
const String DEFAULTPITCH = "C3", DEFAULTLENGTH = "1/8";
// pins (digital)
// pitch pins
const int pitchUp = 0, pitchDown = 1;
// modifier pins
const int addY = 3, handakuten = 4, dakuten = 5;
// submit pin
const int submit = 2;
// lcd panel
const int rs = 9, en = 8, d4 = 10, d5= 11, d6= 12, d7= 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// pins (analog)
int lengthChange = 0;
int consonantValue = 0;
int vowelValue = 0;

void setup() {
  // initialise pins as input
  pinMode(pitchUp, INPUT);
  pinMode(pitchDown, INPUT);
  pinMode(submit, INPUT);
  pinMode(addY, INPUT);
  pinMode(handakuten, INPUT);
  pinMode(dakuten, INPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (digitalRead(submit) == LOW)
  {
    checkPins();
  }
  // submit button pressed
  addNote();
}

void addNote(){
  // adds note to v5 editor
  // maybe use final data from checkPins() in loop
  // so not needed to call function in here
  checkPins();
}

// won't be void but do not yet know how data will be handled
void checkPins(){
  // checks pins
  char consonant = getConsonant();
  delay(100); // for stability
  char vowel = getVowel();
  delay(100);
  if (consonant != 'n' && vowel == ' '){
    // will have to break
    return;
  }
  if (consonant == 'h' && vowel == 'u'){
    consonant = 'f';
  }
}

char getConsonant(){
  int temp = analogRead(consonantValue);
  Serial.println(temp);
  if (temp < 100){ return ' '; } // no consonant
  if (temp < 150){
    // k or g (depends on dakuten)
    if (digitalRead(dakuten) == HIGH){
      return 'g';
    }
    return 'k';
  }
  if (temp < 250){
    // s or z
    if (digitalRead(dakuten) == HIGH){
      return 'z';
    }
    return 's';
  }
  if (temp < 350){
    // t or d
    if (digitalRead(dakuten) == HIGH){
      return 'd';
    }
    return 't';
  }
  if (temp < 450){ return 'n'; } // always n
  if (temp < 550){
    //h, b or p (or f if f+u, need to work out how that'll work)
    if (digitalRead(dakuten) == HIGH){
      return 'b';
    }
    if (digitalRead(handakuten) == HIGH){
      return 'p';
    }
    return 'h';
  }
  if (temp < 650) { return 'm'; } // always m
  if (temp < 750) { return 'y'; } // always y
  if (temp < 850) { return 'r'; } // always r
  else { return 'w'; } // always w
}

char getVowel(){
  int temp = analogRead(vowelValue);
  Serial.println(temp);
  if (temp < 100){ return 'a'; }
  if (temp < 150){ return 'i'; }
  if (temp < 250){ return 'u'; }
  if (temp < 350){ return 'e'; }
  if (temp < 450){ return 'o'; }
  else { return ' '; }
}