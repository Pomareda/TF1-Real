#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include "Entidad.h"  

using namespace System;
using namespace std;

class Jugador : public Entidad {
protected:
    int confianza;
	int opc; //1 humano, 2 IA. Dfine bmp a dibujar
public:
    Jugador(int x, int y);
    ~Jugador();

    virtual void mover();

    void mostrarConfianza();

    bool colision_mapa();
    bool colision_enemigos();
    bool colision_IAsuprema();
    bool colisiona_aliado();

    virtual void dibujar() = 0;

    // Getters y setters
    int getConfianza() { return confianza; };
    int getAncho() { return ancho; };
    int getAlto() { return alto; };
    void setConfianza(int p) { confianza = p; };
};