#include<fstream>

class Maze
{
    private:
        unsigned int N{}, M{};
        const char* path{};
        std::ifstream* reader{new std::ifstream()};
        char** tiles{};
    public:
        Maze(unsigned int, unsigned int, const char*);
        void AllocateMemory();
        void FillArray();
        char** GetTiles() const;
        ~Maze();
};