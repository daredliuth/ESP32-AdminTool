/*Definiciones*/
#define RELAY1 27 //Puerto para el relay 1.
#define RELAY2 26 //Puerto para el relay 2.
#define LEDWIFI 12 //Puerto para el LED indicador del WiFi.
#define LEDMQTT 13 //Puerto para el LED indicador del MQTT.
/*Capacidad de los JSON*/
const size_t capacidadWiFi = JSON_OBJECT_SIZE(16)+301;
const size_t capacidadMqtt = JSON_OBJECT_SIZE(7)+117;
const size_t capacidadRelays = JSON_OBJECT_SIZE(2)+30;
/*Versión del Firmware*/
#define TEXTIFY(A) #A
#define ESCAPEQUOTE(A) TEXTIFY(A)
String firmwareActual = ESCAPEQUOTE(BUILD_TAG);
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
/*Variables MQTT*/
boolean mqttHabilitado;
char mqttUsuario[30];
char mqttId[30];
char mqttPassword[30];
char mqttServidor[39];
int mqttPuerto;
int mqttTiempo;
/*Configuración general*/
char idDispositivo[30]; //ID del dispositivo.
int contadorReinicios; //Contador para el número de reinicios del dispositivo.
/*Otros*/
uint8_t ip[4]; //Variable auxiliar para convertir string a IP.
float tempCPU; //Variable para almacenar la temperatura del CPU.
long ultimoMensaje = 0;
/*Relays*/
bool relay1Estado, relay2Estado; //Estado (Encendido/Apagado) de los relays.