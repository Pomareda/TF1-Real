#pragma once
#include "Entidad.h"

using namespace System;

class Recurso
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
		x = rand->Next(100);
		y = rand->Next(60);
		idX = idY = 0;

		activo = true;

	}
	~Recurso() {}

	void dibujar(Graphics^ g, Bitmap^ bmp);
	void moverRecurso();


	bool estaActivo() const { return activo; }

	void setActivo(bool a) { activo = a; }
};


inline void Recurso::dibujar(Graphics^ g, Bitmap^ bmp) {
	System::Drawing::Rectangle sectionShow = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
	System::Drawing::Rectangle zoom = System::Drawing::Rectangle(x, y, ancho * 0.7, alto * 0.7);
	g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);
}

inline void Recurso::moverRecurso()
{
	
	if (!activo) return;
	//animacion idle
	if (idX < 4) { ++idX; }
	else { idX = 0; }

	if (idX == 3) { ++idY; idX = 0; }

	if (idY == 5 && idX == 4) { idY = 0; idX = 0; }

	

	
}



