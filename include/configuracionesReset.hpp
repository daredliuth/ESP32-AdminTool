void ReiniciarConfiguracionWifi(){
    strlcpy(idDispositivo, "adminesp32", sizeof(idDispositivo));
    contadorReinicios = 0;
    wifiIpEstatica = false;
    strlcpy(wifiSsid, "CD_UNAM", sizeof(wifiSsid));
    strlcpy(wifiPassword, "MegaChidoLiro", sizeof(wifiPassword));
    strlcpy(wifiIpLocal, "192.168.100.1", sizeof(wifiIpLocal));
    strlcpy(wifiGateway, "192.168.100.1", sizeof(wifiGateway));
    strlcpy(wifiSubnet, "255.255.255.0", sizeof(wifiSubnet));
    strlcpy(wifiDnsPrimaria, "8.8.8.8", sizeof(wifiDnsPrimaria));
    strlcpy(wifiDnsSecundaria, "8.8.4.4", sizeof(wifiDnsSecundaria));

    apModo = true;
    strlcpy(apSsid, IdDispositivo().c_str(), sizeof(apSsid));
    strlcpy(apPassword, "electroniciot", sizeof(apPassword));
    apCanal = 9;
    apOculto = false;
    apNumConexiones = 4;
}