#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Interfaz : public Drawable{
    private:
        int puntos=0;
        int descubiertas=0;
        Clock clock;
        Time time;
        Font font;
        Text puntosText;
        Text descubiertasText;
        Text clockText;
        Text resultadoText;
    public:
        Interfaz();
        void Update();
        void CambiarPuntaje(int mod);
        void CambiarDescubiertas(int mod);
        int ConsultarDescubiertas();
        int ConsultarTiempo();
        virtual void draw(RenderTarget &rt, RenderStates rs) const;
};