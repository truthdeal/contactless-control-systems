#include<MFRC522.h>
#include<SPI.h>
#include<Servo.h>

int RST_PIN = 9;
int SS_PIN = 10;
int ServoPin = 8;

Servo motor;
MFRC522 rfid(SS_PIN , RST_PIN) ;

byte ID[4] = {249,22,226,93} ;

void setup() {

  motor.attach( ServoPin) ;
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
 motor.write(90);
 delay(5);

pinMode(3, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
}

void loop() {

if (! rfid.PICC_IsNewCardPresent())
  return ;

if (! rfid.PICC_ReadCardSerial())
  return ;

if (rfid.uid.uidByte[0] == ID[0] && 
    rfid.uid.uidByte[1] == ID[1] && 
    rfid.uid.uidByte[2] == ID[2] && 
    rfid.uid.uidByte[3] == ID[3] ) {

      Serial.println("Acildi");

     rfidKodu();
     motor.write(0);
     
     analogWrite(3, 0);
     analogWrite(6, 255);
     analogWrite(7, 0);
     
     delay(2500);
     motor.write(90);
     
    analogWrite(3, 0);
    analogWrite(6, 0);
    analogWrite(7, 0);
     delay(1500); }

     else { 

      Serial.println("Hatali kart!!") ;
      analogWrite(3, 255);
     analogWrite(6, 0);
     analogWrite(7, 0);
     rfidKodu();  
     }
      

  
}

void rfidKodu () {
  Serial.print("Kart IDsi şu şekildedir: ") ;
  for (int say=0 ; say <4 ; say++ ) {
  
  Serial.print(rfid.uid.uidByte[say]);
  Serial.print(" ");
  
  }
    Serial.println(" ");

  
  }
