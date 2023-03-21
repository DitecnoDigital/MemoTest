#include "Ficha.hpp"

Ficha::Ficha(int tip,int x, int y){
    tipo=tip;
    sprite.setPosition(x,y);
    if(!textureBlock.loadFromFile("0.png")) cout<<"Error al cargar textura Block"<<endl;
}
void Ficha::AsignarTextura(Texture tex){
    texture=tex;
}
void Ficha::BloquearSprite(){
    sprite.setTexture(textureBlock);
}

void Ficha::DesbloquearSprite(){
    sprite.setTexture(texture);
}
int Ficha::ConsultarTipo(){
    return tipo;
}
bool Ficha::ConsultarEstado(){
    return descubierta;
}
void Ficha::Descubrir(){
    descubierta=true;
}
void Ficha::draw(RenderTarget& rt,RenderStates rs) const{
    rt.draw(sprite,rs);
}