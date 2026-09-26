#include <WiFi.h>
#include <WebServer.h>

// ===============================
// Wi-Fi Configuration
// ===============================

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ===============================
// ESP32 Configuration
// ===============================

#define LED_PIN LED_BUILTIN

WebServer server(80);

// ===============================
// Web Page
// ===============================

String getHTML() {

  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>

  <meta name="viewport" content="width=device-width, initial-scale=1">

  <title>ESP32 Web Server</title>

  <style>

    body {
      margin: 0;
      padding: 0;
      font-family: Arial, sans-serif;
      background: #111;
      color: white;
      text-align: center;
    }

    .container {
      max-width: 500px;
      margin: 80px auto;
      padding: 30px;
    }

    h1 {
      margin-bottom: 10px;
    }

    p {
      color: #aaa;
      margin-bottom: 30px;
    }

    .button {
      display: inline-block;
      padding: 15px 35px;
      margin: 10px;
      border-radius: 8px;
      text-decoration: none;
      color: white;
      font-size: 18px;
      font-weight: bold;
    }

    .on {
      background: #18a558;
    }

    .off {
      background: #d62828;
    }

  </style>

</head>

<body>

  <div class="container">

    <h1>ESP32 Web Server</h1>

    <p>Built-in LED Control</p>

    <a href="/on" class="button on">
      TURN ON
    </a>

    <a href="/off" class="button off">
      TURN OFF
    </a>

  </div>

</body>
</html>
)rawliteral";

  return html;
}

// ===============================
// Handle Home Page
// ===============================

void handleRoot() {

  server.send(
    200,
    "text/html",
    getHTML()
  );
}

// ===============================
// Turn LED ON
// ===============================

void handleLEDOn() {

  digitalWrite(
    LED_PIN,
    HIGH
  );

  server.send(
    200,
    "text/html",
    getHTML()
  );

  Serial.println("LED: ON");
}

// ===============================
// Turn LED OFF
// ===============================

void handleLEDOff() {

  digitalWrite(
    LED_PIN,
    LOW
  );

  server.send(
    200,
    "text/html",
    getHTML()
  );

  Serial.println("LED: OFF");
}

// ===============================
// Setup
// ===============================

void setup() {

  Serial.begin(115200);

  pinMode(
    LED_PIN,
    OUTPUT
  );

  digitalWrite(
    LED_PIN,
    LOW
  );

  Serial.println();
  Serial.println("==============================");
  Serial.println("ESP32 WEB SERVER");
  Serial.println("==============================");

  // Connect to Wi-Fi
  WiFi.begin(
    ssid,
    password
  );

  Serial.print("Connecting to Wi-Fi");

  while (
    WiFi.status() != WL_CONNECTED
  ) {

    delay(500);

    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");

  Serial.print("ESP32 IP Address: ");
  Serial.println(
    WiFi.localIP()
  );

  // Routes
  server.on(
    "/",
    handleRoot
  );

  server.on(
    "/on",
    handleLEDOn
  );

  server.on(
    "/off",
    handleLEDOff
  );

  // Start server
  server.begin();

  Serial.println(
    "Web server started."
  );

  Serial.println(
    "Open the IP address in a browser."
  );
}

// ===============================
// Main Loop
// ===============================

void loop() {

  server.handleClient();

}