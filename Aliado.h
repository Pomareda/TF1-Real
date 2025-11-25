#pragma once
#include "Entidad.h"

ref class Aliado : public Entidad {
	public:
	Aliado(int x, int y) : Entidad(x, y, 118, 123) {};
	~Aliado() {};

	void dibujar(Graphics^ g, Bitmap^ bmp, int scrollX, int scrollY)  {
		idX = 0; idY = 0; // no quiero que se mueva, se ve feo, tu te ves feo daaaaaaaaaaa

		int pantallaX = x - scrollX;
		int pantallaY = y - scrollY;

		if (pantallaX < -ancho || pantallaX > 1084 || pantallaY < -alto || pantallaY > 661) {
			return;
		}

		System::Drawing::Rectangle src = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
		System::Drawing::Rectangle dest = System::Drawing::Rectangle(pantallaX, pantallaY, ancho * 0.4, alto * 0.4);

		g->DrawImage(bmp, dest, src, GraphicsUnit::Pixel);
	}

	System::Drawing::Rectangle getRect() override {
		return System::Drawing::Rectangle(x , y, ancho * 0.4, alto * 0.4);
	}
	System::Drawing::Rectangle getRectGrande() override {
		return System::Drawing::Rectangle(x - 16, y - 16, ancho + 16, alto + 16);
	}
};
