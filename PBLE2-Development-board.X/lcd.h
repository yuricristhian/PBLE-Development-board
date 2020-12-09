#ifndef LCD
#define LCD
  void lcdCommand(char value);
  void lcdChar(char value);
  void lcdString(char msg[]);
  void lcdNumber(unsigned long int value);
  void lcdPosition(int line, int col);
  void lcdInit(void);
  void digitalWrite(int pin, int state);
  void soInit(void);
#endif
