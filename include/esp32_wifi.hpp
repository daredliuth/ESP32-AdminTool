#include <WiFi.h>
#include <DNSServer.h>
#include <ESPmDNS.h>

const byte  DNSSERVER_PORT = 53;
DNSServer dnsServer;

IPAddress apIp(192,168,4,1);
IPAddress netMask(255,255,255,0);

int wifiModo = WIFI_STA;

const char* espHostname = idDispositivo;

unsigned long milisPreviosWifi = 0;
unsigned long intervaloWifi = 30000;


void IniciarAP(){
    GenerarLog("Iniciando modo AP.", 0);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    WiFi.softAPConfig(apIp, apIp, netMask);
    WiFi.setHostname(IdDispositivo().c_str());
    WiFi.softAP(apSsid, apPassword, apCanal, apOculto, apNumConexiones);
    GenerarLog("WiFi " + IdDispositivo() + " - IP " + IpCadena(WiFi.softAPIP()) ,0);
    dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    dnsServer.start(DNSSERVER_PORT, "*", apIp);
    wifiModo = WIFI_AP;
}

void IniciarCliente(){
    if(wifiIpEstatica){
        if(!WiFi.config(IpChar(wifiIpLocal), IpChar(wifiGateway), IpChar(wifiSubnet), IpChar(wifiDnsPrimaria), IpChar(wifiDnsSecundaria))){
            GenerarLog("Fallo al conectar en modo estación.",1);
        }
    }
    WiFi.hostname(IdDispositivo());
    WiFi.begin(wifiSsid, wifiPassword);
    GenerarLog("Conectando a la red WiFi: " + String(wifiSsid),0);
    delay(50);
    byte b = 0;
    while (WiFi.status() != WL_CONNECTED && b<60){
        b++;
        GenerarLog("Intentando conexión WiFi.",2);
        delay(500);
        ParpadeoSimple(100,LEDWIFI);
    }
    if(WiFi.status() == WL_CONNECTED){
        GenerarLog("WiFi conectado (" + String(WiFi.RSSI()) + "IP: " + IpCadena(WiFi.localIP()),0);
        ParpadeoSimpleAleatorio(10, 100, LEDWIFI);
        delay(100);
    }
    else{
        GenerarLog("WiFi no conectado.",1);
        ParpadeoSimpleAleatorio(10, 100, LEDWIFI);
        delay(100);
    }
    if(wifiModo == WIFI_STA || wifiModo == WIFI_AP){
        if(MDNS.begin(espHostname)){
            MDNS.addService("http","tcp",80);
        }
    }
}

void WiFiSetup(){
    WiFi.disconnect();
    if(apModo){
        IniciarAP();
        GenerarLog("Modo WiFi AP.",0);
    }
    else{
        WiFi.mode(WIFI_STA);
        wifiModo = WIFI_STA;
        IniciarCliente();
        GenerarLog("Modo estación.",0);
    }
}

void WifiLoop(){
    unsigned long milisActuales = millis();
    if(WiFi.status() != WL_CONNECTED && (milisActuales - milisPreviosWifi >= intervaloWifi)){
        ParpadeoSimple(100, LEDWIFI);
        WiFi.disconnect();
        WiFi.reconnect();
        milisPreviosWifi = milisActuales;
    }
    else{
        ParpadeoSimpleAsincrono(10,500,LEDWIFI);
    }
}

void WifiApLoop(){
    ParpadeoSimpleAleatorio(50,10,LEDWIFI);
    dnsServer.processNextRequest();
}