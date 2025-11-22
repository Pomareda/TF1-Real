#pragma once
#include <iostream>
using namespace System;
using namespace System::Drawing;
using namespace std;

ref class Fondo_Didi
{
private:
	int idX, idY;
	int ancho, alto;
public:
	Fondo_Didi() {
		idX = 0;
		idY = 0;
		ancho = 0;
		alto = 0;
	};
	~Fondo_Didi() {};
	void dibujar(Graphics^ g, Bitmap^ bmpFondo_instrucciones);
	void mover(Graphics^ g);

};
inline void Fondo_Didi::dibujar(Graphics^ g, Bitmap^ bmpFondo_instrucciones)
{
	ancho = bmpFondo_instrucciones->Width / 2;
	alto = bmpFondo_instrucciones->Height / 1;
	System::Drawing::Rectangle sectionShow = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
	System::Drawing::Rectangle destino = System::Drawing::Rectangle(0, 0, g->VisibleClipBounds.Width, g->VisibleClipBounds.Height);
	g->DrawImage(bmpFondo_instrucciones, destino, sectionShow, GraphicsUnit::Pixel);
}
inline void Fondo_Didi::mover(Graphics^ g)
{ 
	idX++;
	if (idX >= 2)
	{
		idX = 0;
		idY++;
		if (idY >= 1)
		{
			idY = 0;
		}
	}
}
