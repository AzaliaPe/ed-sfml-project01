#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "Maze.hh"
#include "Inputs.hh"
#include "Character.hh"
#include "Tile.hh"
#include "GameObject.hh"
#include "ContactListener.hh"
#include "Score.hh"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_NAME "Roguelike game"
#define TILES1 "assets/sprites/tiles1.png"
#define TILES2 "assets/sprites/tiles2.png"
#define TILES3 "assets/sprites/tiles3.png"
#define FONT1 "assets/fonts/8-BIT_WONDER.TTF"
#define SPRITE_SCALE 4.f
#define FPS 120
#define PLAYER_MOVESPEED 3.0f

int main()
{
    //Esto es la ventana del gráfico
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
    //Aqui vas a guardar los eventos dentro de la ventana, eje: teclado, mouse, etc.
    sf::Event event;

    Score* score{new Score(FONT1, "Score ", 24, new sf::Vector2f(25, 5), new sf::Color(255, 255, 255), window)};

    //physics declaration
    b2Vec2* gravity{new b2Vec2(0.f, 0.f)};
    b2World* world{new b2World(*gravity)}; 

    sf::Clock* clock{new sf::Clock()};
    float deltaTime{};

    window->setFramerateLimit(FPS);
    
    //Game inputs
    Inputs* inputs{new Inputs()};
    
    //Textures
    sf::Texture* tilesTexture1{new sf::Texture()};
    tilesTexture1->loadFromFile(TILES1);
    sf::Texture* tilesTexture2{new sf::Texture()};
    tilesTexture2->loadFromFile(TILES2);
    sf::Texture* tilesTexture3{new sf::Texture()};
    tilesTexture3->loadFromFile(TILES3);

    const float tileBaseWidth{16 * SPRITE_SCALE};
    const float tileBaseHeight{16 * SPRITE_SCALE};

    //Animaciones de algunos objetos
    sf::Sprite* tileTramp{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 4, 16 * 11, 16, 16)))};
    tileTramp->setScale(SPRITE_SCALE, SPRITE_SCALE);
    Animation* trampAnimation{new Animation{11, 1, 4, tileTramp, 270}};

    sf::Sprite* tileFont1_1{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 5, 16 * 3, 16, 16)))};
    tileFont1_1->setScale(SPRITE_SCALE, SPRITE_SCALE);
    Animation* font1_1Animation{new Animation{3, 5, 6, tileFont1_1, 250}};
    sf::Sprite* tileFont1_2{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 4, 16 * 4, 16, 16)))};
    tileFont1_2->setScale(SPRITE_SCALE, SPRITE_SCALE);
    Animation* font1_2Animation{new Animation{4, 4, 6, tileFont1_2, 250}};

    sf::Sprite* tileFont2_1{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 5, 16 * 1, 16, 16)))};
    tileFont2_1->setScale(SPRITE_SCALE, SPRITE_SCALE);
    Animation* font2_1Animation{new Animation{1, 5, 6, tileFont2_1, 250}};
    sf::Sprite* tileFont2_2{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 4, 16 * 2, 16, 16)))};
    tileFont2_2->setScale(SPRITE_SCALE, SPRITE_SCALE);
    Animation* font2_2Animation{new Animation{2, 4, 6, tileFont2_2, 250}};

    unsigned int N{10}, M{13};
    Maze* maze1{new Maze(N, M, SPRITE_SCALE, 16, tilesTexture3, "assets/mazes/maze1.txt")};

    tileTramp->setPosition(64*3, 64*4);

    tileFont1_1->setPosition(64*4, 64*1);
    tileFont1_2->setPosition(64*4, 64*2);

    tileFont2_1->setPosition(64*8, 64*1);
    tileFont2_2->setPosition(64*8, 64*2);

    //Main player
    Character* character1{new Character(tilesTexture2, 16 * 1, 16 * 5, 16, 16, 
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(400, 300), b2BodyType::b2_dynamicBody, world, window)};
    character1->SetAnimations(
        new Animation*[2]
        {
            new Animation(5, 0, 5, character1->GetSprite(), 40.f),
            new Animation(6, 0, 5, character1->GetSprite(), 80.f)
        }
    );

    character1->SetTagName("player");

    GameObject* treasure{new GameObject(tilesTexture3, 16 * 19, 16 * 19, 16, 16, 
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(400, 400), b2BodyType::b2_staticBody, world, window)}; 
    treasure->SetTagName("item");
    GameObject* treasure2{new GameObject(tilesTexture3, 16 * 19, 16 * 19, 16, 16, 
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(200, 400), b2BodyType::b2_staticBody, world, window)}; 
    treasure2->SetTagName("item");

    std::vector<GameObject*>* items{new std::vector<GameObject*>()};
    items->push_back(treasure);
    items->push_back(treasure2);

    world->SetContactListener(new ContactListener(score, items));

    //Esto es el loop principal, mientras la ventana este abierta, esto se va ejecutar.
    while (window->isOpen())
    {
        //Mientras se esten ejecutando eventos dentro de la ventana, esto se va repetir eje: teclado, joystick, mouse, etc
        while (window->pollEvent(event))
        {
            //Si el evento fue la acción de cerrar la ventana, entonces termina la aplicación.
            if(event.type == sf::Event::Closed)
            {
                window->close();
            }
        }
        
        Vec2* keyboardAxis{inputs->GetKeyboardAxis()};
        Vec2* joystickAxis{inputs->GetJoystickAxis()};

        if(sf::Joystick::isConnected(0))
        {
            character1->Move(new b2Vec2(joystickAxis->x * deltaTime * PLAYER_MOVESPEED, joystickAxis->y * deltaTime * PLAYER_MOVESPEED));
            character1->FlipSpriteX(joystickAxis->x);

            if(std::abs(joystickAxis->x) > 0 || std::abs(joystickAxis->y) > 0)
            {
                //run
                character1->GetAnimation(1)->Play(deltaTime);
            }
            else
            {
                //idle
                character1->GetAnimation(0)->Play(deltaTime);
            }
        }
        else
        {
            character1->Move(new b2Vec2(keyboardAxis->x * deltaTime * PLAYER_MOVESPEED, keyboardAxis->y * deltaTime * PLAYER_MOVESPEED));
            character1->FlipSpriteX(keyboardAxis->x);

            if(std::abs(keyboardAxis->x) > 0 || std::abs(keyboardAxis->y) > 0)
            {
                //run
                character1->GetAnimation(1)->Play(deltaTime);
            }
            else
            {
                //idle
                character1->GetAnimation(0)->Play(deltaTime);
            }
        }

        window->clear(*(new sf::Color(26, 26, 26, 100)));//Limpiar la pantalla y poner un color.

        for(auto& tile : *maze1->GetContainer())
        {
            window->draw(*tile->GetSprite());
        }

        trampAnimation->Play(deltaTime);
        window->draw(*tileTramp);
        
        font1_1Animation->Play(deltaTime);
        window->draw(*tileFont1_1);
        font1_2Animation->Play(deltaTime);
        window->draw(*tileFont1_2);

        font2_1Animation->Play(deltaTime);
        window->draw(*tileFont2_1);
        font2_2Animation->Play(deltaTime);
        window->draw(*tileFont2_2);

        character1->Update();

        for(auto& item : *items)
        {
            item->Update();
        }

        score->Update();

        window->display(); //display para mostrar.

        sf::Time timeElapsed = clock->getElapsedTime();
        deltaTime = timeElapsed.asMilliseconds();
        world->ClearForces();
        world->Step(1.f / 100 * deltaTime, 8, 8);
        clock->restart();
        
        //std::cout << "delta time: " << deltaTime << std::endl;

        delete keyboardAxis;
        delete joystickAxis;
    }
    
    return 0;
}