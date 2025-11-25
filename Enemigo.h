#pragma once
#include "Entidad.h"
#include "Jugador.h"
using namespace System::Drawing;

ref class Enemigo : public Entidad {
protected:
	int dx, dy;
	bool activo;
	bool pregunta_contestada;
public:
	Enemigo(int x, int y, int dx, int dy);
	~Enemigo();

	bool verPregunta() { return pregunta_contestada; }
	void preguntaContestada() { pregunta_contestada = true; }
	bool estaActivo() { return activo; }
	void desactivar() { activo = false; }

	void mover() override;
	void dibujar(Graphics^ g, Bitmap^ bmp, int scrollX, int scrollY);
	int getAncho() { return ancho; }
	int getAlto() { return alto; }
	System::Drawing::Rectangle getRect() override;
};

inline Enemigo::Enemigo(int x, int y, int dx, int dy) : Entidad(x, y, 64, 64) {
	pregunta_contestada = false;
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
	return System::Drawing::Rectangle(x + 20, y + 5, (ancho +15), (alto - 10));
}
inline void Enemigo::dibujar(Graphics^ g, Bitmap^ bmp, int scrollX, int scrollY) {
	if (!activo) return;

	int pantallaX = x - scrollX;
	int pantallaY = y - scrollY;

	// NO dibujar si está fuera de la pantalla
	if (pantallaX < -ancho || pantallaX > 2750 || pantallaY < -alto || pantallaY > 1730) {
		return;
	}

	System::Drawing::Rectangle src = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
	System::Drawing::Rectangle dest = System::Drawing::Rectangle(pantallaX, pantallaY, ancho*2, alto*2);

	g->DrawImage(bmp, dest, src, GraphicsUnit::Pixel);
}