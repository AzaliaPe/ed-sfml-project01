#include<iostream>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_NAME "Roguelike game"

int main()
{
    //Esto de aquí funciona igual, pero no se esta generando en el heap, por lo que no es lo ideal.
    // sf::RenderWindow window(sf::VideoMode(800, 600), "Platform Game");
    // sf::Event event;
    // while(window.isOpen())
    // {
       
    // }

    //Esto es la ventana del grafico
    sf::Window* window = new sf::Window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
    //Aquí se guardan los eventos dentro de la ventana, eje: teclado, mouse, etc.
    sf::Event event;
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

        //la clase Keyboard trae la inputs del teclado
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            std::cout << "left" << std::endl;
        }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            std::cout << "right" << std::endl;
        }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            std::cout << "up" << std::endl;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            std::cout << "down" << std::endl;
        }

        // Esto es para contar los Joystick
        // sf::Joystick::Count;   
        
        //Esto es por si hay un Joystick conectado
        if(sf::Joystick::isConnected(0)) //Aqui se busca el Joystick 0, el primero que salga
        {
            //Cachamos el valor de axis X y Y, lo dividimos entre 100 por que el valor minimo de los axis es -100 y maximo 100
            //Hicimos lo mismo, pero en escala de 1
            float x{sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) / 100};
            float y{sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) / 100};

            //El joystick siempre manda datos aunque no lo estemos tocando
            //por eso se debe hacer un filtro de las entradas de este,
            //en este caso el espectro de menos a -0.2 y mayor a 0.2, que significa que si vale.
            x = x > 0.2f ? 1 : x < -0.2f ? -1 : 0;
            y = -(y > 0.2f ? 1 : y < -0.2f ? -1 : 0);

            std::cout << "X: " << x << " Y: " << y << std::endl;
            std::cout << "X: " << x << " Y: " << y << std::endl;
        }
    }
    //Tarea: meter todos estos inputs en un class
    return 0;
}