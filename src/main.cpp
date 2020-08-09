#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <string>
#include <LittleFS.h>
// -- ESP8266 libs
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>
#include <WebSocketsServer.h>
// -- Adafruit libs
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
// #include <ESP8266httpUpdate.h>

#include "index.h"

#define PIN D5

uint16_t getPayloadColor(const char *payload);
uint8_t getPayloadBrightness(const char *payload);

// -- INIT MATRIX
Adafruit_NeoMatrix *matrix = new Adafruit_NeoMatrix(
    8, 8, PIN,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
    NEO_GRB + NEO_KHZ800);

// -- INIT WebServer
ESP8266WebServer server(80);
WebSocketsServer socket(81);
MDNSResponder mdns;
ulong sec10 = 0;
uint counter = 0;
// uint16_t m_color = 0xFFFF;
uint8_t m_color[3] = {255, 255, 255};
uint8_t m_brightness = 140;

// uint16_t RGB888toRGB565(const char *rgb32_str_){
//   long rgb32=strtoul(rgb32_str_, 0, 16);
//   return (rgb32>>8&0xf800)|(rgb32>>5&0x07e0)|(rgb32>>3&0x001f);
// }
void initMatrix() {
  matrix->begin();
  matrix->setBrightness(m_brightness);
  matrix->fillScreen(matrix->Color(m_color[0], m_color[1], m_color[2]));
  matrix->show();
  delay(1000);
  matrix->clear();
}

void handleRoot() { server.send_P(200, "text/html", HTML_INDEX); }
void handleNotFound() { server.send(404, "text/plain", "404"); }
void handleSocket(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
  case WStype_DISCONNECTED:
    break;
  case WStype_CONNECTED:
    char msg[512];
    sprintf(msg, "c_r%dg%db%d-b_%d", m_color[0], m_color[1], m_color[2], m_brightness);
    socket.sendTXT(num, msg, strlen(msg));
    break;
  case WStype_TEXT:
    Serial.printf("[%u] get Text: %s\r\n", num, payload);
    const char *pch = (const char*)payload;
    if(pch[0] == 'c' && pch[1] == '_'){
      matrix->fillScreen(getPayloadColor(pch));
      matrix->setBrightness(getPayloadBrightness(pch));
    }
    socket.broadcastTXT(payload, length);
    break;
  }
}

uint16_t getPayloadColor(const char *payload){
  int p1 = payload - strchr(payload, 'r') + 1;
  int p2 = payload - strchr(payload, 'g') + 1;
  int p3 = payload - strchr(payload, 'b') + 1;
  int p4 = payload - strchr(payload, '-') + 1;

  String p = String(payload);
  uint8_t r = (p.substring(p1, p2)).toInt();
  uint8_t g = (p.substring(p2, p3)).toInt();
  uint8_t b = (p.substring(p3, p4)).toInt();
  
  return matrix->Color(r, g, b);
}

uint8_t getPayloadBrightness(const char *payload){
  // int p1 = payload - strchr(payload, '-') + 1;
  return 140;
}

String getContentType(String filename){
    if(server.hasArg("download")) return "application/octet-stream";
    else if(filename.endsWith(".htm")) return "text/html";
    else if(filename.endsWith(".html")) return "text/html";
    else if(filename.endsWith(".css")) return "text/css";
    else if(filename.endsWith(".js")) return "application/javascript";
    else if(filename.endsWith(".png")) return "image/png";
    else if(filename.endsWith(".gif")) return "image/gif";
    else if(filename.endsWith(".jpg")) return "image/jpeg";
    else if(filename.endsWith(".ico")) return "image/x-icon";
    else if(filename.endsWith(".xml")) return "text/xml";
    else if(filename.endsWith(".pdf")) return "application/x-pdf";
    else if(filename.endsWith(".zip")) return "application/x-zip";
    else if(filename.endsWith(".gz")) return "application/x-gzip";
    return "text/plain";
}

bool handleFileRead(String path){
  if(path.endsWith("/")) path += "index.html";
	path = "../web" + path;

	Serial.print("OPEN PATH - ");
  Serial.println(path);

  if(LittleFS.exists(path)){
    File file = LittleFS.open(path, "r");
    size_t sent = server.streamFile(file, getContentType(path));
    file.close();
    return true;
  }
  return false;
  
}

void setup() {
  Serial.begin(115200);

  // -- INIT WiFi
  WiFiManager wifiManager;
  initMatrix();
  wifiManager.autoConnect("JapanLamp#1");

  delay(100);

  LittleFS.begin();
  // -- socket
  socket.begin();
  socket.onEvent(handleSocket);
  // -- web server
  server.begin();
  // server.on("/", handleRoot);
  // server.onNotFound(handleNotFound);
  server.onNotFound([](){
    if(!handleFileRead(server.uri()))
      server.send(404, "text/plain", "404");
  });
  // -- DNS
  if (mdns.begin("japanlamp", WiFi.localIP())) {
    Serial.println("MDNS responder started");
    mdns.addService("http", "tcp", 80);
    mdns.addService("ws", "tcp", 81);
  }
  else {
    Serial.println("MDNS.begin failed");
  }
  Serial.print("Wifi Connected..");
  Serial.println(WiFi.localIP());
}

void loop() {
  socket.loop();
  server.handleClient();

  // -- socket ping
  unsigned long t = millis();
  if((t - sec10) > 10 * 1000){
    counter++;
    bool ping = counter % 2;
    socket.connectedClients(ping);
    sec10 = millis();
  }
}
