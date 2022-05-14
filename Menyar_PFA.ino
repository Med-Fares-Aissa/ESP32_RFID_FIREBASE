
#include <WiFi.h>
#include <FirebaseESP32.h>


//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

/* 1. Define the WiFi credentials */
#define WIFI_SSID "globalnet"
#define WIFI_PASSWORD "6982669826a"

/* 2. Define the API Key */
#define API_KEY "2pLBFdYCoabbxu3NHpVeYzIIn6DD5TiG0q22qNQT"

/* 3. Define the RTDB URL */
#define DATABASE_URL "https://rfid-8a126-default-rtdb.europe-west1.firebasedatabase.app/RFIDTEST" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "menyaraazizi@gmail.com"
#define USER_PASSWORD "123456789Az."

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

int count = 0;

void setup()
{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);

  //Or use legacy authenticate method
  //Firebase.begin(DATABASE_URL, "<database secret>");
}

void loop()
{
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

    Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, "/test/int", count) ? "ok" : fbdo.errorReason().c_str());

    Serial.printf("Get int... %s\n", Firebase.getInt(fbdo, "/test/int") ? String(fbdo.intData()).c_str() : fbdo.errorReason().c_str());

    FirebaseJson json;
    json.add("value", count);

    Serial.printf("Push json... %s\n", Firebase.pushJSON(fbdo, "/test/push", json) ? "ok" : fbdo.errorReason().c_str());

    json.set("value", count + 100);
    Serial.printf("Update json... %s\n\n", Firebase.updateNode(fbdo, String("/test/push/" + fbdo.pushName()), json) ? "ok" : fbdo.errorReason().c_str());

    count++;
  }
}
