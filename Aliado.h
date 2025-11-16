#pragma once
#include "Entidad.h"

ref class Aliado : public Entidad {
	public:
	Aliado(int x, int y) : Entidad(x, y, 60, 60) {};
	~Aliado() {};

	void dibujar(Graphics^ g, Bitmap^ bmp) override {
		System::Drawing::Rectangle sectionShow = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
		System::Drawing::Rectangle zoom = System::Drawing::Rectangle(x, y, ancho * 1.0, alto * 1.0);
		g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);
	}

	Rectangle getRect() override {
		return System::Drawing::Rectangle(x + 5, y + 5, ancho + 10, alto + 10);
	}
};

