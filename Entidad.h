#pragma once

class Entidad {
protected:
    int x, y;
    int ancho, alto;
public:
    Entidad(int x, int y, int ancho, int alto) : x(x), y(y), ancho(ancho), alto(alto) {}
    ~Entidad() {};

    void borrar(int x, int y);

    virtual void mover();
    virtual void dibujar() = 0;

    //getters y setters
    int getX() { return x; };
    int getY() { return y; };

    //dibujos especificos
    void dibujar_Humano();
    void dibujar_IA();

    virtual System::Drawing::Rectangle getRect() {
        return System::Drawing::Rectangle(x, y, ancho, alto);
    }
};