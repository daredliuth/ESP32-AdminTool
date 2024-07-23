#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

#include "configuraciones.hpp"
#include "funciones.hpp"
#include "parpadeoLed.hpp"
#include "configuracionesReset.hpp"
#include "configuracionesLeer.hpp"
#include "configuracionesEscribir.hpp"
#include "esp32_wifi.hpp"

// put function declarations here:
int myFunction(int, int);

void setup() {
  Serial.begin(115200);
  setCpuFrequencyMhz(240);
  GenerarLog("Iniciando configuración.",0);
  ConfiguracionPines();
  if(!SPIFFS.begin()){
    GenerarLog("Falló la inicialización del SPIFFS.",1);
    while(true);
  }
  LeerConfiguracionWiFi();
  WiFi.disconnect();
  delay(1000);
  WiFiSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  yield();
  if(wifiModo == WIFI_STA){
    WifiLoop();
  }
  if(wifiModo == WIFI_AP){
    WifiApLoop();
  }
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}