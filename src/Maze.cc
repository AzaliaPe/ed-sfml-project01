#include<Maze.hh>

Maze::Maze(unsigned int N, unsigned int M, const char* path)
{
    this->N = N;
    this->M = M;
    this->path = path;
    tiles = new char*[N];
    reader->open(path);
    AllocateMemory();
    FillArray();
}

void Maze::AllocateMemory()
{
    for(int i{}; i < N; i++)
    {
        tiles[i] = new char[M];
    }
}

void Maze::FillArray()
{
    for(int i{}; i < N; i++)
    {
        for(int j{}; j < M; j++)
        {
            *reader >> tiles[i][j];
        }
    }
}

char** Maze::GetTiles() const
{
    return tiles;
}

Maze::~Maze()
{
}