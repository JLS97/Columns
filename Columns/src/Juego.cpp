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

    bool activada = true;

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

    mapa[1][4] = ficha[0];
    mapa[2][4] = ficha[1];
    mapa[3][4] = ficha[2];


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

    bool nueva = false;

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
            //buscara la primera posicion que no sea 0 de l amatriz y sobre esta y sus dos de abajao(la pieza)
            //se aplicara un movimiento hacia la izquierda, es decir copiara los valores en las celdas adyacentes
            //y por ultimo borrará los valores del comienzo, dadno asi una impresion de movimiento a la izquierda
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                bool movido = false;
                for(int i =  0;i<M && movido==false;i++)
                {
                    for(int j = 0;j<N;j++)
                    {
                        if( mapa[i][j]!=NULL && mapa[i][j]!=0 && j > 0 && i<17)
                        {
                            mapa[i][j-1] = mapa[i][j];
                            mapa[i+1][j-1] = mapa[i+1][j];
                            mapa[i+2][j-1] = mapa[i+2][j];

                            mapa[i][j] = 0;
                            mapa[i+1][j] = 0;
                            mapa[i+2][j] = 0;

                            movido = true;
                        }
                    }
                }

            }
            //se mueve la pieza a la derecha
            //Seguimos el mismo procedimiento que para la izquierda pero al reves, obviamente
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                bool movido1 = false;
                for(int i =  0;i<M && movido1==false;i++)
                {
                    for(int j = 0;j<N && movido1==false;j++)
                    {
                        if( mapa[i][j]!=NULL && mapa[i][j]!=0 && j < 9 && i<17)
                        {
                            mapa[i][j+1] = mapa[i][j];
                            mapa[i+1][j+1] = mapa[i+1][j];
                            mapa[i+2][j+1] = mapa[i+2][j];

                            mapa[i][j] = 0;
                            mapa[i+1][j] = 0;
                            mapa[i+2][j] = 0;

                            movido1 = true;
                        }
                    }
                }
            }
            //se rota la pieza
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if(activada)
                {
                    bool movido1 = false;
                    for(int i =  0;i<M && movido1==false;i++)
                    {
                        for(int j = 0;j<N && movido1==false;j++)
                        {
                            if( mapa[i][j]!=NULL && mapa[i][j]!=0 && i<17)
                            {
                                //el buen ejercicio de programacion 1, Gracias Rosana
                                int  aux = mapa[i][j];
                                mapa[i][j] = mapa[i+1][j];
                                mapa[i+1][j] = mapa[i+2][j];
                                mapa[i+2][j] = aux;

                                movido1 = true;
                            }
                        }
                    }
                }
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
                        }
                    }
                }
            }
            //reloj.restart();
        }

        //Cuando ninguna de las piezas se puede mover hacia abajo entonces creamos una nueva
        //y la  incluimos a nuestra matriz mapa, y asi sucesivamente
        if(nueva)
        {
            mapa[1][3] = (1+rand()%7);
            mapa[2][3] = (1+rand()%7);
            mapa[3][3] = (1+rand()%7);
            nueva = false;
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
