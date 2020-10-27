#include "Maze.hh"

Maze::Maze(unsigned int N, unsigned int M, float scale, float cropSize, sf::Texture*& texture, const char* path)
{
    this->N = N;
    this->M = M;
    this->scale = scale;
    this->cropSize = cropSize;
    this->texture = texture;
    this->path = path;
    tiles = new char*[N];
    reader->open(path);
    AllocateMemory();
    FillArray();
    Generate();
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

void Maze::Generate()
{
    for(int i = 0; i < N; i++)
    {
        for(int x = 0; x < M; x++)
        {

           char& tile{tiles[i][x]};

           switch (tile)
           {
            case 'w'://Pared normal
                container->push_back(new Tile(cropSize * 1, cropSize * 1, scale, cropSize, texture));
               break;
            case 'e'://Bandera roja
                container->push_back(new Tile(cropSize * 1, cropSize * 2, scale, cropSize, texture));
               break;
            case 'r'://Bandera azul
                container->push_back(new Tile(cropSize * 2, cropSize * 2, scale, cropSize, texture));
               break;
            case 'f'://Bandera amarilla
                container->push_back(new Tile(cropSize * 2, cropSize * 3, scale, cropSize, texture));
                break;
            case 't'://Pared con hoyo
                container->push_back(new Tile(cropSize * 3, cropSize * 3, scale, cropSize, texture));
               break;
            case 'v'://Bandera verde
                container->push_back(new Tile(cropSize * 1, cropSize * 3, scale, cropSize, texture));
                break;
            case 'b'://Pared cosa verde
                container->push_back(new Tile(cropSize * 4, cropSize * 5, scale, cropSize, texture));
                break;
            case 'u'://Pared pilar1
                container->push_back(new Tile(cropSize * 6, cropSize * 5, scale, cropSize, texture));
                break;
            case 'x'://Pared pilar2
                container->push_back(new Tile(cropSize * 6, cropSize * 6, scale, cropSize, texture));
                break;
            case 'g'://Piso normal
                container->push_back(new Tile(cropSize * 1, cropSize * 4, scale, cropSize, texture));
               break;
            case 'a'://Piso roto esquina inferior izquierda
                container->push_back(new Tile(cropSize * 1, cropSize * 5, scale, cropSize, texture));
               break;
            case 's'://Piso roto esquina superior izquierda
                container->push_back(new Tile(cropSize * 2, cropSize * 6, scale, cropSize, texture));
               break;
            case 'm'://Piso donde sale una escalera
                container->push_back(new Tile(cropSize * 3, cropSize * 6, scale, cropSize, texture));
               break;
            case 'z'://Piso quebrado
                container->push_back(new Tile(cropSize * 2, cropSize * 4, scale, cropSize, texture));
               break;
            case 'p'://Piso roto con hoyitos
                container->push_back(new Tile(cropSize * 3, cropSize * 5, scale, cropSize, texture));
               break;
            case 'c'://Piso donde cae la cosa verde
                container->push_back(new Tile(cropSize * 4, cropSize * 6, scale, cropSize, texture));
               break;
            case 'n'://Piso donde hay un agujero
                container->push_back(new Tile(cropSize * 6, cropSize * 9, scale, cropSize, texture));
               break;
            case 'j'://Piso donde esta el pilar
                container->push_back(new Tile(cropSize * 6, cropSize * 7, scale, cropSize, texture));
               break;
            default:
               break;
           }
           container->back()->Move(cropSize * scale * x, cropSize * scale * i);
        }
    }
}

std::vector<Tile*>* Maze::GetContainer() const
{
    return container;
}

char** Maze::GetTiles() const
{
    return tiles;
}

Maze::~Maze()
{
}