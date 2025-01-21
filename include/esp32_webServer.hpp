
void HandleHome(AsyncWebServerRequest *peticion){
    AsyncResponseStream *respuesta;

    File file = SPIFFS.open(F("/index.html"), "r");

    if(file){
        file.setTimeout(100);
        String s = file.readString();
        file.close();

        s.replace(F("#id#"), idDispositivo);
        s.replace(F("#serie#"), dispositivo_id);
        /* Bloque Inalámbrico */
        s.replace(F("#wifi_status#"), WiFi.status() == WL_CONNECTED ? F("<span class='label label-success'>CONECTADO</span>") : F("<span class='label label-danger'>DESCONECTADO</span>"));
        s.replace(F("#wifi_ssid#"), WiFi.status() == WL_CONNECTED ? F(wifiSsid) : F("WiFi not connected"));
        s.replace(F("#wifi_ip#"),  IpCadena(WiFi.status() == WL_CONNECTED ? WiFi.localIP() : WiFi.softAPIP()));
        s.replace(F("#wifi_mac#"), String(WiFi.macAddress()));
        s.replace(F("#wifi_dbm#"), WiFi.status() == WL_CONNECTED ? String(WiFi.RSSI()) : F("0"));
        s.replace(F("#wifi_percent#"), WiFi.status() == WL_CONNECTED ? String(getCalidadRSSI(WiFi.RSSI())) : F("0"));
        /* Bloque MQTT */
        s.replace(F("#mqtt_status#"), mqttcliente.connected() ? F("<span class='label label-success'>CONECTADO</span>") : F("<span class='label label-danger'>DESCONECTADO</span>"));
        s.replace(F("#mqtt_server#"), mqttcliente.connected() ? F(mqttServidor) : F("server not connected"));
        s.replace(F("#mqtt_user#"), F(mqttUsuario));
        s.replace(F("#mqtt_id#"), F(mqttId));
        /* Bloque Información */
        s.replace(F("#clientIP#"),IpCadena(peticion->client()->remoteIP()));
        s.replace(F("#userAgent#"), peticion->getHeader("User-Agent")->value().c_str());
        s.replace(F("#firmware#"), firmwareActual);
        s.replace(F("#sdk#"), String(ESP.getSdkVersion()));
        s.replace(F("#hardware#"), F(HARDWARE));
        s.replace(F("#cpu_freq#"), String(getCpuFrequencyMhz()));
        s.replace(F("#flash_size#"), String(ESP.getFlashChipSize() / (1024.0 * 1024), 2));
        s.replace(F("#ram_size#"), String(ESP.getHeapSize() / 1024.0, 2));
        s.replace(F("#time_active#"), CadenaTiempoLargo(millis() / 1000));
        s.replace(F("#bootCount#"), String(contadorReinicios));
        /* Bloque General */
        s.replace(F("#platform#"), Plataforma());
        s.replace(F("#mqtt_on#"), mqttcliente.connected() ? F("<span class='label btn-metis-2'>Online</span>") : F("<span class='label label-danger'>Offline</span>"));
        s.replace(F("#temp_cpu#"), String(ValorTempCPU()));
        /* Bloque Progressbar */
        s.replace(F("#flash_available#"), String(round(SPIFFS.usedBytes() * 100 / SPIFFS.totalBytes()), 0));
        s.replace(F("#ram_available#"), String(ESP.getFreeHeap() * 100 / ESP.getHeapSize()));
        /* Botones Relays */
        s.replace(F("#relay1#"), relay1Estado ? "checked" : "");
        s.replace(F("#relay2#"), relay2Estado ? "checked" : "");
        s.replace(F("#label1#"), relay1Estado ? "label-primary" : "label-info");
        s.replace(F("#label2#"), relay2Estado ? "label-primary" : "label-info");
        s.replace(F("#Statustext1#"), relay1Estado ? "Activo" : "Apagado");
        s.replace(F("#Statustext2#"), relay2Estado ? "Activo" : "Apagado");
        // Send Data
        peticion->send(200, "text/html", s);
    }
    else{
        peticion->send(500,"text/plain","index.html no encontrado, ¿Ha flasheado los SPIFFS?");
    }
}

void IniciarServidor(){
    /*Carga de archivos estáticos*/
    servidor.serveStatic("/www/plugins/bootstrap.css",SPIFFS,"/www/pluginsbootstrap-switch.css").setDefaultFile("/www/plugins/bootstrap.css").setCacheControl("max-age=600");
    servidor.serveStatic("/www/plugins/bootstrap.min.js",SPIFFS,"/www/plugins/bootstrap.min.js").setDefaultFile("/www/plugins/bootstrap.min.js").setCacheControl("max-age=600");

    servidor.serveStatic("/www/bootstrap-switch.css",SPIFFS,"/www/bootstrap-switch.css").setDefaultFile("/www/bootstrap-switch.css").setCacheControl("max-age=600");
    servidor.serveStatic("/www/bootstrap-switch.min.js",SPIFFS,"/www/bootstrap-switch.min.js").setDefaultFile("/www/bootstrap-switch.min.js").setCacheControl("max-age=600");

    servidor.serveStatic("/www/img/logo.png",SPIFFS,"/www/img/logo.png").setDefaultFile("/www/img/logo.png").setCacheControl("max-age=600");

    servidor.serveStatic("/www/css/font-awesome.css",SPIFFS,"/www/css/font-awesome.css").setDefaultFile("/www/css/font-awesome.css").setCacheControl("max-age=600");
    servidor.serveStatic("/www/fontawesome-webfont.eot",SPIFFS,"/www/fontawesome-webfont.eot").setDefaultFile("/www/fontawesome-webfont.eot").setCacheControl("max-age=600");
    servidor.serveStatic("/www/fontawesome-webfont.svg",SPIFFS,"/www/fontawesome-webfont.svg").setDefaultFile("/www/fontawesome-webfont.svg").setCacheControl("max-age=600");
    servidor.serveStatic("/www/fontawesome-webfont.ttf",SPIFFS,"/www/fontawesome-webfont.ttf").setDefaultFile("/www/fontawesome-webfont.ttf").setCacheControl("max-age=600");
    servidor.serveStatic("/www/fontawesome-webfont.woff",SPIFFS,"/www/fontawesome-webfont.woff").setDefaultFile("/www/fontawesome-webfont.woff").setCacheControl("max-age=600");
    servidor.serveStatic("/www/FontAwesome.otf",SPIFFS,"/www/FontAwesome.otf").setDefaultFile("/www/FontAwesome.otf").setCacheControl("max-age=600");

    servidor.serveStatic("/www/plugins/jquery.min.js",SPIFFS,"/www/plugins/jquery.min.js").setDefaultFile("/www/plugins/jquery.min.js").setCacheControl("max-age=600");

    servidor.serveStatic("/www/css/layout2.css",SPIFFS,"/www/css/layout2.css").setDefaultFile("/www/css/layout2.css").setCacheControl("max-age=600");

    servidor.serveStatic("/www/img/user.gif",SPIFFS,"/www/img/user.gif").setDefaultFile("/www/img/user.gif").setCacheControl("max-age=600");

    servidor.serveStatic("/www/css/main.css",SPIFFS,"/www/css/main.css").setDefaultFile("/www/css/main.css").setCacheControl("max-age=600");

    servidor.serveStatic("/www/plugins/modernizr.min.js",SPIFFS,"/www/plugins/modernizr.min.js").setDefaultFile("/www/plugins/modernizr.min.js").setCacheControl("max-age=600");

    servidor.serveStatic("/www/css/MoneAdmin.css",SPIFFS,"/www/css/MoneAdmin.css").setDefaultFile("/www/css/MoneAdmin.css").setCacheControl("max-age=600");

    servidor.serveStatic("/www/plugins/scripts.js",SPIFFS,"/www/plugins/scripts.js").setDefaultFile("/www/plugins/scripts.js").setCacheControl("max-age=600");

    servidor.serveStatic("/www/css/styles.css",SPIFFS,"/www/css/styles.css").setDefaultFile("/www/css/styles.css").setCacheControl("max-age=600");

    servidor.serveStatic("/www/css/theme.css",SPIFFS,"/www/css/theme.css").setDefaultFile("/www/css/theme.css").setCacheControl("max-age=600");

    /*Carga de archivos HTML*/
    servidor.on("/",HTTP_GET,HandleHome);

    /*Inicializar servidor web*/
    servidor.begin();
    GenerarLog("Servidor HTTP iniciado.",0);
}