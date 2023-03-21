#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Ficha : public Drawable{
    private:
        Texture texture,textureBlock;
        Sprite sprite;
        bool descubierta=false;
        int tipo;
    public:
        Ficha(int tip,int x, int y);
        void AsignarTextura(Texture tex);
        void BloquearSprite();
        void DesbloquearSprite();
        int ConsultarTipo();
        bool ConsultarEstado();
        void Descubrir();
        virtual void draw(RenderTarget& rt,RenderStates rs) const;
};