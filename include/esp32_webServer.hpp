void HandleHome(AsyncWebServerRequest *peticion){
    AsyncResponseStream *respuesta;

    File archivo = SPIFFS.open(F("/index.html"), "r");

    if(archivo){
        archivo.setTimeout(100);
        String s = archivo.readString();
        archivo.close();

        s.replace(F("#idDispositivo#"), idDispositivo);
        s.replace(F("#dispositivo_id#"), dispositivo_id);
        /* Bloque Inalámbrico */
        s.replace(F("#wifi_status#"), WiFi.status() == WL_CONNECTED ? F("<span class='label label-success'>CONECTADO</span>") : F("<span class='label label-danger'>DESCONECTADO</span>"));
        s.replace(F("#wifiSsid#"), WiFi.status() == WL_CONNECTED ? F(wifiSsid) : F("WiFi not connected"));
        s.replace(F("#wifi_ip#"),  IpCadena(WiFi.status() == WL_CONNECTED ? WiFi.localIP() : WiFi.softAPIP()));
        s.replace(F("#wifi_mac#"), String(WiFi.macAddress()));
        s.replace(F("#wifi_dbm#"), WiFi.status() == WL_CONNECTED ? String(WiFi.RSSI()) : F("0"));
        s.replace(F("#wifi_percent#"), WiFi.status() == WL_CONNECTED ? String(getCalidadRSSI(WiFi.RSSI())) : F("0"));
        /* Bloque MQTT */
        s.replace(F("#mqtt_status#"), mqttcliente.connected() ? F("<span class='label label-success'>CONECTADO</span>") : F("<span class='label label-danger'>DESCONECTADO</span>"));
        s.replace(F("#mqttServidor#"), mqttcliente.connected() ? F(mqttServidor) : F("server not connected"));
        s.replace(F("#mqttUsuario#"), F(mqttUsuario));
        s.replace(F("#mqttId#"), F(mqttId));
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
        s.replace(F("#contadorReinicios#"), String(contadorReinicios));
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

    servidor.serveStatic("/www/css/error.css",SPIFFS,"/www/css/error.css").setDefaultFile("/www/css/error.css").setCacheControl("max-age=600");
    /*Carga de archivos WiFi*/
    servidor.on("/",HTTP_GET,HandleHome);
    servidor.on("/esp-wifi", HTTP_GET,[](AsyncWebServerRequest *peticion){
        File archivo = SPIFFS.open(F("wifi.html"),"r");
        if(archivo){
            archivo.setTimeout(100);
            String s = archivo.readString();
            archivo.close();

            s.replace(F("#platform#"), Plataforma());
            s.replace(F("#wifiSsid#"), wifiSsid);
            s.replace(F("#wifiIpEstatica#"),wifiIpEstatica ? "Checked" : "");
            s.replace(F("#wifiIpLocal#"),IpCadena(IpChar(wifiIpLocal)));
            s.replace(F("#wifiSubnet#"),IpCadena(IpChar(wifiSubnet)));
            s.replace(F("#wifiGateway#"),IpCadena(IpChar(wifiGateway)));
            s.replace(F("#wifiDnsPrimaria#"),IpCadena(IpChar(wifiDnsPrimaria)));
            s.replace(F("#wifiDnsSecundaria#"),IpCadena(IpChar(wifiDnsSecundaria)));

            s.replace(F("#apModo#"),apModo ? "CHecked" : "");
            s.replace(F("#apSsid#"),String(apSsid));
            s.replace(F("#apCanal#"),String(apCanal));
            s.replace(F("#apOculto#"),apOculto ? "Checked" : "");
            s.replace(F("#apNumConexiones#"),String(apNumConexiones));
            peticion->send(200,"text/html",s);
        }
        else{
            peticion->send(500,"text/plain","wifi.html no encontrado, ¿Ha flasheado los SPIFFS?");
        }
    });
    /*Carga de archivos MQTT*/
    servidor.on("/esp-mqtt", HTTP_GET,[](AsyncWebServerRequest *peticion){
        File archivo = SPIFFS.open(F("mqtt.html"),"r");
        if(archivo){
            archivo.setTimeout(100);
            String s = archivo.readString();
            archivo.close();

            s.replace(F("#platform#"), Plataforma());
            s.replace(F("#mqttHabilitado#"), mqttHabilitado ? "Checked" : "");
            s.replace(F("#mqttId#"),mqttId);
            s.replace(F("#mqttUsuario#"),mqttUsuario);
            s.replace(F("#mqttServidor#"),mqttServidor);
            s.replace(F("#mqttPuerto#"),String(mqttPuerto));
            s.replace(F("#mqttTiempo#"),String(mqttTiempo/60000));

            peticion->send(200,"text/html",s);
        }
        else{
            peticion->send(500,"text/plain","mqtt.html no encontrado, ¿Ha flasheado los SPIFFS?");
        }
    });

    /*Carga de archivos device.*/
    servidor.on("/esp-device", HTTP_GET,[](AsyncWebServerRequest *peticion){
        File archivo = SPIFFS.open(F("device.html"),"r");
        if(archivo){
            archivo.setTimeout(100);
            String s = archivo.readString();
            archivo.close();

            s.replace(F("#platform#"), Plataforma());
            s.replace(F("#idDispositivo#"), idDispositivo);
            s.replace(F("#dispositivo_id#"), dispositivo_id);

            peticion->send(200,"text/html",s);
        }
        else{
            peticion->send(500,"text/plain","device.html no encontrado, ¿Ha flasheado los SPIFFS?");
        }
    });

    /*Carga de archivos restore.*/
    servidor.on("/esp-restore", HTTP_GET,[](AsyncWebServerRequest *peticion){
        File archivo = SPIFFS.open(F("restore.html"),"r");
        if(archivo){
            archivo.setTimeout(100);
            String s = archivo.readString();
            archivo.close();

            s.replace(F("#platform#"), Plataforma());

            peticion->send(200,"text/html",s);
        }
        else{
            peticion->send(500,"text/plain","restore.html no encontrado, ¿Ha flasheado los SPIFFS?");
        }
    });

    /*Carga de archivos restart.*/
    servidor.on("/esp-restart", HTTP_GET,[](AsyncWebServerRequest *peticion){
        File archivo = SPIFFS.open(F("restart.html"),"r");
        if(archivo){
            archivo.setTimeout(100);
            String s = archivo.readString();
            archivo.close();

            s.replace(F("#platform#"), Plataforma());

            peticion->send(200,"text/html",s);
        }
        else{
            peticion->send(500,"text/plain","restart.html no encontrado, ¿Ha flasheado los SPIFFS?");
        }
    });

    /*Carga de archivos admin*/
    servidor.on("/esp-admin", HTTP_GET,[](AsyncWebServerRequest *peticion){
        File archivo = SPIFFS.open(F("admin.html"),"r");
        if(archivo){
            archivo.setTimeout(100);
            String s = archivo.readString();
            archivo.close();

            s.replace(F("#platform#"), Plataforma());

            peticion->send(200,"text/html",s);
        }
        else{
            peticion->send(500,"text/plain","admin.html no encontrado, ¿Ha flasheado los SPIFFS?");
        }
    });

    /*Carga de arcchivos error*/
    servidor.onNotFound([](AsyncWebServerRequest *peticion){
        File archivo = SPIFFS.open(F("error.html"),"r");
        if(archivo){
            archivo.setTimeout(100);
            String s = archivo.readString();
            archivo.close();

            peticion->send(404,"text/html",s);
        }
    });

    /*Inicializar servidor web*/
    servidor.begin();
    GenerarLog("Servidor HTTP iniciado.",0);
}