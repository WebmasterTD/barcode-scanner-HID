#include <HID-Settings.h>
#include <HID-Project.h>

#define baudrate 2400

byte rx = 6;
int BitDelay, HalfBitDelay, num;

void setup() {
  Serial.begin(9600);
  pinMode(rx,INPUT);
  BitDelay = 1000000 / baudrate;
  HalfBitDelay = BitDelay/2;
  
}

int Sread()
{
  byte val = 0;
  while (digitalRead(rx));
  //wait for start bit
  if (digitalRead(rx) == LOW) {
    delayMicroseconds(HalfBitDelay);
    for (int offset = 0; offset < 8; offset++) {
     delayMicroseconds(BitDelay);
     val |= digitalRead(rx) << offset;
    }
    //wait for stop bit + extra
    delayMicroseconds(BitDelay); 
    delayMicroseconds(BitDelay);
    return val;
  }
}

void NumToKey(int num)
{
  switch (num) {
    case 9:
      //do something when var equals 9
      Keyboard.press(KEY_UP_ARROW);
      Keyboard.releaseAll();
      break;
    case 48:
      //do something when var equals 0
      Keyboard.press(KEYPAD_0);
      Keyboard.releaseAll();
      break;
    case 49:
      //do something when var equals 1
      Keyboard.press(KEYPAD_1);
      Keyboard.releaseAll();
      break;
    case 50:
      //do something when var equals 2
      Keyboard.press(KEYPAD_2);
      Keyboard.releaseAll();
      break;
    case 51:
      //do something when var equals 3
      Keyboard.press(KEYPAD_3);
      Keyboard.releaseAll();
      break;
    case 52:
      //do something when var equals 4
      Keyboard.press(KEYPAD_4);
      Keyboard.releaseAll();
      break;
    case 53:
      //do something when var equals 5
      Keyboard.press(KEYPAD_5);
      Keyboard.releaseAll();
      break;
    case 54:
      //do something when var equals 6
      Keyboard.press(KEYPAD_6);
      Keyboard.releaseAll();
      break;
    case 55:
      //do something when var equals 7
      Keyboard.press(KEYPAD_7);
      Keyboard.releaseAll();
      break;
    case 56:
      //do something when var equals 8
      Keyboard.press(KEYPAD_8);
      Keyboard.releaseAll();
      break;
    case 57:
      //do something when var equals 9
      Keyboard.press(KEYPAD_9);
      Keyboard.releaseAll();
      break;      
    default:
      // if nothing else matches, do the default
    break;
  }
}

void loop() {
  num = Sread();
  NumToKey(num);
}
