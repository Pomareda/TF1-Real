#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include "Entidad.h"  

using namespace System::Drawing;
using namespace System;
using namespace std;

ref class Jugador : public Entidad {
protected:
    int confianza;
	int opc; //1 humano, 2 IA. Dfine bmp a dibujar
	Direcciones Ultima;
	Direcciones Direccion;

public:
	Jugador(int x, int y, int ancho, int alto);
    ~Jugador();

    void mover(Graphics^ g);
	void dibujar(Graphics^ g, Bitmap^ bmp, int scrollY, int scrollX);
   /* void mostrarConfianza();

    bool colision_mapa();
    bool colision_enemigos();
    bool colision_IAsuprema();
    bool colisiona_aliado();*/

	System::Drawing::Rectangle getRect() override;

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
	confianza = 0;
	opc = 1; 
	Ultima = Direcciones::Abajo;
	Direccion = Direcciones::Ninguna;
}

inline Jugador::~Jugador() {}

inline void Jugador::dibujar(Graphics^ g, Bitmap^ bmp, int scrollY, int scrollX) {
	//Si se va hacer con opcion, faltaria eso aqui

	/*System::Drawing::Rectangle  Jugador1 = System::Drawing::Rectangle(x + dx + 5, y + 22, (ancho - 15), (alto - 30));
	g->DrawRectangle(System::Drawing::Pens::Red, Jugador1);*/

	int pantallaY = y - scrollY;
	int pantallaX = x - scrollX;

	System::Drawing::Rectangle sectionShow = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
	System::Drawing::Rectangle zoom = System::Drawing::Rectangle(pantallaX, pantallaY, ancho * 0.85, alto * 0.85);
	g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);

}

inline void Jugador::mover(Graphics^ g) {
	int X = 0, Y = 0;
	switch (Direccion)
	{
	case Direcciones::Abajo:
		idY = 0;  // Fila 0 - mirando abajo
		if (idX >= 0 && idX < 5)
			++idX;
		else
			idX = 0;
		dx = 0;
		dy = 20;
		Ultima = Abajo;
		break;
	case Direcciones::Arriba:
		idY = 2;  // Fila 2 - mirando arriba
		if (idX >= 0 && idX < 5)
			++idX;
		else
			idX = 0;
		dx = 0;
		dy = -20;
		Ultima = Arriba;
		break;
	case Direcciones::Derecha:
		idY = 1;  // Fila 1 - derecha mirando abajo
		if (idX >= 0 && idX < 5)
			++idX;
		else
			idX = 0;
		dx = 20;
		dy = 0;
		Ultima = Derecha;
		break;
	case Direcciones::Izquierda:
		idY = 4;  // Fila 4 - izquierda mirando abajo
		if (idX >= 0 && idX < 5)
			++idX;
		else
			idX = 0;
		dx = -20;
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
	//System::Drawing::Rectangle  Jugador2 = System::Drawing::Rectangle(x + 5, y + 22 + dy, (ancho - 15), (alto - 30));
	//g->DrawRectangle(System::Drawing::Pens::Blue, Jugador2);
	
	x += dx;
	y += dy;
}

inline System::Drawing::Rectangle Jugador::getRect() {
	return System::Drawing::Rectangle(x, y , ancho *0.85 , alto * 0.85);
}