#pragma once
using namespace System::Drawing;

ref class USB
{
private:
    int x, y;
    int ancho, alto;
    int dx; // Velocidad horizontal
    bool activo;

public:
    USB(int _x, int _y, int velocidadX) {
        x = _x;
        y = _y;
        dx = velocidadX;
        ancho = 40;
        alto = 20;
        activo = true;
    }
    ~USB() {};

    void mover() {
        if (activo) {
            x += dx;

            // Desactivar si se sale del mapa (asumiendo ancho de pantalla ~1082)
            if (x < -100 || x > 1200) {
                activo = false;
            }
        }
    }

    bool esActivo() { return activo; }
    void setActivo(bool act) { activo = act; }

    int getX() { return x; }
    int getY() { return y; }
    int getdX() { return dx; }

    System::Drawing::Rectangle getRect() {
        return System::Drawing::Rectangle(x, y, ancho, alto);
    }
};
