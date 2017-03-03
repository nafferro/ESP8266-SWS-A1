#include <ESP8266WiFi.h>
#include <WiFiudp.h>

const char* ssid     = "ssid"; // wifi SSID
const char* password = "password"; // wifi password
WiFiUDP udp;

// set socket ON/OFF
byte setOn[] = {0x01,0x42,0xac,0xcf,0x23,0x36,0x9b,0x48,0x10,0x4c,0xf7,0x5f,0x5a,0x28,0xa1,0x81,0x57,0x4a,0xc1,0xb5,0x63,0xcd,0x51,0xa7,0x8d};
byte setOff[] = {0x01,0x42,0xac,0xcf,0x23,0x36,0x9b,0x48,0x10,0xf7,0xb4,0xe7,0x4b,0x97,0x0d,0x96,0xf3,0xca,0x2b,0xb5,0xd3,0xcd,0x1c,0x19,0xd0};

boolean off = false;

void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wifi connected");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void loop() {
  udp.beginPacket("192.168.1.100", 8530);
  
  if (off){
      udp.write(setOn, sizeof(setOn));
      off = false;
    }
  else{
      udp.write(setOff, sizeof(setOn));
      off = true;
    }
  
  udp.endPacket();

  delay(10000);
}