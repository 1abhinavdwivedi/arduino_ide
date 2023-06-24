#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// ... Code for RFID module setup and configuration ...

// WiFi credentials
const char* ssid = "neo";      // Replace with your WiFi SSID
const char* password = "wireless519";  // Replace with your WiFi password

// Database connection parameters
IPAddress serverAddr(192, 168, 0, 10);  // Replace with your database server IP address
int serverPort = 3306;
char dbUser[] = "root";      // Replace with your database username
char dbPassword[] = "...";  // Replace with your database password
char dbName[] = "attendance_system";      // Replace with your database name

WiFiClient client;

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Connect to WiFi
  connectWiFi();

  // ... Other setup code for RFID module ...
}

void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected to WiFi. IP address: ");
  Serial.println(WiFi.localIP());
}

void insertDataToDatabase(String tagID) {
  // Establish connection to the database server
  MySQL_Connection conn((Client *)&client);
  if (conn.connect(serverAddr, serverPort, dbUser, dbPassword, dbName)) {
    Serial.println("Connected to database!");

    // Execute an SQL query to insert data
    MySQL_Cursor *cursor = new MySQL_Cursor(&conn);
    String query = "INSERT INTO attendance (tag_id, timestamp) VALUES ('" + tagID + "', NOW())";
    cursor->execute(query.c_str());
    delete cursor;

    // Close the connection
    conn.close();
  }
}

void loop() {
  // Read RFID tag
  bool tagRead = false;
  String tagID = "";  // Variable to store the RFID tag ID

  // ... Code for reading RFID tag ...
  // Set the values of tagRead and tagID variables based on the RFID reading

  if (tagRead) {
    // Insert the tag details into the database
    insertDataToDatabase(tagID);
  }
}
