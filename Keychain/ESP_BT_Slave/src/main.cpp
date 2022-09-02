#include <Arduino.h>
#include "BluetoothSerial.h"
/*
master(header up)   : 7C:9E:BD:47:A9:26
slave(header down)  : 24:6F:28:B0:4D:5A
*/

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define Indicator 2
#define pinBat    25
#define bat_full  32
#define bat_low   33
#define pinBuzz   14

BluetoothSerial SlaveBT;
uint8_t address[6]    = {0x7C, 0x9E, 0xBD, 0x47, 0xA9, 0x26};
float Vbat=0;

void setup() {
  Serial.begin(115200);
  pinMode(Indicator,OUTPUT);
  pinMode(pinBuzz,OUTPUT);
  pinMode(bat_full,OUTPUT);
  pinMode(bat_low,OUTPUT);
  pinMode(pinBat,INPUT);
  SlaveBT.begin("Slave Key");
  Serial.println("Slave Started!!!");
  // SlaveBT.connect(address);
  //----------Start up tone----------//
  digitalWrite(Indicator,HIGH);
  delay(2000);
  digitalWrite(Indicator,LOW);
  delay(200);
  digitalWrite(Indicator,HIGH);
  delay(200);
  digitalWrite(Indicator,LOW);
  delay(200);
  digitalWrite(Indicator,HIGH);
  delay(200);
  digitalWrite(Indicator,LOW);
}

void batt(){
  Vbat=analogRead(pinBat);
  if(Vbat>1600){//40 % batt
    digitalWrite(bat_full,HIGH);
    digitalWrite(bat_low,LOW);
  }else{
    digitalWrite(bat_full,LOW);
    digitalWrite(bat_low,HIGH);
  }
}

void loop() {
  while (SlaveBT.connected(1000))
  {
    digitalWrite(Indicator,HIGH);
    delay(100);
    digitalWrite(Indicator,LOW);
    delay(2000);
    batt();
  }
  
  digitalWrite(Indicator,HIGH);
  digitalWrite(pinBuzz,HIGH);
  delay(200);
  digitalWrite(Indicator,LOW);
  digitalWrite(pinBuzz,LOW);
  delay(200);
  batt();
  
}