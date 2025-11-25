#pragma once
//#include "Entidad.h"

using namespace System;

ref class Recurso
{
private:

	bool activo;
	int x, y, ancho, alto;
	int idX = 0;
	int idY = 0;

public:
	Recurso(Bitmap^ bmpRecurso)
	{
		Random^ rand = gcnew Random();
		ancho = bmpRecurso->Width / 4;
		alto = bmpRecurso->Height / 6;
		x = rand->Next(1000);
		y = rand->Next(672);
		idX = idY = 0;

		activo = true;

	}
	~Recurso() {}

	void dibujar(Graphics^ g, Bitmap^ bmp, int scrollX, int scrollY);
	void moverRecurso();


	bool estaActivo() override { return activo; }

	void setActivo(bool a) { activo = a; }

	System::Drawing::Rectangle getRect() {
		return System::Drawing::Rectangle(x + 10, y + 10, ancho - 80, alto- 80);
	}
};


inline void Recurso::dibujar(Graphics^ g, Bitmap^ bmp, int scrollX, int scrollY) {

	if (!activo) return;

	// Coordenadas en pantalla ajustadas por la cámara
	int pantallaX = x - scrollX;
	int pantallaY = y - scrollY;

	// Sección del sprite
	System::Drawing::Rectangle src = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);

	// Tamaño visual final del recurso
	System::Drawing::Rectangle dest = System::Drawing::Rectangle(pantallaX, pantallaY, ancho * 0.4, alto * 0.4);

	// Dibujar el recurso
	g->DrawImage(bmp, dest, src, GraphicsUnit::Pixel);
}
// 4 de ancho y 6 de alto
inline void Recurso::moverRecurso()
{
	/*	if (!activo) return;*/
		if (idX < 4) { ++idX; }
		else { idX = 0; }

		if (idX == 4) { ++idY; idX = 0; }

		if (idY == 6 && idX <= 4) { idY = 0; }
	
}



