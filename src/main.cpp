// #include <Arduino.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include <ESP8266WiFi.h>
// #include <ESP8266WiFiMulti.h>
// #include <ESP8266HTTPClient.h>
// #include <WiFiClientSecureBearSSL.h>
// #include <iostream>
// #include <ArduinoJson.h>
// #include <String.h>

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels'

// const int RELAY = 14 ;
// String parameter = "amzn";
// String url = "https://uj5jycqnud.execute-api.us-east-1.amazonaws.com/dev/"+ parameter;

// // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// const uint8_t fingerprint[20] = { 0x40, 0xaf, 0x00, 0x6b, 0xec, 0x90, 0x22, 0x41, 0x8e, 0xa3, 0xad, 0xfa, 0x1a, 0xe8, 0x25, 0x41, 0x1d, 0x1a, 0x54, 0xb3 };
// ESP8266WiFiMulti WiFiMulti;

// void setup() {
//   Serial.begin(115200);
//   Wire.begin();					// inicializa bus I2C
//   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);


//   for (uint8_t t = 4; t > 0; t--) {
//     Serial.printf("[SETUP] WAIT %d...\n", t);
//     Serial.flush();
//     delay(1000);
//   }

//   WiFi.mode(WIFI_STA);
//   WiFiMulti.addAP("GEMELOS92", "Gj180692");
//   // WiFiMulti.addAP("1802", "gj180692");


//   pinMode(RELAY, OUTPUT); 
//   pinMode(LED_BUILTIN, OUTPUT); 
// }

// void loop() {
//   delay(10000);
//   Serial.print("[LOOP] init");
 
  
//   if ((WiFiMulti.run() == WL_CONNECTED)) {

//     std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

//     // client.setFingerprint(fingerprint);
//     // Or, if you happy to ignore the SSL certificate, then use the following line instead:
//     client->setInsecure();

//     HTTPClient https;

//     Serial.print("[HTTPS] begin...\n");

//     if (https.begin(*client, "https://uj5jycqnud.execute-api.us-east-1.amazonaws.com/dev/amzn")) {
     
//       int httpCode = https.GET();
//       Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

//       if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {

//         String payload = https.getString();
//         DynamicJsonDocument doc(1024);
//         deserializeJson(doc, payload);

//         const String price = doc["price"];
//         const String movement = doc["movement"];
//         // const int sign = doc["sign"];
//         // String mySign = String(sign);
//         String mySign;
//         int sign;

//         const double mov = movement.toDouble();
//         String movementDisplay;

//         if (mov > 0)
//         {
//           movementDisplay = '+' + movement;
//           mySign = '1';
//           sign = 1;
//         }
//         else
//         {
//           movementDisplay = movement;
//           mySign = '0';
//           sign = 0;
//         }

//         String stock = parameter;
//         stock.toUpperCase();

//         Serial.println(payload);
//         Serial.println(mySign);

//         display.clearDisplay();
//         Serial.print("[LOOP] screen");
//         display.setTextSize(2);
//         display.setTextColor(WHITE);
//         display.setCursor(0, 0);
//         // Display static text
//         display.print(stock);
//         display.setCursor (10, 30);		// ubica cursor en coordenas 10,30
//         display.setTextSize(2);			// establece tamano de texto en 2
//         display.print(price);		// escribe valor de millis() dividido por 1000
       
//         display.setCursor (10, 52);		// ubica cursor en coordenas 10,30
//         display.setTextSize(1);			// establece tamano de texto en 2
//         display.print(movementDisplay);

//         display.display(); 

//         digitalWrite(RELAY, sign);
//         digitalWrite(LED_BUILTIN, sign);
//       }

//     }
//     https.end();
//   }
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
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

const int RELAY = 14;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  Wire.begin(); // inicializa bus I2C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  // WiFi.mode(WIFI_STA);
  // WiFiMulti.addAP("GEMELOS92", "Gj180692");

  pinMode(RELAY, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  delay(10000);
  Serial.print("[LOOP] init");

  // Predefined data
  const char* jsonData = R"([
    {
        "price": "185.772",
        "movement": "+0.00%"
    },
    {
        "price": "185.132",
        "movement": "-0.34%"
    },
    {
        "price": "185.445",
        "movement": "+0.17%"
    },
    {
        "price": "185.525",
        "movement": "+0.04%"
    },
    {
        "price": "185.17",
        "movement": "-0.19%"
    },
    {
        "price": "185.28",
        "movement": "+0.06%"
    },
    {
        "price": "184.95",
        "movement": "-0.18%"
    },
    {
        "price": "184.88",
        "movement": "-0.04%"
    },
    {
        "price": "185.135",
        "movement": "+0.14%"
    },
    {
        "price": "184.5",
        "movement": "-0.34%"
    },
    {
        "price": "184.71",
        "movement": "+0.11%"
    },
    {
        "price": "185.152",
        "movement": "+0.24%"
    },
    {
        "price": "184.74",
        "movement": "-0.22%"
    },
    {
        "price": "184.3",
        "movement": "-0.24%"
    },
    {
        "price": "184.28",
        "movement": "-0.01%"
    },
    {
        "price": "184.508",
        "movement": "+0.12%"
    },
    {
        "price": "184.237",
        "movement": "-0.15%"
    },
    {
        "price": "183.998",
        "movement": "-0.13%"
    },
    {
        "price": "183.91",
        "movement": "-0.05%"
    },
    {
        "price": "183.672",
        "movement": "-0.13%"
    },
    {
        "price": "183.3",
        "movement": "-0.20%"
    },
    {
        "price": "183.899",
        "movement": "+0.33%"
    },
    {
        "price": "184.397",
        "movement": "+0.27%"
    },
    {
        "price": "184.645",
        "movement": "+0.13%"
    },
    {
        "price": "185.06",
        "movement": "+0.22%"
    },
    {
        "price": "185.025",
        "movement": "-0.02%"
    },
    {
        "price": "185.37",
        "movement": "+0.19%"
    },
    {
        "price": "185.094",
        "movement": "-0.15%"
    },
    {
        "price": "185.115",
        "movement": "+0.01%"
    },
    {
        "price": "184.895",
        "movement": "-0.12%"
    },
    {
        "price": "185.12",
        "movement": "+0.12%"
    },
    {
        "price": "185.142",
        "movement": "+0.01%"
    },
    {
        "price": "184.93",
        "movement": "-0.11%"
    },
    {
        "price": "184.58",
        "movement": "-0.19%"
    },
    {
        "price": "184.137",
        "movement": "-0.24%"
    },
    {
        "price": "184.44",
        "movement": "+0.16%"
    },
    {
        "price": "184.34",
        "movement": "-0.05%"
    },
    {
        "price": "184.16",
        "movement": "-0.10%"
    },
    {
        "price": "184.5",
        "movement": "+0.18%"
    },
    {
        "price": "184.8",
        "movement": "+0.16%"
    },
    {
        "price": "184.77",
        "movement": "-0.02%"
    },
    {
        "price": "184.91",
        "movement": "+0.08%"
    },
    {
        "price": "185.2",
        "movement": "+0.16%"
    },
    {
        "price": "185.64",
        "movement": "+0.24%"
    },
    {
        "price": "185.6",
        "movement": "-0.02%"
    },
    {
        "price": "185.585",
        "movement": "-0.01%"
    },
    {
        "price": "185.89",
        "movement": "+0.16%"
    },
    {
        "price": "185.94",
        "movement": "+0.03%"
    },
    {
        "price": "185.92",
        "movement": "-0.01%"
    },
    {
        "price": "185.91",
        "movement": "-0.01%"
    },
    {
        "price": "186.041",
        "movement": "+0.07%"
    },
    {
        "price": "186.07",
        "movement": "+0.02%"
    },
    {
        "price": "185.735",
        "movement": "-0.18%"
    },
    {
        "price": "186.69",
        "movement": "+0.51%"
    },
    {
        "price": "185.87",
        "movement": "-0.44%"
    },
    {
        "price": "185.8",
        "movement": "-0.04%"
    },
    {
        "price": "185.72",
        "movement": "-0.04%"
    },
    {
        "price": "185.73",
        "movement": "+0.01%"
    },
    {
        "price": "185.89",
        "movement": "+0.09%"
    },
    {
        "price": "185.875",
        "movement": "-0.01%"
    },
    {
        "price": "185.84",
        "movement": "-0.02%"
    },
    {
        "price": "185.78",
        "movement": "-0.03%"
    },
    {
        "price": "185.67",
        "movement": "-0.06%"
    },
    {
        "price": "185.745",
        "movement": "+0.04%"
    },
    {
        "price": "185.81",
        "movement": "+0.03%"
    },
    {
        "price": "185.74",
        "movement": "-0.04%"
    },
    {
        "price": "185.71",
        "movement": "-0.02%"
    },
    {
        "price": "185.64",
        "movement": "-0.04%"
    },
    {
        "price": "185.72",
        "movement": "+0.04%"
    },
    {
        "price": "185.65",
        "movement": "-0.04%"
    },
    {
        "price": "185.61",
        "movement": "-0.02%"
    },
    {
        "price": "185.79",
        "movement": "+0.10%"
    },
    {
        "price": "185.75",
        "movement": "-0.02%"
    },
    {
        "price": "185.75",
        "movement": "+0.00%"
    },
    {
        "price": "185.81",
        "movement": "+0.03%"
    },
    {
        "price": "185.825",
        "movement": "+0.01%"
    },
    {
        "price": "185.77",
        "movement": "-0.03%"
    },
    {
        "price": "185.84",
        "movement": "+0.04%"
    },
    {
        "price": "185.865",
        "movement": "+0.01%"
    },
    {
        "price": "185.87",
        "movement": "+0.00%"
    },
    {
        "price": "185.89",
        "movement": "+0.01%"
    },
    {
        "price": "185.86",
        "movement": "-0.02%"
    },
    {
        "price": "185.802",
        "movement": "-0.03%"
    },
    {
        "price": "185.86",
        "movement": "+0.03%"
    },
    {
        "price": "185.81",
        "movement": "-0.03%"
    },
    {
        "price": "185.88",
        "movement": "+0.04%"
    },
    {
        "price": "185.88",
        "movement": "+0.00%"
    },
    {
        "price": "185.84",
        "movement": "-0.02%"
    },
    {
        "price": "185.86",
        "movement": "+0.01%"
    },
    {
        "price": "185.86",
        "movement": "+0.00%"
    },
    {
        "price": "185.865",
        "movement": "+0.00%"
    },
    {
        "price": "185.82",
        "movement": "-0.02%"
    },
    {
        "price": "185.852",
        "movement": "+0.02%"
    },
    {
        "price": "185.9",
        "movement": "+0.03%"
    },
    {
        "price": "185.98",
        "movement": "+0.04%"
    },
    {
        "price": "186.17",
        "movement": "+0.10%"
    },
    {
        "price": "186.11",
        "movement": "-0.03%"
    },
    {
        "price": "186.0",
        "movement": "-0.06%"
    },
    {
        "price": "185.98",
        "movement": "-0.01%"
    },
    {
        "price": "186.2",
        "movement": "+0.12%"
    }
])";

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, jsonData);

  for (JsonVariant v : doc.as<JsonArray>()) {
    const char* price = v["price"];
    const char* movement = v["movement"];

    String movementDisplay = movement;
    int sign = (movement[0] == '-') ? 0 : 1;

    String stock = "AMZN"; // Hardcoded stock parameter
    stock.toUpperCase();

    display.clearDisplay();
    Serial.print("[LOOP] screen");
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print(stock);
    display.setCursor(10, 30);
    display.setTextSize(2);
    display.print(price);
    display.setCursor(10, 52);
    display.setTextSize(1);
    display.print(movementDisplay);
    display.display();

    digitalWrite(RELAY, sign);
    digitalWrite(LED_BUILTIN, sign);

    delay(5000); // Display each entry for 5 seconds
  }
}
