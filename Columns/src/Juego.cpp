#include "Juego.h"


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

            }

        }



        window.clear();


        window.display();
    }
}
