#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9   //RFID를 통한 입장로그 입력받기
#define SS_PIN 10
#define BUTTON_PIN 2 //물리적 버튼을 퇴장버튼으로 가장해서 퇴장 로그 받을 스위치 선언
MFRC522 mfrc522(SS_PIN,RST_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(BUTTON_PIN, INPUT_PULLUP); 

  Serial.println("wating Log in...");
  Serial.println();

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(BUTTON_PIN)==LOW){
    Serial.println("퇴장하였습니다.");
    delay(1000); //버튼 입력시 퇴장 로그 출력
  }

  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.println("Card UID :");
    for (byte i =0; i < mfrc522.uid.size; i++){
    Serial.println(mfrc522.uid.uidByte[i] < 0x10 ? "0":" ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
  
  Serial.println();

  mfrc522.PICC_HaltA();
  }
}
