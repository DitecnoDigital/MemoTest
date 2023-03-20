#include "Ficha.hpp"
#include <iostream>

using namespace std;

Ficha::Ficha(int tip,int x,int y){
    tipo=tip;
    sprite.setPosition(x,y);
    if(!textureBlock.loadFromFile("0.png")){
        cout<<"Fallo al cargar textura 0"<<endl;
    }
}

int Ficha::ConsultarTipo(){
    return tipo;
}

void Ficha::Descubrir(){
    descubierta=true;
}
bool Ficha::ConsultarEstado(){
    return descubierta;
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

void Ficha::draw(RenderTarget& rt,RenderStates rs) const{
    rt.draw(sprite,rs);
}