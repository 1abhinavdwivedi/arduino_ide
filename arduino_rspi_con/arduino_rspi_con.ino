#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

void setup() {
  Serial.begin(9600);   // Initialize serial communication
  SPI.begin();          // Initiate SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  Serial.println("Scan your RFID card or tag...");
}

void loop() {
  // Check for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Print UID (Unique Identifier) of the card
    Serial.print("Card UID: ");
    String cardUID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardUID += String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      cardUID += String(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println(cardUID);
    mfrc522.PICC_HaltA();   // Halt PICC (Proximity Integrated Circuit Card)
  }
}

