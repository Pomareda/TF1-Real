#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include "Entidad.h"  

using namespace System::Drawing;
using namespace System;
using namespace std;

class Jugador : public Entidad {
protected:
    int confianza;
	int opc; //1 humano, 2 IA. Dfine bmp a dibujar
	Direcciones Ultima;
	Direcciones Direccion;

public:
	Jugador(int x, int y, int ancho, int alto);
    ~Jugador();

    void mover();
	void dibujar(Graphics^ g, Bitmap^ bmp);
    void mostrarConfianza();

    bool colision_mapa();
    bool colision_enemigos();
    bool colision_IAsuprema();
    bool colisiona_aliado();

    int getConfianza() { return confianza; };

    int getAncho() { return ancho; };
    int getAlto() { return alto; };

    void setConfianza(int p) { confianza = p; };

	void setDireccion(Direcciones d) { Direccion = d; }

	Direcciones getUltima() { return Ultima; }

	void SetDx(int newvalor) { dx = newvalor; }
	void SetDy(int newvalor) { dy = newvalor; }
	void SetX(int newX) { x = newX; }
	void SetY(int newY) { y = newY; }
};

inline Jugador::Jugador(int x, int y, int ancho, int alto) : Entidad(x, y, ancho, alto) {
	confianza = 100;
	opc = 1; 
	Ultima = Direcciones::Abajo;
	Direccion = Direcciones::Ninguna;
}

inline Jugador::~Jugador() {}

inline void Jugador::mover() {
	switch (Direccion)
	{
	case Direcciones::Abajo:
		idY = 0;  // Fila 0 - mirando abajo
		if (idX >= 0 && idX < 5)
			++idX;
		else
			idX = 0;
		dx = 0;
		dy = 10;
		Ultima = Abajo;
		break;
	case Direcciones::Arriba:
		idY = 2;  // Fila 2 - mirando arriba
		if (idX >= 0 && idX < 5)
			++idX;
		else
			idX = 0;
		dx = 0;
		dy = -10;
		Ultima = Arriba;
		break;
	case Direcciones::Derecha:
		idY = 1;  // Fila 1 - derecha mirando abajo
		if (idX >= 0 && idX < 5)
			++idX;
		else
			idX = 0;
		dx = 10;
		dy = 0;
		Ultima = Derecha;
		break;
	case Direcciones::Izquierda:
		idY = 4;  // Fila 4 - izquierda mirando abajo
		if (idX >= 0 && idX < 5)
			++idX;
		else
			idX = 0;
		dx = -10;
		dy = 0;
		Ultima = Izquierda;
		break;
	case Direcciones::Ninguna:
		dx = dy = 0;
		switch (Ultima)
		{
		case Direcciones::Abajo:
			idY = 0;
			idX = 0;
			break;
		case Direcciones::Arriba:
			idY = 2;
			idX = 0;
			break;
		case Direcciones::Derecha:
			idY = 1;
			idX = 0;
			break;
		case Direcciones::Izquierda:
			idY = 4;
			idX = 0;
			break;
		default:
			break;
		}
		break;
	}
	x += dx;
	y += dy;
}

inline void Jugador::dibujar(Graphics^ g, Bitmap^ bmp) {
	//Si se va hacer con opcion, faltaria eso aqui
	System::Drawing::Rectangle  Jugador1 = System::Drawing::Rectangle(x + 2+ dx, y + 12, (ancho - 7), (alto - 13));
	g->DrawRectangle(System::Drawing::Pens::Red, Jugador1);

	System::Drawing::Rectangle sectionShow = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
	System::Drawing::Rectangle zoom = System::Drawing::Rectangle(x , y, ancho * 1.0, alto * 1.0);
	g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);

}