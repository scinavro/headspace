/***************************************************
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_ThinkInk.h"

#define DELAY 200
#define COLOR1 EPD_BLACK
#define COLOR2 EPD_WHITE

#define SRAM_CS     -1
#define EPD_RESET   5
#define EPD_BUSY    10

#define EPD_CS_1      14
#define EPD_DC_1      13

#define EPD_CS_2      6
#define EPD_DC_2      7

#define EPD_CS_3      11
#define EPD_DC_3      12

#define EPD_CS_4      4
#define EPD_DC_4      3

#define EPD_CS_5      2
#define EPD_DC_5      1

#define EPD_CS_6      16
#define EPD_DC_6      15

// Uncomment the following line if you are using 2.13" Monochrome EPD with SSD1680
//ThinkInk_213_Mono_BN display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
//ThinkInk_213_Mono_B74 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

// Uncomment the following line if you are using 2.13" Tri-Color EPD with SSD1680
//ThinkInk_213_Tricolor_RW display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

// Uncomment the following line if you are using 2.13" EPD with SSD1675
// ThinkInk_213_Mono_B72 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

// Uncomment the following line if you are using 2.13" EPD with SSD1675B
//ThinkInk_213_Mono_B73 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

// Uncomment the following line if you are using 2.13" EPD with UC8151D
//ThinkInk_213_Mono_M21 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

//Uncomment the following line if you are using 2.13" EPD with IL0373
//ThinkInk_213_Tricolor_Z16 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
//#define FLEXIBLE_213

// Uncomment the following line if you are using 2.9" Tri-Color EPD with IL0373
//ThinkInk_290_Tricolor_Z10 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

// Uncomment the following line if you are using 2.9" Grayscale EPD with IL0373
//ThinkInk_290_Grayscale4_T5 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
#define FLEXIBLE_290

// Uncomment the following line if you are using 2.9" Monochrome EPD with UC8151D
//ThinkInk_290_Mono_M06 display(EPD_DC_0, 16, EPD_CS_0, SRAM_CS, EPD_BUSY_0); //reset -> busy
ThinkInk_290_Mono_M06 display_1(EPD_DC_1, EPD_RESET, EPD_CS_1, SRAM_CS, EPD_BUSY);
ThinkInk_290_Mono_M06 display_2(EPD_DC_2, EPD_RESET, EPD_CS_2, SRAM_CS, EPD_BUSY);
ThinkInk_290_Mono_M06 display_3(EPD_DC_3, EPD_RESET, EPD_CS_3, SRAM_CS, EPD_BUSY);
ThinkInk_290_Mono_M06 display_4(EPD_DC_4, EPD_RESET, EPD_CS_4, SRAM_CS, EPD_BUSY);
ThinkInk_290_Mono_M06 display_5(EPD_DC_5, EPD_RESET, EPD_CS_5, SRAM_CS, EPD_BUSY);
ThinkInk_290_Mono_M06 display_6(EPD_DC_6, EPD_RESET, EPD_CS_6, SRAM_CS, EPD_BUSY);
// Uncomment the following line if you are using 2.9" Tri-Color EPD with UC8151D
//ThinkInk_290_Tricolor_Z13 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);


void setup() {  
  display_1.begin();
  display_2.begin();
  display_3.begin();
  display_4.begin();
  display_5.begin();
  display_6.begin();
#if defined(FLEXIBLE_213) || defined(FLEXIBLE_290)
  // The flexible displays have different buffers and invert settings!
  display_1.setBlackBuffer(1, false);
  display_1.setColorBuffer(1, false);
  display_2.setBlackBuffer(1, false);
  display_2.setColorBuffer(1, false);
  display_3.setBlackBuffer(1, false);
  display_3.setColorBuffer(1, false);
  display_4.setBlackBuffer(1, false);
  display_4.setColorBuffer(1, false);
  display_5.setBlackBuffer(1, false);
  display_5.setColorBuffer(1, false);
  display_6.setBlackBuffer(1, false);
  display_6.setColorBuffer(1, false);
#endif
}

void loop() {

//  testdrawtext(display_1,"one", COLOR1);
//  testdrawtext(display_2,"two", COLOR1);
//  testdrawtext(display_3,"three", COLOR1);
//  testdrawtext(display_4,"four", COLOR1);
//  testdrawtext(display_5,"five", COLOR1);
//  testdrawtext(display_6,"six", COLOR1);


//Square-moving starts
  display_1.clearBuffer();
  display_2.clearBuffer();
  display_3.clearBuffer();
  display_4.clearBuffer();
  display_5.clearBuffer();
  display_6.clearBuffer();    

  display_1.fillRect(display_1.width()/2-60, display_1.height()/2-60, 60, 60, COLOR1);
  display_2.fillRect(display_2.width()/2-60, display_1.height()/2-60, 60, 60, COLOR1);
  display_3.fillRect(display_3.width()/2-60, display_1.height()/2-60, 60, 60, COLOR1);
  display_4.fillRect(display_4.width()/2-60, display_1.height()/2-60, 60, 60, COLOR1);
  display_5.fillRect(display_5.width()/2-60, display_1.height()/2-60, 60, 60, COLOR1);
  display_6.fillRect(display_6.width()/2-60, display_1.height()/2-60, 60, 60, COLOR1);

  display_1.display();
  delay(DELAY);
  display_2.display();
  delay(DELAY);
  display_3.display();
  delay(DELAY);
  display_4.display();
  delay(DELAY);
  display_5.display();
  delay(DELAY);
  display_6.display();
  delay(DELAY);

  display_1.clearBuffer();
  display_2.clearBuffer();
  display_3.clearBuffer();
  display_4.clearBuffer();
  display_5.clearBuffer();
  display_6.clearBuffer();  
  
  display_1.fillRect(display_1.width()/2-30, display_1.height()/2-30, 60, 60, COLOR1);
  display_2.fillRect(display_2.width()/2-30, display_1.height()/2-30, 60, 60, COLOR1);
  display_3.fillRect(display_3.width()/2-30, display_1.height()/2-30, 60, 60, COLOR1);
  display_4.fillRect(display_4.width()/2-30, display_1.height()/2-30, 60, 60, COLOR1);
  display_5.fillRect(display_5.width()/2-30, display_1.height()/2-30, 60, 60, COLOR1);
  display_6.fillRect(display_6.width()/2-30, display_1.height()/2-30, 60, 60, COLOR1);

  display_1.display();
  delay(DELAY);
  display_2.display();
  delay(DELAY);
  display_3.display();
  delay(DELAY);
  display_4.display();
  delay(DELAY);
  display_5.display();
  delay(DELAY);
  display_6.display();
  delay(DELAY);

  display_1.clearBuffer();
  display_2.clearBuffer();
  display_3.clearBuffer();
  display_4.clearBuffer();
  display_5.clearBuffer();
  display_6.clearBuffer();  
  
  display_1.fillRect(display_1.width()/2, display_1.height()/2, 60, 60, COLOR1);
  display_2.fillRect(display_2.width()/2, display_1.height()/2, 60, 60, COLOR1);
  display_3.fillRect(display_3.width()/2, display_1.height()/2, 60, 60, COLOR1);
  display_4.fillRect(display_4.width()/2, display_1.height()/2, 60, 60, COLOR1);
  display_5.fillRect(display_5.width()/2, display_1.height()/2, 60, 60, COLOR1);
  display_6.fillRect(display_6.width()/2, display_1.height()/2, 60, 60, COLOR1);

  display_1.display();
  delay(DELAY);
  display_2.display();
  delay(DELAY);
  display_3.display();
  delay(DELAY);
  display_4.display();
  delay(DELAY);
  display_5.display();
  delay(DELAY);
  display_6.display();
  delay(DELAY);
//Square-moving stops



//Circle-moving starts
  display_1.clearBuffer();
  display_2.clearBuffer();
  display_3.clearBuffer();
  display_4.clearBuffer();
  display_5.clearBuffer();
  display_6.clearBuffer();

  display_1.fillCircle(60, display_1.height()/2, 30, COLOR1);
  display_2.fillCircle(60, display_1.height()/2, 30, COLOR1);
  display_3.fillCircle(60, display_1.height()/2, 30, COLOR1);
  display_4.fillCircle(60, display_1.height()/2, 30, COLOR1);
  display_5.fillCircle(60, display_1.height()/2, 30, COLOR1);
  display_6.fillCircle(60, display_1.height()/2, 30, COLOR1);

  display_1.display();
  delay(DELAY);
  display_2.display();
  delay(DELAY);
  display_3.display();
  delay(DELAY);
  display_4.display();
  delay(DELAY);
  display_5.display();
  delay(DELAY);
  display_6.display();
  delay(DELAY);

  display_1.clearBuffer();
  display_2.clearBuffer();
  display_3.clearBuffer();
  display_4.clearBuffer();
  display_5.clearBuffer();
  display_6.clearBuffer();

  display_1.fillCircle(display_1.width()-61, display_1.height()/2, 30, COLOR1);
  display_2.fillCircle(display_2.width()-61, display_1.height()/2, 30, COLOR1);
  display_3.fillCircle(display_3.width()-61, display_1.height()/2, 30, COLOR1);
  display_4.fillCircle(display_4.width()-61, display_1.height()/2, 30, COLOR1);
  display_5.fillCircle(display_5.width()-61, display_1.height()/2, 30, COLOR1);
  display_6.fillCircle(display_6.width()-61, display_1.height()/2, 30, COLOR1);

  display_1.display();
  delay(DELAY);
  display_2.display();
  delay(DELAY);
  display_3.display();
  delay(DELAY);
  display_4.display();
  delay(DELAY);
  display_5.display();
  delay(DELAY);
  display_6.display();
  delay(DELAY);
//Circle-moving stops



//Clearing
  display_1.clearBuffer();
  display_2.clearBuffer();
  display_3.clearBuffer();
  display_4.clearBuffer();
  display_5.clearBuffer();
  display_6.clearBuffer();

  display_1.fillScreen(COLOR2);
  display_2.fillScreen(COLOR2);
  display_3.fillScreen(COLOR2);
  display_4.fillScreen(COLOR2);
  display_5.fillScreen(COLOR2);
  display_6.fillScreen(COLOR2);
  
  display_1.display();
  delay(DELAY);
  display_2.display();
  delay(DELAY);
  display_3.display();
  delay(DELAY);
  display_4.display();
  delay(DELAY);
  display_5.display();
  delay(DELAY);
  display_6.display();
  delay(DELAY);
}

//void testdrawtext(ThinkInk_290_Mono_M06 display, const char *text, uint16_t color) {
//  display.setCursor(display.width()/2-60, display.height()/2-10);
//  display.setTextColor(color);
//  display.setTextWrap(true);
//  display.setTextSize(3);
//  display.print(text);
//}
