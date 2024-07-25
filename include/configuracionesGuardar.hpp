boolean ConfiguracionGuardarRelays(){
    StaticJsonDocument<500> jsonConfig;
    File file = SPIFFS.open(F("/configrelays.json"),"w+");
    if(file){
        jsonConfig["relay1Estado"] = relay1Estado;
        jsonConfig["relay2Estado"] = relay2Estado;
        serializeJsonPretty(jsonConfig, file);
        file.close();
        GenerarLog("Estado de los relays guardados.",0);
        return true;
    }
    else{
        GenerarLog("Falló el guardado del estado de los relays.",1);
        return false;
    }
}