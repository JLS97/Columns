#ifndef PIEZA_HPP
#define PIEZA_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class Pieza{
public:
    Pieza(sf::Vector2f size);

    ~Pieza();


    int getRight();

    int getLeft();

    int getTop();

    int getBottom();

    int getDmg();

    void draw(sf::RenderWindow &window);

    void setPos(sf::Vector2f newPos);

private:
    sf::RectangleShape sprite_Pieza;


};

#endif /* NEWFILE_HPP */
