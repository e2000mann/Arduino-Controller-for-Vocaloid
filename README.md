# Arduino Voice Synth Controller

(Formally Arduino Controller For Vocaloid)

The purpose of this project is to create an Arduino Controller to allow the user to input Japanese notes into various voice synthesiser software. My current priority is to get it to work with Arduino boards based on the ATmega32u4 - i.e. the Leonardo & Mega. I hope to eventually create a version to work with other boards such as the Uno. I am also planning to first implement it to work with Synthesizer V, however I still intend on creating a Vocaloid 5 version in the future.

## Current Setup (WIP)
The circuit currently requires:
- 22 pushbuttons
- 25 220Ω resistors
- 1 Rotarv Shaft Potentiometer
- 1 trimmer Potentiometer
- 1 2x16 LCD Display

## How it will work (WIP)
- 10 buttons are to represent the 10 main Japanese consonants (inc. no consonant)
- 6 buttons are to represent the 5 Japanese vowels. There is a button for no vowel - this will only work for ん
- 2 buttons are for the Dakuten and Handakuten marks
- There is a button to add a y to the consonant, e.g. turning "no/の" into "nyo/にょ"
- 2 buttons are used to change the pitch, and the rotarv shaft potentiometer is used to vary the length
- The final button is used to submit the note
- The LCD panel is used to show the currently selected options

## Tutorials used
- https://www.the-diy-life.com/multiple-push-buttons-on-one-arduino-input/
- https://www.arduino.cc/en/Tutorial/LibraryExamples/HelloWorld
