/***************************************************
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <ArduinoBLE.h>
#include "Adafruit_ThinkInk.h"
#include "whiteArray.h"
//#include "titleArray.h"

#define DELAY 200

#define SRAM_CS     -1
#define EPD_RESET   6
#define EPD_BUSY    7

#define EPD_CS_1      A3
#define EPD_DC_1      A2

#define EPD_CS_2      13
#define EPD_DC_2      14

#define EPD_CS_3      5
#define EPD_DC_3      4

#define EPD_CS_4      3
#define EPD_DC_4      2

#define EPD_CS_5      1
#define EPD_DC_5      0

#define EPD_CS_6      A1
#define EPD_DC_6      A0

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

BLEService einkService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service
// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);


const int WIDTH = 128;
const int HEIGHT = 296;

int COLOR1 = EPD_BLACK;
int COLOR2 = EPD_WHITE;

unsigned char image_bits_headspace1 [WIDTH*HEIGHT];
unsigned char image_bits_headspace2 [WIDTH*HEIGHT];
unsigned char image_bits_headspace3 [WIDTH*HEIGHT];
unsigned char image_bits_headspace4 [WIDTH*HEIGHT];
unsigned char image_bits_headspace5 [WIDTH*HEIGHT];
unsigned char image_bits_headspace6 [WIDTH*HEIGHT];

void setup() {
  bootM4();
  Serial.begin(9600);
  while (!Serial);
  
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }
  
  // set advertised local name and service UUID:
  BLE.setLocalName("e-ink display");
  BLE.setAdvertisedService(einkService);
  
  // add the characteristic to the service
  einkService.addCharacteristic(switchCharacteristic);
  // add service
  BLE.addService(einkService);

  // set the initial value for the characeristic:
  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();
  
  Serial.println("BLE Setup Ready");
  
  
  display_1.begin();
  display_2.begin();
  display_3.begin();
  display_4.begin();
  display_5.begin();
  display_6.begin();

  display_1.setRotation(3);
  display_2.setRotation(3);
  display_3.setRotation(3);
  display_4.setRotation(3);
  display_5.setRotation(3);
  display_6.setRotation(3);

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

  Serial.println("Display Setup Ready");

  for(int i = 0; i < sizeof(epd_bitmap_headspace1)*8; i++){
    image_bits_headspace1[i] = ((0b10000000 >> (i % 8)) & (epd_bitmap_headspace1[i/8])) >> (7 - i % 8);
  }
  for(int i = 0; i < sizeof(epd_bitmap_headspace2)*8; i++){
    image_bits_headspace2[i] = ((0b10000000 >> (i % 8)) & (epd_bitmap_headspace2[i/8])) >> (7 - i % 8);
  }
  for(int i = 0; i < sizeof(epd_bitmap_headspace3)*8; i++){
    image_bits_headspace3[i] = ((0b10000000 >> (i % 8)) & (epd_bitmap_headspace3[i/8])) >> (7 - i % 8);
  }
  for(int i = 0; i < sizeof(epd_bitmap_headspace4)*8; i++){
    image_bits_headspace4[i] = ((0b10000000 >> (i % 8)) & (epd_bitmap_headspace4[i/8])) >> (7 - i % 8);
  }
  for(int i = 0; i < sizeof(epd_bitmap_headspace5)*8; i++){
    image_bits_headspace5[i] = ((0b10000000 >> (i % 8)) & (epd_bitmap_headspace5[i/8])) >> (7 - i % 8);
  }
  for(int i = 0; i < sizeof(epd_bitmap_headspace6)*8; i++){
    image_bits_headspace6[i] = ((0b10000000 >> (i % 8)) & (epd_bitmap_headspace6[i/8])) >> (7 - i % 8);
  }

  Serial.println("Image Loading Ready");
}

void loop() {
  display_1.clearBuffer();
  display_2.clearBuffer();
  display_3.clearBuffer();
  display_4.clearBuffer();
  display_5.clearBuffer();
  display_6.clearBuffer();
  
//        Serial.println("Title");
//        display_1.fillRect(0, 0, WIDTH, HEIGHT, COLOR1);
//        display_2.fillRect(0, 0, WIDTH, HEIGHT, COLOR1);
//        display_3.fillRect(0, 0, WIDTH, HEIGHT, COLOR1);
//        display_4.fillRect(0, 0, WIDTH, HEIGHT, COLOR1);
//        display_5.fillRect(0, 0, WIDTH, HEIGHT, COLOR1);
//        display_6.fillRect(0, 0, WIDTH, HEIGHT, COLOR1);
//        
//        for(int i = 0; i < WIDTH*HEIGHT; i++){
//          int x = i % WIDTH;
//          int y = i / WIDTH;
//          if(epd_bitmap_1[i] == 1){
//            display_1.writePixel(x, y, COLOR2);
//          }
//        }
//        for(int i = 0; i < WIDTH*HEIGHT; i++){
//          int x = i % WIDTH;
//          int y = i / WIDTH;
//          if(epd_bitmap_2[i] == 1){
//            display_2.writePixel(x, y, COLOR2);
//          }
//        }
//        for(int i = 0; i < WIDTH*HEIGHT; i++){
//          int x = i % WIDTH;
//          int y = i / WIDTH;
//          if(epd_bitmap_3[i] == 1){
//            display_3.writePixel(x, y, COLOR2);
//          }
//        }
//          for(int i = 0; i < WIDTH*HEIGHT; i++){
//          int x = i % WIDTH;
//          int y = i / WIDTH;
//          if(epd_bitmap_4[i] == 1){
//            display_4.writePixel(x, y, COLOR2);
//          }
//        }
//          for(int i = 0; i < WIDTH*HEIGHT; i++){
//          int x = i % WIDTH;
//          int y = i / WIDTH;
//          if(epd_bitmap_5[i] == 1){
//            display_5.writePixel(x, y, COLOR2);
//          }
//        }
//          for(int i = 0; i < WIDTH*HEIGHT; i++){
//          int x = i % WIDTH;
//          int y = i / WIDTH;
//          if(epd_bitmap_6[i] == 1){
//            display_6.writePixel(x, y, COLOR2);
//          }
//        }
      
  
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();
  

  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

  // while the central is still connected to peripheral:
 
    // if the remote device wrote to the characteristic,
    // use the value to control the LED:
    if (switchCharacteristic.written()) {
      if (switchCharacteristic.value()==0) {   // any value other than 0
        Serial.println("Input A");
        display_1.fillRect(0, 0, WIDTH, HEIGHT, COLOR1);
        display_2.fillRect(0, 0, WIDTH, HEIGHT, COLOR1);
        display_3.fillRect(0, 0, WIDTH, HEIGHT, COLOR1);
        display_4.fillRect(0, 0, WIDTH, HEIGHT, COLOR1);
        display_5.fillRect(0, 0, WIDTH, HEIGHT, COLOR1);
        display_6.fillRect(0, 0, WIDTH, HEIGHT, COLOR1);
        
        for(int i = 0; i < WIDTH*HEIGHT; i++){
          int x = i % WIDTH;
          int y = i / WIDTH;
          if(image_bits_headspace1[i] == 1){
            display_1.writePixel(x, y, COLOR2);
          }
        }
        for(int i = 0; i < WIDTH*HEIGHT; i++){
          int x = i % WIDTH;
          int y = i / WIDTH;
          if(image_bits_headspace2[i] == 1){
            display_2.writePixel(x, y, COLOR2);
          }
        }
        for(int i = 0; i < WIDTH*HEIGHT; i++){
          int x = i % WIDTH;
          int y = i / WIDTH;
          if(image_bits_headspace3[i] == 1){
            display_3.writePixel(x, y, COLOR2);
          }
        }
          for(int i = 0; i < WIDTH*HEIGHT; i++){
          int x = i % WIDTH;
          int y = i / WIDTH;
          if(image_bits_headspace4[i] == 1){
            display_4.writePixel(x, y, COLOR2);
          }
        }
          for(int i = 0; i < WIDTH*HEIGHT; i++){
          int x = i % WIDTH;
          int y = i / WIDTH;
          if(image_bits_headspace5[i] == 1){
            display_5.writePixel(x, y, COLOR2);
          }
        }
          for(int i = 0; i < WIDTH*HEIGHT; i++){
          int x = i % WIDTH;
          int y = i / WIDTH;
          if(image_bits_headspace6[i] == 1){
            display_6.writePixel(x, y, COLOR2);
          }
        }
      } else if (switchCharacteristic.value()==1) {                              // a 0 value
        Serial.println("Input B");
        display_1.fillRect(0, 0, WIDTH, HEIGHT, COLOR2);
        display_2.fillRect(0, 0, WIDTH, HEIGHT, COLOR2);
        display_3.fillRect(0, 0, WIDTH, HEIGHT, COLOR2);
        display_4.fillRect(0, 0, WIDTH, HEIGHT, COLOR2);
        display_5.fillRect(0, 0, WIDTH, HEIGHT, COLOR2);
        display_6.fillRect(0, 0, WIDTH, HEIGHT, COLOR2);
        
        for(int i = 0; i < WIDTH*HEIGHT; i++){
          int x = i % WIDTH;
          int y = i / WIDTH;
          if(image_bits_headspace1[i] == 1){
            display_1.writePixel(x, y, COLOR1);
          }
        }
        for(int i = 0; i < WIDTH*HEIGHT; i++){
          int x = i % WIDTH;
          int y = i / WIDTH;
          if(image_bits_headspace2[i] == 1){
            display_2.writePixel(x, y, COLOR1);
          }
        }
        for(int i = 0; i < WIDTH*HEIGHT; i++){
          int x = i % WIDTH;
          int y = i / WIDTH;
          if(image_bits_headspace3[i] == 1){
            display_3.writePixel(x, y, COLOR1);
          }
        }
          for(int i = 0; i < WIDTH*HEIGHT; i++){
          int x = i % WIDTH;
          int y = i / WIDTH;
          if(image_bits_headspace4[i] == 1){
            display_4.writePixel(x, y, COLOR1);
          }
        }
          for(int i = 0; i < WIDTH*HEIGHT; i++){
          int x = i % WIDTH;
          int y = i / WIDTH;
          if(image_bits_headspace5[i] == 1){
            display_5.writePixel(x, y, COLOR1);
          }
        }
          for(int i = 0; i < WIDTH*HEIGHT; i++){
          int x = i % WIDTH;
          int y = i / WIDTH;
          if(image_bits_headspace6[i] == 1){
            display_6.writePixel(x, y, COLOR1);
          }
        }
      }
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
    
      
  } else {
    Serial.println("Connection lost");
  }
  
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
