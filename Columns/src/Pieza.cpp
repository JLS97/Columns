#include "Pieza.h"

using namespace std;


Pieza::Pieza()
{
    t = new Texture();
    t->loadFromFile("images/tiles.png");


    //Cada pieza esta compuesta por 3 sprites distintos
    //son los distintos colores que hay en una pieza
    s1 = new Sprite(*t);
    s2 = new Sprite(*t);
    s3 = new Sprite(*t);

    creaSprite();

}

Pieza::~Pieza()
{
    //dtor
}

void Pieza::mueve()
{
    int pos = s1->getPosition().x;
    int pos2 = s2->getPosition().x;
    int pos3 = s3->getPosition().x;

    if(pos<=100 || pos2<=100 ||pos3<=100){
        s1->move(0,0.1);
        s2->move(0,0.1);
        s3->move(0,0.1);
    }
    cout<<s1->getPosition().x<<endl;
    cout<<s1->getPosition().y<<endl;
/*    else if(s2->getPosition().x<=370)
        s2->move(0,0.1);
    else if(s3->getPosition().x<=370)
        s3->move(0,0.1);*/
}
void Pieza::creaSprite()
{
    ids1 = (1 + rand()%7);
    ids2 = (1 + rand()%7);
    ids3 = (1 + rand()%7);

    s1->setTextureRect(IntRect(ids1*18,0,18,18));
    s1->setPosition(28,28);

    s2->setTextureRect(IntRect(ids2*18,0,18,18));
    s2->setPosition(s1->getPosition().x,s1->getPosition().y+18);

    s3->setTextureRect(IntRect(ids3*18,0,18,18));
    s3->setPosition(s2->getPosition().x,s2->getPosition().y+18);
}

int Pieza::getIds1()
{
    return ids1;
}

int Pieza::getIds2()
{
    return ids2;
}

int Pieza::getIds3()
{
    return ids3;
}

void Pieza::rotacion()
{

    //s1 pasara a la posicion 2, s2 a la posicion 3, y s3 a la uno

    //esto es de primero de carrera, gracias Rosana apprendí algo en P1
     int x = s1->getPosition().x;
     int y = s1->getPosition().y;

     s1->setPosition(s2->getPosition().x,s2->getPosition().y);
     s2->setPosition(s3->getPosition().x,s3->getPosition().y);
     s3->setPosition(x,y);

}

void Pieza::draw(RenderWindow &window)
{
    window.draw(*s1);
    window.draw(*s2);
    window.draw(*s3);
}
