#include "BoxCollider.hh"

BoxCollider::BoxCollider(float posX, float posY, sf::Color* borderColor, float width, float height, Rigidbody* rigidbody)
{
    this->posX = posX;
    this->posY = posY;
    this->borderColor = borderColor;
    this->width = width;
    this->height = height;
    this->rigidbody = rigidbody;

    InitShape();
}

BoxCollider::~BoxCollider(){}

void BoxCollider::InitShape()
{
    boxShape = new sf::RectangleShape(*(new sf::Vector2f(posX, posY)));
    boxShape->setSize(*(new sf::Vector2f(width, height)));
    boxShape->setFillColor(sf::Color::Transparent);
    boxShape->setOutlineColor(*borderColor);
    boxShape->setOutlineThickness(0.5f);
}

sf::RectangleShape* BoxCollider::GetBoxShape() const
{
    return boxShape;
}

b2Vec2 BoxCollider::GetBodyPosition() const
{
    return rigidbody->GetBody()->GetPosition();
}

void BoxCollider::UpdatePhysics()
{
    boxShape->setPosition(GetBodyPosition().x, GetBodyPosition().y);
}