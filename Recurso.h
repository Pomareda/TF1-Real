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

	void dibujar(Graphics^ g, Bitmap^ bmp, const int mapa1[84][143]);
	void moverRecurso();


	bool estaActivo() override { return activo; }

	void setActivo(bool a) { activo = a; }

	System::Drawing::Rectangle getRect() {
		return System::Drawing::Rectangle(x + 10, y + 10, ancho - 100, alto- 88);
	}
};


inline void Recurso::dibujar(Graphics^ g, Bitmap^ bmp, const int mapa1[84][143]) {
	Random^ rand = gcnew Random();

	System::Drawing::Rectangle r1 = System::Drawing::Rectangle(x + 10, y + 10, ancho - 100, alto - 88);
	g->DrawRectangle(System::Drawing::Pens::Red, r1);
	System::Drawing::Rectangle sectionShow = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
	System::Drawing::Rectangle zoom = System::Drawing::Rectangle(x, y, ancho * 0.4, alto * 0.4);
	g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);
	int X = 0, Y = 0;

	for (int i = 0; i < 84; i++)
	{
		X = 0;
		for (int j = 0; j < 143; j++)
		{
			System::Drawing::Rectangle  Rec1 = System::Drawing::Rectangle(X, Y, 8, 8);
			if (mapa1[i][j] != 0) {
				if (getRect().IntersectsWith(Rec1)) {
					activo = false;
					x = rand->Next(1000);
					y = rand->Next(600);
				}
			}

			X = X + 8;
		}
		Y = Y + 8;
	}
}
// 4 de ancho y 6 de alto
inline void Recurso::moverRecurso()
{
		if (!activo) return;
		if (idX < 4) { ++idX; }
		else { idX = 0; }

		if (idX == 4) { ++idY; idX = 0; }

		if (idY == 6 && idX <= 4) { idY = 0; }
	
}



