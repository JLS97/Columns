#ifndef Juego_H
#define Juego_H

#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Pieza.h"
#include "Mapa.h"

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
    void crearPieza();
    void bucleJuego();
    void crearMapa();
    bool check();


    int right = 600;


    sf::RenderWindow window;

    private:
    Juego();
    static Juego* unica_instancia;
    Pieza* pieza;
    Mapa* mapa;

    Texture *Fondo=NULL;
    Sprite  *sprite_fondo;


};

#endif
