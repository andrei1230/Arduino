#include "JoiceStick.h"

/*
 * COUNTERINTUITIVE, BUT:
 *        X(VRx) IS FOR VERTICAL
 *        Y(VRy) IS FOR HORIZONTAL
 *        
 * LEFT   ->   Y = 0
 * RIGHT  ->   Y = 1024
 * 
 * UP     ->   X = 0
 * DOWN   ->   X = 1024
 */



JoiceStick::JoiceStick():joyX(A0),joyY(A1)
{
  resetVars();
}

JoiceStick::JoiceStick(int anlInputX, int anlInputY):joyX(anlInputX),joyY(anlInputY)
{
  resetVars();
}

void JoiceStick::resetVars()
{
  delayTime = 150;
  lastTime = millis();
  goLeft = NULL;
  goRight = NULL;
  goUp = NULL;
  goDown = NULL;
  pinMode( joyX, INPUT );
  pinMode( joyY, INPUT );
}

void JoiceStick::setDelay (unsigned long aDelay) 
{ 
  delayTime = aDelay;
}

bool JoiceStick::checkDelay()
{
  unsigned long currTime = millis();
  if ( currTime - lastTime > delayTime )
  {
    lastTime = currTime ;
    return true;
  }
  return false;
}

///HORIZONTAL
void JoiceStick::initH (void (*left)(), void (*right)())
{
  goLeft = left;
  goRight = right;
}

///VERTICAL
void JoiceStick::initV ( void (*down)(), void (*up)())
{
  goDown = down;
  goUp = up;
}


int JoiceStick::isX () 
{
    int xx = analogRead(joyX);
    if ( xx < 400 ) return 1;
    if ( xx > 600 ) return -1;
    return 0;
}


int JoiceStick::isY () 
{
  
    int yy = analogRead(joyY);
    if ( yy < 400 ) return 1;
    if ( yy > 600 ) return -1;
    return 0;
}


void JoiceStick::checkH()
{
  
  int wh = isY();
  if ( goLeft == NULL || goRight == NULL || wh == 0) return;
  
  if ( wh < 0 && checkDelay() )  goLeft();
  if ( wh > 0 && checkDelay() )  goRight();

}

void JoiceStick::checkV()
{
  
  int wh = isX();
  if (goLeft == NULL || goRight == NULL || wh == 0) return;
  if ( wh < 0 && checkDelay() )  goDown();
  if ( wh > 0 && checkDelay() )  goUp();

}
