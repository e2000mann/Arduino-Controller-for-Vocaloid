// Arduino Voice Synth Controller by Emma Mann
// Requires ATmega32u4 (Leonardo/Mega)

// external libraries
#include <LiquidCrystal.h>

// global variables
// pitch uses midi numbers (60 = C4)
const int DEFAULTPITCH = 60;

const float DEFAULTLENGTH = 0.125;
const float LENGTHS[7] = {0.0625, 0.125, 0.25, 0.5, 1, 2, 4};
const int CURLENGTHVALUE = 0;

const String DEFAULTSYLLABLE[2] = {"","a"} ;

String CURRENTSYLLABLE[2] = {DEFAULTSYLLABLE[0], DEFAULTSYLLABLE[1]};
float CURRENTLENGTH = DEFAULTLENGTH;
int CURRENTPITCH = DEFAULTPITCH;

// pins (digital)
// pitch pins
const int pitchUp = 0, pitchDown = 1;
// modifier pins
const int addY = 3, handakuten = 4, dakuten = 5;
// submit pin
const int submit = 2;
// lcd panel
const int rs = 8, en = 9, d4 = 10, d5= 11, d6= 12, d7= 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// pins (analog)
int lengthValue = A0;
int vowelValue = A1;
int consonantValue = A2;
int contrast = A3;

void setup() {
  // initialise pins as input
  pinMode(pitchUp, INPUT);
  pinMode(pitchDown, INPUT);
  pinMode(submit, INPUT);
  pinMode(addY, INPUT);
  pinMode(handakuten, INPUT);
  pinMode(dakuten, INPUT);
  
  Serial.begin(9600); // serial needed to use analog pins

  // initialise lcd
  analogWrite(contrast, 75);
  lcd.begin(16, 2);
  lcd.print("current note:");
}

void loop() {

  if (digitalRead(submit) == HIGH){
    // submit button pressed
    addNote(CURRENTSYLLABLE, CURRENTLENGTH, CURRENTPITCH);
  }

  else {
    int consonantRead = analogRead(consonantValue);
    bool updateConst = consonantRead > 160;

    int vowelRead = analogRead(vowelValue);
    bool updateVowel = vowelRead > 160;

    int lengthRead = analogRead(lengthValue);
    bool updateLength = (CURLENGTHVALUE - 100) < lengthRead || (CURLENGTHVALUE + 100) > lengthRead;

    if (updateConst || updateVowel || updateLength){
      update(updateConst, updateVowel, updateLength);
    }

    char test[32];
    snprintf(test, 32, "%d %d %d", consonantRead, vowelRead, lengthRead);
    Serial.println(test);
  }

  // while (digitalRead(submit) == LOW)
  // { 
  //   String newSyllable = checkAnalogPins();
  //   bool update = newSyllable != "" || newSyllable != " ";
  //   if (update){
  //     // don't update syllable if there was invalid input
  //     CURRENTSYLLABLE = newSyllable;
  //   }
  //   CURRENTLENGTH = updateLength();
  //   bool pitchUpPress = digitalRead(pitchUp) == HIGH;
  //   bool pitchDownPress = digitalRead(pitchDown) == HIGH;
  //   if (pitchUpPress || pitchDownPress)
  //   {
  //     CURRENTPITCH = updatePitch(CURRENTPITCH, pitchUpPress);
  //   }
    
    

  // }
}

void addNote(String* syllable, float length, int pitch){
  // adds note to editor
  // TODO: how to connect Arduino code to synth v plugin?
  lcd.clear();
  lcd.print("note submitted");
  delay(1000); // so user can see submission note
}

void setlcd(String* syllable, float length, int pitch){
  // convert syllable into char array
  char syBuffer[3];
  strcpy(syBuffer, syllable[0].c_str());
  if (syBuffer[2] == ""){
    syBuffer[2] = syllable[1][0];
  } else {
    syBuffer[3] = syllable[1][0];
  }

  // convert float into 3dp string (temp)
  char lenBuffer[10];
  dtostrf(length, 3, 3, lenBuffer);

  char output[32];
  snprintf(output, 32, "%s %s %d", syBuffer, lenBuffer, pitch);

  lcd.clear();
  lcd.print("current note:");
  lcd.setCursor(0, 1);
  lcd.print(output);
}

void update(bool updateConst, bool updateVowel, bool updateLength){
  if (updateConst){
    Serial.println("update consonant");
  }
  if (updateVowel){
    Serial.println("update vowel");
  }
  if (updateLength){
    Serial.println("update length");
  }
  // Serial.println("Update");
  setlcd(CURRENTSYLLABLE, CURRENTLENGTH, CURRENTPITCH);
  delay(200);
}

// TODO: is a string a good output?
// String checkAnalogPins(){
//   String output = "";
//   // checks pins
//   char consonant = getConsonant();
//   delay(100); // for stability
//   char vowel = getVowel();
//   delay(100);
//   if (consonant != 'n' && vowel == ' '){
//     // will have to break
//     return "";
//   }
//   if (consonant == 'h' && vowel == 'u'){
//     consonant = 'f';
//   }

//   output.concat(consonant);
//   // TODO: what vowels don't work with y?
//   if (digitalRead(addY) == HIGH){
//     output.concat("y");
//   }
//   output.concat(vowel);

//   return output;
// }

// int updatePitch(int curPitch, bool pitchUp){
//   if (pitchUp){
//     // pitch up
//     curPitch += 1;
//   } else {
//     // pitch down
//     curPitch -= 1;
//   }
//   return curPitch;
// }

// float updateLength(){
//   // TODO: how to update length
//   int temp = analogRead(length);
//   if (temp < 7000){
//     temp = 7000;
//   }
//   int index = temp / 1000;
//   return LENGTHS[index];
// }

// // TODO: (here & on getVowel) check values & make switch statements
// char getConsonant(){
//   int temp = analogRead(consonantValue);
//   // Serial.println(temp);
//   if (temp < 30000){ return ' '; } // no consonant
//   if (temp < 250000){
//     // k or g (depends on dakuten)
//     if (digitalRead(dakuten) == HIGH){
//       return 'g';
//     }
//     return 'k';
//   }
//   if (temp < 250){
//     // s or z
//     if (digitalRead(dakuten) == HIGH){
//       return 'z';
//     }
//     return 's';
//   }
//   if (temp < 350){
//     // t or d
//     if (digitalRead(dakuten) == HIGH){
//       return 'd';
//     }
//     return 't';
//   }
//   if (temp < 450){ return 'n'; } // always n
//   if (temp < 550){
//     //h, b or p (or f if f+u, need to work out how that'll work)
//     if (digitalRead(dakuten) == HIGH){
//       return 'b';
//     }
//     if (digitalRead(handakuten) == HIGH){
//       return 'p';
//     }
//     return 'h';
//   }
//   if (temp < 650) { return 'm'; } // always m
//   if (temp < 750) { return 'y'; } // always y
//   if (temp < 850) { return 'r'; } // always r
//   else { return 'w'; } // always w
// }

// char getVowel(){
//   int temp = analogRead(vowelValue);
//   // Serial.println(temp);
//   if (temp < 100){ return 'a'; }
//   if (temp < 150){ return 'i'; }
//   if (temp < 200){ return 'u'; }
//   if (temp < 300){ return 'e'; }
//   if (temp < 450){ return 'o'; }
//   else { return ' '; }
// }