#include "Juego.h"

using namespace std;

Juego* Juego::unica_instancia = 0;


Juego::Juego(){

}

Juego::~Juego()
{

}


void Juego::crearVentana(){
	window.create(sf::VideoMode(320, 480), "Columns");
    window.setKeyRepeatEnabled(true);
    cout << "VENTANA" << endl;
}

void Juego::bucleJuego(){

    Clock reloj;

    bool fuera = false;

    int dx = 0;

    //cargamos el fondo del juego
    Fondo = new Texture();
    Fondo->loadFromFile("images/background.png");

    f = new Texture();
    f->loadFromFile("images/tiles.png");

    s = new Sprite(*f);

    sprite_fondo = new Sprite(*Fondo);


    //estado inicial del mapa, la posicion en 0 implica posicion vacia
    //conforme vamos llenando el mapa se van actualizando los 0 a un numero del 1 al 7
    //cada numero representa un color y asi podremos comprobar las colisiones y eliminar
    int mapa[M][N] = {
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
    };

    //Ficha inicial, se genera un numero del 1 al 7 aleatorio qeu corresponde a un color
    int ficha[3] = {
            (1+rand()%7),
            (1+rand()%7),
            (1+rand()%7),
    };

    mapa[1][1] = ficha[0];
    mapa[2][1] = ficha[1];
    mapa[3][1] = ficha[2];


     for(int i = 0;i<M;i++)
    {
        for(int j = 0;j<N;j++)
        {
            cout<<mapa[i][j];
        }
        cout<<endl;
    }


    ficha[0] = (1+rand()%7);
    ficha[1] = (1+rand()%7);
    ficha[2] = (1+rand()%7);

    for(int i = 0;i<3;i++)
        cout<<ficha[i]<<endl;

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
                dx = -1;

            }
            //se mueve la pieza a la derecha
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                dx = 1;
            }
            //se rota la pieza
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                //rotacion();
            }

        }


        if(reloj.getElapsedTime().asMilliseconds() >= 700)
        {
        fuera = false;
    cout<<"Hola"<<endl;
            for(int i = 0;i<M && !fuera;i++)
            {
                cout<<"Hola2"<<endl;
                for(int j = 0;j<N;j++)
                {
                    if(mapa[i][j]!=0 && i<20)
                    {
                        if(mapa[i+1][j]==0){
                            mapa[i+1][j] = mapa[i][j];
                            mapa[i][j] = mapa[i-1][j];
                            mapa[i-1][j] = mapa[i-2][j];
                            mapa[i-2][j] = 0;
                            fuera = true;
                            reloj.restart();
                            dx = 0;
                        }
                    }
                }
            }
            //reloj.restart();
        }


        window.clear();
        window.draw(*sprite_fondo);

        for(int i = 0;i<M;i++)
        {
            for(int j = 0;j<N;j++)
            {

                if(mapa[i][j]!=0){
                    s->setTextureRect(IntRect(mapa[i][j]*18,0,18,18));
                    s->setPosition(j*18,i*18);
                    s->move(28,31);
                    window.draw(*s);
                }
            }
        }


        window.display();
    }
}
