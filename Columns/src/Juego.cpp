#include "Juego.h"


Juego* Juego::unica_instancia = 0;

Juego::Juego(){

}

Juego::~Juego()
{

}

void Juego::crearPieza(){
    pieza = new Pieza(sf::Vector2f(50,50));
    cout << "Pieza Creada" << endl;
}
void Juego::crearVentana(){
	window.create(sf::VideoMode(400, 600), "Columns");
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

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){

            }

        }



        window.clear();


        window.display();
    }
}
