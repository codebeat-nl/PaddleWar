#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2020-01-06 22:50:10

#include "Arduino.h"
#include <TVout.h>
#include "DisplayFoundation.h"

uint8_t getFontPixelEventHandler( TDisplayFoundation* poSender,                                   DFC_UINT_TYPE x,                                   DFC_UINT_TYPE y ) ;
void setFontPixelEventHandler( TDisplayFoundation* poSender,                                DFC_UINT_TYPE x,                                DFC_UINT_TYPE y,                                uint8_t iSetMode ) ;
void gameReset() ;
void displayScore() ;
void gameClear() ;
void bouncePaddle(int paddleX) ;
void miss() ;
void gameEnd(bool bHasWon) ;
int getPaddleValPerc() ;
int getPaddlePos() ;
void setup() ;
void loop() ;

#include "PaddleWar.ino"


#endif
