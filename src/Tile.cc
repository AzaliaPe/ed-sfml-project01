#include "Tile.hh"

Tile::Tile(float posX, float posY, float scale, float cropSize, sf::Texture*& texture)
{
    this->posX = posX;
    this->posY = posY;
    this->scale = scale;
    this->cropSize = cropSize;
    sprite = new sf::Sprite(*texture, *(new sf::IntRect(posX, posY, cropSize, cropSize)));
    sprite->setScale(scale, scale);
}

Tile::Tile(float posX, float posY, float scale, float cropSize, sf::Texture*& texture, b2World*& world)
{
    this->posX = posX;
    this->posY = posY;
    this->scale = scale;
    this->cropSize = cropSize;
    this->world = world;
    sprite = new sf::Sprite(*texture, *(new sf::IntRect(posX, posY, cropSize, cropSize)));
    sprite->setScale(scale, scale);
}

Tile::~Tile()
{

}

sf::Sprite* Tile::GetSprite() const
{
    return sprite;
}

void Tile::Move(float x, float y)
{
    sprite->move(x, y);
}

void Tile::SetPosition(float x, float y)
{
    sprite->setPosition(x, y);
}

void Tile::SetTagName(const char* tagName)
{
    this->tagName = tagName;
}

const char* Tile::GetTagName() const
{
    return tagName;
}

void Tile::TurnPhysicsOn(float x, float y)
{
    Rigidbody* rb{new Rigidbody(world, b2BodyType::b2_staticBody, new b2Vec2(x, y), 
    cropSize * scale / 2, cropSize * scale / 2, 1, 0, 0)};

    boxCollider = new BoxCollider(x, y, new sf::Color(0, 255, 0, 255), cropSize, cropSize, rb, sprite);
    boxCollider->GetBoxShape()->setScale(scale, scale);
}

void Tile::TurnPhysicsOn(float x, float y, bool isSensor)
{
    Rigidbody* rb{new Rigidbody(world, b2BodyType::b2_staticBody, new b2Vec2(x, y), 
    cropSize * scale / 2, cropSize * scale / 2, 1, 0, 0)};

    boxCollider = new BoxCollider(x, y, new sf::Color(0, 255, 0, 255), cropSize, cropSize, rb, sprite);
    boxCollider->GetBoxShape()->setScale(scale, scale);
    rb->SetSensor(isSensor);
    rb->SetUserData((void*) this);
}