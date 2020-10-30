#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class ContactListener : public b2ContactListener
{
    private:
        sf::Text* scoreText;
        int score{};
    public:
        ContactListener(sf::Text*&);
        ~ContactListener();
        
        void BeginContact(b2Contact*);
        void EndContact(b2Contact*);
};