#pragma once
#include <ctime>

enum Direcciones { Ninguna, Arriba, Abajo, Derecha, Izquierda };
using namespace System::Drawing;


class Entidad {
protected:
    int x, y;
	int dx, dy;
    int ancho, alto;
	int idX, idY; //posicion en el sprite
public:
    Entidad(int x, int y, int ancho, int alto) : x(x), y(y), ancho(ancho), alto(alto) 
    {
		idX = idY = 0;
		dx = dy = 0;
        
    }
    ~Entidad() {};

    //void borrar(int x, int y);

    virtual void mover() {};
    virtual void dibujar(Graphics^ g, Bitmap^ bmp);

    //getters y setters
    int getX() { return x; };
    int getY() { return y; };

    virtual System::Drawing::Rectangle getRect() {
        return System::Drawing::Rectangle(x, y, ancho, alto);
    }
};


inline void Entidad::dibujar(Graphics^ g, Bitmap^ bmp) {

    System::Drawing::Rectangle sectionShow = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
    System::Drawing::Rectangle zoom = System::Drawing::Rectangle(x, y, ancho * 1.0, alto * 1.0);
    g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);
}