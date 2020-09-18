#include <iostream>
#include <SFML/Graphics.hpp>

#include "Inputs.hh"
#include "Character.hh"
#include "Animation.hh"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_NAME "Roguelike game"
#define TILES1 "assets/sprites/tiles1.png"
#define TILES2 "assets/sprites/tiles2.png"
#define SPRITE_SCALE 4.f
#define FPS 120
#define PLAYER_MOVESPEED 0.2f

int main()
{
    //Esto es la ventana del gráfico
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
    
    // //Para crear un sprite primero se tiene que crear una textura
    // sf::Texture texture;

    //Aquí se carga la textura, 
    //se utiliza la sentencia if para comprobar si el archivo se ha cargado correctamente
    // if(!texture.loadFromFile("sprites/character.png"))
    // {
    //     //Esto es por si algo sale mal
    //     std::cout << "Load failed" << std::endl;
        
    //     system("pause");
    // }

    //Aquí se crea el sprite
    // sf::Sprite sprite;

    // //Se asigna la textura
    // sprite.setTexture(texture);

    // //Esto dibuja una parte de la imágen 
    // sprite.setTextureRect(sf::IntRect(0, 0, 100, 120));

    // //Esto es una mascara de color (Azul)
    // // sprite.setColor(sf::Color(0, 0, 255));

    // //Se mueve el sprite
    // sprite.move(100, 100);

    // //Se cambia el origen al centro del sprite
    // sf::Vector2f centro;
    // centro.x = sprite.getTextureRect().width / 2.f;
    // centro.y = sprite.getTextureRect().height / 2.f;
    // sprite.setOrigin(centro);
    
    // //Aqui se rota el sprite 360 grados
    // sprite.rotate(360);

    // //Se crea otro sprite con la misma textura
    // sf::Sprite character(texture);

    // //Posicion donde estará en la ventana.
    // character.setPosition(150, 40);

    // //Los 0 son las coordenadas en x y Y de donde se empezara a recortar la foto.
    // //Los otros dos es la resolución de la imagen.
    // character.setTextureRect(sf::IntRect(0, 0, 512, 444));

    //Aqui se guardan los eventos dentro de la ventana, eje: teclado, mouse, etc.
    sf::Event event;

    sf::Clock* clock{new sf::Clock()};
    float deltaTime{};

    window->setFramerateLimit(FPS);

    Inputs* inputs{new Inputs()};

    sf::Texture* tilesTexture1{new sf::Texture()};
    tilesTexture1->loadFromFile(TILES1);

    sf::Texture* tilesTexture2{new sf::Texture()};
    tilesTexture2->loadFromFile(TILES2);

    Character* character1{new Character(tilesTexture2, 16 * 1, 16 * 5, 16, 16, SPRITE_SCALE, SPRITE_SCALE)};
    Animation* idle{new Animation(0, 5, character1->GetSprite(), 40.f)};

    /*sf::RectangleShape* boxShape{new sf::RectangleShape(*(new sf::Vector2f(100, 100)))};
    boxShape->setPosition((WINDOW_WIDTH / 2), WINDOW_HEIGHT / 2);
    boxShape->setFillColor(sf::Color::Transparent);
    boxShape->setOutlineColor(sf::Color::Green);
    boxShape->setOutlineThickness(2.f);

    sf::CircleShape* pointShape{new sf::CircleShape(2.f)};
    pointShape->setPosition(boxShape->getPosition());
    pointShape->setFillColor(sf::Color::White);*/

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
            character1->GetSprite()->move(joystickAxis->x * deltaTime * PLAYER_MOVESPEED, joystickAxis->y * deltaTime * PLAYER_MOVESPEED);
            character1->FlipSpriteX(joystickAxis->x);
        }
        else
        {
            character1->GetSprite()->move(keyboardAxis->x * deltaTime * PLAYER_MOVESPEED, keyboardAxis->y * deltaTime * PLAYER_MOVESPEED);
            character1->FlipSpriteX(keyboardAxis->x);
        }

        idle->Play(deltaTime);

        window->clear(*(new sf::Color(71, 179, 240)));//Limipiar la pantalla y poner un color.
        // window->draw(*boxShape);//draw es para agregar lo que se dibuja.
        // window->draw(*pointShape);
        // window->draw(sprite);
        // window->draw(character);   
        window->draw(*character1->GetSprite());
        window->display(); //display para mostrar.

        sf::Time timeElapsed = clock->getElapsedTime();
        deltaTime = timeElapsed.asMilliseconds();
        clock->restart();

        //std::cout << "delta time: " << deltaTime << std::endl;

        delete keyboardAxis;
        delete joystickAxis;
    }
    
    return 0;
}