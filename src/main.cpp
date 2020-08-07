#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <string>
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

// -- INIT MATRIX
Adafruit_NeoMatrix *matrix = new Adafruit_NeoMatrix(
    8, 8, PIN,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
    NEO_GRB + NEO_KHZ800);

// -- INIT WebServer
ESP8266WebServer server(80);
WebSocketsServer socket(81);
MDNSResponder mdns;
unsigned long sec10 = 0;
unsigned int counter = 0;
uint16_t m_color = 0xFFFF;
uint8_t m_brightness = 140;

uint16_t RGB888toRGB565(const char *rgb32_str_){
  long rgb32=strtoul(rgb32_str_, 0, 16);
  return (rgb32>>8&0xf800)|(rgb32>>5&0x07e0)|(rgb32>>3&0x001f);
}
void initMatrix() {
  matrix->begin();
  matrix->setBrightness(m_brightness);
  matrix->fillScreen(m_color);
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
    const char *c = reinterpret_cast<const char *>(m_color);
    const char *b = reinterpret_cast<const char *>(m_brightness);
    sprintf(msg, "c_%s-b_%s", c, b);
    socket.sendTXT(num, msg, strlen(msg));
    break;
  case WStype_TEXT:
    Serial.printf("[%u] get Text: %s\r\n", num, payload);
    const char *pch = static_cast<const char*>(payload);
    if(pch[0] == 'c' && pch[1] == '_'){

    }
    break;
  }
}

void setup() {
  Serial.begin(115200);

  // -- INIT WiFi
  WiFiManager wifiManager;
  initMatrix();
  wifiManager.autoConnect("JapanLamp#1");

  delay(100);

  // -- socket
  socket.begin();
  socket.onEvent(handleSocket);
  // -- web server
  server.begin();
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
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
