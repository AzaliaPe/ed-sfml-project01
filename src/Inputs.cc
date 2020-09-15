#include "Inputs.hh"

Inputs::Inputs()
{
    
}

Vec2* Inputs::GetKeyboardAxis()
{  
    //la clase Keyboard trae la inputs del teclado
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        x = -1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        x = 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        y = 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        y = -1;
    }
    return new Vec2(x, -y);
}

Vec2* Inputs::GetJoystickAxis()
{
    // Esto es para contar los Joystick
    // sf::Joystick::Count;   
        
    //Esto es por si hay un Joystick conectado

    //Cachamos el valor de axis X y Y, lo dividimos entre 100 por que el valor minimo de los axis es -100 y maximo 100
    //Hicimos lo mismo, pero en escala de 1
    x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) / 100;
    y= sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) / 100;

    //El joystick siempre manda datos aunque no lo estemos tocando
    //por eso se debe hacer un filtro de las entradas de este,
    //en este caso el espectro de menos a -0.2 y mayor a 0.2, que significa que si vale.
    x = x > 0.2f ? 1 : x < -0.2f ? -1 : 0;
    y = y > 0.2f ? 1 : y < -0.2f ? -1 : 0;
    
    return new Vec2(x, y);
}