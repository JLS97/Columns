#ifndef Juego_H
#define Juego_H

#include <sstream>
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <string>


using namespace sf;
using namespace std;

class Juego
{
    public:
    ~Juego(void);
    static Juego *getInstance()
    {
        if(unica_instancia == 0)
        unica_instancia = new Juego();
        return unica_instancia;
    }

    static void ResetInstance()
    {
        delete unica_instancia;
        unica_instancia = 0;
    }


    int estado = 1;
    void crearVentana();
    void bucleJuego();
    void cargaTextos();

    int right = 600;


    sf::RenderWindow window;

    private:
    Juego();
    static Juego* unica_instancia;

    //Mapa* mapa;

     //Texto de controles y puntuacion
    Text izq,der,up,ff,g,puntuacion,puntoss;
    //Texto de siguiente ficha
    Text sigFicha;
    Font font;

    Texture *Fondo=NULL;
    Texture *Fondo2=NULL;
    Texture *F=NULL;
    Texture *PressF=NULL;

    Sprite  *sprite_fondo;
    Sprite  *sprite_fondo2;
    Sprite  *sprite_F;
    Sprite  *sprite_pressF;

    Texture *f=NULL;
    Sprite  *s;
    const int M = 20;
    const int N = 10;
};

#endif
