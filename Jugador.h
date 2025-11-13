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
	Direcciones Ultima;
	Direcciones Direccion;

public:
    Jugador(int x, int y, int ancho, int alto) : Entidad(x, y, ancho, alto) {
		
		Ultima = Direcciones::Abajo;
		Direccion = Direcciones::Ninguna;


	};
    ~Jugador();

    void mover(Graphics^ g, Bitmap^ bmp)override;

    void mostrarConfianza();

    bool colision_mapa();
    bool colision_enemigos();
    bool colision_IAsuprema();
    bool colisiona_aliado();

    /*virtual void dibujar() = 0;*/

    // Getters y setters
    int getConfianza() { return confianza; };
    int getAncho() { return ancho; };
    int getAlto() { return alto; };
    void setConfianza(int p) { confianza = p; };
	void setDireccion(Direcciones d) { Direccion = d; }
	Direcciones getUltima() { return Ultima; }

};


inline void Jugador::mover(Graphics^ g, Bitmap^ bmp) {
	switch (Direccion)
	{
	case Direcciones::Abajo:
		idX = 0;
		if (idY > 0 && idY < 3)
			++idY;
		else
			idY = 1;
		dx = 0;
		dy = 10;
		Ultima = Abajo;
		break;
	case Direcciones::Arriba:
		idY = 0;
		if (idX >= 0 && idX < 3)
			++idX;
		else
			idX = 0;
		dx = 0;
		dy = -10;
		Ultima = Arriba;
		break;
	case Direcciones::Derecha:
		idY = 1;
		if (idX >= 1 && idX < 3)
			++idX;
		else
			idX = 1;
		dx = 10;
		dy = 0;
		Ultima = Derecha;
		break;
	case Direcciones::Izquierda:
		idY = 3;
		if (idX >= 1 && idX < 3)
			++idX;
		else
			idX = 1;
		dx = -10;
		dy = 0;
		Ultima = Izquierda;
		break;
	case Direcciones::Ninguna:
		dx = dy = 0;
		switch (Ultima)
		{
		case Direcciones::Abajo:
			idY = 2;
			idX = 0;
			break;
		case Direcciones::Arriba:
			idY = 0;
			idX = 0;
			break;
		case Direcciones::Derecha:
			idY = 1;
			idX = 1;
			break;
		case Direcciones::Izquierda:
			idY = 3;
			idX = 1;
			break;
		default:
			break;
		}
		break;
	}

	x += dx;
	y += dy;
}