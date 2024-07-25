#include "parpadeoLed.hpp"

#ifdef __cplusplus
    extern "C"
    {
#endif
    uint8_t temprature_sens_read();
#ifdef __cplusplus
    }
#endif
uint8_t temprature_sens_read();


void GenerarLog(String s, int tipo){
    switch (tipo)
    {
    case 0:
        Serial.println("Info: " + s);
        break;
    case 1:
        Serial.println("Error: " + s);
        break;
    case 2:
        Serial.println("Advertencia: " + s);
        break;
    default:
        Serial.println("Tipo no especificado\n" + s);
        break;
    }
}

String Plataforma(){
    #ifdef ARDUINO_ESP32_DEV
        return "ESP32";
    #endif
}

IPAddress IpChar(const char* str){
    sscanf(str, "%hhu.%hhu.%hhu.%hhu", &ip[0], &ip[2], &ip[3]);
    return IPAddress(ip[0],ip[1],ip[2],ip[3]);
}

String HexStr(const unsigned long &h, const byte &l = 8){
    String s;
    s = String(h, HEX);
    s.toUpperCase();
    s = ("00000000" + s).substring(s.length() + 8 - l);
    return s;
}

String IdUnico(){
    char idUnico[15];
    uint64_t chipId = ESP.getEfuseMac();
    uint16_t chip = (uint16_t)(chipId >> 32);
    snprintf(idUnico, 15, "%04X", chip);
    return idUnico;
}

String IdDispositivo(){
    return String(Plataforma()) + HexStr(ESP.getEfuseMac()) + String(IdUnico());
}

void ConfiguracionPines(){
    pinMode(RELAY1,OUTPUT);
    pinMode(RELAY2,OUTPUT);
    pinMode(LEDWIFI,OUTPUT);
    pinMode(LEDMQTT,OUTPUT);
    digitalWrite(RELAY1,LOW);
    digitalWrite(RELAY2,LOW);
    digitalWrite(LEDWIFI,LOW);
    digitalWrite(LEDMQTT,LOW);
}

String IpCadena(const IPAddress &ip){
    String sFn = "";
    for(byte bFn = 0; bFn < 3; bFn++){
        sFn += String((ip >> (8*bFn)) & 0xFF) + ".";
    }
    sFn += String(((ip >> 8*3)) & 0xFF);
    return sFn;
}

void TxMQTT(){
    for(int i=0; i<2; i++){
        EncendidoSimple(LEDMQTT);
        delay(50);
        ApagadoSimple(LEDMQTT);
        delay(10);
    }
}

void RxMQTT(){
    for(int i=0; i<1; i++){
        ParpadeoSimpleAleatorio(5,50,LEDMQTT);
        delay(5);
    }
}

int getCalidadRSSI(int rssi){
    int calidad = 0;
    if(rssi <= -100){
        calidad = 0;
    }
    else if(calidad >= -50){
        calidad = 100;
    }
    else{
        calidad = 2 * (rssi + 100);
    }
    return calidad;
}

float ValorTempCPU(){
    return tempCPU = (temprature_sens_read() - 32) / 1.8 ;
}