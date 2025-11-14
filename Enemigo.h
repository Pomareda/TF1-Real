#pragma once
#include "Entidad.h"
#include "Jugador.h"

class Enemigo : public Entidad {
protected:
	int dx, dy;
	bool activo;

public:
	Enemigo(int x, int y, int dx, int dy);
	~Enemigo();

	bool estaActivo() { return activo; }
	void desactivar() { activo = false; }

	void mover();
	void dibujar(Graphics^ g, Bitmap^ bmp);

	int getAncho() { return ancho; }
	int getAlto() { return alto; }
};

inline Enemigo::Enemigo(int x, int y, int dx, int dy) : Entidad(x, y, 64, 64) {
	activo = true;
	this->dx = dx;
	this->dy = dy;
}

inline Enemigo::~Enemigo() { }

inline void Enemigo::mover() {
	if (!activo) return;
	//animacion idle
	if (idX < 4) { ++idX; }
	else { idX = 0; }

	if (idX == 3) { ++idY; idX = 0; }

	if (idY == 4 && idX < 4) { idY = 0; }
	
	x += dx;
	y += dy;
	
}

inline void Enemigo::dibujar(Graphics^ g, Bitmap^ bmp) {
	if (!activo) return;
	System::Drawing::Rectangle sectionShow = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
	System::Drawing::Rectangle zoom = System::Drawing::Rectangle(x, y, ancho * 1.15, alto * 1.15);
	g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);
}