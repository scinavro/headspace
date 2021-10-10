/*
 * An example that uses the partial update function of the Adafruit eInk display.
 * Copyright 2021, Digame Systems. All rights reserved.
 * 
 * NOTE: Be sure to update your SPI bus pinouts in digameDisplay.h
 */

#include "digameDisplay.h"

#include <Wire.h>

//****************************************************************************************
// Device initialization                                   
//****************************************************************************************
void setup()
{
    String compileDate = F(__DATE__);
    String compileTime = F(__TIME__);
       
    Serial.begin(115200);   // Intialize terminal serial port
    delay(1000);

    Wire.begin();
   

    display.init(0);
    displaySplashScreen();
    delay(5000);
    displayCountScreen(0);
    showValue(0);

}

//************************************************************************
// Main Loop
//************************************************************************

double count = 0;
long int t1, t2;

void loop()
{ 
   t1=millis();
   count++;
   showValue(count);
   t2=millis();
   Serial.print("Update Time: ");
   Serial.println(t2-t1);
}
