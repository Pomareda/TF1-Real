#pragma once
#pragma once
using namespace System::Drawing;

ref class JugadorM3
{
private:
    double velY;
    double gravedad;

    int vida;
    int x, y, dx, ancho, alto, idx, idy;

    bool izq, der, enSuelo, disparando;

    Direcciones Ultima;

public:
    JugadorM3(Bitmap^ bmp) {
        x = 100; y = 50;
        dx = 10;
        velY = 0;
        gravedad = 1.5;

        idx = idy = 0;
        ancho = bmp->Width / 3;
        alto = bmp->Height / 10;
        Ultima = Derecha;
        izq = der = false;
        enSuelo = false;
        disparando = false;
        vida = 100;
    };

    ~JugadorM3() {};

    void mover() {
        Direcciones preUltima = Ultima;
        if (vida > 0) {
            //movimiento
            if (izq) {
                x -= dx;
                Ultima = Izquierda;
            }
            if (der) {
                x += dx;
                Ultima = Derecha;
            }

            //Sprites:
            //1.esta en el aire 
            if (enSuelo == false) {
                if (disparando) idx = 1; //disparando en el aire
                else idx = 0; //salto 

                if (Ultima == Izquierda) idy = 4; //mira lado izq
                else idy = 5; //mira lado derecho
            }

            //2.esta en el suelo
            if (enSuelo == true) {
                if (disparando) {//dispara
                    if (izq) {
                        idy = 7; //movimiento derecha disparando
                    }
                    else if (der) {
                        idy = 8;  //movimiento izquierda disparando
                    }
                    else {
                        idy = 6;
                        if (Ultima == Izquierda) {
                            idx = 0; //idle izq disparando
                        }
                        else {
                            idx = 1; //idle der disparando
                        }
                    }
                }

                else { //no dispara
                    if (izq) {
                        idy = 2; //movimiento derecha 
                    }
                    else if (der) {
                        idy = 3;  //movimiento izquierda 
                    }
                    else {
                        idx = 0;
                        if (Ultima == Izquierda) {
                            idy = 0; //idle izq 
                        }
                        else {
                            idy = 1; //idle der 
                        }
                    }
                }

                if (izq || der) {
                    idx++;
                    if (idx > 2) idx = 0;
                }
            }
        }
    }

    void liberarSalto() {
        //ahora no tiene carga, salta directamente
        if (enSuelo) {

            double saltoFinal = 18.0;
            velY = -saltoFinal;  // Velocidad negativa (hacia arriba)
            enSuelo = false;  // Ya no está en el suelo
        }

    }

    void aplicarGravedad() {
        // Siempre aplicar gravedad, las colisiones manejarán enSuelo
        if (velY < 40) {
            velY += gravedad;
        }
        y += (int)velY;
    }

    void reiniciarPosicion() {
        //por si se sale de la pantalla
        if (y > 900) {
            y = 0;
        }
        if (x < 0 || x + ancho > 1000) {
            x = 0;
        }
    }

    //Setters
    void setIzquierda(bool v) { izq = v; }
    void setDerecha(bool v) { der = v; }
    void setY(int nuevaY) { y = nuevaY; }
    void setX(int nuevaX) { x = nuevaX; }
    void setEnSuelo(bool v) { enSuelo = v; }
    void setVelY(double v) { velY = v; }
    void setUltima(Direcciones d) { Ultima = d; }
    void setDisparando(bool d) { disparando = d; }
    void setVida(int v) { vida = v; }
    void setIDY(int v) { idy = v; }

    //Getters
    System::Drawing::Rectangle getRect() { return System::Drawing::Rectangle(x + 5, y, ancho, alto); }
    Direcciones getUltima() { return Ultima; }
    bool getIzquierda() { return izq; }
    bool getDerecha() { return der; }
    bool getEnSuelo() { return enSuelo; }
    int getVelY() { return (int)velY; }
    int getX() { return x; }
    int getY() { return y; }
    int getAncho() { return ancho; }
    int getAlto() { return alto; }
    int getIDX() { return idx; }
    int getIDY() { return idy; }
    int getVida() { return vida; }
};

