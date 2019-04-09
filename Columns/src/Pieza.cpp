#include <iostream>
#include <SFML/Graphics.hpp>
#include "Pieza.h"



Pieza::Pieza(sf::Vector2f size){

    sprite_Pieza.setSize(size);
    sprite_Pieza.setFillColor(sf::Color::White);

}

Pieza::~Pieza() {
    //delete[] sprite_Pieza;
}


int Pieza::getRight(){
    //return sprite_Pieza.getPosition().x + sprite_Pieza.getSize().x;
    return sprite_Pieza.getPosition().x;
}

int Pieza::getLeft(){
    return sprite_Pieza.getPosition().x;
}

int Pieza::getTop(){
    return sprite_Pieza.getPosition().y;
}

int Pieza::getBottom(){
    return sprite_Pieza.getPosition().y + sprite_Pieza.getSize().y;
}

int Pieza::getDmg(){
    return kDmg;
}

void Pieza::draw(sf::RenderWindow &window){
    window.draw(sprite_Pieza);
}

void Pieza::setPos(sf::Vector2f newPos){
    sprite_Pieza.setPosition(newPos);
}
