#include <SFML/Graphics.hpp>

class Animation
{
    private:
        int startFrame;
        int endFrame;
        sf::Sprite* sprite;
        float delay;
        int currentFrame;
        float timer{};
    public:
        Animation(int, int, sf::Sprite*, float);
        ~Animation();
        void Play(float&);
};
