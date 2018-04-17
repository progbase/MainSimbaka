#include <string.h>
#define token 500
int dinamicPin = 9;
const int buttonPin = 2;
 
 
 
typedef enum {
  DOT, LONG, BLANK
}Signal;
 
 
 
      int lenOfArray = 46;
      char      chrMorze[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5',  '6',  '7',  '8',  '9',  '0',  '.',  ';',  ',',  ':',  '?',  '!',  '-',  ' ', '\n', '\r'};
      uint8_t   lenMorze[] = {  2,   4,   4,   3,   1,   4,   3,   4,   2,   4,   3,   4,   2,   2,   3,   4,   4,   3,   3,   1,   3,   4,   3,   4,   4,   4,   5,   5,   5,   5,   5,    5,    5,    5,    5,    5,    6,    6,    6,    6,    6,    6,    6,    5,    5,    5};
      uint8_t   varMorze[] = {0x1, 0x8, 0xA, 0x4, 0x0, 0x2, 0x6, 0x0, 0x0, 0x7, 0x5, 0x4, 0x3, 0x2, 0x7, 0x6, 0xD, 0x2, 0x0, 0x1, 0x1, 0x1, 0x3, 0x9, 0xB, 0xC, 0xF, 0x7, 0x3, 0x1, 0x0, 0x10, 0x18, 0x1C, 0x1E, 0x1F,  0x0, 0x2A, 0x15, 0x38, 0x0C, 0x33, 0x21, 0x11, 0x15, 0x0A};
 
int saySignal (Signal sig) {
  switch(sig){
    case DOT:{
       int dotLen =  20;
       analogWrite(dinamicPin, 0); //включаем звук
       delay(dotLen);
       analogWrite(dinamicPin, -1); //выключаем звук
       delay(token - dotLen);
      break;
   }
    case LONG:{
       int longLen =  token + 20;
       analogWrite(dinamicPin, 0);
       delay(longLen);
       analogWrite(dinamicPin, -1);
       delay(token - longLen + 20);
      break;
   }
    case BLANK:{
      delay((int)(token * 2.5));
      break;
   }
  }
  delay(token);
  return 0;
}
 
Signal typeOfSignal(uint8_t a, int index, int len){
  return index == 0 ? a >> (len - 1) == 1 ? LONG : DOT:
  ((a >> (len - 1 - index)) ^ ((a >> (len - index)) << 1)) ^ 1 == 0 ? LONG : DOT;
}
 
int sayChar(char ch){
  int index = 0;
  while(index < lenOfArray){
    if(chrMorze[index] == ch) break;
    index++;
  }
  if(index == lenOfArray) return 1;
 
  for(int i = 0; i < lenMorze[index]; i++){
     saySignal(typeOfSignal(varMorze[index], i, lenMorze[index]));
  }
  saySignal(BLANK);
  return 0;
}
 
char charToUpper(char a){
  if(isupper(a)) return a;
  if(!isalpha(a)) return a;
  return a - 'a' + 'A';
}
 
int sayStr(const char * str){
  for(int i = 0; i < strlen(str);i++)
    sayChar(charToUpper(str[i]));
  return 0;
}
 
 
void setup()
{
  //Serial.begin (9600);
  //delay(token * 4);
  pinMode(dinamicPin, OUTPUT);
  Serial.begin(115200);
  analogWrite(dinamicPin, -1);
 
//Пока без свободного ввода, только посимвольная передача!
 
 
  //sayStr("  sos");
 
 
}
void loop(){
  while(!Serial.available());
 
  char input = Serial.read();
  Serial.print(input);
  sayChar(charToUpper(input));
  //Serial.println("lol");
 
}
