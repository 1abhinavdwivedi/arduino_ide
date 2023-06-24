#include <MFRC522.h>
#include <Servo.h>

// RFID reader configuration
#define RST_PIN     16   // Reset pin for MFRC522
#define SS_PIN      15   // Slave Select pin for MFRC522

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

// Servo motor configuration
#define SERVO_PIN_1   3   // GPIO pin for servo motor 1
#define SERVO_PIN_2   1   // GPIO pin for servo motor 2

Servo motor;   // Create Servo instance

// Authorized card UID (replace with your card's UID)
byte authorizedCardUID[] = {0xDE, 0xAD, 0xBE, 0xEF};

void setup() {
  Serial.begin(115200);

  // Initialize RFID reader
  SPI.begin();
  mfrc522.PCD_Init();

  // Attach servo motors to GPIO pins
  motor.attach(SERVO_PIN_1);
  motor.attach(SERVO_PIN_2);
  motor.write(0);  // Initialize motor positions to 0 degrees
}

void loop() {
  // Check for new RFID cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Compare card UID with authorized card UID
    if (memcmp(mfrc522.uid.uidByte, authorizedCardUID, mfrc522.uid.size) == 0) {
      Serial.println("Authorized card detected!");

      // Rotate the servo motors to activate them
      motor.write(90);  // Adjust the angle according to your requirements
      delay(2000);      // Keep the motors activated for 2 seconds

      // Power off the servo motors after 10 seconds
      delay(10000);
      motor.write(0);   // Adjust the angle according to your requirements
    } else {
      Serial.println("Unauthorized card detected!");
    }

    mfrc522.PICC_HaltA();   // Halt PICC to prepare for a new card
  }
}
