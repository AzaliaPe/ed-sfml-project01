#include "SFX.hh"

SFX::SFX()
{
    soundBuffer = new sf::SoundBuffer();
    sound = new sf::Sound();

    soundsList = new const char*[1]
    {
        "assets/audio/coin1.ogg"
    };
}

SFX::~SFX()
{

}

void SFX::PlaySFX(int index)
{
    soundBuffer->loadFromFile(soundsList[index]);
    sound->setBuffer(*soundBuffer);
    sound->play();
}