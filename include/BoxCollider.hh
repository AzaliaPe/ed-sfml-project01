#include<SFML/Graphics.hpp>
#include "Rigidbody.hh"

class BoxCollider
{
    private:
        sf::RectangleShape* boxShape;
        float posX;
        float posY;
        sf::Color* borderColor;
        float width;
        float height;
        Rigidbody* rigidbody;

        void InitShape();
        
    public:
        BoxCollider(float, float, sf::Color*, float, float, Rigidbody*);
        ~BoxCollider();

        sf::RectangleShape* GetBoxShape() const;

        void UpdatePhysics();

        b2Vec2 GetBodyPosition() const;
};


