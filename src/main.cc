#include<iostream>
#include <SFML/Graphics.hpp>

#include "Inputs.hh"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_NAME "Roguelike game"
#define TILES1 "assets/sprites/tiles.png"
#define SPRITE_SCALE 2.f

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

    Inputs* inputs {new Inputs()};

    sf::Texture* tilesTexture1{new sf::Texture()};
    tilesTexture1->loadFromFile(TILES1);

    sf::Sprite* sprite1{new sf::Sprite(*tilesTexture1, *(new sf::IntRect(16 * 0, 16 * 11, 16, 16)))};
    sprite1->setScale(*(new sf::Vector2f(SPRITE_SCALE, SPRITE_SCALE)));
    //sprite1->setPosition((WINDOW_WIDTH / 2), WINDOW_HEIGHT / 2);

    // sf::RectangleShape* boxShape{new sf::RectangleShape(*(new sf::Vector2f(100,100)))};
    // boxShape->setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    // boxShape->setFillColor(sf::Color::Transparent);
    // boxShape->setOutlineColor(sf::Color::Green);
    // boxShape->setOutlineThickness(2.f);

    // sf::CircleShape* pointShape{new sf::CircleShape(2.f)};
    // pointShape->setPosition(boxShape->getPosition());
    // pointShape->setFillColor(sf::Color::White);

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

        //std::cout << "keyboard axis x: " << keyboardAxis->x << " keyboard axis y: " << keyboardAxis->y << std::endl;
        // std::cout << "joystic axis x: " << joystickAxis->x << " joystic axis y: " << joystickAxis->y << std::endl;

        // if(sf::Joystick::isConnected(0))
        // {
        //     //sf::Vector2f* newPosition{new sf::Vector2f(joystickAxis->x, joystickAxis->y)};
        //     //boxShape->setPosition(boxShape->getPosition() + *newPosition);
        //     boxShape->move(joystickAxis->x, joystickAxis->y);
        // }
        // else
        // {
        //     //sf::Vector2f* newPosition{new sf::Vector2f(keyboardAxis->x, keyboardAxis->y)};
        //     //boxShape->setPosition(boxShape->getPosition() + *newPosition);
        //     boxShape->move(keyboardAxis->x, keyboardAxis->y);
        // }
        // pointShape->setPosition(boxShape->getPosition());

        if(sf::Joystick::isConnected(0))
        {
            sprite1->move(joystickAxis->x, joystickAxis->y);
        }
        else
        {
            sprite1->move(keyboardAxis->x, keyboardAxis->y);
        }

        // window->clear(sf::Color(205, 252, 205)); 
        window->clear(sf::Color::Black);//Limipiar la pantalla y poner un color.
        // window->draw(*boxShape);//draw es para agregar lo que se dibuja.
        // window->draw(*pointShape);
        window->draw(*sprite1);
        // window->draw(sprite);
        // window->draw(character);   
        window->display();//display para mostrar.

        delete keyboardAxis;
        delete joystickAxis;
    }
    return 0;
}