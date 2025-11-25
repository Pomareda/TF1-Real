#pragma once
#include "Jugador.h"
using namespace System::Drawing;

ref class Camara
{
private:


	Jugador^ jugador;
	int scrollX;
	int scrollY;
	int cuantoScrollX;  //cuanto se movio el scroll, es la dif del scroll actual con el anterior
	int cuantoScrollY;
	int maxScrollX;
	int maxScrollY;




public:
	Camara();
	~Camara();

	void actualizarCamaraYDibujar(Jugador^ jugador, int anchoVentana, int altoVentana, int altoMapa, int anchoMapa, Graphics^ g, Bitmap^ bmp);


	int getScrollX() { return scrollX; };
	int getScrollY() { return scrollY; };
};

Camara::Camara()
{
}

Camara::~Camara()
{
}

inline void Camara::actualizarCamaraYDibujar(Jugador^ jugador, int anchoVentana, int altoVentana, int anchoMapa, int altoMapa, Graphics^ g, Bitmap^ bmp)
{
	int posicionJugadorY = jugador->getY();
	int posicionJugadorX = jugador->getX();
	scrollY = posicionJugadorY - altoVentana  / 2;
	scrollX = posicionJugadorX - anchoVentana  / 2;

	int maxScrollY = altoMapa - altoVentana ;
	int maxScrollX = anchoMapa - anchoVentana;

	if (scrollY > maxScrollY) scrollY = maxScrollY;
	if (scrollY < 0) scrollY = 0;

	if (scrollX > maxScrollX) scrollX = maxScrollX;
	if (scrollX < 0) scrollX = 0;

	System::Drawing::Rectangle porcionImagen = System::Drawing::Rectangle(
		scrollX,
		scrollY,
		anchoVentana,
		altoVentana
	);


	System::Drawing::Rectangle destinoPantalla = System::Drawing::Rectangle(
		0, 0,
		anchoVentana,
		altoVentana
	);

	g->DrawImage(
		bmp, //deberia ser el background del mapa para el mundo 2 (yaveoeso) paramtro?
		destinoPantalla,
		porcionImagen,
		GraphicsUnit::Pixel
	);

}
