#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <TimeLib.h>

#include "configuraciones.hpp"
#include "funciones.hpp"
#include "configuracionesReset.hpp"
#include "configuracionesLeer.hpp"
#include "configuracionesGuardar.hpp"
#include "esp32_wifi.hpp"
#include "esp32_mqtt.hpp"
#include "esp32_api.hpp"
#include "esp32_webSocket.hpp"
#include "esp32_webServer.hpp"

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
  LeerConfiguracionRelays();
  ApagadoEncendidoSimple(RELAY1,relay1Estado);
  ApagadoEncendidoSimple(RELAY2,relay2Estado);
  LeerConfiguracionWiFi();
  WiFi.disconnect();
  delay(1000);
  WiFiSetup();

  LeerConfiguracionMqtt();

  IniciarServidor();
  
}

void loop() {
  /*WiFi*/
  yield();
  if(wifiModo == WIFI_STA){
    WifiLoop();
  }
  if(wifiModo == WIFI_AP){
    WifiApLoop();
  }
  /*MQTT*/
  if((WiFi.status() == WL_CONNECTED) && (wifiModo == WIFI_STA)){
    if(mqttServidor != 0){
      LoopMQTT();
      if(mqttcliente.connected()){
        if(millis() - ultimoMensaje > mqttTiempo){
          ultimoMensaje = millis();
          PublicarMQTT();
        }
      }
    }
  }
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

