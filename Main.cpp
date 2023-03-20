#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Ficha.hpp"
#include "Interfaz.hpp"

using namespace std;
using namespace sf;

int main(){
    //crear la ventana para esto vamos a declarar un RenderWindow
    RenderWindow window(VideoMode(850,750),"Memotest"); 
    //definir un promedio de 60 frames
    //aunque sea un juego estatico lo hacemos porque es una buena practica
    window.setFramerateLimit(60);

    int cantDesbloqueada=0;
    vector<Texture> textures(7);
    vector<vector<Ficha>> v(3,vector<Ficha>(4,Ficha(0,0,0)));
    vector<int> vN(7,0); 
    srand(time(NULL));
    Clock clock;
    Time time;
    int iAnt,jAnt;
    
    Texture bTexture;
    Sprite background;
    Interfaz interfaz;        

    if(!bTexture.loadFromFile("Fondo.png")){
        cout<<"Error al cargar textura de fondo"<<endl;
    }
    
    background.setTexture(bTexture);
    
    for(int i = 0; i < 7; i++){
        if(!textures[i].loadFromFile(string(to_string(i)+".png"))){
            cout<<"Fallo al cargar textura "<<i<<endl;
        }
    }

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            bool podemos = true;
            int random;
            do{
                podemos = true;
                random = 1+rand()%6;
                if(vN[random]>=2){
                    podemos = false;
                }
            }while(!podemos);
            if(podemos){
                v[i][j]=Ficha(random,(j)*200+(j+1)*10,(i)*200+(i+1)*10);
                v[i][j].AsignarTextura(textures[random]);
                v[i][j].BloquearSprite();
                vN[random]++;
            }
        }
    }
    
    //Hacemos el loop de nuestro juego por asi decirle
    while(window.isOpen()){
        //Dentro del loop vamos a controlar los ventos tales como cerrar la ventana
        //Y mas adelante hacer click sobre la ventana
        //Declaramos un Event event en el cual gracias a la funcion pollEvent 
        //vamos a guardar el evento mas proximo en la cola de eventos
        Event event;
        //Mientras haya un evento asignalo a event asi lo puedo procesar
        while(window.pollEvent(event)){
            //Una vez que ya  tenemos ele evevento ahora quiero saber que tipo de event es
            //Entonces vamos a hacer un if
            if(event.type==Event::Closed) window.close();
            if(event.type==Event::MouseButtonPressed){
                if(event.mouseButton.button==Mouse::Left && cantDesbloqueada<2){
                    for(int i = 0; i < 3; i++){
                        for(int j = 0; j < 4; j++){
                            IntRect rect((j)*200+(j+1)*10,(i)*200+(i+1)*10,200,200);
                            if(rect.contains(event.mouseButton.x,event.mouseButton.y)){
                                v[i][j].DesbloquearSprite();
                                if(cantDesbloqueada==0) iAnt=i,jAnt=j,cantDesbloqueada++;
                                else if(v[i][j].ConsultarTipo()==v[iAnt][jAnt].ConsultarTipo()){
                                    v[i][j].Descubrir();
                                    v[iAnt][jAnt].Descubrir();
                                    cantDesbloqueada=0;
                                    interfaz.CambiarPuntaje(+15);
                                    interfaz.CambiarDescubiertas(+2);
                                }else{
                                    cantDesbloqueada++;
                                    interfaz.CambiarPuntaje(-5);
                                }
                            }
                        }
                    }
                    clock.restart();
                }
            }
        }
        if(cantDesbloqueada==2 && (time=clock.getElapsedTime()) >= seconds(2)){
            cantDesbloqueada=0;
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 4; j++){
                    if(!v[i][j].ConsultarEstado()) v[i][j].BloquearSprite();
                }
            }
        }
        interfaz.Update();
        //Ahora vamos a limpiar la pantalla
        window.clear();
        window.draw(background);
        if(interfaz.ConsultarDescubiertas()!=12 && interfaz.ConsultarTimer()>=0){
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < (int)v[i].size(); j++){
                    window.draw(v[i][j]);
                }
            }
        }
        window.draw(interfaz);
        //Mostramos todo lo dibujado en la pantalla
        window.display();
    }
    return 0;
}