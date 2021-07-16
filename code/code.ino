// Arduino Voice Synth Controller by Emma Mann
// Requires ATmega32u4 (Leonardo/Mega)

// external libraries
#include <LiquidCrystal.h>

// global variables
// pitch uses midi numbers (60 = C4)
const int DEFAULTPITCH = 60;
const float DEFAULTLENGTH = 0.125;
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
int length = A0;
int vowelValue = A1;
int consonantValue = A2;

void setup() {
  // initialise pins as input
  pinMode(pitchUp, INPUT);
  pinMode(pitchDown, INPUT);
  pinMode(submit, INPUT);
  pinMode(addY, INPUT);
  pinMode(handakuten, INPUT);
  pinMode(dakuten, INPUT);
  Serial.begin(9600); // serial needed to use analog pins
}

void loop() {
  String currentSyllable;
  float currentLength = DEFAULTLENGTH;
  int currentPitch = DEFAULTPITCH;
  while (digitalRead(submit) == LOW)
  { 
    String newSyllable = checkAnalogPins();
    if (newSyllable != ""){
      // don't update syllable if there was invalid input
      currentSyllable = newSyllable;
    }
    currentLength = updateLength();
    bool pitchUpPress = digitalRead(pitchUp) == HIGH;
    bool pitchDownPress = digitalRead(pitchDown) == HIGH;
    if (pitchUpPress || pitchDownPress)
    {
      currentPitch = updatePitch(currentPitch, pitchUpPress);
    }
    
  }
  // submit button pressed
  addNote(currentSyllable, currentLength, currentPitch);
}

void addNote(String syllable, float length, int pitch){
  // adds note to v5 editor
  return;
}

// TODO: is a string a good output?
String checkAnalogPins(){
  String output = "";
  // checks pins
  char consonant = getConsonant();
  delay(100); // for stability
  char vowel = getVowel();
  delay(100);
  if (consonant != 'n' && vowel == ' '){
    // will have to break
    return "";
  }
  if (consonant == 'h' && vowel == 'u'){
    consonant = 'f';
  }
  // TODO: what vowels don't work with y?
  if (digitalRead(addY) == HIGH){
    output = consonant + "y" + vowel;
  } else {
    output = consonant + vowel;
  }
  return output;
}

int updatePitch(int curPitch, bool pitchUp){
  if (pitchUp){
    // pitch up
    curPitch += 1;
  } else {
    // pitch down
    curPitch -= 1;
  }
  return curPitch;
}

float updateLength(){
  // TODO: how to update length
  int temp = analogRead(length);
  return 0.125;
}

// TODO: (here & on getVowel) check values & make switch statements
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