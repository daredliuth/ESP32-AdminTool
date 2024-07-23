bool LeerConfiguracionWiFi(){
    StaticJsonDocument<500> jsonConfig;
    File file = SPIFFS.open("/ConfigWiFi.json", "r");
    
    if (deserializeJson(jsonConfig, file)){
        ReiniciarConfiguracionWifi();
        GenerarLog("Falló la lectura de la configuración WiFi, se tomarán los valores por defecto.", 1);
        return false;
    }
    else{

        strlcpy(idDispositivo, jsonConfig["idDispositivo"], sizeof(idDispositivo));
        contadorReinicios = jsonConfig["contadorReinicios"];
        wifiIpEstatica = jsonConfig["wifiIpEstatica"];
        strlcpy(wifiSsid, jsonConfig["wifiSsid"], sizeof(wifiSsid));
        strlcpy(wifiPassword, jsonConfig["wifiPassword"], sizeof(wifiPassword));
        strlcpy(wifiIpLocal, jsonConfig["wifiIpLocal"], sizeof(wifiIpLocal));
        strlcpy(wifiGateway, jsonConfig["wifiGateway"], sizeof(wifiGateway));
        strlcpy(wifiSubnet, jsonConfig["wifiSubnet"], sizeof(wifiSubnet));
        strlcpy(wifiDnsPrimaria, jsonConfig["wifiDnsPrimaria"], sizeof(wifiDnsPrimaria));
        strlcpy(wifiDnsSecundaria, jsonConfig["wifiDnsSecundaria"], sizeof(wifiDnsSecundaria));

        apModo = jsonConfig["apModo"];
        strlcpy(apSsid, jsonConfig["apSsid"], sizeof(apSsid));
        strlcpy(apPassword, jsonConfig["apPassword"], sizeof(apPassword));
        apCanal = jsonConfig["apCanal"];
        apOculto = jsonConfig["apOculto"];
        apNumConexiones = jsonConfig["apNumConexiones"];
        file.close();
        GenerarLog("Lectura de configuración WiFi correcta.", 0);

        return true;
    }
}