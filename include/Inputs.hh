//class es para cosas privadas

//struct es para cosas publicas

#include<iostream>
#include <SFML/Graphics.hpp>
#include "Vec2.hh"

struct Inputs
{
    float x{};
    float y{};

    Vec2* keyboardAxis;
    Vec2* joystickAxis;

    //Constructor
    Inputs();

    Vec2* GetKeyboardAxis();
    Vec2* GetJoystickAxis();
};