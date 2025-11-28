#pragma once
ref class PlataformaM2 {
public:
    int x, y, ancho, alto;
    int velocidad;
    Bitmap^ imagen;

    PlataformaM2(int _x, int _y, int _ancho, int _alto) {
        x = _x;
        y = _y;
        ancho = _ancho;
        alto = _alto;
        velocidad = 5;

        try {
            imagen = gcnew Bitmap("Imagenes/piso2.png");
            imagen->MakeTransparent(Color::White);
        }
        catch (...) {
            imagen = nullptr;
        }
    }

    void mover(int anchoVentana) {
        if (x + ancho >= anchoVentana || x <= 0) {
            velocidad *= -1;
        }
        x += velocidad;
    }

    void dibujar(Graphics^ g, int scrollY) {
        if (imagen != nullptr) {
            g->DrawImage(imagen, x, y - scrollY, ancho, alto);
        }
        else {
            g->FillRectangle(Brushes::Brown, x, y - scrollY, ancho, alto);
        }
    }

    System::Drawing::Rectangle getRect() {
        return System::Drawing::Rectangle(x, y, ancho, alto);
    }
};
