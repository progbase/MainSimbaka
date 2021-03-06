//// Подключаем стандартную библиотеку LiquidCrystal
#include <LiquidCrystal.h>
// 
//// Инициализируем объект-экран, передаём использованные 
//// для подключения контакты на Arduino в порядке:
//// RS, E, DB4, DB5, DB6, DB7
LiquidCrystal lcd(4, 5, 10, 11, 12, 13);

const int buttonPin = 2;

int nunOfPrintLetters = 0;
int row = 0;

#define micPin 7            //Пин Датчика Звука №7
#define token 500
unsigned long timeBefore;   //
unsigned long timeAfter;    //
unsigned long counter;      //
unsigned long i;            //
typedef enum Signal{ 
  BLANK = 2,
  DOT = 0,
  LONG = 1
} Signal;
 
Signal letter[8];
       
      uint8_t   varLetter;            //  Объявляем переменную для хранения принятых точек и тире одного символа (бит 0 - точка, бит 1 - тире)
      uint8_t   lenLetter;            //  Объявляем переменную для хранения количества точек и тире в принятом символе
      bool      flgSignal;            //  Объявляем флаг указывающий на то что была принята хотя бы одна точка или тире  21 == 10101
      bool      flgLetter;            //  Объявляем флаг указывающий на то что был принят символ
      char      chrMorze[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5',  '6',  '7',  '8',  '9',  '0',  '.',  ';',  ',',  ':',  '?',  '!',  '-',  ' ', '\n', '\r'};
      uint8_t   lenMorze[] = {  2,   4,   4,   3,   1,   4,   3,   4,   2,   4,   3,   4,   2,   2,   3,   4,   4,   3,   3,   1,   3,   4,   3,   4,   4,   4,   5,   5,   5,   5,   5,    5,    5,    5,    5,    5,    6,    6,    6,    6,    6,    6,    6,    5,    5,    5};
      uint8_t   varMorze[] = {0x1, 0x8, 0xA, 0x4, 0x0, 0x2, 0x6, 0x0, 0x0, 0x7, 0x5, 0x4, 0x3, 0x2, 0x7, 0x6, 0xD, 0x2, 0x0, 0x1, 0x1, 0x1, 0x3, 0x9, 0xB, 0xC, 0xF, 0x7, 0x3, 0x1, 0x0, 0x10, 0x18, 0x1C, 0x1E, 0x1F,  0x0, 0x2A, 0x15, 0x38, 0x0C, 0x33, 0x21, 0x11, 0x15, 0x0A};
 // Массивы: chrMorze - содержит символы, lenMorze - количество точек и тире в символе, varMorze - комбинация точек и тире (бит 0 - точка, бит 1 - тире)
void setup(){

  pinMode(buttonPin, OUTPUT);  
  
    timeBefore = millis();
    pinMode(13, OUTPUT);
    
    pinMode(micPin, INPUT);
    flgLetter=varLetter=lenLetter=0;                                                  // Сбрасываем флаги и переменные относящиеся к принятому символу
     lcd.begin(16, 2);

}                                                                                     //
                                                                                      //

int SlshN(){
  if(row == 1){
    lcd.clear();
    row = 0;
  }
  else{
    row++;
    lcd.setCursor(0, row);
  }
}

void loop(){

  if(digitalRead(buttonPin)){
    lcd.clear();
  }
  
 if(digitalRead(micPin) == HIGH)                                    //Если датчик звука получил сигнал, мы заходим в цикл.
  {
    timeAfter = millis() - timeBefore;                              //Вичисляем время между сигналами.
    if(timeAfter / token > 2)
    {
      //Serial.println("BLANK");
      lenLetter = i;
      i = 0;
      for(int j = 0; j < lenLetter; j++)
      {
        varLetter <<= 1; 
        varLetter |= letter[j];
      }
      flgLetter = true;  
    }
    counter = 0;
    for(int i = 0; i <  10 ; i++)
    {
      if(digitalRead(micPin) == HIGH)
      {
        counter++;
      }
      delay(token/ 10);
    }
    if(counter > 1000/token)
    {
      letter[i] = LONG;
      if(i < 7)
        i++;
    }
    else
    {
     letter[i] = DOT;
     if(i < 7)
      i++;
     //Serial.println("DOT");
    }
    delay(token);
    timeBefore = millis();
  }
                                                             
    if(flgLetter){                                                                    // Если установлен флаг flgLetter значит символ полностью принят, его нужно сравнить и вывести
        for(uint8_t i=0; i<46; i++){                                                  // Проходим по всем 46 символам массивов
          if(varLetter==varMorze[i] && lenLetter==lenMorze[i]){                         // Если комбинация точек и тире в varLetter совпала с varMorze[i] и количество точек и тире совпало с lenMorze[i], то...
              if(nunOfPrintLetters == 16){
                SlshN();
                nunOfPrintLetters = 0;
              }
              if(chrMorze[i] == '\n' || chrMorze[i] == '\r'){
                SlshN();
              }
              else{
                lcd.print(chrMorze[i]);                                                // Выводим символ из chrMorze[i] в монитор последовательного порта
                nunOfPrintLetters++;
              }
          }
        }  flgLetter=varLetter=lenLetter=0;  
        flgLetter = false;                                                      // Сбрасываем флаги и переменные относящиеся к принятому символу, так как мы его уже вывели
    }                                                                     //
}  
