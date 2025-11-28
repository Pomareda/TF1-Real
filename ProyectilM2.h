#pragma once
using namespace System::Drawing;
using namespace System;

ref class ProyectilM2 {
private:
    int x, y;
    int ancho, alto;
    int dx, dy;
    bool activo;
    Bitmap^ bmpRoca;

public:
    ProyectilM2(int posX, int posY, int targetX, int targetY) {
        x = posX;
        y = posY;
        ancho = 15;
        alto = 15;
        activo = true;
		bmpRoca = gcnew Bitmap("Imagenes/roca.png");
        int difX = targetX - x;
        int difY = targetY - y;
        double distancia = Math::Sqrt(difX * difX + difY * difY);

        int velocidad = 10;
        if (distancia > 0) {
            dx = (int)((difX / distancia) * velocidad); //teorema del vector unitario LOL
            dy = (int)((difY / distancia) * velocidad);
        }
        else {
            dx = velocidad;
            dy = 0;
        }
    }

    void mover() {
        if (activo) {
            x += dx;
            y += dy;
        }
    }

    void dibujar(Graphics^ g, int scrollY) {
        if (activo) {
            int pantallaY = y - scrollY;

            /*g->FillEllipse(Brushes::OrangeRed, x - ancho / 2, pantallaY - alto / 2, ancho, alto);
            g->DrawEllipse(Pens::Red, x - ancho / 2, pantallaY - alto / 2, ancho, alto);*/

			g->DrawImage(bmpRoca, x - ancho / 2, pantallaY - alto / 2, ancho * 1.5, alto * 1.5);
        }
    }

    bool estaFueraDePantalla(int anchoMapa, int altoMapa) {
        return x < -50 || x > anchoMapa + 50 || y < -50 || y > altoMapa + 50;
    }

    System::Drawing::Rectangle getRect() {
        return System::Drawing::Rectangle(x - ancho / 2, y - alto / 2, ancho * 1.5, alto * 1.5);
    }

    bool getActivo() { return activo; }
    void setActivo(bool val) { activo = val; }
    int getX() { return x; }
    int getY() { return y; }
};