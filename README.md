# Week 7 — Task 01: ESP32 Web Server

## Overview

This task demonstrates how an ESP32 can work as a local web
server and provide a browser-based interface for controlling
its built-in LED.

The ESP32 connects to a Wi-Fi network and starts an HTTP web
server. After receiving a local IP address, the IP address can
be opened from a browser connected to the same network.

The browser provides ON and OFF controls. When a button is
pressed, the browser sends a request to the ESP32 and the
ESP32 changes the state of its built-in LED.

## Objective

Create a web-based control system where the built-in LED of
the ESP32 can be switched ON and OFF from a browser over Wi-Fi.

## Components Used

- ESP32 development board
- USB cable
- Computer
- Wi-Fi network

No external LED circuit is required because this implementation
uses the ESP32's built-in LED.

## Software Used

- Arduino IDE
- ESP32 board package
- C/C++
- HTML
- CSS
- Local Wi-Fi network
- Web browser

## System Architecture

```text
Browser
   |
   | HTTP Request
   v
Local Wi-Fi
   |
   v
ESP32 Web Server
   |
   | GPIO
   v
Built-in LED
```

## GPIO Configuration

| Component | GPIO | Type |
|---|---|---|
| Built-in LED | `LED_BUILTIN` | Digital Output |

The code uses `LED_BUILTIN` instead of assuming a fixed GPIO
number because the built-in LED mapping can vary between ESP32
board variants.

## Wiring

No external LED wiring is required for this implementation.

The ESP32 is connected to the computer through USB for power
and program upload. The onboard LED is controlled using the
board-defined `LED_BUILTIN` constant.

See:

`hardware/wiring.png`

## Arduino IDE Setup

1. Install Arduino IDE.
2. Install ESP32 board support through Boards Manager.
3. Connect the ESP32 through USB.
4. Select the correct ESP32 board.
5. Select the correct COM port.
6. Open `src/esp32_web_server.ino`.

## Wi-Fi Configuration

Change these values in the source code:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

Do not commit real Wi-Fi credentials to GitHub.

## Uploading

1. Connect the ESP32.
2. Open the `.ino` file.
3. Select the ESP32 board.
4. Select the COM port.
5. Verify the program.
6. Upload it.
7. Open Serial Monitor.
8. Set the baud rate to `115200`.

## Connecting to the Web Server

After Wi-Fi connection, the Serial Monitor displays the local
IP address.

Example:

```text
Wi-Fi connected!
ESP32 IP Address: 192.168.1.105
Web server started.
Open the IP address in a browser.
```

Open that IP address in a browser:

```text
http://192.168.1.105
```

The browser/device must be connected to the same local network
as the ESP32.

## Web Controls

The webpage provides:

- `TURN ON`
- `TURN OFF`

The ON button sends:

```text
/on
```

The OFF button sends:

```text
/off
```

The ESP32 processes those requests and changes the LED state.

## Important Code Sections

### LED definition

```cpp
#define LED_PIN LED_BUILTIN
```

### Wi-Fi connection

```cpp
WiFi.begin(ssid, password);
```

### HTTP server

```cpp
WebServer server(80);
```

### Routes

```cpp
server.on("/", handleRoot);
server.on("/on", handleLEDOn);
server.on("/off", handleLEDOff);
```

### Request processing

```cpp
server.handleClient();
```

## Testing

| Test | Expected Result |
|---|---|
| ESP32 powered | Board starts |
| Wi-Fi connected | IP appears in Serial Monitor |
| Open IP address | Web interface appears |
| Press TURN ON | Built-in LED turns ON |
| Press TURN OFF | Built-in LED turns OFF |

## Challenges & Fixes

### Wi-Fi Connection

The ESP32 must connect successfully before the browser can
communicate with its web server.

**Fix:** Serial Monitor was used to verify the connection and
identify the assigned IP address.

### Accessing the ESP32

The browser and ESP32 need to be on the same local network.

**Fix:** The ESP32's local IP address was opened from a device
connected to the same Wi-Fi network.

### Built-in LED Behaviour

Built-in LED mappings can vary between board variants.

**Fix:** The program uses `LED_BUILTIN` instead of hard-coding
a GPIO number.

## Result

A local ESP32 web server was created successfully. The built-in
LED could be controlled from a browser using ON and OFF buttons
over Wi-Fi.

## Evidence

Add actual evidence to the `screenshots/` folder, such as:

- Arduino IDE setup
- Board and COM port selection
- Serial Monitor
- ESP32 IP address
- Web interface
- Physical ESP32 test
- Final LED result

A demonstration video can also be added to the repository if
required.

## Repository Structure

```text
Week7-Task01-ESP32-Web-Server/
├── README.md
├── src/
│   └── esp32_web_server.ino
├── hardware/
│   └── wiring.png
└── screenshots/
```

## Reflection

This task introduced the relationship between a web interface,
network communication, microcontroller logic, and physical
hardware.

The ESP32 was used not only as a programmable board but also
as a web server capable of receiving commands from a browser.

This task formed the foundation for the later Week 7 activities,
where communication moves from local browser control toward
cloud platforms, automation, and Firebase-based systems.

## Author

**Aatif**  
B.Tech Information Technology  
Kumaraguru College of Technology

## Project Status

Completed — Week 7 Task 01
