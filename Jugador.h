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
	bool izq, der, arr,abajo;
	Direcciones Ultima;
	Direcciones Direccion;
	int contadorAnimacion;  
	int velocidadAnimacion;

public:
	Jugador(int x, int y, int ancho, int alto);
    ~Jugador();

    void mover(Graphics^ g, int an, int al);
	void dibujar(Graphics^ g, Bitmap^ bmp, int scrollY, int scrollX);

	void dibujarNpcHumano(Graphics^ g, Bitmap^ bmp, int scrollY);
	System::Drawing::Rectangle getRect() override;
	System::Drawing::Rectangle getRectNpcHumano() ;

    int getConfianza() { return confianza; };

    int getAncho() { return ancho; };
    int getAlto() { return alto; };

	void setIzquierda(bool v) { izq = v; }
	void setDerecha(bool v) { der = v; }
	void setArriba(bool v) { arr = v; }
	void setAbajo(bool v) { abajo = v; }

	void setY(int nuevaY) { y = nuevaY; }
	void setX(int nuevaX) { x = nuevaX; }

	int getY() { return y; }
	int getX() { return x; }

	bool getIzquierda() { return izq; }
	bool getDerecha() { return der; }
	

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
	izq = der = arr = abajo = false;
	contadorAnimacion = 0;
	velocidadAnimacion = 3;
}

inline Jugador::~Jugador() {}

inline void Jugador::dibujar(Graphics^ g, Bitmap^ bmp, int scrollY, int scrollX) {
	//Si se va hacer con opcion, faltaria eso aqui

	// System::Drawing::Rectangle  Jugador1 = System::Drawing::Rectangle(x + dx + 5, y + 22, (ancho - 15), (alto - 30));
	// g->DrawRectangle(System::Drawing::Pens::Red, Jugador1);

	int pantallaY = y - scrollY;
	int pantallaX = x - scrollX;

	System::Drawing::Rectangle sectionShow = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
	System::Drawing::Rectangle zoom = System::Drawing::Rectangle(pantallaX, pantallaY, ancho * 1.3 , alto * 1.3);
	g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);

}

inline void Jugador::mover(Graphics^ g, int an, int al) {


	bool seMovio = false;

	if (izq && x > 0) {
		x -= dx;
		idY = 4;
		Ultima = Izquierda;
		seMovio = true;
	}
	if (der && x + ancho * 1.3 < an) {
		x += dx;
		idY = 1;
		Ultima = Derecha;
		seMovio = true;
	}

	if (arr && y > 0) {
		y -= dy;
		if (!izq && !der) {
			idY = 2;
			Ultima = Arriba;
		}
		seMovio = true;
	}
	if (abajo && y + alto * 1.3 < al) {
		y += dy;
		if (!izq && !der) {
			idY = 0;
			Ultima = Abajo;
		}
		seMovio = true;
	}

	if (seMovio) {
		contadorAnimacion++;
		if (contadorAnimacion >= velocidadAnimacion) {
			contadorAnimacion = 0;
			idX++;
			if (idX > 5) idX = 0;
		}
	}
	else {
		contadorAnimacion = 0;
		idX = 0; 
	}
}

inline void Jugador::dibujarNpcHumano(Graphics^ g, Bitmap^ bmp, int scrollY)
{
	idY = 1;
	int pantallaY = y - scrollY;


	System::Drawing::Rectangle src = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
	System::Drawing::Rectangle dest = System::Drawing::Rectangle(x, pantallaY, ancho * 0.5, alto * 0.5);

	g->DrawImage(bmp, dest, src, GraphicsUnit::Pixel);

	contadorAnimacion++;
	if (contadorAnimacion >= velocidadAnimacion) {
		contadorAnimacion = 0;
		idX++;
		if (idX >= 4) idX = 0;
	}

}

inline System::Drawing::Rectangle Jugador::getRect() {
	return System::Drawing::Rectangle(x, y , ancho *1.3 , alto * 1.3);
}

inline System::Drawing::Rectangle Jugador::getRectNpcHumano()
{
	return System::Drawing::Rectangle(x, y, ancho * 0.5, alto * 0.5);
}
