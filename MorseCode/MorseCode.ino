
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SIZE 26
#define vmOne 9
#define vmTwo 10
const int dotButton=8;
const int dashButton=7;
const int sendButton=4;
const int spaceLetterButton=6;
const int spaceWordButton=5;
const int yesVibrateButton=3;
const int noVibrateButton=2;

String morseCode="";
String text="";
int characterAscii=0;
int startPos=0, endPos=0;
int startPos1=0, endPos1=0;
String characterCode="";
int dashButtonState=0;
int dotButtonState=0;
int sendButtonState=0;
int spaceLetterButtonState=0;
int spaceWordButtonState=0;
int yesVibrateButtonState=0;
int noVibrateButtonState=0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

//Array of MorseCode for letters of English Language A to Z
String letters[SIZE]={

// A to I
".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
// J to R 
".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
// S to Z
"...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." 
};

        
void setup() {
  // put your setup code here, to run once:
//Getting things Ready
//pinMode(ledPin, OUTPUT);
pinMode(dotButton, INPUT);
pinMode(dashButton, INPUT);
pinMode(sendButton, INPUT);
pinMode(spaceLetterButton, INPUT);
pinMode(spaceWordButton, INPUT);
pinMode(yesVibrateButton, INPUT);
pinMode(noVibrateButton, INPUT);
pinMode(vmOne, OUTPUT);
pinMode(vmTwo, OUTPUT);
lcd.begin();
Serial.begin(9600);

Serial.println("\n\nEnter Your Morse Code Here  ");

}


void loop() {
  // put your main code here, to run repeatedly:

  sendButtonState = digitalRead(sendButton);
  spaceLetterButtonState = digitalRead(spaceLetterButton);
  spaceWordButtonState = digitalRead(spaceWordButton);
  
  if(sendButtonState == HIGH){
    Serial.print("\n");
        morseCode.concat('#');// Placeing # at the end of morseCode to simplify further processing

         Serial.print("\nYour Morse code Translation :  ");
         
        endPos1=morseCode.indexOf('#');

        while(endPos1 < morseCode.length() )
        {
            extractLetters(morseCode.substring(startPos1, endPos1)); // This function would extract Letter as name suggest and would convert  code to text SIMPLE!
           startPos1=endPos1+1;
           if(startPos1 == morseCode.length() )
           {
              break; 
           }
           endPos1= morseCode.indexOf('#', startPos1);
        }
        startPos1=0;
        endPos1=0;

        text=""; //  For New Translation   
        morseCode="";
        Serial.println("\n\nEnter Your Morse Code Here ");
        delay(1000);
  }else if(spaceLetterButtonState == HIGH){
         morseCode.concat("@");
        Serial.print("@");
        delay(200);
  }else if(spaceWordButtonState == HIGH){
     morseCode.concat("#");
        Serial.print("#");
        delay(200);
  }

while(Serial.available() > 0 ) 
{
      int ascii=Serial.read();

      switch(ascii)
      {
        case 49: // 49 is Ascii value of 1

        Serial.print("\n");
        morseCode.concat('#');// Placeing # at the end of morseCode to simplify further processing

         Serial.print("\nYour Morse code Translation :  ");
         
        endPos1=morseCode.indexOf('#');

        while(endPos1 < morseCode.length() )
        {
            extractLetters(morseCode.substring(startPos1, endPos1)); // This function would extract Letter as name suggest and would convert  code to text SIMPLE!
           startPos1=endPos1+1;
           if(startPos1 == morseCode.length() )
           {
              break; 
           }
           endPos1= morseCode.indexOf('#', startPos1);
        }
        startPos1=0;
        endPos1=0;

        text=""; //  For New Translation   
        morseCode="";
        Serial.println("\n\nEnter Your Morse Code Here ");
        
              
        break;

        case 50: // 50 is Ascii value of 2
        
        morseCode.concat("@");
        Serial.print("@");
        delay(200);
        
        break;

        case 51: // 51 is Ascii value of 3
          
        morseCode.concat("#");
        Serial.print("#");
        delay(200);
        
        break;
        
      }
      
}

process();

}

void turnONLedSpeaker()
{
  //Turn ON LED
  //digitalWrite(ledPin, HIGH);
  //tone(speakerPin, 4699, 300); // tone(speakerPin, frequency, duration in milliSec)
 
}

void process()
{
  
  dotButtonState=digitalRead(dotButton);
  dashButtonState=digitalRead(dashButton);
  yesVibrateButtonState=digitalRead(yesVibrateButton);
  noVibrateButtonState=digitalRead(noVibrateButton);

  if(yesVibrateButtonState == HIGH){
    digitalWrite(vmOne, HIGH);
    digitalWrite(vmTwo, HIGH);
    delay(1000);
    digitalWrite(vmOne, LOW);
    digitalWrite(vmTwo, LOW);
  }else if(noVibrateButtonState == HIGH){
    digitalWrite(vmTwo, HIGH);
    digitalWrite(vmOne, HIGH);
    delay(800);
    digitalWrite(vmTwo  , LOW);
    digitalWrite(vmOne, LOW);
  }

  if(dashButtonState == HIGH)
  {
    turnONLedSpeaker();
   
    morseCode.concat("-"); // Storing code in variable morseCode with the help of concatenation function
    Serial.print("-");//Prints User entered Code
    digitalWrite(vmOne, HIGH);
    digitalWrite(vmTwo, HIGH);
    delay(500);
    digitalWrite(vmOne, LOW);
    digitalWrite(vmTwo, LOW);
  }
  else if(dotButtonState == HIGH)
  {
   turnONLedSpeaker();
  
   morseCode.concat(".");
   Serial.print(".");
   digitalWrite(vmOne, HIGH);
   digitalWrite(vmTwo, HIGH);
   delay(200);
   digitalWrite(vmOne, LOW);
   digitalWrite(vmTwo, LOW); 
    
  }
  else
  {
    //Turn OFF LED
    //digitalWrite(ledPin, LOW);
     
  }

}

char convertIntoText(String characterCode)
{
  characterAscii=65;
  
  for(int index=0; index<SIZE; index++)
  {
    if(characterCode == letters[index])
    {
      return characterAscii;   
    }
    characterAscii++;  
  }

}

void extractLetters(String words)
{
        words.concat('@'); // Placeing @ at the end of word to simplify further processing

        endPos=words.indexOf('@');

        
        //Loop to extracting single character morse Code from string of word        
        while( endPos<words.length() )
       {
         characterCode=words.substring(startPos, endPos);
         
         //Now CharacterCode will now convert in text

         text.concat(convertIntoText(characterCode));
         
         startPos=endPos+1;
         characterCode="";
         
          // if condition is just to terminate loop when our extracting single character code is complete thats all
         if(startPos == words.length() )
         {
           break;
         }
         
         endPos=words.indexOf('@', startPos);   
       
       }
                
        
        Serial.print(text);
        Serial.print(" ");
        lcd.backlight();
        lcd.clear();
        lcd.print(text);
        delay(4000);
        lcd.clear();
        lcd.noBacklight();
        startPos=0;
        endPos=0;
        text="";    
  
}
