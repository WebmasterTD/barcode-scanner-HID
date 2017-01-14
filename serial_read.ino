#include <HID-Settings.h>
#include <HID-Project.h>

#define baudrate 2400

byte rx = 6;
int BitDelay, HalfBitDelay, num, in, buffer[15];

void setup()
{
  //Serial.begin(9600);
  pinMode(rx,INPUT);
  BitDelay = 1000000 / baudrate;
  HalfBitDelay = BitDelay/2;
  in = 0;
  
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
  int i;
  switch (num) {
    case 9:
      //do something when var equals TAB
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(KEY_HOME);
      Keyboard.releaseAll();
      break;
    case 48:
      //do something when var equals 48 0
      Keyboard.write(KEYPAD_0);
      break;
    case 49:
      //do something when var equals 49 1
      Keyboard.write(KEYPAD_1);
      break;
    case 50:
      //do something when var equals 50 2
      Keyboard.write(KEYPAD_2);
      break;
    case 51:
      //do something when var equals 51 3
      Keyboard.write(KEYPAD_3);
      break;
    case 52:
      //do something when var equals 52 4
      Keyboard.write(KEYPAD_4);
      break;
    case 53:
      //do something when var equals 53 5
      Keyboard.write(KEYPAD_5);
      break;
    case 54:
      //do something when var equals 54 6
      Keyboard.write(KEYPAD_6);
      break;
    case 55:
      //do something when var equals 55 7
      Keyboard.write(KEYPAD_7);
      break;
    case 56:
      //do something when var equals 56 8
      Keyboard.write(KEYPAD_8);
      break;
    case 57:
      //do something when var equals 57 9
      Keyboard.write(KEYPAD_9);
      break;
    case 13:
      //do something when var equals CR
      Keyboard.write(KEY_LEFT_ARROW);
      Keyboard.press(KEY_LEFT_SHIFT);
      for(i=0; i<5; i++)
      {
         Keyboard.write(KEY_LEFT_ARROW);
      }
      Keyboard.releaseAll();
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_C);
      Keyboard.releaseAll();
      Keyboard.write(KEY_END);
      break;
    default:
      // if nothing else matches, do the default
    break;
  }
}
void buffr(int num)
{
  int i;
  if (num == 9)
  {
    in = 0;
    buffer[in] = num;
    in++;
  }
  else if (num == 13)
  {
    buffer[in] = num;
    for(i=0; i<15; i++)
    {
      NumToKey(buffer[i]);
    }
  }
  else
  {
    buffer[in] = num;
    in++;
  }
}
void loop() {
  num = Sread();
  buffr(num);
}

