#include <SPI.h>

#define DO 11 //mosi
#define DI 12 // miso
#define CLK 13 //sck
#define EEPROM_CS 10

void setup() {
  pinMode(EEPROM_CS, OUTPUT);
  pinMode(DO, OUTPUT);
  pinMode(DI, INPUT);
  pinMode(CLK, OUTPUT);
  digitalWrite(EEPROM_CS, HIGH);
  SPI.begin();
  SPI.beginTransaction(SPISettings(1500000,MSBFIRST,SPI_MODE0));
  Serial.begin(9600);

  uint16_t address_M = 0x0000; //EEPROM에 저장할 주소 24bit
  uint8_t address_L = 0x00;
  uint8_t send_data = 0x01; //8bit
  byte dataout = 0x00; //1byte
  byte a,b;
  byte EEPROM_READ = 0x03;
  byte EEPROM_WRITE = 0x02;
  byte EEPROM_WREN = 0x06;
  byte EEPROM_WRDS = 0x04;
  byte EEPROM_RDSR = 0x05;
  
  digitalWrite(EEPROM_CS,LOW);
  SPI.transfer(EEPROM_RDSR);
  a=SPI.transfer(dataout);
  delay(10);
  digitalWrite(EEPROM_CS, HIGH);

  Serial.print("initial read status:  ");
  printByte(a);

  
  //enable writing on EEPROM
  digitalWrite(EEPROM_CS,LOW);
  SPI.transfer(EEPROM_WREN); //send command 1byte
  delay(10);
  digitalWrite(EEPROM_CS, HIGH);

  //read status register WEL=1인지 확인
  digitalWrite(EEPROM_CS,LOW);
  SPI.transfer(EEPROM_RDSR);
  a=SPI.transfer(dataout);
  delay(10);
  digitalWrite(EEPROM_CS, HIGH);

  Serial.print("read status:  ");
  printByte(a);

  
  //write on EEPROM
  digitalWrite(EEPROM_CS, LOW);
  SPI.transfer(EEPROM_WRITE); //1byte
  SPI.transfer(address_M); // 2byte
  SPI.transfer(address_L); //1byte
  SPI.transfer(send_data); //1byte
  delay(2);
  digitalWrite(EEPROM_CS, HIGH);

  delay(10);
  //disable writing
  digitalWrite(EEPROM_CS, LOW);
  SPI.transfer(EEPROM_WRDS);
  digitalWrite(EEPROM_CS, HIGH);
  Serial.print("I wrote .... ");
  Serial.println(send_data);

  digitalWrite(EEPROM_CS,LOW);
  SPI.transfer(EEPROM_RDSR);
  a=SPI.transfer(dataout);
  delay(10);
  digitalWrite(EEPROM_CS, HIGH);

  Serial.print("disable writing:  ");
  printByte(a);

  //read from EEPROM
  digitalWrite(EEPROM_CS, LOW);
  SPI.transfer(EEPROM_READ); //1byte
  SPI.transfer(address_M); //2byte
  SPI.transfer(address_L); //1byte
  b=SPI.transfer(dataout);
  digitalWrite(EEPROM_CS, HIGH);
  SPI.endTransaction();
  Serial.print("I read .... ");
  printByte(b);
  Serial.println("done");
} 

void loop() {
  // put your main code here, to run repeatedly:
}
void printByte_16(uint16_t data){ // print with all preceding 0's
  for (int i = 15; i >= 0 ; i--) {
    if (bitRead(data, i) == 1) {
      Serial.print(1);
    } else {
      Serial.print(0);
    }
  }
  Serial.print("\n");
}
void printByte(byte data){ // print with all preceding 0's
  for (int i = 7; i >= 0 ; i--) {
    if (bitRead(data, i) == 1) {
      Serial.print(1);
    } else {
      Serial.print(0);
    }
  }
  Serial.print("\n");
}
