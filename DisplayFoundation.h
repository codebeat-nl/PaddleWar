/*
 * TDisplayFoundation - Graphic Basics and event driven driver for many displays
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
 *
 */


#ifndef TDISPLAYFOUNDATION_H
#define TDISPLAYFOUNDATION_H

#include "DisplayFoundation.config.h"
#include <stdint.h>
#include <inttypes.h>
#include <Arduino.h>

 // 'Colours' possible
#define DF_PIXEL_CLEAR       0x00  // Clears a pixel (black)
#define DF_PIXEL_NORMAL      0x01  // Draws  a pixel (white)
#define DF_PIXEL_INVERT      0x02  // Inverts a pixel
#define DF_PIXEL_TRANS       0x03  // Do nothing pixel
#define DF_PIXEL_FOREGROUND  0xFE  // Use fgColor setting
#define DF_PIXEL_BACKGROUND  0xFF  // Use bgColor setting

#ifdef DFFC_FONT_VARI_16SEG
  /*
   Segment drawing with use of drawLine function.

   VARI 16-SEGMENT LAYOUT

      A      B
   ______ ______
   |\     |     /|
   | K    |    N |
   |  \   M   /  |
 H |   \  |  /   | C
   |    \ | /    |
   |__U__\|/__P__|
   |     /|\     |
   |    / | \    |
   |   /  |  \   |
 G |  /   S   \  | D
   | T    |    R |
   |/     |     \|
   ------ -------  [DP]
      F      E
 */
 #define DF_DRAW_16SEG_DP() drawLine(cursX+fontWidthHalf,cursY+fontHeight,cursX+fontWidthHalf,cursY+fontHeight)
 #define DF_DRAW_16SEG_U()  drawLine(cursX,cursY+fontHeightHalf,cursX+fontWidthHalf,cursY+fontHeightHalf)
 #define DF_DRAW_16SEG_T()  drawLine(cursX,cursY+fontHeight,cursX+fontWidthHalf,cursY+fontHeightHalf)
 #define DF_DRAW_16SEG_S()  drawLine(cursX+fontWidthHalf,cursY+fontHeightHalf,cursX+fontWidthHalf,cursY+fontHeight)
 #define DF_DRAW_16SEG_R()  drawLine(cursX+fontWidthHalf,cursY+fontHeightHalf,cursX+fontWidth,cursY+fontHeight)
 #define DF_DRAW_16SEG_P()  drawLine(cursX+fontWidthHalf,cursY+fontHeightHalf,cursX+fontWidth,cursY+fontHeightHalf)
 #define DF_DRAW_16SEG_N()  drawLine(cursX+fontWidthHalf,cursY+fontHeightHalf,cursX+fontWidth,cursY)
 #define DF_DRAW_16SEG_M()  drawLine(cursX+fontWidthHalf,cursY,cursX+fontWidthHalf,cursY+fontHeightHalf)
 #define DF_DRAW_16SEG_K()  drawLine(cursX,cursY,cursX+fontWidthHalf,cursY+fontHeightHalf)
 #define DF_DRAW_16SEG_H()  drawLine(cursX,cursY,cursX,cursY+fontHeightHalf)
 #define DF_DRAW_16SEG_G()  drawLine(cursX,cursY+fontHeightHalf,cursX,cursY+fontHeight)
 #define DF_DRAW_16SEG_F()  drawLine(cursX,cursY+fontHeight,cursX+fontWidthHalf,cursY+fontHeight)
 #define DF_DRAW_16SEG_E()  drawLine(cursX+fontWidthHalf,cursY+fontHeight,cursX+fontWidth,cursY+fontHeight)
 #define DF_DRAW_16SEG_D()  drawLine(cursX+fontWidth,cursY+fontHeightHalf,cursX+fontWidth,cursY+fontHeight)
 #define DF_DRAW_16SEG_C()  drawLine(cursX+fontWidth,cursY,cursX+fontWidth,cursY+fontHeightHalf)
 #define DF_DRAW_16SEG_B()  drawLine(cursX+fontWidthHalf,cursY,cursX+fontWidth,cursY)
 #define DF_DRAW_16SEG_A()  drawLine(cursX,cursY,cursX+fontWidthHalf,cursY)
 #define DF_DRAW_16SEG_POINT() drawLine(cursX+fontWidthHalf,cursY+fontHeight,cursX+fontWidthHalf,cursY+fontHeight)
#endif


// ----------------------------------------------------------------------------

class TDisplayFoundation; // Forward declaration

 // Event types
typedef void    (* TDFENotifyEvent)( TDisplayFoundation* poSender  );
typedef uint8_t (* TDFEGetPixelEvent)( TDisplayFoundation* poSender, DFC_UINT_TYPE x, DFC_UINT_TYPE y );
typedef void    (* TDFESetPixelEvent)( TDisplayFoundation* poSender, DFC_UINT_TYPE x, DFC_UINT_TYPE y, uint8_t iSetMode );
typedef bool    (* TDFEDrawCharEvent)( TDisplayFoundation* poSender, unsigned char c, bool* pbUseNextSpacing );
typedef bool    (* TDFEDelayEvent)( TDisplayFoundation* poSender, uint16_t iDelay );


class TDisplayFoundation: public Print {

   private:   
    DFC_UINT_TYPE width;
    DFC_UINT_TYPE height;
    DFC_UINT_TYPE fontWidth;
    DFC_UINT_TYPE fontHeight;
    DFC_UINT_TYPE fontWidthHalf;
    DFC_UINT_TYPE fontHeightHalf;
    DFC_UINT_TYPE charSpacing;
    DFC_UINT_TYPE lineSpacing;
    DFC_UINT_TYPE cursX;	   // Current cursor x-position (in pixels)
    DFC_UINT_TYPE cursY;       // Current cursor y-position (in pixels)
    bool          smallSpace;  // Smaller space character true/false
    bool          cursor;      // Cursor visible true/false
    uint8_t       fgColor;     // Foreground 'colour'
    uint8_t       bgColor;     // Background 'colour'
    
   public:
    TDisplayFoundation();
     
     // Event properties
    TDFEGetPixelEvent onGetPixel     = NULL;
    TDFESetPixelEvent onSetPixel     = NULL;
    TDFEDrawCharEvent onDrawChar     = NULL;
    TDFEDelayEvent    onDelay        = NULL;
    TDFENotifyEvent   onClearDisplay = NULL;

     // can-functions: Determine the applied font capabilities 
    bool    canDisplayControlCode();
    bool    canDisplayNumeric();
    bool    canDisplayText();
    bool    canDisplaySpecial();
    bool    canDisplayGraphic(); 
    bool    canDisplayAll();
    
    bool    isCursorVisible(); // Determine cursor is visible
     // is-functions: Determine the kind of char 
    bool    isControlCodeChar( unsigned char chr ); // Determine char is #31 or below
    bool    isNumericChar(     unsigned char chr ); // Determine char is 0..9
    bool    isAlphabetChar(    unsigned char chr ); // Determine char is a..z,A..Z
    bool    isTextChar(        unsigned char chr ); // Determine is normal ASCII char
    bool    isSpecialChar(     unsigned char chr ); // Determine char is for example é,ê,ë,ì,í,î,ï etc.
    bool    isGraphicChar(     unsigned char chr ); // Determine char is ASCII grapical char
    bool    isCalcChar(        unsigned char chr ); // Determine char is *.,/+-
    bool    isPrintableChar(   unsigned char chr,   // Determine char can be printed on screen
                               bool bAllowSpecialChars = true );

     // ** getters **
     // Get display size in pixels
    DFC_UINT_TYPE getWidth();
    DFC_UINT_TYPE getHeight();
     
     // Get the screen width or height in character units
    DFC_UINT_TYPE getScreenWidth(  bool bWithSpacing = true );
    DFC_UINT_TYPE getScreenHeight( bool bWithSpacing = true );

     // Get the cursor position on display in pixels
    DFC_UINT_TYPE getX();
    DFC_UINT_TYPE getY();

     // Get the cursor position on screen in character units
    DFC_UINT_TYPE getScreenX( bool bWithSpacing = true );
    DFC_UINT_TYPE getScreenY( bool bWithSpacing = true );
    
     // Get size of font in pixels
    DFC_UINT_TYPE getFontWidth();
    DFC_UINT_TYPE getFontHeight();
    bool          getFontSmallSpace();
    
     // Get spacing of font in pixels
    DFC_UINT_TYPE getCharSpacing(); // Spacing on x-axis, between chars
    DFC_UINT_TYPE getLineSpacing(); // Spacing on y-axis, between line of chars
    
     // Get 'colour' settings, see also top of file for expected return values 
    DFC_UINT_TYPE getFG(); // Get foreground 'colour'
    DFC_UINT_TYPE getBG(); // Get background 'colour'
    
     // Get the 'colour' of a pixel that is on display, units in pixels
     // Notice: To be able to capture pixel values, you need to assign 
     //         an eventhandler function to the onGetPixel event 
     //         variabele/property of this class! Without this function
     //         it will return the iReturnDefault value only.  
    uint8_t getPixel( DFC_UINT_TYPE x, 
                      DFC_UINT_TYPE y, 
                      uint8_t iReturnDefault = DF_PIXEL_TRANS 
                    );

     
     // ** Setters **

    // Set cursor position, units in characters (not pixels!)
    void setCursorX( DFC_UINT_TYPE x,
                     bool bWithSpacing = true
                   );
    void setCursorY( DFC_UINT_TYPE x,
                     bool bWithSpacing = true
                   );
    void setCursor(  DFC_UINT_TYPE x, 
                     DFC_UINT_TYPE y, 
                     bool bWithSpacing = true 
                  );
    void setCursRow( DFC_UINT_TYPE y );
    void setCursCol( DFC_UINT_TYPE x );
    void setCursNewLine(); // Same as newLine();

     // Move cursor to next x (column) or y (row) position
    void setCursNextRow();
    void setCursNextColumn( int8_t iExtraSpace = 0 );
    
     // Set the fontsize, width and height, units in pixels
    void setFontWidth(  DFC_UINT_TYPE iValue );
    void setFontHeight( DFC_UINT_TYPE iValue );
    void setFontSize(   DFC_UINT_TYPE iWidth  = DFC_DEF_FONT_WIDTH, 
                        DFC_UINT_TYPE iHeight = DFC_DEF_FONT_HEIGHT
                     );
     // Set a small space character (half the width of a character)
    void setFontSmallSpace( bool bValue );                 

     // Set spacing between characters and lines, units in pixels
    void setCharSpacing( DFC_UINT_TYPE iValue );
    void setLineSpacing( DFC_UINT_TYPE iValue );
    void setSpacing( DFC_UINT_TYPE xCharValue,  
                     DFC_UINT_TYPE yLineValue 
                    );
     
     // Set display width and height
    void setWidth( DFC_UINT_TYPE iValue );
    void setHeight( DFC_UINT_TYPE iValue );
    void setSize( DFC_UINT_TYPE iWidth, DFC_UINT_TYPE iHeight );
    
     // Set colors to use
    void setFG( uint8_t iColor ); // Foreground
    void setBG( uint8_t iColor ); // Background
    

    // Set the 'colour' of a pixel on display, units in pixels
    // Notice: To be able to set pixel values, you need to assign
    //         an eventhandler function to the onSetPixel event
    //         variabele/property of this class! Without this
    //         assignment nothing will happen.
    void setPixel( DFC_UINT_TYPE x, DFC_UINT_TYPE y, uint8_t iSetMode = DF_PIXEL_FOREGROUND  );


     // Performs an new line, goto next line and set cursor
     // at the beginning of the line.
    void newLine();

    // Show or hide the cursor
    // Notice: In the loop function you must call update() to
    //         be able to show or hide the cursor.
    void showCursor();
    void hideCursor();

     // GotoXY moves the cursor to a character position, 
     // units in characters (not pixels!). 
     // Practically the same as setCursor() except the
     // default of bool option is opposite value. 
    void gotoScreenXY( DFC_UINT_TYPE x, // x-coordinate
                       DFC_UINT_TYPE y, // y-coordinate
                       bool bWithSpacing = false 
                      );
    void gotoScreenX( DFC_UINT_TYPE x, bool bWithSpacing = false );
    void gotoScreenY( DFC_UINT_TYPE y, bool bWithSpacing = false );

     
     // GotoXY moves the cursor to any position, 
     // units in pixels. 
    void gotoXY( DFC_UINT_TYPE x, // x-coordinate
                 DFC_UINT_TYPE y  // y-coordinate
                );
    void gotoX( DFC_UINT_TYPE x );
    void gotoY( DFC_UINT_TYPE y );

    // ** Draw and print functions **
    // Notice: To capture and process the output of these functions 
    //         you need to assign an eventhandler on the onSetPixel 
    //         event variabele/property!  
    
     // Draws the cursor, visible or hidden
    void drawCursor( bool bShow = true );

     // Low level functions to draw font characters.
     // These functions uses the fgColor and bgColor color settings
     // and current cursor position set by setCursor(), gotoScreenXY(),
     // gotoXY() etc.
     // Notice: Beter use drawChar() only, this function will call
     //         the other two automatically when fontsize is below or 
     //         greater than default fontsize.
    #ifdef DFFC_FONT_VARI_16SEG
     void drawCharSeg1( uint16_t iCh );
     void drawCharSeg2( uint16_t iCh );
     void drawChar( uint8_t c, bool __notused__ = true );
    #endif
    #ifdef DFFC_FONT_DOT_5X8
     void drawChar( uint8_t c, bool bUseNextSpacing = true );
     void drawScaledChar( uint8_t c, bool bUseNextSpacing = true );
     void drawSmallChar(  uint8_t c, bool bUseNextSpacing = true );
    #endif
    
     // Prints a string in center/in between of a x-axis start- and endpoint,
     // units in characters (not pixels!).     
     // Returns: the calculated position of the string (in pixels)
    DFC_UINT_TYPE centerPrint( DFC_UINT_TYPE x1, 
                               DFC_UINT_TYPE x2, 
                               DFC_UINT_TYPE y,
                               const char* s, bool bWithSpacing = true
                             );
     
     // Prints a string in center on current cursor (line) position.
     // Returns: the calculated position of the string (in pixels)
    DFC_UINT_TYPE centerPrint( const char* s, bool bWithSpacing = true );
    
     // Draws a vertical line, units in pixels
    void drawVertLine( DFC_UINT_TYPE x, // x-coordinate
                       DFC_UINT_TYPE y, // y-coordinate
                       DFC_UINT_TYPE l, // length of line
                       uint8_t iSetMode = DF_PIXEL_FOREGROUND  // 'colour' 
                      );
    
     // Draws a vertical line, units in pixels
    void drawHorzLine( DFC_UINT_TYPE x, // x-coordinate
                       DFC_UINT_TYPE y, // x-coordinate
                       DFC_UINT_TYPE l, // length of line
                       uint8_t iSetMode = DF_PIXEL_FOREGROUND  // 'colour'
                      );
    
     // Draws a line into any direction, units in pixels
    void drawLine( DFC_UINT_TYPE x1, // start x-coordinate
                   DFC_UINT_TYPE y1, // start y-coordinate
                   DFC_UINT_TYPE x2, // end x-coordinate
                   DFC_UINT_TYPE y2, // end y-coordinate
                   uint8_t iSetMode = DF_PIXEL_FOREGROUND  // 'colour'
                 );
     
     // Draws a line into any direction, units in pixels
    void drawRect( DFC_UINT_TYPE x1, // start x-coordinate
                   DFC_UINT_TYPE y1, // start y-coordinate
                   DFC_UINT_TYPE x2, // end x-coordinate
                   DFC_UINT_TYPE y2, // end y-coordinate
                   uint8_t iSetMode = DF_PIXEL_FOREGROUND  // 'colour'
                 );

     // Draws a solid rect, units in pixels
    void drawFillRect( DFC_UINT_TYPE x1, // start x-coordinate
                       DFC_UINT_TYPE y1, // start y-coordinate
                       DFC_UINT_TYPE x2, // end x-coordinate
                       DFC_UINT_TYPE y2, // end y-coordinate
                       uint8_t iSetMode = DF_PIXEL_FOREGROUND  // 'colour'
                     );
     
     // Draws a rectangle boundary with a character, units in characters (not pixels!)
     // This function uses the fgColor and bgColor color settings
    void drawCharRect( DFC_UINT_TYPE x1, // start column-coordinate
                       DFC_UINT_TYPE y1, // start row-coordinate
                       DFC_UINT_TYPE x2, // end column-coordinate
                       DFC_UINT_TYPE y2, // end row-coordinate
                       char ch = ' '     // character to draw
                     );
     
     // Draws a rectangle boundary with a string, units in characters (not pixels!)
     // This function uses the fgColor and bgColor color settings
    void drawStrRect(  DFC_UINT_TYPE x1, // start column-coordinate
                       DFC_UINT_TYPE y1, // start row-coordinate
                       DFC_UINT_TYPE x2, // end column-coordinate
                       DFC_UINT_TYPE y2, // end row-coordinate
                       const char* s           // string to draw
                     );
    
     // Draws a rectangle filled with a character, units in characters (not pixels!)
     // This function uses the fgColor and bgColor color settings
    void drawCharFillRect(  DFC_UINT_TYPE x1, // start column-coordinate
                            DFC_UINT_TYPE y1, // start row-coordinate
                            DFC_UINT_TYPE x2, // end column-coordinate
                            DFC_UINT_TYPE y2, // end row-coordinate
                            char ch = ' '     // character to draw 
                          );
    
    
     // Draws a rectangle filled with a string, units in characters (not pixels!)
     // This function uses the fgColor and bgColor color settings
    void drawStrFillRect( DFC_UINT_TYPE x1, // start column-coordinate
                          DFC_UINT_TYPE y1, // start row-coordinate
                          DFC_UINT_TYPE x2, // end column-coordinate
                          DFC_UINT_TYPE y2, // end row-coordinate
                          const char* s           // string to draw
                        );
    
     // Draws a rectangle boundary with or without a caption, units in characters (not pixels!)
     // This function uses the fgColor and bgColor color settings.
     // Notice: This function uses the graphic characters of the font. If not
     //         included in the font array, it will use the line functions instead.        
    void drawWindow( DFC_UINT_TYPE x1, // start column-coordinate
                     DFC_UINT_TYPE y1, // start row-coordinate
                     DFC_UINT_TYPE x2, // end column-coordinate
                     DFC_UINT_TYPE y2, // end row-coordinate
                     const char* sCaption = NULL
                   );
    
     // Draws a rectangle boundary from point x,y to the end of the screen size, 
     // units in characters (not pixels!).
     // This function uses the fgColor and bgColor color settings.
     // Notice: This function uses the graphic characters of the font. If not
     //         included in the font array, it will use the line functions instead.        
    void drawWindow( DFC_UINT_TYPE x, DFC_UINT_TYPE y, 
                     const char* sCaption = NULL
                   );
     
    void drawElipse( DFC_UINT_TYPE x, 
                     DFC_UINT_TYPE y, 
                     DFC_UINT_TYPE radius, 
                     uint8_t iSetMode = DF_PIXEL_FOREGROUND  
                   );

    void drawCircle( DFC_UINT_TYPE x1, 
                     DFC_UINT_TYPE y1,
                     DFC_UINT_TYPE x2, 
                     DFC_UINT_TYPE y2,
                     uint8_t iSetMode = DF_PIXEL_FOREGROUND 
                   );

     // Draws a monochrome bitmap, each byte contains 8 pixels.
     // units in pixels.
    void drawBitmap( const uint8_t* bitmap, // bitmap array with bytes
                     DFC_UINT_TYPE x, // x-coordinate
                     DFC_UINT_TYPE y, // y-coordinate
                     DFC_UINT_TYPE w, // width of bitmap 
                     DFC_UINT_TYPE h, // height of bitmap
                     bool bDataIsInProgmem = true // Datapointer points to data in program area
                   );
    


    
     // Clears a pixel on position (x,y), units in pixels.
		void clearPixel( DFC_UINT_TYPE x, // x-coordinate
		                 DFC_UINT_TYPE y  // y-coordinate
		               );
    
    

    DFC_UINT_TYPE calcCharPosition( DFC_UINT_TYPE iPixels, 
                                    DFC_UINT_TYPE iFontSize, 
                                    DFC_UINT_TYPE iFontSpace
                                  );  

    void showAsciiTable( uint8_t y = 0, uint16_t iDelayBetweenPages = 4000 );
    void serialPlotFontTable();
    void swapVarIf( bool bTrue, DFC_UINT_TYPE* i1, DFC_UINT_TYPE* i2 );

     // Standard functions
    void delay( uint16_t iDelay );
    void begin( DFC_UINT_TYPE iWidth  = DFC_DEF_DISPLAY_WIDTH, 
                DFC_UINT_TYPE iHeight = DFC_DEF_DISPLAY_HEIGHT
              );
    void reset();
    void update();
    void clear( uint8_t iSetMode = DF_PIXEL_BACKGROUND );
    virtual size_t write(uint8_t c); using Print::write;

};


extern TDisplayFoundation displayFoundry;

// ----------------------------------------------------------------------------

#endif
