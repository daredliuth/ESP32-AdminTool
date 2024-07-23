#include <Arduino.h>

bool ioParpadeo = false;
unsigned long milisAnterior;
int rndTmp = 0;

void ParpadeoSimple(int velocidad, int pin){
    if((milisAnterior + velocidad) < millis()){
        milisAnterior = millis();
        digitalWrite(pin,HIGH);
        ioParpadeo = true;
    }
    else{
        digitalWrite(pin,LOW);
        ioParpadeo = false;
    }
}

void ParpadeoSimpleAsincrono(int tiempoHigh, int tiempoLow, int pin){
    if(ioParpadeo == false){
        if((milisAnterior + tiempoHigh) < millis()){
            milisAnterior = millis();
            digitalWrite(pin, LOW);
            ioParpadeo = true;
        }
    }
    else{
        if((milisAnterior + tiempoLow) < millis()){
            milisAnterior = millis();
            digitalWrite(pin, HIGH);
            ioParpadeo = false;
        }
    }
}

void ParpadeoSimpleAleatorio(int tiempoMin, int tiempoMax, int pin){
    if((milisAnterior + rndTmp) < millis()){
        milisAnterior = millis();
        rndTmp = random(tiempoMin,tiempoMax);
        if(ioParpadeo == false){
            digitalWrite(pin, HIGH);
            ioParpadeo = true;
        }
        else{
            digitalWrite(pin,LOW);
            ioParpadeo = false;
        }
    }
}

void EncendidoSimple(int pin){
    digitalWrite(pin, HIGH);
}

void ApagadoSimple(int pin){
    digitalWrite(pin, LOW);
}