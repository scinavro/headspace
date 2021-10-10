/* Functions for using the Adafruit 1.54" Monochrome eInk Display. 
 * 
 * See: https://www.adafruit.com/product/4196
 * 
 * I'm using an ESP32 WROOM DevKit V4.0 as my microcontroller.
 * 
 */
 
#ifndef __DIGAME_DISPLAY_H__
#define __DIGAME_DISPLAY_H__

// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0

/* Here we are making use of Jean-Marc Zingg's nifty GxEPD2 library.
 * https://github.com/ZinggJM/GxEPD2
 * His header files, used for display selection are included for reference. 
 */
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#define MAX_DISPLAY_BUFFER_SIZE 800
#define MAX_HEIGHT_3C(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))

// Our pinouts to the Adafruit display. Your values may differ!
//featherwing -> not working
#define SRAM_CS     -1
#define EPD_CS      12
#define EPD_DC      14
#define EPD_RESET   10
#define EPD_BUSY    11


//feather friend
//#define SRAM_CS     -1
//#define EPD_CS      7
//#define EPD_DC      13
//#define EPD_RESET   6
//#define EPD_BUSY    -1
/* You could edit the GxEPD2_display_selection.h header to pick the display you want and then include it, but I just
 * grabbed the constructor we need from GxEPD2_display_selection and copied here.
 */
//#include "GxEPD2_display_selection.h"
//GxEPD2_BW<GxEPD2_154, GxEPD2_154::HEIGHT> display(GxEPD2_154(/*C=5*/ EPD_CS, /*DC=*/ EPD_DC, /*RST=*/ EPD_RESET, /*BUSY=*/ EPD_BUSY)); // GDEH0154D67
//GxEPD2_3C<GxEPD2_290c, MAX_HEIGHT_3C(GxEPD2_290c)> display(GxEPD2_290c(/*CS=77*/ SS, /*DC=*/ EPD_DC, /*RST=*/ EPD_RESET, /*BUSY=*/ EPD_BUSY));
GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> display(GxEPD2_290(/*CS=D8*/ SS, /*DC=D3*/ EPD_DC, /*RST=D4*/ EPD_RESET, /*BUSY=D2*/ EPD_BUSY)); // GDEH029A1

//#define MAX_DISPLAY_BUFFER_SIZE 15000ul // ~15k is a good compromise
//#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
//GxEPD2_BW<GxEPD2_213_flex, MAX_HEIGHT(GxEPD2_213_flex)> display(GxEPD2_213_flex(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); // GDEW0213I5F
void initDisplay();
void displaySplash();
void displayInitializing();
void displayCount(double c);
void showValue(double v);


//******************************************************************************************
void initDisplay()
{
  display.setRotation(0);
  //display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds("Initializing...", 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print("Initializing...");
  }
  while (display.nextPage());
  //Serial.println("helloWorld done");

  
  return;
}

//******************************************************************************************
#if defined(ESP8266) || defined(ESP32)
#include <StreamString.h>
#define PrintString StreamString
#else
class PrintString : public Print, public String
{
  public:
    size_t write(uint8_t data) override
    {
      return concat(char(data));
    };
};
#endif


//******************************************************************************************
// Print a string on the display, centered, at a particular y value.
void centerPrint(String s, uint16_t y){
  int16_t tx, ty; 
  uint16_t tw, th;
  display.getTextBounds(s, 0, 0, &tx, &ty, &tw, &th);
  uint16_t utx = ((display.width() - tw) / 2) - tx;
  uint16_t uty = y;   //((display.height() - th) / 2) - ty;
  display.setCursor(utx, uty);
  display.print(s);
}

void displayCopyright(){
  display.setTextSize(1);
  centerPrint("Copyright 2021, Digame Systems.", 180);
  centerPrint("All rights reserved.", 190);    
}

//******************************************************************************************
void displaySplashScreen(){
  display.fillScreen(GxEPD_WHITE);   
  display.setTextColor(GxEPD_BLACK);      
  display.setTextSize(3);
  centerPrint("eInk Test", 10);  
  display.setTextSize(2);
  centerPrint("Adafruit 1.54\"", 60);
  centerPrint("Mono Display", 80);
  centerPrint("200x200 pix", 100);
  centerPrint("Partial", 120);
  centerPrint("Update", 140);
  display.setTextSize(1);
  displayCopyright(); 
  display.display(); 
  display.fillScreen(GxEPD_WHITE); 
}


//******************************************************************************************
void displayInitializingScreen(){ 
  display.setTextColor(GxEPD_BLACK);     
  display.setTextSize(3);
  centerPrint("INITIALIZE", 10);
  display.setTextSize(2);
  centerPrint("...", 60);
  centerPrint("Configuring", 80);
  centerPrint("System", 100);
  centerPrint("Components", 120);
  centerPrint("...", 140);
  displayCopyright();
  display.display(); 
  display.fillScreen(GxEPD_WHITE); 
}


//******************************************************************************************
void displayStatusScreen(String s){
  display.setTextColor(GxEPD_BLACK);      
  display.setTextSize(3);
  centerPrint("STATUS", 10);  
  display.setTextSize(2);
  display.setCursor(0, 60);
  display.print(s);
  display.setTextSize(1);
  displayCopyright();
  display.display(); 
  display.fillScreen(GxEPD_WHITE);  
}


//******************************************************************************************
void displayCountScreen(double v)
{
  int digits = 0;
  
  display.fillScreen(GxEPD_WHITE); 
  display.setTextColor(GxEPD_BLACK);  
  PrintString valueString;
  valueString.print(v, digits);
  display.setTextSize(3);
  centerPrint("COUNTS", 10);
  displayCopyright();  
  display.display();   
}


//******************************************************************************************
// Use the updatePartial function to show the value in the center of the screen without 
// a big refresh. - Faster and no flicker! 
void showValue(double v)
{
  int digits = 0;
  
  display.setTextSize(5);
  display.setTextColor(GxEPD_BLACK);
  
  PrintString valueString;
  valueString.print(v, digits);
  
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(valueString, 0, 0, &tbx, &tby, &tbw, &tbh);

  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;  //+ tbh / 2; // y is base line!

  // show what happens, if we use the bounding box for partial window
  uint16_t wx = (display.width() - tbw) / 2;
  uint16_t wy = (display.height()- tbh) / 2;  // / 2;
  
  display.setPartialWindow(wx, wy, tbw, tbh);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(valueString);
  }
  while (display.nextPage());
  
}

#endif //__DIGAME_DISPLAY_H__
