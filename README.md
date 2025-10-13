## Wait code coming soon
# BLE-Keyboard-ducky
## ESP32 BLE Remote HID 

Control any Windows PC remotely using your ESP32 over Bluetooth + WiFi.
This project turns your ESP32 into a wireless keyboard that can open CMD, PowerShell, Notepad, or run custom commands directly from a web interface.
Everything works through your browser — no extra app needed!

**__🧰 Hardware Requirements__**

1. ESP32 board (any standard dev board).<br>
2. USB cable to flash the code and power the board.<br>

**__🛠 Arduino IDE Setup__**

1. Open Arduino IDE → File → Preferences<br>
In Additional Board Manager URLs, add:
```bash
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```
2. Go to Tools → Board → Board Manager<br>
Search for ESP32 and
Install version 2.0.15 (recommended)<br>
## Highly recommended setup for IDE
Go to tools → Partition scheme → Huge APP

<br>



**__🌟 Features__**

-  Fully Control Windows PC from a web interface hosted on ESP32<br>
- Works over Bluetooth (BLE HID Keyboard)<br>
- Supports Command Prompt and PowerShell — both normal and admin modes<br>
- Run Custom Commands directly from the webpage <br>
- Quick-action buttons for:<br>
- Notepad<br>
- Shutdown<br>
- Run upto 3 cmd in one click<br>
- LED indicator shows Bluetooth connection status<br>




__**⚙️ Installation Guide**__

- Open the provided .ino file in Arduino IDE.<br>
- Install required libraries if missing:<br>
- BLEKeyboard [BLEKeyboard library](https://github.com/T-vK/ESP32-BLE-Keyboard)<br>
- WiFi and WebServer (already included with ESP32 i think if missing then download)<br>
- WiFi library [WiFi library](https://www.arduinolibraries.info/libraries/esp32-wifi-manager)
- WebServer library [WebServer library](https://www.arduinolibraries.info/libraries/wi-fi-web-server)
- Update the WiFi credentials and username in the code:<br>
- Connect ESP32 via USB and select the correct Port and Board (ESP32 Dev Module).
 Click Upload to flash the code.
- After upload, open the Serial Monitor → it will show “WiFi connected” and the IP address.

__**💻 How to Use**__

- Connect your ESP32 to your Windows PC via Bluetooth if connected successfully the blue inbuild led of esp32 will automatically turn on.<br>
- On your phone or computer (same WiFi network), open the IP address shown in Serial Monitor.<br>
- You’ll see a clean web interface:<br>
Choose Command Prompt or PowerShell (normal/admin).<br>
- Type a custom command or use quick buttons (Notepad , Shutdown, Run 3).<br>
- Commands are sent as keyboard input to your PC through BLE.<br>
