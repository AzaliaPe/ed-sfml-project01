#include "Character.hh"

Character::Character(sf::Texture*& texture, float cropPosX, float cropPosY, float cropWidth, 
float cropHeight, float scaleX, float scaleY, b2Vec2* position, b2World*& world, sf::RenderWindow*& window)
{
    this->texture = texture;
    this->cropPosX = cropPosX;
    this->cropPosY = cropPosY;
    this->cropWidth = cropWidth;
    this->cropHeight = cropHeight;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->window = window;

    tileBaseWidth = cropWidth * scaleX;
    tileBaseHeight = cropHeight * scaleY;

    InitSprite(world, position);
}

void Character::InitSprite(b2World*& world, b2Vec2* position)
{
    sprite = new sf::Sprite(*texture, *(new sf::IntRect(cropPosX, cropPosY, cropWidth, cropHeight)));
    sprite->setScale(*(new sf::Vector2f(scaleX, scaleY)));

    boxCollider = new BoxCollider(position->x, position->y, new sf::Color(0, 255, 0, 255), cropWidth, cropHeight,
    new Rigidbody(world, b2BodyType::b2_dynamicBody, position, tileBaseWidth / 2, tileBaseHeight / 2, 1, 0, 0),
    sprite);
    boxCollider->GetBoxShape()->setScale(scaleX, scaleY);
}

void Character::Move(b2Vec2* direction)
{
    boxCollider->Move(direction);
}

sf::Sprite* Character::GetSprite() 
{
    return sprite;
}

void Character::SetPosition(float posX, float posY)
{
    sprite->setPosition(posX, posY);
}

void Character::Update()
{
    boxCollider->UpdatePhysics();
    window->draw(*sprite);
    window->draw(*boxCollider->GetBoxShape());
}

BoxCollider* Character::GetCollider() const
{
    return boxCollider;
}

void Character::FlipSpriteX(float x)
{
    if( x > 0)
    {
        sprite->setScale(scaleX, scaleY);
        sprite->setOrigin(0.f, 0.f);
    }
    if (x < 0)
    {
        sprite->setScale(-scaleX, scaleY);
        sprite->setOrigin(sprite->getGlobalBounds().width / scaleX, 0.f);
    }
}

void Character::SetAnimations(Animation** animations)
{
    this->animations = animations;
}

Animation* Character::GetAnimation(int index) const
{
    return *(animations + index);
}

Character::~Character(){}