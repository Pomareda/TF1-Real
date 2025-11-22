#pragma once
#include "Entidad.h"

ref class Aliado : public Entidad {
	public:
	Aliado(int x, int y) : Entidad(x, y, 118, 123) {};
	~Aliado() {};

	void dibujar(Graphics^ g, Bitmap^ bmp) override {
		idX = 0; idY = 0; // no quiero que se mueva, se ve feo, tu te ves feo daaaaaaaaaaa

		System::Drawing::Rectangle sectionShow = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
		System::Drawing::Rectangle zoom = System::Drawing::Rectangle(x, y, ancho * 0.4, alto * 0.4);
		g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);
	}

	System::Drawing::Rectangle getRect() override {
		return System::Drawing::Rectangle(x , y, ancho, alto);
	}
	System::Drawing::Rectangle getRectGrande() override {
		return System::Drawing::Rectangle(x - 16, y - 16, ancho + 16, alto + 16);
	}
};
