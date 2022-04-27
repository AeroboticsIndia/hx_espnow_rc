#include "StateInit.h"

#include "StateCalibrateMinMax.h"
#include "StateRun.h"

#include "TXMain.h"
#include "TXInput.h"

StateInit StateInit::instance;

//======================================================
//======================================================
void StateInit::onEnter()
{
    this->stateTime = millis();  
}

//======================================================
//======================================================
void StateInit::onRun(uint32_t t)
{
  int phase = (t - stateTime) / 500;
  switch (phase)
  {
    case 0: 
      TXMain::instance.setLEDS4( 8 ); 
      break;
    case 1: 
      TXMain::instance.setLEDS4( 8 + 4); 
      break;
    case 2: 
      TXMain::instance.setLEDS4( 8 + 4 + 2); 
      break;
    case 3: 
      TXMain::instance.setLEDS4( 8 + 4 + 2 + 1 ); 
      break;
     case 4: 
      if ( TXInput::instance.isCalibrateGesture() )
      {
        StateBase::Goto(&StateCalibrateMinMax::instance);
      }
      else if ( TXInput::instance.isInitGesture())
      {
        CH16 = 2000;  //Mode Config profile
        StateBase::Goto(&StateRun::instance);
      }
      else
      {
        StateBase::Goto(&StateRun::instance);
      }
      break;
  }
}