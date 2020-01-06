
// Display width and height in pixels
// ----------------------------------
#define DFC_DEF_DISPLAY_WIDTH     128
#define DFC_DEF_DISPLAY_HEIGHT    64

// DFC_DEF_DISPLAY_HIGHRES
// -----------------------
// With 8 bit only screen-sizes up to 255x255 are possible.
// Uncomment this define if you want to use larger screens
// (16 bit declaration types instead of 8 bit).
//#define DFC_DEF_DISPLAY_HIGHRES

// Font selection
// --------------
// Select font you want here, select only one!
// - DFFC_FONT_VARI_16SEG = mimic 16 segment vari characters (limited characterset, 96 characters)
// - DFFC_FONT_DOT_5X8    = mimic dot matrix characters (up to whole ASCII characterset, 256 characters max)
//#define DFFC_FONT_VARI_16SEG
#define DFFC_FONT_DOT_5X8


// Default Font settings
// ---------------------
// Notice:
// - DFC_DEF_FONT_BACKGROUND default is a transparent pixel (DF_PIXEL_TRANS).
//   This is to reduce display writes and speed up drawing by draw only the pixels
//   that needs to be ON.
//   Before overwriting something already on the display, you need to clear the
//   area first or entire display first. If you don't want transparency and can
//   live with some decrease in speed, you can change it to DF_PIXEL_CLEAR instead.
// - Both fonts support font stretching, VARI_16SEG acts more like a vector font
//   with small straight lines and the DOT_5X8 acts more like a zoomed font (pixels
//   get larger). To get best results, scale values proportional. To change the
//   font size at runtime, take a look at the setFontSize() function.
// - All default settings can be changed at run-time, see also DisplayFoundation.h
//   for a function overview.
#ifdef DFFC_FONT_VARI_16SEG
 #define DFC_DEF_FONT_WIDTH        4
 #define DFC_DEF_FONT_HEIGHT       8
 #define DFC_DEF_FONT_WIDTH_HALF   2
 #define DFC_DEF_FONT_HEIGHT_HALF  4
 #define DFC_DEF_FONT_CHAR_SPACING 2
 #define DFC_DEF_FONT_LINE_SPACING 4
 #define DFC_DEF_FONT_SMALL_SPACE  true
 #define DFC_DEF_FONT_FOREGROUND   DF_PIXEL_NORMAL
 #define DFC_DEF_FONT_BACKGROUND   DF_PIXEL_TRANS
#else
 #define DFC_DEF_FONT_WIDTH        5
 #define DFC_DEF_FONT_HEIGHT       8
 #define DFC_DEF_FONT_WIDTH_HALF   2
 #define DFC_DEF_FONT_HEIGHT_HALF  4
 #define DFC_DEF_FONT_CHAR_SPACING 2
 #define DFC_DEF_FONT_LINE_SPACING 2
 #define DFC_DEF_FONT_SMALL_SPACE  true
 #define DFC_DEF_FONT_FOREGROUND   DF_PIXEL_NORMAL
 #define DFC_DEF_FONT_BACKGROUND   DF_PIXEL_TRANS

  // Font characters
  // ---------------
  // At default all printable ASCII characters are selected.

  #define  DFFC_ALL_CHARS       // All 256 characters = 1280 bytes
  //#define  DFFC_CONTROL_CHARS   // 14 characters * 5b =   70 bytes
  #define  DFFC_GRAPHIC_CHARS   // 72 characters * 5b =  360 bytes
  #define  DFFC_STANDARD_CHARS  // 96 characters * 5b =  480 bytes
  #define  DFFC_SPECIAL_CHARS   // 44 characters * 5b =  220 bytes
#endif



 // Some useful char type detection macro's
#define DFFC_IS_CONTROL_CHAR( chr )    ( chr >= 0 && chr <= 31 )   
#define DFFC_IS_NUMERIC_CHAR( chr )    ( chr >= '0' && chr <= '9' )   
#define DFFC_IS_ALPHABET_CHAR( chr )  (( chr >= 'a' && chr <= 'z' )\
                                    || ( chr >= 'A' && chr <= 'Z' ))   
#define DFFC_IS_CALC_CHAR( chr )      (( chr >= '*' ) && ( chr <= '/' ))  
#define DFFC_IS_STANDARD_CHAR( chr )  (( chr >= 32 ) && ( chr <= 127 ))  
#define DFFC_IS_TEXT_CHAR( chr )      (( DFFC_IS_ALPHABET_CHAR( chr ))\
                                    || ( DFFC_IS_CALC_CHAR( chr ))\
                                    || ( chr >= 32 && chr <= 47 )\
                                    || ( chr >= 58 && chr <= 64 )\
                                    || ( chr >= 91 && chr <= 96 )\
                                    || ( chr >= 123 && chr <= 126 ))
#define DFFC_IS_SPECIAL_CHAR( chr )   (( chr >= 127 && chr <= 168 )\
                                    || ( chr >= 171 && chr <= 173 )\
                                    || ( chr >= 224 && chr <= 253 ))    
#define DFFC_IS_GRAPHIC_CHAR(chr)    (( chr >= 169 && chr <= 170 )\
                                    || ( chr >= 174 && chr <= 223 )\
                                    || ( chr >= 254 && chr <= 255 )\
                                    || ( chr >= 14  && chr <= 31 ))     


 // Do not touch this
#if !defined DFC_DEF_DISPLAY_HIGHRES && (DFC_DEF_DISPLAY_WIDTH <= 0xFF && DFC_DEF_DISPLAY_HEIGHT <= 0xFF)
 #define DFC_UINT_TYPE uint8_t
#else
 #define DFC_UINT_TYPE uint16_t
#endif

