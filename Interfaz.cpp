#include "Interfaz.hpp"

Interfaz::Interfaz(){
    if(!font.loadFromFile("Bubblegum.ttf")){
        cout<<"Error al cargar la fuente."<<endl;
    }
    puntajeText.setFont(font);
    puntajeText.setPosition(400,685);
    puntajeText.setScale(1.5,1.5);

    descubiertasText.setFont(font);
    descubiertasText.setPosition(715,695);
    descubiertasText.setScale(1.25,1.25);

    timerText.setFont(font);
    timerText.setPosition(30,695);
    timerText.setScale(1.25,1.25);

    resultadoText.setFont(font);
    resultadoText.setPosition(300,350);
    resultadoText.setScale(2,2);
}
void Interfaz::Update(){
    if(puntaje>9) puntajeText.setString(to_string(puntaje));
    else puntajeText.setString("0"+to_string(puntaje));
    
    if(descubiertas>9) descubiertasText.setString(to_string(descubiertas)+"/12");
    else descubiertasText.setString("0"+to_string(descubiertas)+"/12");
    time=timer.getElapsedTime();
    if(descubiertas!=12){
        if((int)45-(int)time.asSeconds()<0){ 
            resultadoText.setColor(Color::Red);
            resultadoText.setString("PERDISTE");
        }else{
            if(((int)45-(int)time.asSeconds())>9) timerText.setString(to_string(((int)45-(int)time.asSeconds())));
            else timerText.setString("0"+to_string(((int)45-(int)time.asSeconds())));
        }
    }else{
        resultadoText.setColor(Color::Green);
        resultadoText.setString("GANASTE");
    }
    
}

void Interfaz::CambiarPuntaje(int mod){
    puntaje+=mod;
    puntaje=max(puntaje,0);
}

void Interfaz::CambiarDescubiertas(int mod){
    descubiertas+=mod;
}

int Interfaz::ConsultarDescubiertas(){
    return descubiertas;
}

int Interfaz::ConsultarTimer(){
    time=timer.getElapsedTime();
    return (45-time.asSeconds());
}

void Interfaz::draw(RenderTarget &rt,RenderStates rs) const{
    rt.draw(puntajeText,rs);
    rt.draw(descubiertasText,rs);
    rt.draw(timerText,rs);
    rt.draw(resultadoText,rs);
}