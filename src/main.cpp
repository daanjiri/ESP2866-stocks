// #include <Arduino.h>
// #include <ESP8266WiFi.h>
// #include <ESP8266WiFiMulti.h>
// #include <ESP8266HTTPClient.h>
// #include <WiFiClientSecureBearSSL.h>
// #include <ArduinoJson.h>
// #include <iostream>
// #include <Adafruit_GFX.h>	
// #include <Adafruit_SSD1306.h>
// #include <Wire.h>

// // Fingerprint for demo URL, expires on June 2, 2021, needs to be updated well before this date
// const uint8_t fingerprint[20] = { 0x40, 0xaf, 0x00, 0x6b, 0xec, 0x90, 0x22, 0x41, 0x8e, 0xa3, 0xad, 0xfa, 0x1a, 0xe8, 0x25, 0x41, 0x1d, 0x1a, 0x54, 0xb3 };

// ESP8266WiFiMulti WiFiMulti;

// const int RELAY = 2 ;
// const int SCREEN_WIDTH = 128;
// const int SCREEN_HEIGHT = 128;
// const int OLED_RESET = -1;

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// void setup() {

//   Serial.begin(115200);
//   // Serial.setDebugOutput(true);
//   pinMode(RELAY, OUTPUT); 

//   for (uint8_t t = 4; t > 0; t--) {
//     Serial.printf("[SETUP] WAIT %d...\n", t);
//     Serial.flush();
//     delay(1000);
//   }

//   WiFi.mode(WIFI_STA);
//   //! WiFiMulti.addAP("LA COSMICA", "241188MM");
//   // WiFiMulti.addAP("1802", "gj180692");
//   //casa
//   WiFiMulti.addAP("GEMELOS92", "Gj180692");

//   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64
//     Serial.println(F("SSD1306 allocation failed"));
//     for(;;);
//   }
//   display.clearDisplay();	
// }

// void loop() {

//   display.clearDisplay();	
//   display.setTextColor(WHITE);
//   display.setTextSize(1);
//   display.setCursor(0,20);
//   display.println("Hola mundo"); 
//   display.print(millis() / 1000);
//   display.display();
 
//   // wait for WiFi connection
//   if ((WiFiMulti.run() == WL_CONNECTED)) {

//     std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

//     // client.setFingerprint(fingerprint);
//     // Or, if you happy to ignore the SSL certificate, then use the following line instead:
//     client->setInsecure();

//     HTTPClient https;

//     Serial.print("[HTTPS] begin...\n");
//     if (https.begin(*client, "https://uj5jycqnud.execute-api.us-east-1.amazonaws.com/dev/amzn")) {  // HTTPS

//       Serial.print("[HTTPS] GET...\n");
//       // start connection and send HTTP header
//       int httpCode = https.GET();

//       // httpCode will be negative on error
//       if (httpCode > 0) {
//         // HTTP header has been send and Server response header has been handled
//         Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

//         // file found at server
//         if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
//           // Serial.print("entra--");
//           String payload = https.getString();
//           DynamicJsonDocument doc(1024);
//           deserializeJson(doc, payload);

//           const String price = doc["price"];
//           const String movement = doc["movement"];
//           const int sign = doc["sign"];

//           Serial.println(payload);
//           digitalWrite(RELAY, sign);
//           Serial.println(sign);

          
          
          
//         }
//       } else {
//         Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
//       }

//       https.end();
//     } else {
//       Serial.printf("[HTTPS] Unable to connect\n");
//     }
//   }

//   Serial.println("Wait 10s before next round...");
//   delay(10000);
// }

// ! int relay = 5;

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
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <iostream>
#include <ArduinoJson.h>
#include <String.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels'

const int RELAY = 14 ;
String parameter = "amzn";
String url = "https://uj5jycqnud.execute-api.us-east-1.amazonaws.com/dev/"+ parameter;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const uint8_t fingerprint[20] = { 0x40, 0xaf, 0x00, 0x6b, 0xec, 0x90, 0x22, 0x41, 0x8e, 0xa3, 0xad, 0xfa, 0x1a, 0xe8, 0x25, 0x41, 0x1d, 0x1a, 0x54, 0xb3 };
ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  Wire.begin();					// inicializa bus I2C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);


  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("GEMELOS92", "Gj180692");

  pinMode(RELAY, OUTPUT); 
}

void loop() {
  delay(10000);
  Serial.print("[LOOP] init");
 
  
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

    // client.setFingerprint(fingerprint);
    // Or, if you happy to ignore the SSL certificate, then use the following line instead:
    client->setInsecure();

    HTTPClient https;

    Serial.print("[HTTPS] begin...\n");

    if (https.begin(*client, "https://uj5jycqnud.execute-api.us-east-1.amazonaws.com/dev/amzn")) {
     
      int httpCode = https.GET();
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {

        String payload = https.getString();
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);

        const String price = doc["price"];
        const String movement = doc["movement"];
        const int sign = doc["sign"];

        String stock = parameter;
        stock.toUpperCase();

        display.clearDisplay();
        Serial.print("[LOOP] screen");
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        // Display static text
        display.print(stock);
        display.setCursor (10, 30);		// ubica cursor en coordenas 10,30
        display.setTextSize(2);			// establece tamano de texto en 2
        display.print(movement);		// escribe valor de millis() dividido por 1000
        display.display(); 

        digitalWrite(RELAY, sign);
      }

    

    }
    https.end();
  }
}