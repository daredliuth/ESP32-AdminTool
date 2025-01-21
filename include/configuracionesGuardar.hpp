boolean ConfiguracionGuardarRelays(){
    StaticJsonDocument<500> jsonConfig;
    File archivo = SPIFFS.open(F("/configrelays.json"),"w+");
    if(archivo){
        jsonConfig["relay1Estado"] = relay1Estado;
        jsonConfig["relay2Estado"] = relay2Estado;
        serializeJsonPretty(jsonConfig, archivo);
        archivo.close();
        GenerarLog("Estado de los relays guardados.",0);
        return true;
    }
    else{
        GenerarLog("Falló el guardado del estado de los relays.",1);
        return false;
    }
}

boolean GuardarConfiguracionWiFi(){
    StaticJsonDocument<500> jsonConfig;
    File archivo = SPIFFS.open("/configwifi.json","w+");
    if(archivo){
        //General
        jsonConfig["idDispositivo"] = idDispositivo;
        jsonConfig["contadorReinicios"] = contadorReinicios;
        //WiFi
        jsonConfig["wifiIpEstatica"] = wifiIpEstatica;
        jsonConfig["wifiSsid"] = wifiSsid;
        jsonConfig["wifiPassword"] = wifiPassword;
        jsonConfig["WiFiIpLocal"] = wifiIpLocal;
        jsonConfig["wifiGateway"] = wifiGateway;
        jsonConfig["wifiSubnet"] = wifiSubnet;
        jsonConfig["wifiDnsPrimaria"] = wifiDnsPrimaria;
        jsonConfig["wifiDnsSecundaria"] = wifiDnsSecundaria;
        //Access point
        jsonConfig["apModo"] = apModo;
        jsonConfig["apSsid"] = apSsid;
        jsonConfig["apPassword"] = apPassword;
        jsonConfig["apCanal"] = apCanal;
        jsonConfig["apOculto"] = apOculto;
        jsonConfig["apNumConexiones"] = apNumConexiones;
        serializeJsonPretty(jsonConfig, archivo);
        archivo.close();
        GenerarLog("Configuración WiFi guardada.",0);
        return true;
    }
    else{
        GenerarLog("Falló el guardado de la configuración WiFi.",1);
        return false;
    }
}