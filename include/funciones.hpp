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