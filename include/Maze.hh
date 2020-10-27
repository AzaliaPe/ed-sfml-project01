#pragma once
#include<fstream>
#include<iostream>
#include<SFML/Graphics.hpp>
#include "Tile.hh"

class Maze
{
    private:
        unsigned int N{}, M{};
        const char* path{};
        std::ifstream* reader{new std::ifstream()};
        char** tiles{};
        float scale, cropSize;
        sf::Texture* texture;
        std::vector<Tile*>* container{new std::vector<Tile*>()};
    public:
        Maze(unsigned int, unsigned int, float, float, sf::Texture*&, const char*);
        void AllocateMemory();
        void FillArray();
        char** GetTiles() const;
        ~Maze();
        void Generate();
        std::vector<Tile*>* GetContainer() const;
};