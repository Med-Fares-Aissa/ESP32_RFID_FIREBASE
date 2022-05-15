//Libraries
#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <ArduinoJson.h>
#include <time.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define FIREBASE_HOST "rfid-8a126-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_AUTH "2pLBFdYCoabbxu3NHpVeYzIIn6DD5TiG0q22qNQT"
#define WIFI_SSID "globalnet"
#define WIFI_PASSWORD "6982669826a"

//Constants
#define SS_PIN 4
#define RST_PIN 0
//Parameters
const int ipaddress[4] = {103, 97, 67, 25};
//Variables
byte nuidPICC[4] = {0, 0, 0, 0};
String UID_CARD ;

String Fares_Card = "24224817711" ;
String Menyar_Card = "247121202181" ;
MFRC522::MIFARE_Key key;
MFRC522 rfid = MFRC522(SS_PIN, RST_PIN);
void setup() {

  Serial.begin(115200);
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connection WIFI");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println("connecté");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.println(F("Initialize System"));
  //init rfid D8,D5,D6,D7
  SPI.begin();
  rfid.PCD_Init();
  Serial.print(F("Reader :"));
  rfid.PCD_DumpVersionToSerial();
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  // See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv for Timezone codes for your region
  setenv("TZ", "CET-1", 1);
}
int i = 0 ;
void loop() {
  ////Read RFID card
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  // Look for new 1 cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  // Verify if the NUID has been readed
  if (  !rfid.PICC_ReadCardSerial())
    return;
  readRFID();
  UID_CARD = (String)nuidPICC[0] + (String)nuidPICC[1] + (String)nuidPICC[2] + (String)nuidPICC[3];

  int Fares_Aissa_Status = Firebase.getInt("/Fares_Aissa_Status") ;
  int Menyar_Azizi_Status = Firebase.getInt("/Menyar_Azizi_Status") ;

  Serial.print("UID_CARD : ");
  Serial.println(UID_CARD);

  if ( Menyar_Azizi_Status == 1) {
    if ( UID_CARD == Menyar_Card) {
      Firebase.set("/Menyar_Azizi/LastEntryTime", get_time());
      String MSG = "You Are Welcome" ;
      Firebase.set("/Menyar_Azizi/Status", MSG);
    }
    else {
      String MSG = "Please insert Your Card" ;
      Firebase.set("/Menyar_Azizi/Status", MSG);
    }
  }
  else if ( Fares_Aissa_Status == 1) {
    if ( UID_CARD == Fares_Card) {
      Firebase.set("/Fares_Aissa/LastEntryTime", get_time());
      String MSG = "You Are Welcome" ;
      Firebase.set("/Fares_Aissa/Status", MSG);
    }
    else {
      String MSG = "Please insert Your Card" ;
      Firebase.set("/Fares_Aissa/Status", MSG);
    }
  }
      else {
      String MSG = "Please insert Your Card" ;
      Firebase.set("/Fares_Aissa/Status", MSG);
      Firebase.set("/Menyar_Azizi/Status", MSG);
    }

}


/****************************************************************************/


void readRFID(void ) { /* function readRFID */

  // Store NUID into nuidPICC array
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }
  Serial.print(F("RFID In dec: "));
  printDec(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();
  // Halt PICC
  rfid.PICC_HaltA();
  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}
/**
   Helper routine to dump a byte array as hex values to Serial.
*/
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
/**
   Helper routine to dump a byte array as dec values to Serial.
*/
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}

String get_time() {
  time_t now;
  time(&now);
  char time_output[30];
  // See http://www.cplusplus.com/reference/ctime/strftime/ for strftime functions
  strftime(time_output, 30, "%a  %d-%m-%y %T", localtime(&now));
  return String(time_output); // returns Sat 20-Apr-19 12:31:45
}
