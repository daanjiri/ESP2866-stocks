#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include <iostream>

// Fingerprint for demo URL, expires on June 2, 2021, needs to be updated well before this date
const uint8_t fingerprint[20] = { 0x40, 0xaf, 0x00, 0x6b, 0xec, 0x90, 0x22, 0x41, 0x8e, 0xa3, 0xad, 0xfa, 0x1a, 0xe8, 0x25, 0x41, 0x1d, 0x1a, 0x54, 0xb3 };

ESP8266WiFiMulti WiFiMulti;
int relay = 16;

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  pinMode(LED_BUILTIN, OUTPUT); 

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  //! WiFiMulti.addAP("LA COSMICA", "241188MM");
  WiFiMulti.addAP("1802", "gj180692");
}

void loop() {
 
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

    // client.setFingerprint(fingerprint);
    // Or, if you happy to ignore the SSL certificate, then use the following line instead:
    client->setInsecure();

    HTTPClient https;

    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, "https://uj5jycqnud.execute-api.us-east-1.amazonaws.com/dev/amzn")) {  // HTTPS

      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          // Serial.print("entra--");
          String payload = https.getString();
          DynamicJsonDocument doc(1024);
          deserializeJson(doc, payload);

          const String price = doc["price"];
          const String movement = doc["movement"];
          const int sign = doc["sign"];

          digitalWrite(LED_BUILTIN, sign);
          Serial.println(sign);
          
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }

  Serial.println("Wait 10s before next round...");
  delay(10000);
}

//! int relay = 5;

// void setup() {
//   // Configuración
//   pinMode(relay, OUTPUT); // Configurar relay como salida o OUTPUT
//   Serial.begin(115200); // Abrir el puerto serie a la velocidad de 9600bps para trasnmicion de datos.
// }

// void loop() {
//   // Código principal donde ocurren en loop
//   digitalWrite(relay, HIGH); // envia señal alta al relay
//   Serial.println("Relay accionado");
//   delay(1000);           // 1 segundo
  
//   digitalWrite(relay, LOW);  // envia señal baja al relay
//   Serial.println("Relay no accionado");
//   delay(1000);           // 1 segundo

// }