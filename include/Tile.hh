//pragma once permite importar una cabecera (un archivo h o hh) muchas veces pero solo lo carga una vez.
#pragma once
#include <SFML/Graphics.hpp>
#include "BoxCollider.hh"
#include <box2d/box2d.h>

class Tile
{
    private:
        sf::Sprite* sprite;
        BoxCollider* boxCollider;
        b2World* world;
        float posX, posY, scale, cropSize;
    public:
        Tile(float, float, float, float, sf::Texture*&);
        Tile(float, float, float, float, sf::Texture*&, b2World*&);
        ~Tile();
        void Move(float, float);
        void SetPosition(float, float);
        sf::Sprite* GetSprite() const;
        void TurnPhysicsOn(float, float);
        void TurnPhysicsOn(float, float, bool);
};