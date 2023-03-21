#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include "Ficha.hpp"
#include "Interfaz.hpp"

using namespace std;
using namespace sf;

int main(){
    //Ventana
    RenderWindow window(VideoMode(850,750),"Memotest");
    window.setFramerateLimit(60);
    //Fondo
    Texture fondoTexture;
    Sprite fondo;
    if(!fondoTexture.loadFromFile("Fondo.png")) cout<<"Error al cargar textura de fondo"<<endl;
    fondo.setTexture(fondoTexture);
    //Fichas
    vector<Texture> textures(6);
    for(int i = 1; i<=6; i++){
        if(!textures[i-1].loadFromFile(to_string(i)+".png")) cout<<"Error al cargar la textura "<<i<<endl;
    }
    vector<vector<Ficha>> ficha(3,vector<Ficha>(4,Ficha(0,0,0)));
    vector<int> cantApariciones(6,0);
    int tipoRandom;

    srand(time(NULL));
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            do{
                tipoRandom=1+(rand()%6);
            }while(cantApariciones[tipoRandom-1]==2);
            cantApariciones[tipoRandom-1]++;
            ficha[i][j]=Ficha(tipoRandom,200*j+(j+1)*10,200*i+(i+1)*10);
            ficha[i][j].AsignarTextura(textures[tipoRandom-1]);
            ficha[i][j].BloquearSprite();
        }
    }
    //Click(Auxiliar)
    int cantDesbloqueada=0;
    int iAnt,jAnt;
    //Espera
    Clock clock;
    Time time;
    //Interfaz
    Interfaz interfaz;
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type==Event::Closed) window.close();
            if(event.type==Event::MouseButtonPressed && event.mouseButton.button==Mouse::Left && cantDesbloqueada<2){
                if(interfaz.ConsultarDescubiertas()!=12 && interfaz.ConsultarTiempo()>=0){
                    for(int i = 0; i < 3; i++){
                        for(int j = 0; j < 4; j++){
                            IntRect rect(200*j+(j+1)*10,200*i+(i+1)*10,200,200);
                            if(rect.contains(event.mouseButton.x,event.mouseButton.y)){
                                ficha[i][j].DesbloquearSprite();
                                if(cantDesbloqueada==0) iAnt=i,jAnt=j,cantDesbloqueada++;
                                else if(ficha[i][j].ConsultarTipo()==ficha[iAnt][jAnt].ConsultarTipo()){
                                    ficha[i][j].Descubrir();
                                    ficha[iAnt][jAnt].Descubrir();
                                    interfaz.CambiarDescubiertas(+2);
                                    interfaz.CambiarPuntaje(+15);
                                    cantDesbloqueada=0;
                                }else{
                                    cantDesbloqueada++;
                                    interfaz.CambiarPuntaje(-5);
                                    clock.restart();
                                }
                            }
                        }
                    }
                }
            }
        }
        //Bloquear Fichas Desbloqueadas
        if(cantDesbloqueada==2 && (time=clock.getElapsedTime())>=seconds(1)){
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 4; j++){
                    if(!ficha[i][j].ConsultarEstado()) ficha[i][j].BloquearSprite();
                }
            }
            cantDesbloqueada=0;
        }
        //Actualizar Interfaz
        interfaz.Update();

        window.clear();
        window.draw(fondo);
        if(interfaz.ConsultarDescubiertas()!=12 && interfaz.ConsultarTiempo()>=0){
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 4; j++){
                    window.draw(ficha[i][j]);
                }
            }
        }
        window.draw(interfaz);
        window.display();
    }
    return 0;
}