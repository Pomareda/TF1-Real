#pragma once
#include "Entidad.h"

using namespace System;

ref class Recurso : public Entidad
{
private:

	bool activo;
	int x, y, ancho, alto;
	int idX = 0;
	int idY = 0;

public:
	Recurso(int x, int y);
	~Recurso() {}

	void dibujar(Graphics^ g, Bitmap^ bmp, int scrollX, int scrollY);
	void moverRecurso();


	bool estaActivo() override { return activo; }

	void setActivo(bool a) { activo = a; }

	System::Drawing::Rectangle getRect() override {
		return System::Drawing::Rectangle(x + 10, y + 10, ancho - 80, alto- 80);
	}
};

inline Recurso::Recurso(int x, int y) : Entidad(x, y, 448/4, 624/6) {
	this->x = x;
	this->y = y;
	ancho = 448 / 4;
	alto = 624 / 6;
	activo = true;
	idX = 0;
	idY = 0;

}

inline void Recurso::dibujar(Graphics^ g, Bitmap^ bmp, int scrollX, int scrollY) {

	if (!activo) return;

	// Coordenadas en pantalla ajustadas por la cámara
	int pantallaX = x - scrollX;
	int pantallaY = y - scrollY;

	System::Drawing::Rectangle src = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
	System::Drawing::Rectangle dest = System::Drawing::Rectangle(pantallaX, pantallaY, ancho * 0.5, alto * 0.5);

	g->DrawImage(bmp, dest, src, GraphicsUnit::Pixel);
}

inline void Recurso::moverRecurso()
{
	if (idX < 4) { ++idX; }
	else { idX = 0; }

	if (idX == 4) { ++idY; idX = 0; }
	if (idY == 6 && idX <= 4) { idY = 0; }
	
}