#include<iostream>
#include <SFML/Graphics.hpp>

#include "Inputs.hh"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_NAME "Roguelike game"

int main()
{
    //Esto es la ventana del gráfico
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
    
    //Para crear un sprite primero se tiene que crear una textura
    sf::Texture texture;

    //Aquí se carga la textura, 
    //se utiliza la sentencia if para comprobar si el archivo se ha cargado correctamente
    if(!texture.loadFromFile("sprites/character.png"))
    {
        //Esto es por si algo sale mal
        std::cout << "Load failed" << std::endl;
        
        system("pause");
    }

    //Aquí se crea el sprite
    sf::Sprite sprite;

    //Se asigna la textura
    sprite.setTexture(texture);

    //Esto dibuja una parte de la imágen 
    sprite.setTextureRect(sf::IntRect(0, 0, 100, 120));

    // // Esto es una mascara de color (Azul)
    // sprite.setColor(sf::Color(0, 0, 255));

    //Se mueve el sprite
    sprite.move(100, 100);

    //Se cambia el origen al centro del sprite
    sf::Vector2f centro;
    centro.x = sprite.getTextureRect().width / 2.f;
    centro.y = sprite.getTextureRect().height / 2.f;
    sprite.setOrigin(centro);
    
    //Aqui se rota el sprite 360 grados
    sprite.rotate(360);

    //Se crea otro sprite con la misma textura
    sf::Sprite character(texture);

    //Posicion donde estará en la ventana.
    character.setPosition(150, 40);

    //Los 0 son las coordenadas en x y Y de donde se empezara a recortar la foto.
    //Los otros dos es la resolución de la imagen.
    character.setTextureRect(sf::IntRect(0, 0, 512, 444));

    //Aqui se guardan los eventos dentro de la ventana, eje: teclado, mouse, etc.
    sf::Event event;

    Inputs* inputs = new Inputs();

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
        std::cout << "joystic axis x: " << joystickAxis->x << " joystic axis y: " << joystickAxis->y << std::endl;

        delete keyboardAxis;
        delete joystickAxis;
        
        window->clear(sf::Color(205, 252, 205));
        window->draw(sprite);
        window->draw(character);   
        window->display();
    }
    return 0;
}