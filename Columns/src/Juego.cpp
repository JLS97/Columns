#include "Juego.h"

const int M = 20;
const int N = 10;

struct Point
{int x,y;} a[4], b[4];

//Matriz Mapa
int field[M][N] = {0};

//direccion
int dx = 0;

Juego* Juego::unica_instancia = 0;

Juego::Juego(){

}

Juego::~Juego()
{

}

void Juego::crearPieza(){
    pieza = new Pieza();
    cout << "Pieza Creada" << endl;
}
void Juego::crearMapa(){
    mapa = new Mapa();
}

void Juego::crearVentana(){
	window.create(sf::VideoMode(320, 480), "Columns");
    window.setKeyRepeatEnabled(true);
    cout << "VENTANA" << endl;

    //cargamos el fondo del juego
    Fondo = new Texture();
    Fondo->loadFromFile("images/background.png");

    sprite_fondo = new Sprite(*Fondo);
}

bool Juego::check()
{
   for (int i=0;i<4;i++)
   {
	  if (a[i].x<0 || a[i].x>=N || a[i].y>=M)
        return 0;
      else if (field[a[i].y][a[i].x])
        return 0;
    }

   return 1;
}

void Juego::bucleJuego(){

	while (window.isOpen())
    {

        sf::Event event;

        while (window.pollEvent(event))
        {

            switch(event.type){

                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code){
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                    }
                    break;
            }

            //se mueve la pieza a la izquierda
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {

            }
            //se mueve la pieza a la derecha
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {

            }
            //se rota la pieza
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                pieza->rotacion();
            }

        }

        //--MOVIMIENTO--
        for (int i=0;i<4;i++)
        {
            b[i]=a[i];
            a[i].x+=dx;
        }
        if(!check())
        {
            for (int i=0;i<4;i++)
            {
                a[i]=b[i];
            }
        }



        window.clear();

        window.draw(*sprite_fondo);

        pieza->draw(window);

        //if(pieza->getLimite()==false)
        //{
            pieza->mueve();
        //}

        window.display();
    }
}
