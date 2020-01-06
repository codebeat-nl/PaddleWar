/*
 * TDisplayFoundation - Basics and event driven driver for many displays
 *
 * @created: 2019-11-09
 * @author : codebeat / Erwin Haantjes
 *
 * Source code available at: ...
 *
 * @updated    : 05 jan 2020
 * @modified by: codebeat
 * @changelog  : Some bugfixes
 * @notice     : This is actually an initial release, not fully documented,
 *               features might change or removed in final release.
 *               For now it is suitable for this project however don't
 *               use this class for other purposes.
 */

// ----------------------------------------------------------------------------

//#include "DisplayFoundation.config.h"
#include "DisplayFoundation.h"
#include "DisplayFoundation.font.h"

// ----------------------------------------------------------------------------


TDisplayFoundation::TDisplayFoundation()
{
  reset();
}


bool TDisplayFoundation::canDisplayControlCode()
{
  #if defined DFFC_ALL_CHARS || defined DFFC_CONTROL_CHARS
   return true;
  #else
   return false;
  #endif    
}

bool TDisplayFoundation::canDisplayNumeric()
{
  #if defined DFFC_FONT_VARI_16SEG || defined DFFC_ALL_CHARS || defined DFFC_STANDARD_CHARS
   return true;
  #else
   return false;
  #endif    
}

bool TDisplayFoundation::canDisplayText()
{
  #if defined DFFC_FONT_VARI_16SEG || defined DFFC_ALL_CHARS || defined DFFC_STANDARD_CHARS
   return true;
  #else
   return false;
  #endif    
}

bool TDisplayFoundation::canDisplaySpecial()
{
  #if defined DFFC_ALL_CHARS || defined DFFC_SPECIAL_CHARS
   return true;
  #else
   return false;
  #endif    
}

bool TDisplayFoundation::canDisplayGraphic()
{
  #if defined DFFC_ALL_CHARS || defined DFFC_GRAPHIC_CHARS
   return true;
  #else
   return false;
  #endif    
}

bool TDisplayFoundation::canDisplayAll()
{
  #if defined DFFC_ALL_CHARS
 return true;
  #else
   return false;
  #endif
}

bool TDisplayFoundation::isCursorVisible()
{ return cursor; }

bool TDisplayFoundation::isControlCodeChar( unsigned char chr )
{ return ( chr <= 31 ); }   

bool TDisplayFoundation::isNumericChar( unsigned char chr )
{ return ( chr >= '0' && chr <= '9' ); }   

bool TDisplayFoundation::isAlphabetChar( unsigned char chr )
{ return (( chr >= 'a' && chr <= 'z' ) || ( chr >= 'A' && chr <= 'Z' )); }   

bool TDisplayFoundation::isTextChar( unsigned char chr )
{ 
  return (( isAlphabetChar( chr ) )       // 'a' .. 'z' / 'A' .. 'Z'
       || ( isCalcChar( chr ) )           // *+,-./ 
       || ( chr >= 32 && chr <= 47 )      // Space .. '/'
       || ( chr >= 58 && chr <= 64 )      // ':' .. '@'
       || ( chr >= 91 && chr <= 96 )      // '[' .. '`'
       || ( chr >= 123 && chr <= 126 ) ); // '{' .. '~'
}   

bool TDisplayFoundation::isSpecialChar( unsigned char chr )
{ 
  return (( chr >= 127 && chr <= 168 )    // '⌂'.. '¿'
       || ( chr >= 171 && chr <= 173 )    // '½'.. '¡'
       || ( chr >= 224 && chr <= 253 ));  // alpha..'²'
}   

bool TDisplayFoundation::isGraphicChar( unsigned char chr )
{ 
  return (( chr >= 169 && chr <= 170 )    // 
       || ( chr >= 174 && chr <= 223 )    // '«'..'▀' 
       || ( chr >= 254 && chr <= 255 )    // '■'..' '
       || ( chr >= 14  && chr <= 31 ));   // '♫'..'▼'
}   

bool TDisplayFoundation::isCalcChar( unsigned char chr )
{ return (( chr >= '*' ) && ( chr <= '/' )); } // *+,-./

bool TDisplayFoundation::isPrintableChar( unsigned char chr, bool bAllowSpecialChars /* = true */ )
{ 
  return ( ( isTextChar( chr ) ) 
        || ( isNumericChar( chr ) )
        || ( isCalcChar( chr ) )
        || ( ( bAllowSpecialChars ) && ( isSpecialChar( chr ) )) ); 
}   

// ** getters ** 

DFC_UINT_TYPE TDisplayFoundation::getWidth()
{
  return width;
}

DFC_UINT_TYPE TDisplayFoundation::getHeight()
{
  return height;
}

DFC_UINT_TYPE TDisplayFoundation::getScreenWidth( bool bWithSpacing /* = true */ )
{
  return calcCharPosition( width-1, fontWidth, bWithSpacing?charSpacing:0 );  
}

DFC_UINT_TYPE TDisplayFoundation::getScreenHeight( bool bWithSpacing /* = true */ )
{
  return calcCharPosition( height-1, fontHeight, bWithSpacing?lineSpacing:0 );  
}

DFC_UINT_TYPE TDisplayFoundation::getX()
{
  return cursX;
}

DFC_UINT_TYPE TDisplayFoundation::getY()
{
  return cursY;
}

DFC_UINT_TYPE TDisplayFoundation::getScreenX( bool bWithSpacing /* = true */ )
{
  return calcCharPosition( cursX, fontWidth, bWithSpacing?charSpacing:0 );  
}

DFC_UINT_TYPE TDisplayFoundation::getScreenY( bool bWithSpacing /* = true */ )
{
  return calcCharPosition( cursY, fontHeight, bWithSpacing?lineSpacing:0 );  
}

DFC_UINT_TYPE TDisplayFoundation::getFontWidth()
{
  return fontWidth;
}

DFC_UINT_TYPE TDisplayFoundation::getFontHeight()
{
  return fontHeight;
}

bool TDisplayFoundation::getFontSmallSpace()
{
  return smallSpace;
}

DFC_UINT_TYPE TDisplayFoundation::getCharSpacing()
{
  return charSpacing;
}

DFC_UINT_TYPE TDisplayFoundation::getLineSpacing()
{
  return lineSpacing;
}

DFC_UINT_TYPE TDisplayFoundation::getFG()
{
  return fgColor;
}

DFC_UINT_TYPE TDisplayFoundation::getBG()
{
  return bgColor;
}

uint8_t TDisplayFoundation::getPixel( DFC_UINT_TYPE x, 
                                      DFC_UINT_TYPE y, 
                                      uint8_t iReturnDefault /* = DF_PIXEL_TRANS */ 
                                    ) 
{
  if( onGetPixel != NULL )
   { return onGetPixel( this, x, y ); }
  
  return iReturnDefault;
}


// ** Setters **
void TDisplayFoundation::setCursorX( DFC_UINT_TYPE x,
                                     bool bWithSpacing /* = true */
                                   )
{
 if( cursor )
  { drawCursor(false); }
 cursX = min( ((bWithSpacing && x > 0)?((x-1)*charSpacing):0)+(x*fontWidth), width-fontWidth-1 );
}

void TDisplayFoundation::setCursorY( DFC_UINT_TYPE y,
                                     bool bWithSpacing /* = true */
                                   )
{
 if( cursor )
  { drawCursor(false); }
    cursY = min( ((bWithSpacing && y > 0)?((y-1)*lineSpacing):0)+(y*fontHeight), height-fontHeight-1 );
}

void TDisplayFoundation::setCursor( DFC_UINT_TYPE x, 
                                    DFC_UINT_TYPE y, 
                                    bool bWithSpacing /* = true */
                                   )
{
   setCursorX( x, bWithSpacing );
   setCursorY( y, bWithSpacing );
}

void TDisplayFoundation::setCursRow( DFC_UINT_TYPE y )
{
   if( cursor )
  { drawCursor(false); }

   cursY+=y*fontHeight;

   if( cursY+fontHeight > height )
   { 
     cursY = 0;
     cursX = 0;
   }
}

void TDisplayFoundation::setCursCol( DFC_UINT_TYPE x )
{
  if( cursor )
   { drawCursor(false); }

  cursX=x*fontWidth+charSpacing;
  if( cursX+fontWidth > width )
   { 
     cursX = 0;
     setCursNextRow(); 
   }
}

void TDisplayFoundation::setCursNewLine()
{
  if( cursor )
   { drawCursor(false); }

  cursY+=fontHeight+lineSpacing;
  if( cursY+fontHeight > height )
   { 
     cursY = 0;
   }
 
  cursX=0;
}

void TDisplayFoundation::newLine()
{
  setCursNewLine();
}

void TDisplayFoundation::setCursNextRow()
{
  if( cursor )
   { drawCursor(false); }

  cursY+=fontHeight+lineSpacing;

  if( cursY+fontHeight > height )
   { 
     cursY = 0;
   }
}

void TDisplayFoundation::setCursNextColumn( int8_t iExtraSpace /* = 0 */ )
{
  if( cursor )
   { drawCursor(false); }

  cursX+=fontWidth+charSpacing+iExtraSpace;

  if( cursX+fontWidth > width )
   { 
     cursX = 0;
     setCursNextRow(); 
   }
}

void TDisplayFoundation::setFontWidth( DFC_UINT_TYPE iValue )
{
  fontWidth      = min( iValue , width  );
  fontWidthHalf  = (DFC_UINT_TYPE)fontWidth>>1; 
}

void TDisplayFoundation::setFontHeight( DFC_UINT_TYPE iValue )
{
  fontHeight     = min( iValue, height );
  fontHeightHalf = (DFC_UINT_TYPE)fontHeight>>1; 
}

void TDisplayFoundation::setFontSize( DFC_UINT_TYPE iWidth /* = DF_DEF_FONT_WIDTH */, 
                                      DFC_UINT_TYPE iHeight /* = DF_DEF_FONT_HEIGHT */ 
                                     )
{
  setFontWidth( iWidth );
  setFontHeight( iHeight );
}

void TDisplayFoundation::setFontSmallSpace( bool bValue )
{
  smallSpace = bValue;                 
}

void TDisplayFoundation::setCharSpacing( DFC_UINT_TYPE iValue )
{
  charSpacing = iValue;
}

void TDisplayFoundation::setLineSpacing( DFC_UINT_TYPE iValue )
{
  lineSpacing = iValue;
}

void TDisplayFoundation::setSpacing( DFC_UINT_TYPE xCharValue,  
                                     DFC_UINT_TYPE yLineValue 
                                   )
{
  setCharSpacing( xCharValue );
  setLineSpacing( yLineValue );
}

void TDisplayFoundation::setWidth( DFC_UINT_TYPE iValue )
{
  width  = max( fontWidth , iValue  );
}

void TDisplayFoundation::setHeight( DFC_UINT_TYPE iValue )
{
  height = max( fontHeight, iValue );
}

void TDisplayFoundation::setSize( DFC_UINT_TYPE iWidth, DFC_UINT_TYPE iHeight )
{
 setWidth( iWidth );
 setHeight( iHeight );
}


void TDisplayFoundation::setFG( uint8_t iColor )
{
  if( iColor != DF_PIXEL_FOREGROUND && iColor != DF_PIXEL_BACKGROUND )
   { fgColor = iColor; }
}

void TDisplayFoundation::setBG( uint8_t iColor )
{
  if( iColor != DF_PIXEL_FOREGROUND && iColor != DF_PIXEL_BACKGROUND )
   { bgColor = iColor; }
}
    

void TDisplayFoundation::setPixel( DFC_UINT_TYPE x, 
                                   DFC_UINT_TYPE y, 
                                   uint8_t iSetMode /* = DF_PIXEL_FOREGROUND  */ 
                                 )
{
  // calls event
  if( iSetMode != DF_PIXEL_TRANS && onSetPixel != NULL )
  {
    if( ( iSetMode == DF_PIXEL_FOREGROUND && fgColor == DF_PIXEL_TRANS )
        || ( iSetMode == DF_PIXEL_BACKGROUND && bgColor == DF_PIXEL_TRANS ) )
       { return; }
        
    if( iSetMode == DF_PIXEL_INVERT )
     { 
        iSetMode = getPixel( x, y );
        if( iSetMode == DF_PIXEL_TRANS || iSetMode == DF_PIXEL_INVERT )
         { return; }
        
        onSetPixel( this, x, y, 
                    iSetMode==DF_PIXEL_NORMAL?DF_PIXEL_CLEAR:
                    iSetMode==DF_PIXEL_CLEAR?DF_PIXEL_NORMAL:
                    iSetMode==DF_PIXEL_FOREGROUND?bgColor:
                    iSetMode==DF_PIXEL_BACKGROUND?fgColor:
                    iSetMode 
                  );  
     }
    else {
            onSetPixel( this, x, y, 
                        iSetMode==DF_PIXEL_FOREGROUND?fgColor:
                        iSetMode==DF_PIXEL_BACKGROUND?bgColor:
                        iSetMode
                      );
         }             
  }
}

void TDisplayFoundation::showCursor()
{
  cursor = true;
}

void TDisplayFoundation::hideCursor()
{
  cursor = false;
}

void TDisplayFoundation::gotoScreenXY( DFC_UINT_TYPE x, 
                                       DFC_UINT_TYPE y, 
                                       bool bWithSpacing /* = false */
                                      )
{
  setCursor( x, y, bWithSpacing );
}

void TDisplayFoundation::gotoScreenX( DFC_UINT_TYPE x, bool bWithSpacing /* = false */ )
{
  gotoScreenXY( x, getScreenY( bWithSpacing ), bWithSpacing );
}

void TDisplayFoundation::gotoScreenY( DFC_UINT_TYPE y, bool bWithSpacing /* = false */ )
{
  gotoScreenXY( getScreenX( bWithSpacing ), y, bWithSpacing );
}


void TDisplayFoundation::gotoXY( DFC_UINT_TYPE x, 
                                 DFC_UINT_TYPE y 
                               )
{
  cursX = ( x < width  )?x:0;
  cursY = ( y < height )?y:0;
}

void TDisplayFoundation::gotoX( DFC_UINT_TYPE x )
{
  gotoXY( x, cursY );
}

void TDisplayFoundation::gotoY( DFC_UINT_TYPE y )
{
  gotoXY( cursX, y );
}

void TDisplayFoundation::drawCursor( bool bShow /* = true */ )
{
  drawLine( cursX,
      cursY+fontHeight+lineSpacing-1,
      cursX+fontWidth,
   cursY+fontHeight+lineSpacing-1,
            bShow?((fgColor == DF_PIXEL_TRANS)?DF_PIXEL_NORMAL:fgColor):
               ((bgColor == DF_PIXEL_TRANS)?DF_PIXEL_CLEAR :bgColor)
          );
}


#ifdef DFFC_FONT_VARI_16SEG
void TDisplayFoundation::drawCharSeg1( DFF_DATA_TYPE iCh )
{
  if( iCh & _U  ) { DF_DRAW_16SEG_U(); }
  if( iCh & _T  ) { DF_DRAW_16SEG_T(); }
  if( iCh & _S  ) { DF_DRAW_16SEG_S(); }
  if( iCh & _R  ) { DF_DRAW_16SEG_R(); }
  if( iCh & _P  ) { DF_DRAW_16SEG_P(); }
  if( iCh & _N  ) { DF_DRAW_16SEG_N(); }
  if( iCh & _M  ) { DF_DRAW_16SEG_M(); }
  if( iCh & _K  ) { DF_DRAW_16SEG_K();  }
}

void TDisplayFoundation::drawCharSeg2( DFF_DATA_TYPE iCh )
{
  if( iCh & _H  ) { DF_DRAW_16SEG_H(); }
  if( iCh & _G  ) { DF_DRAW_16SEG_G(); }
  if( iCh & _F  ) { DF_DRAW_16SEG_F(); }
  if( iCh & _E  ) { DF_DRAW_16SEG_E(); }
  if( iCh & _D  ) { DF_DRAW_16SEG_D(); }
  if( iCh & _C  ) { DF_DRAW_16SEG_C(); }
  if( iCh & _B  ) { DF_DRAW_16SEG_B(); }
  if( iCh & _A  ) { DF_DRAW_16SEG_A(); }
}

void TDisplayFoundation::drawChar( uint8_t c, bool bUseNextSpacing /* = true */ )
{ 
  if( onDrawChar != NULL )
  {
      // Function returns true when handled
  if( onDrawChar( this, c, &bUseNextSpacing ) )
      { return; }
  }

  if( bgColor != DF_PIXEL_TRANS )
   { drawFillRect( cursX, cursY, cursX+fontWidth, cursY+fontHeight, bgColor ); }

  DFF_DATA_TYPE iCh = DFF_GET_CHAR_DATA(c);

  #if _DP > 0 
   if( iCh & _DP ) { DF_DRAW_16SEG_DP(); iCh-=_DP; }
  #else
   if( c == '.' ) { DF_DRAW_16SEG_POINT(); return; }  
  #endif
  
   // Avoid compiler/linker error: invalid opcode.
   // Do not know what is exactly going on however when
   // splitting the segment detection into two 
   // separated parts, it compiles fine. Compiler bug?
  drawCharSeg1( iCh );
  drawCharSeg2( iCh );
  
  setCursNextColumn(bUseNextSpacing?0:-charSpacing);
}
#else
void TDisplayFoundation::drawChar( uint8_t c, bool bUseNextSpacing /* = true */ )
{
   if( onDrawChar != NULL )
   {
    // Function returns true when handled
   if( onDrawChar( this, c, &bUseNextSpacing ) )
    { return; }
   }

   if( c == ' ' && smallSpace )
   {
     setCursNextColumn(bUseNextSpacing?-fontWidthHalf:-charSpacing);
     return;
   }
   
   if( fontWidth > DFF_WIDTH || fontHeight > DFF_HEIGHT ) 
   {
     drawScaledChar( c, bUseNextSpacing );
     return;
   }
   
   if( fontWidth < DFF_WIDTH || fontHeight < DFF_HEIGHT ) 
   {
     drawSmallChar( c, bUseNextSpacing );
     return;
   }

   
   DFF_DATA_TYPE iChrData;
   uint8_t x = DFF_DATA_COUNT;
   uint8_t y;
  
   while( x-- )
   {
      iChrData = DFF_GET_CHAR_BYTE( c, x );
      y = 8;
      
      while( y-- )
      {
        setPixel( cursX+x,cursY+y, (iChrData & (1<<y))?fgColor:bgColor );
      }
   }
   
   setCursNextColumn(bUseNextSpacing?0:-charSpacing);
}

void TDisplayFoundation::drawScaledChar( uint8_t c, bool bUseNextSpacing /* = true */ )
{

   DFF_DATA_TYPE iChrData;
   uint8_t x  = fontWidth;
   uint8_t y  = fontHeight;
   float xInc = 5.0/(float)fontWidth; 
   float yInc = 8.0/(float)fontHeight; 
   float fX   = DFF_DATA_COUNT-1;
   float fY;
   uint8_t iX = DFF_DATA_COUNT-1; 
   uint8_t iY; 

   while( x-- )
   {
      if( cursX+x < width )
      {
        iChrData = DFF_GET_CHAR_BYTE( c, iX );
      
         fY = iY = 7;
         y  = fontHeight;
      
         while( y-- )
         {
           if( cursY+y < height )
            { setPixel( cursX+x,cursY+y, (iChrData & (1<<iY))?fgColor:bgColor ); }

           fY-=yInc;
         
           if( fY <= (iY-1) )
            { --iY; }
         }
      }
      
      fX-=xInc;

      if( fX <= (iX-1) )
       { --iX; }
   }
   
   setCursNextColumn(bUseNextSpacing?0:-charSpacing);
}

void TDisplayFoundation::drawSmallChar( uint8_t c, bool bUseNextSpacing /* = true */ )
{

   DFF_DATA_TYPE iChrData;
   uint8_t x = DFF_DATA_COUNT;
   uint8_t y;
   uint8_t xPlus = 0;
   uint8_t yPlus = 0;
  
   while( x-- )
   {
      if(( x == 1 && c != '1') || ( x == 4 && c == '1'))
        { xPlus=1; }
         
      iChrData = DFF_GET_CHAR_BYTE( c, x );
      y = 8;
      while( y-- )
      {
         yPlus = (bool)(y<4);
         setPixel( cursX+x+xPlus,cursY+y+yPlus, (iChrData & (1<<y))?fgColor:bgColor );
      }
   }
   
   setCursNextColumn(bUseNextSpacing?0:-charSpacing);
}
#endif

void TDisplayFoundation::drawVertLine( DFC_UINT_TYPE x, 
                                       DFC_UINT_TYPE y, 
                                       DFC_UINT_TYPE l, 
                                       uint8_t iSetMode 
                                      )
{
  if( x < width )
  {
    while( l-- && y < height )
    {
      setPixel( x, y++, iSetMode );
    }
  }
}

void TDisplayFoundation::drawHorzLine( DFC_UINT_TYPE x, 
                                       DFC_UINT_TYPE y, 
                                       DFC_UINT_TYPE l, 
                                       uint8_t iSetMode 
                                      )
{
  if( y < height )
  {
    while( l-- && x < width )
    {
      setPixel( x++, y, iSetMode );
    }
  }
}


void TDisplayFoundation::drawLine( DFC_UINT_TYPE x1, 
                                   DFC_UINT_TYPE y1, 
                                   DFC_UINT_TYPE x2, 
                                   DFC_UINT_TYPE y2, 
                                   uint8_t iSetMode /* = DF_PIXEL_FOREGROUND  */ 
                                  )

{
 
  if( y1==y2 )
  {
    swapVarIf(x1>x2,&x1,&x2);
    drawHorzLine(x1, y1, x2-x1+1, iSetMode );
    return;
  }
  
  if( x1==x2 )
  {
    swapVarIf(y1>y2,&y1,&y2);
    drawVertLine(x1, y1, y2-y1+1, iSetMode );
    return;
  }
    
    // Iterators, counters required by algorithm
    DFC_UINT_TYPE x, y;
    float dx, dy; 
    float dx1, dy1;
    float px, py;
    DFC_UINT_TYPE xe, ye, i;
    
    // Calculate line deltas
    dx = x2 - x1;
    dy = y2 - y1;
    
    // Create a positive copy of deltas (makes iterating easier)
    dx1 = abs(dx);
    dy1 = abs(dy);
    
    // Calculate error intervals for both axis
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;
    
    // The line is X-axis dominant
    if (dy1 <= dx1) 
    {
        // Line is drawn left to right
        if (dx >= 0) 
        {
            x = x1; 
            y = y1; 
            xe = x2;
        } 
        else { // Line is drawn right to left (swap ends)
               x = x2; 
               y = y2; 
               xe = x1;
             }
        
        setPixel(x, y, iSetMode ); // Draw first pixel
        
        // Rasterize the line
        for (i = 0; x < xe; i++) 
        {
            ++x;
            
            // Deal with octants...
            if (px < 0) 
             { px+=(2 * dy1); } 
            else {
                   if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) 
                    { ++y; } 
                   else { --y; }
                   
                   px+=(2 * (dy1 - dx1));
                 }
            
            // Draw pixel from line span at
            // currently rasterized position
            setPixel(x, y, iSetMode);
        }
    } else { // The line is Y-axis dominant
        
             // Line is drawn bottom to top
             if (dy >= 0) 
              {  //Serial.println( "here" );
                 x = x1; y = y1; ye = y2; } 
             else { // Line is drawn top to bottom
                    x = x2; y = y2; ye = y1;
                  }
        

             if( y > ye )
             {  
               // some issues with the code below, for example when:
               // - Different width and height is used
               px=x;
               dx=(abs(x2-x1)+1)/(y-ye); 
               
               while( y >= ye && (y || ye ))
               {  
                 //Serial.println( y );
                 //setPixel(px, y, iSetMode );
                 px+=dx;
                 if( y > 0 )
                  { --y; }
               }
             }
             else {
                    setPixel(x, y, iSetMode ); // Draw first pixel
                    // Rasterize the line
                    for (i = 0; y < ye; i++) 
                    {
                      ++y;
            
                      // Deal with octants...
                     if (py <= 0) 
                      { py+=(2 * dx1); } 
                     else {
                            if ((dx < 0 && dy<0) || (dx > 0 && dy > 0)) 
                             { ++x; } 
                            else { --x; }
                
                            py+=(2 * (dx1 - dy1));
                          }
            
                     // Draw pixel from line span at
                     // currently rasterized position
                     setPixel(x, y, iSetMode );
                   }
             }
           }
}


void TDisplayFoundation::drawRect( DFC_UINT_TYPE x1, 
                                   DFC_UINT_TYPE y1, 
                                   DFC_UINT_TYPE x2, 
                                   DFC_UINT_TYPE y2, 
                                   uint8_t iSetMode /* = DF_PIXEL_FOREGROUND  */ 
                                  )
{
  swapVarIf(x1>x2,&x1,&x2);
  swapVarIf(y1>y2,&y1,&y2);
  drawHorzLine(x1, y1, x2-x1+1, iSetMode );
  drawHorzLine(x1, y2, x2-x1+1, iSetMode );
  drawVertLine(x1, y1, y2-y1+1, iSetMode );
  drawVertLine(x2, y1, y2-y1+1, iSetMode );
}

void TDisplayFoundation::drawFillRect( DFC_UINT_TYPE x1, 
                                       DFC_UINT_TYPE y1, 
                                       DFC_UINT_TYPE x2, 
                                       DFC_UINT_TYPE y2, 
                                       uint8_t iSetMode /* = DF_PIXEL_FOREGROUND  */ 
                                     )
{
  swapVarIf(x1>x2,&x1,&x2);
  swapVarIf(y1>y2,&y1,&y2);
  while( y1 <= y2 )
   { drawHorzLine(x1, y1++, x2-x1+1, iSetMode ); }
}


void TDisplayFoundation::drawCharRect( DFC_UINT_TYPE x1, 
                                       DFC_UINT_TYPE y1, 
                                       DFC_UINT_TYPE x2, DFC_UINT_TYPE y2,
                                       char ch /* = ' ' */
                                     )
{
  DFC_UINT_TYPE i = x1;
      
     // Draw vertical lines
  while( i < x2 )
   {
      gotoScreenXY( i, y1 );
      drawChar( (char)ch, false );
      gotoScreenXY( i++, y2 );
      drawChar( (char)ch, false );
   }

   // Draw horizontal lines
  i = y1+1;
  --y2;
  while( i < y2 )
   {
     gotoScreenXY( x1, i );
     drawChar( (char)ch, false );
     gotoScreenXY( x2, i++ );
     drawChar( (char)ch, false );
   }
}

void TDisplayFoundation::drawStrRect( DFC_UINT_TYPE x1, 
                                      DFC_UINT_TYPE y1, 
                                      DFC_UINT_TYPE x2,
           DFC_UINT_TYPE y2,
                                      const char* s
                                    )
{
  uint8_t  iLen = strlen( s );
  DFC_UINT_TYPE i  = x1;
  DFC_UINT_TYPE iX = 0;
  uint8_t  iStage = 0;
  
  if( iLen == 0 )
   { return; }

  if( iLen == 1 )
  { 
     drawCharRect( x1, y1, x2, y2, *s );     
     return; 
  }

     // Draw vertical lines
  while( iStage < 4 )
   {
      if( iStage == 0 )
      {
        // To right
        gotoScreenXY( i++, y1 );
        if( i >= x2 )
         { ++iStage;
           i = y1;
         }   
      }  
      else
      if( iStage == 1 )
      {
        // To bottom
        gotoScreenXY( x2, i++ );
        if( i >= y2 )
         { ++iStage;
           i = x2;
         }   
      }  
      else
      if( iStage == 2 )
      {
        gotoScreenXY( i--, y2 );
        if( i <= x1 )
         { ++iStage;
           i = y2;
         }   
      }  
      else
      if( iStage == 3 )
      {
        gotoScreenXY( x1, i-- );
        if( i <= y1 )
         { ++iStage; }   
      }  
      drawChar( (char)s[iX], false );
      
      if( ++iX >= iLen )
       { iX=0; }
   }
}



void TDisplayFoundation::drawCharFillRect( DFC_UINT_TYPE x1, 
                                           DFC_UINT_TYPE y1, 
                                           DFC_UINT_TYPE x2,
             DFC_UINT_TYPE y2,
                                           char ch /* = ' ' */
                                          )
{
   DFC_UINT_TYPE x;
   
   while( y1 <= y2  )
   {
     x = x1;
     gotoScreenXY( x, y1++ ); 
     while( x <= x2 )
      { 
        drawChar( (char)ch, false ); 
        ++x;
      }
   }
}

void TDisplayFoundation::drawStrFillRect( DFC_UINT_TYPE x1, 
                                          DFC_UINT_TYPE y1, 
                                          DFC_UINT_TYPE x2, 
                                          DFC_UINT_TYPE y2,
                                          const char* s
                                        )
{
  DFC_UINT_TYPE x;
  uint8_t  iLen = strlen( s );
  DFC_UINT_TYPE iX   = 0;

  if( iLen == 0 )
   { return; }
    
  if( iLen == 1 )
   { 
     drawCharFillRect( x1, y1,x2, y2, (char)*s );
     return;
   }  
   
  while( y1 <= y2  )
   {
     x = x1;
     gotoScreenXY( x, y1++ ); 
     while( x <= x2  )
      { 
        drawChar( (char)s[iX++], false ); 
        ++x;
        if( iX >= iLen )
         { iX = 0; }
      }
   }
}


DFC_UINT_TYPE TDisplayFoundation::centerPrint( DFC_UINT_TYPE x1, 
                                               DFC_UINT_TYPE x2, 
                                               DFC_UINT_TYPE y, 
                                               const char* s,
                                               bool bWithSpacing /* = true */ 
                                             )
{
  DFC_UINT_TYPE i    = strlen( s );
  //DFC_UINT_TYPE iPos = x1+max( 0, (((x2+1)-(x1))-i)*0.5 );
  DFC_UINT_TYPE iPos = x1+max( 0, (DFC_UINT_TYPE)(((x2+1)-(x1))-i)>>1 );
  Serial.println( iPos );
  setCursor( iPos, y, bWithSpacing );
  ++cursX;
  
  if( i > 0 ) 
  {
    while( i-- )
     { drawChar( *s++, bWithSpacing ); }  
  }
  
  return iPos;
}


DFC_UINT_TYPE TDisplayFoundation::centerPrint( const char* s, bool bWithSpacing /* = true */ )
{
  DFC_UINT_TYPE i= strlen( s );
  //cursX = max( 0, (width-i)*0.5 );
  cursX = max( 0, (DFC_UINT_TYPE)(width-i)>>1 );
  
  if( i > 0 ) 
  {
    while( i-- )
     { drawChar( *s++, bWithSpacing ); }  
  }
  
  return cursX;
}


void TDisplayFoundation::drawWindow( DFC_UINT_TYPE x1, DFC_UINT_TYPE y1,
                                     DFC_UINT_TYPE x2, DFC_UINT_TYPE y2,
                                     const char* sCaption /* = NULL */
                                    )
{
  DFC_UINT_TYPE i         = x1+1;
  uint8_t       iCapLen   = 0;
  DFC_UINT_TYPE iCapPos   = 0;
  bool          bCapHooks = false;

  if( canDisplayGraphic() )
  {
    // Draw corners
    gotoScreenXY( x1, y1 ); // TopLeft
    drawChar( (char)218, false ); 
    gotoScreenXY( x2, y1 ); // TopRight
    drawChar( (char)191, false );
    gotoScreenXY( x1, y2 ); // BottomLeft
    drawChar( (char)192, false );
    gotoScreenXY( x2, y2 ); // BottomRight
    drawChar( (char)217, false );
  }
  
  iCapLen = (sCaption != NULL)?strlen( sCaption ):0;
  if( iCapLen > 0 )
  {
    iCapPos = centerPrint( x1, x2, y1, sCaption, false );
    if( iCapPos > x1 )
     {
       bCapHooks = ( iCapPos-2 > 0 );

       if( bCapHooks )
        {
          iCapPos-=1;
          iCapLen+=2;
        }
     }
  }

 iCapLen+=iCapPos;

 if( bCapHooks && canDisplayGraphic() )
 {
   gotoScreenXY( iCapPos, y1 );
   drawChar( (char)180, false );
   gotoScreenXY( --iCapLen, y1 );
   drawChar( (char)195, false );
 }

  if( canDisplayGraphic() )
  { 
    // Draw with graphic characters
    // Draw vertical lines
    while( i < x2 )
    {
       if( iCapLen == 0 || (iCapLen > 0 && (i < iCapPos || i > iCapLen )) )
       {
         gotoScreenXY( i, y1 );
         drawChar( (char)196, false );
       }

       gotoScreenXY( i++, y2 );
       drawChar( (char)196, false );
   }

    // Draw horizontal lines
    i = y1+1;
    while( i < y2 )
    {
       gotoScreenXY( x1, i );
       drawChar( (char)179, false );
       gotoScreenXY( x2, i++ );
       drawChar( (char)179, false );
    }
  }
  else {
          // Draw with lines
         x1*=fontWidth;
         x2*=fontWidth;
         y1*=fontHeight;
         y2*=fontHeight;
         
         if( iCapLen > 0 )
          {
            drawLine( x1, y1, iCapPos = iCapPos*fontWidth, y1, fgColor );
            drawLine( iCapLen*fontWidth, y1, x2+fontWidth, y1, fgColor );
            
            if( bCapHooks )
            {
               drawLine( iCapPos, y1, iCapPos, y1+fontHeight, fgColor );
               iCapPos = iCapLen*fontWidth;
               drawLine( iCapPos, y1, iCapPos, y1+fontHeight, fgColor );
            }
          }
         else { drawLine( x1, y1, x2-fontWidth, y1, fgColor ); } // top
         
         drawLine( x1, y2, x2+fontWidth, y2, fgColor ); // bottom
         drawLine( x1, y1, x1, y2, fgColor ); // left
         drawLine( x2+fontWidth, y1, x2+fontWidth, y2, fgColor ); // right
       }  
}

void TDisplayFoundation::drawWindow( DFC_UINT_TYPE x, 
                                     DFC_UINT_TYPE y, 
                                     const char* sCaption
                                    )
{
  drawWindow( x, y, getScreenWidth(false)-1, 
                    getScreenHeight(false)-1, 
                    sCaption 
                   ); 
}

void TDisplayFoundation::drawElipse( DFC_UINT_TYPE  x, 
                                 DFC_UINT_TYPE  y, 
                                 DFC_UINT_TYPE radius, 
                                 uint8_t iSetMode /* default = DF_PIXEL_FOREGROUND  */ 
                                )
{
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x1 = 0;
  int y1 = radius;
  
  setPixel( x, y + radius, iSetMode );
  setPixel( x, y - radius, iSetMode );
  setPixel( x + radius, y, iSetMode );
  setPixel( x - radius, y, iSetMode );
 
  while(x1 < y1)
  {
    if(f >= 0) 
    {
      y1--;
      ddF_y += 2;
      f += ddF_y;
    }
    x1++;
    ddF_x += 2;
    f += ddF_x;    
    
    setPixel( x + x1, y + y1, iSetMode );
    setPixel( x - x1, y + y1, iSetMode );
    setPixel( x + x1, y - y1, iSetMode );
    setPixel( x - x1, y - y1, iSetMode );
    setPixel( x + y1, y + x1, iSetMode );
    setPixel( x - y1, y + x1, iSetMode );
    setPixel( x + y1, y - x1, iSetMode );
    setPixel( x - y1, y - x1, iSetMode );
  }
}


void TDisplayFoundation::drawCircle( DFC_UINT_TYPE x1, 
                                     DFC_UINT_TYPE y1,
                                     DFC_UINT_TYPE x2,
                                     DFC_UINT_TYPE y2,
                                     uint8_t iSetMode /* = DF_PIXEL_FOREGROUND  */
                                   )
{
  DFC_UINT_TYPE iRadius = min( (DFC_UINT_TYPE)(x2-x1+1)>> 1, (DFC_UINT_TYPE)(y2-y1+1)>> 1 ); 
  drawElipse( x1+iRadius, y1+iRadius, iRadius, iSetMode );
}

void TDisplayFoundation::drawBitmap( const uint8_t* bitmap,
                                     DFC_UINT_TYPE x, 
                                     DFC_UINT_TYPE y, 
                                     DFC_UINT_TYPE w, // width 
                                     DFC_UINT_TYPE h,  // height
                                     bool bDataIsInProgmem /* = true */ 
                                   )
{
 //int16_t i, j, byteWidth = (w + 7) / 8;
 int16_t i, j, byteWidth = (w + 7)>>3;
 uint8_t bits;

  for(j=0; j<h; j++)
  {
  for(i=0; i<w; i++)
  {
       if(i & 7)
        { bits <<= 1; }
       else {
              #ifdef DFF_USE_PROGMEM
                bits = (bDataIsInProgmem)?pgm_read_byte(bitmap + j * byteWidth + i / 8):
                       *(bitmap + j * byteWidth + i / 8);
              #else
                bits = *(bitmap + j * byteWidth + i / 8);
              #endif
             }

       setPixel(x+i, y+j, (bits & 0x80)?DF_PIXEL_FOREGROUND:DF_PIXEL_BACKGROUND );
  }
  }
}

void TDisplayFoundation::clearPixel( DFC_UINT_TYPE x, DFC_UINT_TYPE y )
{
  setPixel( x, y, DF_PIXEL_CLEAR );
}


DFC_UINT_TYPE TDisplayFoundation::calcCharPosition( DFC_UINT_TYPE iPixels,
                                                    DFC_UINT_TYPE iFontSize,
                                                    DFC_UINT_TYPE iFontSpace
                                                   )
{  
  if( iPixels < iFontSize )
   { return 0; }
   
  DFC_UINT_TYPE i = iFontSize+iFontSpace;
  DFC_UINT_TYPE iResult = 0;
  
  while( i < iPixels )
  { 
    ++iResult;
    i+=(iFontSize+iFontSpace);
  }
  
  return ( iFontSpace > 0 && iResult > 0 && i-iFontSpace <= iPixels)?iResult+1:iResult;
}

void TDisplayFoundation::showAsciiTable( uint8_t y, uint16_t iDelayBetweenPages /* = 4000 */ )
{
  uint8_t iMaxLines = getScreenHeight()-1;
  uint8_t iMaxChars = getScreenWidth();
  uint8_t x = 0;
  uint8_t r = 1;
  
  clear();
  setCursor( 0,0 );
   
  while( y <= 0xFF && r != 0xFF )
  {
    setCursor( x, r );
    
    if( y < 10 )
     { drawChar( '0' ); }
    if( y < 100 )
     { drawChar( '0' ); }
     
    print( y );
    drawChar( '=' );
    drawChar( y );
    
    ++y;
   
    if( y > 0 && (y % iMaxLines == 0) )
     { 
       x+=6;
       r=1;
     }
    else { ++r; } 
    
    
    if( x+5 > iMaxChars || y == 0 )
     { 
       setCursorX(0);
       delay(iDelayBetweenPages>0?iDelayBetweenPages:4000);
       x = 0;
       r = (y == 0)?0xFF:1;
       clear();
     } 
     
  }
}

void TDisplayFoundation::serialPlotFontTable()
{
#ifdef DFFC_FONT_DOT_5X8  
  DFC_UINT_TYPE y = 0;
  DFC_UINT_TYPE x = 0;
  uint8_t iChrData;
  uint8_t b;
  char dataArr[5][8]; 
 
  while( y < 256 )
  {
     Serial.print("/* ");
       
     if( y < 10 )
      { Serial.print("0"); }
     if( y < 100 )
      { Serial.print("0"); }
        
     Serial.print(y);
     Serial.print(" */ ");

     x = 0;
     while( x < 5 )
     { 
       Serial.print( "0x" );
       iChrData = DFF_GET_CHAR_BYTE( y, x );
      
      
       b = 8;
       while( b-- )
       {
         dataArr[x][b]=(iChrData & (1<<b))?'#':'.';
       } 
        
       if( iChrData < 16 )
        { Serial.print( "0" ); }
       
       Serial.print( iChrData, HEX );
       if( x < 4 )
        { Serial.print( ", " ); }
       else { 
               if( y < 255 )
                 { Serial.print( "," ); }
               Serial.print( " // " ); 
            } 
       ++x;
     } 

     if( isPrintableChar( y ) )
      { Serial.println( (char)y ); }
     else {  
             if( y == 0 )
              { Serial.println("null"); }
             else
             if( y == 10 )
              { Serial.println("new line"); }
             else
             if( y == 13 )
              { Serial.println("return"); }
            else {  
                    Serial.print( "0x" );
                    if( y < 16 )
                      { Serial.print( "0" ); }
                    
                    Serial.println( y, HEX );
                 } 
          }
     
     b=0;
     while( b < 8 )
     {
       Serial.print( "// ");
       x = 0;
       while( x < 5 )
       {
         Serial.print( (char)dataArr[x][b] );
         ++x;
       }
       
       Serial.println("");
       ++b;
     } 
     
     
     ++y;
  }
  #endif
}

void TDisplayFoundation::swapVarIf( bool bTrue, 
                                     DFC_UINT_TYPE* i1, 
                                     DFC_UINT_TYPE* i2 
                                   )
{
  if( bTrue )
  {
    DFC_UINT_TYPE iSwap = *i2;
    *i2 = *i1;
    *i1 = iSwap;
  }
}


void TDisplayFoundation::delay( uint16_t iDelay ) 
{
  if( onDelay != NULL )
  {
 // Function returns true if handled
 if( onDelay( this, iDelay ) )
     { return; }
  }

  unsigned long time = millis() + iDelay;
  while(millis() < time);
} 

void TDisplayFoundation::begin( DFC_UINT_TYPE iWidth /* = DF_DEF_DISPLAY_WIDTH */, 
                                DFC_UINT_TYPE iHeight /* = DF_DEF_DISPLAY_HEIGHT */ 
                              )
{
  setWidth( iWidth );
  setHeight( iHeight );
}

void TDisplayFoundation::reset()
{
    width          = DFC_DEF_DISPLAY_WIDTH;      // default width (128px)
    height         = DFC_DEF_DISPLAY_HEIGHT;     // default height (64px)
    fontWidth      = DFC_DEF_FONT_WIDTH;         // default font width (8px)
    fontHeight     = DFC_DEF_FONT_HEIGHT;        // default font height (8px)
    fontWidthHalf  = DFC_DEF_FONT_WIDTH_HALF;    // default font width (4px)
    fontHeightHalf = DFC_DEF_FONT_HEIGHT_HALF;   // default font height (4px)
    charSpacing    = DFC_DEF_FONT_CHAR_SPACING;  // default font char spacing (2px)
    lineSpacing    = DFC_DEF_FONT_LINE_SPACING;  // default font line spacing (2px)
    cursX          = 0;
    cursY          = 0;
    cursor         = false;
    smallSpace     =  DFC_DEF_FONT_SMALL_SPACE;
    fgColor        =  DFC_DEF_FONT_FOREGROUND;
    bgColor        =  DFC_DEF_FONT_BACKGROUND;
}

void TDisplayFoundation::update()
{
   static unsigned long time = millis();
   static bool bVisible = false;

   if( millis()-time > 200U  )
   {
    time = millis();

    if( cursor )
    {
     drawCursor( bVisible=!bVisible );
    }
    else if( bVisible )
       { drawCursor( false ); }
   }
}

size_t TDisplayFoundation::write(uint8_t c) 
{
 if(c == '\r')
  { return 1; }

 if(c == '\n')
 {
  setCursNewLine();
  return 1;
 }

    drawChar(c);
 return 1;
}


void TDisplayFoundation::clear( uint8_t iSetMode /* = DF_PIXEL_BACKGROUND */ )
{
 drawFillRect( 0, 0, width-1, height-1,
        ( iSetMode == DF_PIXEL_BACKGROUND && bgColor == DF_PIXEL_TRANS )?DF_PIXEL_CLEAR:iSetMode
       );

 setCursor(0,0);

    if( onClearDisplay != NULL )
    {
       onClearDisplay( this );
    }
}



TDisplayFoundation displayFoundry;

// ----------------------------------------------------------------------------
