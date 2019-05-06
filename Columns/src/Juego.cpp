#include "Juego.h"
#include <string>
using namespace std;


//en realidad esto sobra porque estoy tratando la clase juego como si fuese todo un main
//simplemente está puesto porque comence el proyecto tomando como plantilla el proyecto grupal
Juego* Juego::unica_instancia = 0;


Juego::Juego(){

}

Juego::~Juego()
{

}


void Juego::crearVentana(){
	window.create(sf::VideoMode(600, 480), "Columns");
    window.setKeyRepeatEnabled(true);
    cout << "VENTANA" << endl;
}

void Juego::bucleJuego(){

    Clock reloj;
    Clock reloj2;

    bool fuera = false;

    bool activada = true;

    bool perdido = false;

    //cargamos la fuente para el texto
    Font font;
    if(!font.loadFromFile("images/arial.ttf"))
    {
        std::cerr<<"Error al cargar la fuente";
        exit(0);
    }

    //Texto de siguiente ficha
    Text sigFicha;

    sigFicha.setFont(font);
    sigFicha.setColor(Color::White);
    sigFicha.setCharacterSize(20);
    sigFicha.setPosition(385,40);
    sigFicha.setString("Siguiente Ficha:");

    //Texto de controles y puntuacion
    Text izq,der,up,down,ff,g,puntuacion,puntoss;

    izq.setFont(font);
    der.setFont(font);
    up.setFont(font);
    down.setFont(font);
    ff.setFont(font);
    g.setFont(font);
    puntuacion.setFont(font);
    puntoss.setFont(font);

    izq.setColor(Color::White);
    der.setColor(Color::White);
    up.setColor(Color::White);
    down.setColor(Color::White);
    ff.setColor(Color::White);
    g.setColor(Color::White);
    puntuacion.setColor(Color::Black);
    puntoss.setColor(Color::Black);

    izq.setCharacterSize(15);
    der.setCharacterSize(15);
    up.setCharacterSize(15);
    down.setCharacterSize(15);
    ff.setCharacterSize(15);
    g.setCharacterSize(15);
    puntuacion.setCharacterSize(30);
    puntoss.setCharacterSize(50);

    izq.setPosition(370,180);
    der.setPosition(370,200);
    up.setPosition(370,220);
    down.setPosition(370,240);
    ff.setPosition(370,260);
    g.setPosition(370,280);
    puntuacion.setPosition(30,420);
    puntoss.setPosition(215,405);

    izq.setString("Left     -- Mueve izquieda");
    der.setString("Right   -- Mueve derecha");
    up.setString("Up        -- Rotacion de color");
    down.setString("Down   -- Avanzar ficha");
    ff.setString("Pulsa F para reiniciar juego");
    g.setString("Pulsa G para activar modo Dios");
    puntuacion.setString("Puntuacion: ");

    //cargamos el fondo del juego
    Fondo = new Texture();
    Fondo->loadFromFile("images/background.png");

    Fondo2 = new Texture();
    Fondo2->loadFromFile("images/endgame.png");

    F = new Texture();
    F->loadFromFile("images/F.png");

    PressF = new Texture();
    PressF->loadFromFile("images/pressF.png");

    f = new Texture();
    f->loadFromFile("images/tiles.png");


    s = new Sprite(*f);

    sprite_fondo = new Sprite(*Fondo);

    sprite_fondo2 = new Sprite(*Fondo2);

    sprite_F = new Sprite(*F);

    sprite_pressF = new Sprite(*PressF);

    sprite_fondo2->setScale(0.7,0.7);

    sprite_fondo2->setPosition(30,60);

    sprite_F->setScale(0.25,0.25);

    sprite_F->setPosition(100, 290);

    sprite_pressF->setScale(0.3,0.3);

    sprite_pressF->setPosition(350,300);


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


    //la primera ficha la metemos directamente al mapa
    mapa[0][2] = ficha[0];
    mapa[1][2] = ficha[1];
    mapa[2][2] = ficha[2];

    //y generamos la que será la siguiente ficha
    ficha[0] = (1+rand()%7);
    ficha[1] = (1+rand()%7);
    ficha[2] = (1+rand()%7);

    //dificultad del juego expresada en los milisegundos entre actualizacion de posiciond e la ficha
    //es decir la ficha tarda 600 milisegundos en ir una posicion hacia abajo
    //luego bajaremos la velocidad para que sea mas dificil
    int dificultad = 600;

    int puntos = 0;

    bool nueva = false;

    //variables para el control de una nueva pieza de 3 sprites
    int posterior = 1;
    int tempo = 17;
    int vez = 0;

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
                        //el if mas largo del mundo
                        //compuebo que si hay pieza o muro a la izquierda no se puede mover y que ademas
                        //cuando hay abajo muro o pieza tampoco
                        if( mapa[i][j]!=NULL && mapa[i][j]!=0 && j > 0 && i<17
                            && mapa[i][j-1]==0 && mapa[i+1][j-1]==0 && mapa[i+2][j-1]==0
                            && mapa[i+3][j]==0)
                        {

                            cout<<"Mueve izquierda"<<endl;

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
                        //el if mas largo del mundo 2
                        //compuebo que si hay pieza o muro a la derecha no se puede mover y que ademas
                        //cuando hay abajo muro o pieza tampoco
                        if( mapa[i][j]!=NULL && mapa[i][j]!=0 && j < 9 && i<17
                            && mapa[i][j+1]==0 && mapa[i+1][j+1]==0 && mapa[i+2][j+1]==0
                            && mapa[i+3][j]==0)
                        {
                            cout<<"Mueve derecha"<<endl;

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
                cout<<"Rotacion de color"<<endl;
                if(activada)
                {
                    bool movido1 = false;

                    for(int i =  0;i<M && movido1==false;i++)
                    {
                            for(int j = 0;j<N && movido1==false;j++)
                            {
                            //aqui no es el mas largo de mundo porque lo he separado
                            //compuebo que si hay pieza o muro debajo no se puede rotar el color
                            if(mapa[i+3][j]==0){
                                if( mapa[i][j]!=NULL && mapa[i][j]!=0 && i<17)
                                {
                                    //en programacion 1 hicimos un ejercicio parecido
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

            //en vez de un modo dios he hecho un modo diablo,
            //si pulsas pierdes porque es imposible aguantar el ritmo
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
            {
                cout<<"MODO DIABLO"<<endl;
                puntos = 99999;
                dificultad = 10;
            }


            //Bajamos la ficha hasta la ultima posicion en la que puede estar
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                cout<<"Bajo ficha"<<endl;
            }
            //si pulsas F se reinicia el juego
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            {
                cout<<"Reinicio"<<endl;
                puntos = 0;
                dificultad = 600;
                perdido = false;

                for(int i = 0; i<M;i++)
                {
                    for(int j = 0; j<N;j++)
                    {
                        mapa[i][j]=0;
                    }
                }

                mapa[0][2] = ficha[0];
                mapa[1][2] = ficha[1];
                mapa[2][2] = ficha[2];

            }

            //Salimos del juego "QUIT"
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                cout<<"Salimos del juego"<<endl;
                window.close();
            }

        }

        //Recorro la matriz a la inversa para no crear conflicto a la hora de generar una nueva pieza
        //si recorro la matriz normal solo se me creara bien la primera vez la ficha el resto de veces me da error
        // ya que tal y como lo estoy planteando compruebo que si ninguna ficha se puede mover mas entonces la creo
        // para que esto funcione la recorro a la inversa asi siempre terminara el bucle con la ficha que actualmente se esta moviendo
        //mientras que si la recorro normal el bucle termina con las que ya estan paradas y claro siempre se me generara una ficha nueva


        if(reloj.getElapsedTime().asMilliseconds() >= dificultad)
        {

            for(int i = M; i>=0;i--)
            {
                for(int j = N; j>=0 && !fuera;j--)
                {
                    if(mapa[i][j]!=0 && i<19)
                    {
                        if(mapa[i+1][j]==0)
                        {
                            mapa[i+1][j] = mapa[i][j];
                            mapa[i][j] = mapa[i-1][j];
                            mapa[i-1][j] = mapa[i-2][j];
                            mapa[i-2][j] = 0;
                            reloj.restart();
                            fuera = true;
                            nueva = false;
                        }
                        else
                        {
                            nueva = true;
                        }
                    }
                }
            }

            fuera = false;

        }

        //si ninguna ficha tiene movimiento disponible significa que debo crear una nueva
        // la creo y actualizo nueva a false.
        // me volvera a entrar cuando la nueva haya colisionado
        if(nueva)
        {
            //se genera una ficha con 3 colores aleatorios
            //ademas la ficha se coloca en una columna aleatoria
            //el punto de spwan de la ficha no siepre es el mismo
            //esto es algo que vi en una version de tetris y me gustó bastante, le da una jugabilidad extra
            //al no saber donde se genera la ficha tienes que llevar cuidado al subir

            //genero una columna aleatoria en la que ira la nueva ficha
            int columna = (0+rand()%10);

            //ficha en juego
            mapa[0][columna] = ficha[0];
            mapa[1][columna] = ficha[1];
            mapa[2][columna] = ficha[2];

            //siguiente ficha
            //nunca he sido muy fan de mostrar la siguiente ficha en el tetris
            //pero me gustaba la idea de implementarlo simplemente por hacer mas cosas
            ficha[0] = (1+rand()%7);
            ficha[1] = (1+rand()%7);
            ficha[2] = (1+rand()%7);

            //cada vez que se genera una nueva pieza te dan 10 puntos
            //cuanto mas aguantes mas piezas se generan y mas puntos obtendras
            puntos = puntos + 10;


            nueva = false;

            //Compuebo las colisiones horizontales
            //recorro la matriz horizontalmente y compruebo si en una linea hay mas de dos lineas del mismo color juntas

            for(int i = 0; i<M;i++)
            {
                for(int j = 0; j<N;j++)
                {
                    if(mapa[i][j]!=0)
                    {
                        if(mapa[i][j]==mapa[i][j+1] && mapa[i][j]==mapa[i][j+2])
                        {
                            if(mapa[i][j]==mapa[i][j+3])
                            {
                                mapa[i][j+3] = 0;
                            }
                            mapa[i][j] =  0;
                            mapa[i][j+1] = 0;
                            mapa[i][j+2] = 0;
                        }
                    }
                }
            }

            //Compruebo las colisiones vertiales
            //recorro la matriz y me voy fijando si hay 3 o 4 fichas iguales,
            //en cuyo caso hay que actualizar sus valores a 0
            for(int i = 0;i<M;i++)
            {
                for(int j = 0;j<N;j++)
                {
                    if(mapa[i][j]!=0)
                    {
                        if(mapa[i][j]==mapa[i+1][j] && mapa[i+2][j]==mapa[i][j])
                        {
                            if(mapa[i][j]==mapa[i+3][j])
                            {
                                mapa[i+3][j] = 0;
                            }
                            mapa[i][j]=0;
                            mapa[i+1][j]=0;
                            mapa[i+2][j]=0;
                        }
                    }
                }
            }

            //Compueba colision cuadrado
            //vamos a comprobar si existen fichas del mismo colo formando un cuadrado de 2x2
            //este caso es especial ya que ni colisiones en hiruzontal ni en vertical nos lo detecta
            //para ello seguimos las pasos anteriores pero com la comprobacion cambiada
            //en el caso en el que existan fichar iguales formando un cuadrado as actualizamos a 0
            //Voy a meter aqui tambien la colision en diagonal porque no me apetece hacer otro bucle
            for(int i = 0; i<M;i++)
            {
                for(int j = 0;j<N;j++)
                {
                    if(mapa[i][j]!=0)
                    {
                        if(mapa[i][j]==mapa[i+1][j] && mapa[i][j]==mapa[i][j+1] && mapa[i][j]==mapa[i+1][j+1])
                        {
                            mapa[i][j]=0;
                            mapa[i+1][j] = 0;
                            mapa[i][j+1] =  0;
                            mapa[i+1][j+1] = 0;
                        }
                        if(mapa[i][j]==mapa[i+1][j+1] && mapa[i][j]==mapa[i+2][j+2])
                        {
                            mapa[i][j] = 0;
                            mapa[i+1][j+1] = 0;
                            mapa[i+2][j+2] = 0;
                        }
                        else if(mapa[i][j]==mapa[i-1][j+1] && mapa[i][j]==mapa[i-2][j+2])
                        {
                            mapa[i][j] = 0;
                            mapa[i-1][j+1] = 0;
                            mapa[i-2][j+2] = 0;
                        }
                    }
                }
            }
        }


        //conforme vayas sacando mas puntos la dificultad aunmeta
        //aumentando la velocidad de la pieza
        if(puntos >= 200 && puntos <= 500)
        {
            //este nivel aun se aguanta
            dificultad = 300;
        }
        if(puntos >500 && puntos <=800)
        {
            //esta dificil
            dificultad = 100;
        }
        if(puntos > 800 && puntos <99990)
        {
            dificultad = 50;
        }

        //Vamos a comprobar cuando has perdido
        //para este caso si en la fila 0 hay una o mas lineas ocupadas eso significara que has revosado la
        //cantidad de columnas permitidas en el mapa por lo que has perdido
        //el clasico fin de partida del tetris
        int pierde = 0;
        for(int i = 0;i <N;i++)
        {
            if(mapa[0][i]!=0)
            {
                pierde++;
            }
        }

        if(pierde>1)
        {
            perdido = true;
        }

         window.clear(Color::Transparent);

        //Cargamos los sprites de fondo, los que saldran cuando pierdas
        if(perdido)
        {
            window.draw(*sprite_fondo2);
            window.draw(*sprite_F);
            window.draw(*sprite_pressF);
        }

        //mientras no pierdas se muestra el juego, cuando pierdes se deja de mostrar,
        //y se muestra el mensaje de has perdido
        if(!perdido)
        {

            //pongo un Transparent para luego escribir encima
           // window.clear(Color::Transparent);

            //dibujo el fondo
            window.draw(*sprite_fondo);

            //dibujo la siguiente ficha
            s->setTextureRect(IntRect(ficha[0]*18,0,18,18));
            s->setPosition(450,80);
            window.draw(*s);
            s->setTextureRect(IntRect(ficha[1]*18,0,18,18));
            s->setPosition(450,98);
            window.draw(*s);
            s->setTextureRect(IntRect(ficha[2]*18,0,18,18));
            s->setPosition(450,116);
            window.draw(*s);

            //dibujo los colores asociados a cada numero comprobando la matriz mapa
            //si es 0 no e imprimira nada
            //en cualquier otro caso su colo asociado
            for(int i = 0;i<M;i++)
            {
                for(int j = 0;j<N;j++)
                {

                    //bueno esto en realidad no haria falta puesto que si es 0 no se dibujara nada igualmente
                    if(mapa[i][j]!=0){
                        s->setTextureRect(IntRect(mapa[i][j]*18,0,18,18));
                        s->setPosition(j*18,i*18);
                        s->move(28,31);
                        window.draw(*s);
                    }
                }
            }

            //dibujo todos los textos
            window.draw(sigFicha);
            window.draw(izq);
            window.draw(der);
            window.draw(up);
            window.draw(down);
            window.draw(ff);
            window.draw(g);
            window.draw(puntuacion);
            std::string cadena = "";

            cadena = static_cast<std::ostringstream*>(&(std::ostringstream() << puntos))->str();
            puntoss.setString(cadena);
            window.draw(puntoss);

        }


        window.display();
        // Ahora a seguir haciendo la grupal ;)
        // perdona Fidel, no he hecho la interpolacion :(
    }
}
