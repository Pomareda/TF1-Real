#pragma once
#include <iostream>
using namespace System;
using namespace System::Drawing;
using namespace std;

ref class IA_hablando
{
private:
	int idX, idY;
	int ancho, alto;
	int partes_ancho;
	int partes_alto;
public:
	IA_hablando() {
		idX = 0;
		idY = 0;
		ancho = 0;
		alto = 0;
	};
	~IA_hablando() {};
	void dibujar(Graphics^ g, Bitmap^ bmpFondo_instrucciones);
	void mover(Graphics^ g, int partes_an, int partes_alt);
	/*int GetContador() { return contador; }	
	void SetContador(int c) { contador = c; }*/

};
inline void IA_hablando::dibujar(Graphics^ g, Bitmap^ bmpFondo_instrucciones)
{
	/*ancho = bmpFondo_instrucciones->Width / 7;
	alto = bmpFondo_instrucciones->Height / 2;*/
	ancho = bmpFondo_instrucciones->Width / partes_ancho;
	alto = bmpFondo_instrucciones->Height / partes_alto;
	System::Drawing::Rectangle sectionShow = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
	System::Drawing::Rectangle destino = System::Drawing::Rectangle(0, 0, g->VisibleClipBounds.Width, g->VisibleClipBounds.Height);
	g->DrawImage(bmpFondo_instrucciones, destino, sectionShow, GraphicsUnit::Pixel);
}
inline void IA_hablando::mover(Graphics^ g, int partes_an, int partes_alt)
{
	partes_ancho = partes_an;
	partes_alto = partes_alt;
	idX++;
	if (idX >= partes_ancho)
	{
		idX = 0;
		idY++;
		if (idY >= partes_alto)
		{
			idY = 0;
		}
	}
}