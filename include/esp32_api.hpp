#include <ESPAsyncWebServer.h>

AsyncWebServer servidor(80);
AsyncWebSocket webSocket("/websocket");
AsyncEventSource eventos("/eventos");