#ifndef PIEZA_H
#define PIEZA_H

#include <sstream>
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace sf;

class Pieza
{
    public:
        Pieza();
        virtual ~Pieza();

        void creaSprite();
        void mueve();
        void rotacion();
        int getIds1();
        int getIds2();
        int getIds3();
        void draw(RenderWindow &window);

    protected:
    private:
    Texture *t=NULL;
    Sprite  *s1;
    Sprite  *s2;
    Sprite  *s3;
    int ids1,ids2,ids3;
};

#endif // PIEZA_H
