#pragma once
//#include "Entidad.h"

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
		x = rand->Next(1000);
		y = rand->Next(600);
		idX = idY = 0;

		activo = true;

	}
	~Recurso() {}

	void dibujar(Graphics^ g, Bitmap^ bmp);
	void moverRecurso();


	bool estaActivo() const { return activo; }

	void setActivo(bool a) { activo = a; }

	System::Drawing::Rectangle getRect() {
		return System::Drawing::Rectangle(x + 10, y + 10, ancho - 100, alto- 88);
	}
};


inline void Recurso::dibujar(Graphics^ g, Bitmap^ bmp) {
	System::Drawing::Rectangle r1 = System::Drawing::Rectangle(x + 10, y + 10, ancho - 100, alto - 88);
	g->DrawRectangle(System::Drawing::Pens::Red, r1);
	System::Drawing::Rectangle sectionShow = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
	System::Drawing::Rectangle zoom = System::Drawing::Rectangle(x, y, ancho * 0.4, alto * 0.4);
	g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);
}

inline void Recurso::moverRecurso()
{
	
	if (!activo) return;
	//animacion idle
	if (idX < 4) { ++idX; }
	else { idX = 0; }

	if (idX == 3) { ++idY; idX = 0; }

	if (idY == 5 && idX < 3) { idY = 0; }

	

	
}



