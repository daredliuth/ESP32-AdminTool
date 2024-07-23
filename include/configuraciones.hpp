/*Definiciones*/
#define RELAY1 27 //Puerto para el relay 1.
#define RELAY2 26 //Puerto para el relay 2.
#define LEDWIFI 12 //Puerto para el LED indicador del WiFi.
#define LEDMQTT 13 //Puerto para el LED indicador del MQTT.
/*Versión del Hardware*/
#define HARDWARE "Admin ESP32 V1 00000000" //Versión del hardware.
/*Variables WiFi*/
bool wifiIpEstatica;
char wifiSsid[30];
char wifiPassword[30];
char wifiIpLocal[15];
char wifiGateway[15];
char wifiSubnet[15];
char wifiDnsPrimaria[15];
char wifiDnsSecundaria[15];
/*Variables mod AP*/
bool apModo;
char apSsid[31];
char apPassword[63];
int apCanal;
int apOculto; //Si el AP está oculto (1) o no (0).
int apNumConexiones;
/*Configuración general*/
char idDispositivo[30]; //ID del dispositivo.
int contadorReinicios; //Contador para el número de reinicios del dispositivo.
/*Otros*/
uint8_t ip[4]; //Variable auxiliar para convertir string a IP.