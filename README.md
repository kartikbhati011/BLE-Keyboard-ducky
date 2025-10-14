# BLE-Keyboard-ducky
## ESP32 BLE Remote HID 

Control any Windows PC remotely using your ESP32 over Bluetooth + WiFi.
This project turns your ESP32 into a wireless keyboard that can open CMD, PowerShell, Notepad, or run custom commands directly from a web interface.
Everything works through your browser — no extra app needed!

**__🧰 Hardware Requirements__**

- ESP32 board (any standard dev board).<br>
- USB cable to flash the code and power the board.<br>

**__🛠 Arduino IDE Setup__**

1. Open Arduino IDE → File → Preferences<br>
In Additional Board Manager URLs, add:
```bash
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```
2. Go to Tools → Board → Board Manager<br>
Search for ESP32 and
Install version 2.0.15 (recommended)<br>
## Highly recommended
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
   - Run upto 3 commands in one click<br>
- LED indicator shows Bluetooth connection status<br>




__**⚙️ Installation Guide**__

1. Open the provided .ino file in Arduino IDE.<br>
2. Install required libraries if missing:<br>
  - BLEKeyboard [BLEKeyboard library](https://github.com/T-vK/ESP32-BLE-Keyboard)<br>
  - WiFi and WebServer (comes pre-installed with ESP32)<br>
  - WiFi library [WiFi library](https://www.arduinolibraries.info/libraries/esp32-wifi-manager)
  - WebServer library [WebServer library](https://www.arduinolibraries.info/libraries/wi-fi-web-server)
3. Update your WiFi credentials in the code:<br>
4. Connect ESP32 via USB and select the correct Port and Board (ESP32 Dev Module).
5. Click Upload to flash the code.
6. After upload, open the Serial Monitor → it will show “WiFi connected” and the IP address.

__**💻 How to Use**__

1. Pair your ESP32 with your Windows PC via Bluetooth.<br>
   - Once connected successfully, the blue onboard LED on the ESP32 will turn on
2. Turn On your phone hotspot esp32 will automatically connected to your mobile hotspot open the IP address shown in the Serial Monitor.<br>
3. You’ll see a clean web interface:<br>
   - Choose Command Prompt or PowerShell (normal/admin).<br>
   - Type a custom command or use quick buttons (Notepad , Shutdown, Run 3).<br>
4. Commands are sent as keyboard input to your PC through BLE.
