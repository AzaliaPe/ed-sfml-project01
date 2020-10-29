#pragma once

struct Vec2
{
    float x{}; //las llaves son para inicializar en 0
    float y{};

    Vec2(){}

    Vec2(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};
