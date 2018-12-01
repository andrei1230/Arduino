#ifndef JoiceStick_h

#define JoiceStick_h 

#include <avr/pgmspace.h>

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
///Some includes so there is no " 'A0' was not delcared " error

  class JoiceStick
  {
  const int joyX;
  const int joyY;
  
     /*
      * Variabila care e TRUE cand a trecut un timp mai mare 
      *   sau egal decat delayTime de la ultima actiune
      */
  bool goodToGo;
  
    /*
     * Pointeri catre functiile ce trebuie apelate cand se misca
     *  joystickul in anumite pozitii
     */   
  void (*goLeft)(void), (*goRight)(void);
  void (*goUp)(void), (*goDown)(void);

  unsigned long lastTime;
  unsigned long delayTime;

public:
  
  JoiceStick();
  JoiceStick(int, int);
  
  void setDelay (unsigned long aDelay);
  void checkDelay ();
  
   //Resetare pointeri catre functii la NULL si delay la 100
   
  void resetVars();

  ///Init VERTICAL
  void initV (void (*left)(), void (*right)());

  ///Init HORIZONTAL
  void initH ( void (*down)(), void (*up)());

  int isX ();
  int isY ();
  
  ///Check VERTICAL
  void checkV();
  ///Check HORIZONTAL
  void checkH();
  
  /*
   * Functii care folosesc delay in loc de millis
   */
  int isYwDelay();
  void checkHwDelay();

};

#endif //JoiceStick.h 