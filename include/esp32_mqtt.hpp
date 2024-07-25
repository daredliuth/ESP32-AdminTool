#include <PubSubClient.h>

WiFiClient espCliente;
PubSubClient mqttcliente(espCliente);

String Json();
void callback(char* topico, byte* payload, unsigned int tam);

char topico[150];
String mqttDatos = "";
long ultimoIntentoConexionMQTT = 0;


boolean ConectarMQTT(){
    mqttcliente.setServer(mqttServidor,mqttPuerto);
    mqttcliente.setCallback(callback);
    GenerarLog("Intentando conexión al broker MQTT.",0);
    if(mqttcliente.connect(mqttId, mqttUsuario, mqttPassword)){
        GenerarLog("Conectado al broker MQTT",0);
        String topicoSuscribir = String(mqttUsuario) + "/" + idDispositivo + "/command";
        topicoSuscribir.toCharArray(topico,150);
        mqttcliente.subscribe(topico);
        topicoSuscribir.toCharArray(topico,25);
        mqttcliente.publish(topico,"ok");
    }
    else{
        GenerarLog("Fallo. rc= " + mqttcliente.state(),1);
        return false;
    }
    return true;
}

void callback(char* topicoCallback, byte* payload, unsigned int tam){
    String mensaje = "";
    String topicoCadena(topicoCallback);

    for(uint16_t i=0; i<tam; i++){
        mensaje += (char)payload[i];
        RxMQTT();
    }

    mensaje.trim();

    DynamicJsonDocument jsonDoc(300);
    deserializeJson(jsonDoc,mensaje);
    //TODO: Realizar el manejo de acciones al llegar un dato JSON.
    if(jsonDoc["RELAY1"] == "on"){
        EncendidoSimple(LEDMQTT);
        relay1Estado = HIGH;
        ConfiguracionGuardarRelays();
    }
    else if(jsonDoc["RELAY1"] == "off"){
        ApagadoSimple(LEDMQTT);
        relay1Estado = LOW;
        ConfiguracionGuardarRelays();
    }
    if(jsonDoc["RELAY2"] == "on"){
        EncendidoSimple(LEDMQTT);
        relay2Estado = HIGH;
        ConfiguracionGuardarRelays();
    }
    else if(jsonDoc["RELAY2"] == "off"){
        ApagadoSimple(LEDMQTT);
        relay2Estado = LOW;
        ConfiguracionGuardarRelays();
    }
    GenerarLog("Tópico: " + topicoCadena,0);
    GenerarLog("Mensaje: " + mensaje,0);
}

void PublicarMQTT(){
    String topicoAux = String(mqttUsuario) + "/" + mqttId + "/values";
    mqttDatos = Json();
    mqttcliente.publish(topicoAux.c_str(),mqttDatos.c_str());
    mqttDatos = "";
    TxMQTT();
}

String Json(){
    String respuesta;
    DynamicJsonDocument jsonDoc(3000);
    jsonDoc["WFDBM"] = WiFi.status() == WL_CONNECTED ? String(WiFi.RSSI()) : F("0");
    jsonDoc["WFPRC"] = WiFi.status() == WL_CONNECTED ? String(getCalidadRSSI(WiFi.RSSI())) : F("0");
    jsonDoc["tempCPU"] = String(ValorTempCPU());
    jsonDoc["RAMD"] = String(ESP.getFreeHeap() * 100 / ESP.getHeapSize());
    jsonDoc["FLASHU"] = String(round(SPIFFS.usedBytes() * 100 / SPIFFS.totalBytes()),0);
    //jsonDoc["relay1"] = String(estadoRelay1) ? "true" : "false";
    //jsonDoc["relay2"] = String(estadoRelay2) ? "true" : "false";

    serializeJson(jsonDoc, respuesta);
    return respuesta;
}

void LoopMQTT(){
    if(mqttHabilitado){
        if(mqttcliente.connected()){
            long ahora = millis();
            if((ahora < 60000) || ((ahora - ultimoIntentoConexionMQTT) > 120000)){
                ultimoIntentoConexionMQTT = ahora;
                if(ConectarMQTT()){
                    ultimoIntentoConexionMQTT = 0;
                }
                EncendidoSimple(LEDMQTT);
            }
        }
        else{
            mqttcliente.loop();
            ApagadoSimple(LEDMQTT);
        }
    }
}