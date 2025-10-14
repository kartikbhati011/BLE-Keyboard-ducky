#include <BleKeyboard.h>
#include <WiFi.h>
#include <WebServer.h>

//  Credentials
const char* ssid = "lomdesh";
const char* password = "0987654321";
const int ledPin = 2;

BleKeyboard bleKeyboard("BLE Keyboard", "ESP32", 100);
WebServer server(80);

void safeType(const char* text, unsigned int charDelay = 50) {
  for (size_t i = 0; i < strlen(text); ++i) {
    if (!bleKeyboard.isConnected()) return; 
    bleKeyboard.print(String(text[i]));
    delay(charDelay);
  }
}
void openAndRun(const char* program, bool isAdmin, bool typeAfterOpen, const char* textInside) {
  if (!bleKeyboard.isConnected()) {
    return;
  }

  bleKeyboard.press(KEY_LEFT_GUI);
  bleKeyboard.press('r');
  bleKeyboard.releaseAll();
  delay(1000);

  safeType(program, 40);
  delay(300);

  if (isAdmin) {
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.press(KEY_RETURN);
    bleKeyboard.releaseAll();
    delay(1800);
    bleKeyboard.write(KEY_LEFT_ARROW);
    delay(1000);
    bleKeyboard.write(KEY_RETURN);
    delay(900);
  } else {
    bleKeyboard.write(KEY_RETURN);
    delay(900);
  }
  if (typeAfterOpen && textInside != nullptr && strlen(textInside) > 0) {
    delay(700);
    safeType(textInside, 45);
    delay(120);
    bleKeyboard.write(KEY_RETURN);
  }
}
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<title>ESP32 BLE Ducky HID</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<style>
  body {background:white; color:black; text-align:center;}
  select, input, button { width: 92%; max-width:420px; padding:10px; margin:10px; font-size:16px; }
</style>
</head>
<body>
  <h2>ESP32 BLE HID</h2>
  <div class="status">Bluetooth: <b id="bt">Checking...</b></div>

  <select id="mode">
    <option value="cmd">Command Prompt</option>
    <option value="powershell">PowerShell</option>
    <option value="cmd_admin">Command Prompt (Admin)</option>
    <option value="ps_admin">PowerShell (Admin)</option>
  </select>

  <input id="custom" placeholder="Type custom command here" />

  <button onclick="runCustom()">Run Custom Command</button>

  <div style="margin-top:12px;">
    <button class="small" onclick="fetch('/notepad')">Notepad</button>
    <button class="small" onclick="fetch('/shutdown')">Shutdown</button>
    <button class="small" onclick="fetch('/run3')">Run 3 Commands</button>
  </div>
<script>
async function updateStatus(){
  try {
    const r = await fetch('/status');
    const t = await r.text();
    document.getElementById('bt').innerText = t.includes('Connected') ? 'Connected' : 'Disconnected';
  } catch (e) {
    document.getElementById('bt').innerText = 'Error';
  }
}
setInterval(updateStatus,2000);
updateStatus();

function runCustom(){
  const mode = document.getElementById('mode').value;
  const cmd = encodeURIComponent(document.getElementById('custom').value || '');
  fetch('/run?mode=' + mode + '&cmd=' + cmd);
}
</script>
</body>
</html>
)rawliteral";

void handleRoot() { server.send(200, "text/html", htmlPage); }

void handleRun() {
  String mode = server.arg("mode");
  String cmd  = server.arg("cmd");
  cmd.replace("+", " ");
  cmd = UriDecode(cmd);

  if (mode == "cmd") {
    openAndRun("cmd", false, true, cmd.c_str());
  } else if (mode == "powershell") {
    openAndRun("powershell", false, true, cmd.c_str());
  } else if (mode == "cmd_admin") {
    openAndRun("cmd", true, true, cmd.c_str());
  } else if (mode == "ps_admin") {
    openAndRun("powershell", true, true, cmd.c_str());
  }

  server.send(200, "text/plain", "OK");
}

void handleNotepad() {
  openAndRun("notepad", false, true, "lol"); // Notepad
  server.send(200, "text/plain", "Notepad");
}

void handleShutdown() {
  openAndRun("shutdown /s /t 0", false, false, nullptr); //Type custom cmd here
  server.send(200, "text/plain", "Shutdown");
}
void handleRun3() {
  const char* commands[3] = { //Run upto 3 cmd here line by line
    "echo FirstCommand",
    "echo SecondCommand",
    "echo ThirdCommand"
  };
  openAndRun("cmd", false, false, nullptr);

  delay(800);

  for (int i = 0; i < 3; i++) {
    safeType(commands[i]);
    bleKeyboard.write(KEY_RETURN);
    delay(1000);
  }

  server.send(200, "text/plain", "3 commands executed");
}


void handleStatus() {
  String s = bleKeyboard.isConnected() ? "Connected" : "Disconnected";
  server.send(200, "text/plain", s);
}

String UriDecode(const String &src) {
  String ret = "";
  char temp[] = "0x00";
  unsigned int len = src.length();
  unsigned int i = 0;
  while (i < len) {
    char c = src.charAt(i);
    if (c == '%') {
      if (i + 2 < len) {
        temp[2] = src.charAt(i + 1);
        temp[3] = src.charAt(i + 2);
        char ch = (char) strtol(&src.substring(i+1, i+3)[0], NULL, 16);
        ret += ch;
        i += 3;
      } else {
        i++;
      }
    } else if (c == '+') {
      ret += ' ';
      i++;
    } else {
      ret += c;
      i++;
    }
  }
  return ret;
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  WiFi.begin(ssid, password);
  Serial.print("📡 Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected");
  Serial.print("🌐 IP Address: ");
  Serial.println(WiFi.localIP());

  bleKeyboard.begin();
  server.on("/", handleRoot);
  server.on("/run", handleRun);
  server.on("/notepad", handleNotepad);
  server.on("/shutdown", handleShutdown);
  server.on("/run3", handleRun3);
  server.on("/status", handleStatus);
  server.begin();
}

void loop() {
  server.handleClient();
  digitalWrite(ledPin, bleKeyboard.isConnected() ? HIGH : LOW);
}