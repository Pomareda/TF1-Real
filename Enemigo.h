#pragma once
#include "Entidad.h"
#include "Jugador.h"

class Enemigo : public Entidad {
protected:
	int dx, dy;
	Jugador* jugador; //para que los enemigos puedan interactuar con el jugador
	bool activo;

public:
	Enemigo(int x, int y, Jugador* jugador, int dx, int dy);
	~Enemigo();

	bool estaActivo() { return activo; }
	void desactivar() { activo = false; }

	void mover();
	void dibujar(Graphics^ g, Bitmap^ bmp);

	int getAncho() { return ancho; }
	int getAlto() { return alto; }
};

inline Enemigo::Enemigo(int x, int y, Jugador* jugador, int dx, int dy) : Entidad(x, y, 64, 64) {
	activo = true;
	this->jugador = jugador;
	this->dx = dx;
	this->dy = dy;
}

inline Enemigo::~Enemigo() { }

inline void Enemigo::mover() {
	if (!activo) return;
	x += dx;
	y += dy;
	
}

inline void Enemigo::dibujar(Graphics^ g, Bitmap^ bmp) {
	if (!activo) return;
	System::Drawing::Rectangle sectionShow = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
	System::Drawing::Rectangle zoom = System::Drawing::Rectangle(x, y, ancho * 1.0, alto * 1.0);
	g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);
}