#pragma once
#include "Entidad.h"
#include "Jugador.h"
using namespace System::Drawing;

ref class Enemigo : public Entidad {
protected:
	int dx, dy;
	bool activo;

public:
	Enemigo(int x, int y, int dx, int dy);
	~Enemigo();

	bool estaActivo() { return activo; }
	void desactivar() { activo = false; }

	void mover() override;
	void dibujar(Graphics^ g, Bitmap^ bmp) override;
	int getAncho() { return ancho; }
	int getAlto() { return alto; }
	System::Drawing::Rectangle getRect() override;
};

inline Enemigo::Enemigo(int x, int y, int dx, int dy) : Entidad(x, y, 64, 64) {
	activo = true;
	this->dx = dx;
	this->dy = dy;
}

inline Enemigo::~Enemigo() {}


inline void Enemigo::mover() {
	if (!activo) return;
	//animacion idle
	if (idX < 4) { ++idX; }
	else { idX = 0; }

	if (idX == 3) { ++idY; idX = 0; }

	if (idY == 4 && idX < 4) { idY = 0; }

	/*x += dx;
	y += dy;*/

}

inline System::Drawing::Rectangle Enemigo::getRect() {
	return System::Drawing::Rectangle(x + 2 + dx + 10 + 5, y + 12, (ancho - 7 - 10), (alto - 9));
}
inline void Enemigo::dibujar(Graphics^ g, Bitmap^ bmp) {
	if (!activo) return;
	System::Drawing::Rectangle  Jugador1 = System::Drawing::Rectangle(x + 2 + dx + 10 + 5, y + 12, (ancho - 7 - 10), (alto - 9));
	g->DrawRectangle(System::Drawing::Pens::Red, Jugador1);
	System::Drawing::Rectangle sectionShow = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
	System::Drawing::Rectangle zoom = System::Drawing::Rectangle(x, y, ancho * 1.15, alto * 1.15);
	g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);
}