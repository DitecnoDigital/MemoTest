#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Interfaz : public Drawable{
    private:
        int puntaje = 0;
        int descubiertas = 0;
        Font font;
        Text puntajeText;
        Text descubiertasText;
        Text timerText;
        Text resultadoText;
        Clock timer;
        Time time;
    public:
        Interfaz();
        void Update();
        void CambiarPuntaje(int mod);
        void CambiarDescubiertas(int mod);
        int  ConsultarDescubiertas();
        int ConsultarTimer();
        virtual void draw(RenderTarget&,RenderStates) const;
};