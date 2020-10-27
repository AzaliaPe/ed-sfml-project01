#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "Maze.hh"
#include "Inputs.hh"
#include "Character.hh"
#include "Tile.hh"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_NAME "Roguelike game"
#define TILES1 "assets/sprites/tiles1.png"
#define TILES2 "assets/sprites/tiles2.png"
#define TILES3 "assets/sprites/tiles3.png"
// #define SPRITE_SCALE 4.f
#define FPS 120
#define PLAYER_MOVESPEED 3.f

const float SPRITE_SCALE(4.f);

int main()
{
    //Esto es la ventana del gráfico
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
    //Aqui vas a guardar los eventos dentro de la ventana, eje: teclado, mouse, etc.
    sf::Event event;

    //Physics Declarection
    b2Vec2* gravity{new b2Vec2(0.f, 0.0f)};
    b2World* world{new b2World(*gravity)};

    //Textures 
    sf::Texture* tilesTexture1{new sf::Texture()};
    tilesTexture1->loadFromFile(TILES1);

    sf::Texture* tilesTexture2{new sf::Texture()};
    tilesTexture2->loadFromFile(TILES2);

    sf::Texture* tilesTexture3{new sf::Texture()};
    tilesTexture3->loadFromFile(TILES3);

    //Tiles
    const float tileBaseWidth{16 * SPRITE_SCALE};
    const float tileBaseHeight{16 * SPRITE_SCALE};

    sf::Sprite* tileWall1{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 1, 16, 16)))};
    tileWall1->setScale(SPRITE_SCALE, SPRITE_SCALE);
    sf::Sprite* tileWall2{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 2, 16, 16)))};
    tileWall2->setScale(SPRITE_SCALE, SPRITE_SCALE);
    sf::Sprite* tileWall3{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 2, 16 * 2, 16, 16)))};
    tileWall3->setScale(SPRITE_SCALE, SPRITE_SCALE);
    sf::Sprite* tileWall4{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 2, 16 * 3, 16, 16)))};
    tileWall4->setScale(SPRITE_SCALE, SPRITE_SCALE);
    sf::Sprite* tileWall5{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 3, 16 * 3, 16, 16)))};
    tileWall5->setScale(SPRITE_SCALE, SPRITE_SCALE);
    sf::Sprite* tileWall6{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 3, 16, 16)))};
    tileWall6->setScale(SPRITE_SCALE, SPRITE_SCALE);
    sf::Sprite* tileWall7{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 4, 16 * 5, 16, 16)))};
    tileWall7->setScale(SPRITE_SCALE, SPRITE_SCALE);
    sf::Sprite* tileWall8{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 6, 16 * 5, 16, 16)))};
    tileWall8->setScale(SPRITE_SCALE, SPRITE_SCALE);
    sf::Sprite* tileWall9{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 6, 16 * 6, 16, 16)))};
    tileWall9->setScale(SPRITE_SCALE, SPRITE_SCALE);

    sf::Sprite* tileGround1{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 4, 16, 16)))};
    tileGround1->setScale(SPRITE_SCALE, SPRITE_SCALE);
    sf::Sprite* tileGround2{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 5, 16, 16)))};
    tileGround2->setScale(SPRITE_SCALE, SPRITE_SCALE);
    sf::Sprite* tileGround3{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 2, 16 * 6, 16, 16)))};
    tileGround3->setScale(SPRITE_SCALE, SPRITE_SCALE);
    sf::Sprite* tileGround4{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 3, 16 * 6, 16, 16)))};
    tileGround4->setScale(SPRITE_SCALE, SPRITE_SCALE);
    sf::Sprite* tileGround5{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 2, 16 * 4, 16, 16)))};
    tileGround5->setScale(SPRITE_SCALE, SPRITE_SCALE);
    sf::Sprite* tileGround6{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 3, 16 * 5, 16, 16)))};
    tileGround6->setScale(SPRITE_SCALE, SPRITE_SCALE);
    sf::Sprite* tileGround7{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 4, 16 * 6, 16, 16)))};
    tileGround7->setScale(SPRITE_SCALE, SPRITE_SCALE);
    sf::Sprite* tileGround8{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 6, 16 * 9, 16, 16)))};
    tileGround8->setScale(SPRITE_SCALE, SPRITE_SCALE);
    sf::Sprite* tileGround9{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 6, 16 * 7, 16, 16)))};
    tileGround9->setScale(SPRITE_SCALE, SPRITE_SCALE);

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

    //BoxCollider del Treasure 
    sf::Sprite* tileTreasure{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 19, 16 * 19, 16, 16)))};
    tileTreasure->setScale(SPRITE_SCALE, SPRITE_SCALE);
    tileTreasure->setPosition(400, 400);

    BoxCollider* treasureCollider = new BoxCollider(300, 250, new sf::Color(0, 255, 0, 255), 16, 16,
    new Rigidbody(world, b2BodyType::b2_staticBody, new b2Vec2(400, 400), tileBaseWidth / 2, tileBaseHeight / 2, 1, 0, 0),
    tileTreasure);
    
    treasureCollider->GetBoxShape()->setScale(SPRITE_SCALE, SPRITE_SCALE);
    treasureCollider->GetBoxShape()->setPosition(tileTreasure->getPosition());

    //Animación del Treasure 
    Animation* treasureAnimation{new Animation{19, 19, 21, tileTreasure, 450}};

    unsigned int N{10}, M{13};
    Maze* maze1{new Maze(N, M, SPRITE_SCALE, 16, tilesTexture3, "assets/mazes/maze1.txt")};
    
    tileTramp->setPosition(64*3, 64*4);

    tileFont1_1->setPosition(64*2, 64*1);
    tileFont1_2->setPosition(64*2, 64*2);

    tileFont2_1->setPosition(64*5, 64*1);
    tileFont2_2->setPosition(64*5, 64*2);

    sf::Clock* clock{new sf::Clock()};
    float deltaTime{};//tiempo que transcurre entre punto A hasta el punto B.

    window->setFramerateLimit(FPS);

    //Game inputs
    Inputs* inputs{new Inputs()};
    
    //Main player
    Character* character1{new Character(tilesTexture2, 16 * 1, 16 * 5, 16, 16, SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(400, 300), world, window)};
    character1->SetAnimations(
        new Animation*[2]
        {
            new Animation(5, 0, 5, character1->GetSprite(), 40.f),
            new Animation(6, 0, 5, character1->GetSprite(), 80.f)
        }
    );

    // character1->SetPosition(400, 300);

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

        //player sigue la posicion del cuerpo de física
        treasureCollider->UpdatePhysics();

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

        treasureAnimation->Play(deltaTime);
        window->draw(*tileTreasure);

        font1_1Animation->Play(deltaTime);
        window->draw(*tileFont1_1);
        font1_2Animation->Play(deltaTime);
        window->draw(*tileFont1_2);

        font2_1Animation->Play(deltaTime);
        window->draw(*tileFont2_1);
        font2_2Animation->Play(deltaTime);
        window->draw(*tileFont2_2);
        window->draw(*treasureCollider->GetBoxShape());
        
        character1->Update();
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