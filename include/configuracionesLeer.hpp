bool LeerConfiguracionWiFi(){
    StaticJsonDocument<500> jsonConfig;
    File file = SPIFFS.open("/configwifi.json", "r");
    
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

boolean LeerConfiguracionMqtt(){
    StaticJsonDocument<500> jsonConfig;
    File file = SPIFFS.open("/configmqtt.json", "r");
    
    if (deserializeJson(jsonConfig, file)){
        ReiniciarConfiguracionMQTT();
        GenerarLog("Falló la lectura de la configuración MQTT, se tomarán los valores por defecto.", 1);
        return false;
    }
    else{
        strlcpy(mqttUsuario,jsonConfig["mqttUsuario"],sizeof(mqttUsuario));
        strlcpy(mqttPassword,jsonConfig["mqttPassword"],sizeof(mqttPassword));
        strlcpy(mqttServidor,jsonConfig["mqttServidor"],sizeof(mqttServidor));
        strlcpy(mqttId,jsonConfig["mqttId"],sizeof(mqttId));
        mqttTiempo = jsonConfig["mqttTiempo"];
        mqttPuerto = jsonConfig["mqttPuerto"];
        mqttHabilitado = jsonConfig["mqttHabilitado"];
        file.close();
        GenerarLog("Lectura de configuración MQTT correcta.",0);
        return true;
    }
}

boolean LeerConfiguracionRelays(){
    StaticJsonDocument<200> jsonConfig;
    File file = SPIFFS.open("/configrelays.json","r");
    if(deserializeJson(jsonConfig, file)){
        ReiniciarConfiguracionRelays();
        GenerarLog("Falló la lectura de los relays, se tomarán los valores por defecto. ",1);
        return false;
    }
    else{
        relay1Estado = jsonConfig["relay1Estado"];
        relay2Estado = jsonConfig["relay2Estado"];
        file.close();
        GenerarLog("Lectura de los relays correcta.", 0);
        return true;
    }
}