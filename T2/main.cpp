#include <iomanip>
#include <iostream>
#include <vector>
#include <random>
#include <conio.h>

struct Random
{
    Random(int min, int max)
        : DistribucionU(min, max)
    {}

    int operator()()
    {
        return DistribucionU(Engine);
    }

    std::default_random_engine Engine{ std::random_device()() };
    std::uniform_int_distribution<int> DistribucionU;
};

std::vector<std::vector<int>> stage(18, std::vector<int>(11,0));
std::vector<std::vector<int>> block =
{
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
};
std::vector<std::vector<int>>field(18,std::vector<int>(11,0));
//coordenadas

int y = 0;
int x = 4;
int puntaje = 9;

bool gameover = false;

size_t VELOCIDAD =  10000;

Random getRandom{0,6};

std::vector<std::vector<std::vector<int>>> bloques =
{
    {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0}
        },
        {
            {0,0,0,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,1,0,0}
        },
        {
            {0,0,1,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,1,0},
            {0,0,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,1,0,0},
            {1,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,1,1,0},
            {0,0,1,0},
            {0,0,1,0}
        }
};

int menu();
int gameOver();
int pausa();
void title();
void gameLoop();
void display();
bool crearBlocks();
void initGame();
void moveBlock(int, int);
void choque();
bool esChoque(int, int);
void userInput();
bool rotarBloque();
void spawnBlock();
void eliminarFila(size_t);
void seElimina();
void punteo();
bool lineaLlena(size_t, size_t);
int ganar();

int main()
{
    switch(menu())
    {
    case 1:
        gameLoop();
        break;
    case 2:
        return 0;
    case 0:
        std::cerr<< "Escoger 1 o 2" << std::endl;
        return -1;
    }
    return 0;
}

int gameOver()
{
    using namespace std;

    char a;
        cout << " #####     #    #     # ####### ####### #     # ####### ######\n" ;
        cout << "#     #   # #   ##   ## #       #     # #     # #       #     #\n";
        cout << "#        #   #  # # # # #       #     # #     # #       #     #\n";
        cout << "#  #### #     # #  #  # #####   #     # #     # #####   ######\n";
        cout << "#     # ####### #     # #       #     #  #   #  #       #   #\n";
        cout << "#     # #     # #     # #       #     #   # #   #       #    #\n";
        cout << " #####  #     # #     # ####### #######    #    ####### #     #\n";
        cout << "\n" ;
        cout << "#######\n" ;
        cout << "#\n";
        cout << "#\n";
        cout << "#####\n";
        cout << "#\n";
        cout << "#\n";
        cout << "\nPuntaje: " << puntaje << "\n";
        cout << "#\n";
        cout << "#\n";
        cout << "\n\nPresione cualquier tecla para continuar seguido de Enter.\n";
        cin >> a;

        y = 0;
        x = 0;
        puntaje = 0;
        gameover = false;


        switch(menu())
        {
        case 1:
            gameLoop();
            break;
        case 2:
            return 0;
        case 0:
            std::cerr<< "Escoger 1 o 2" << std::endl;
            return -1;
        }

        return 0;
}

int pausa()
{
    using namespace std;
    system("cls");
    char a;
        cout << " #####     #    #     # #######    #\n"
                "#     #   # #   #     # #         # #\n"
                "#     #  #   #  #     # #        #   #\n"
                "######  #     # #     # ####### #     #\n"
                "#       ####### #     #       # #######\n"
                "#       #     # #     #       # #     #\n"
                "#       #     #  #####  ####### #     #\n"
                "\n"
                "\nPuntaje: " << puntaje << "\n"
                "\n"
                "\n"
                "\n\nPresionar \"P\" para reanudar\n";
        cin >> a;
        switch (a) {
        case 'p':
                display();

            break;
        default:
            return -1;
        }
        return 0;
}
void gameLoop()
{
    size_t time = 0;
    initGame();

    while(!gameover)
    {
        if(kbhit())
        {
            userInput();
        }

        if(time < VELOCIDAD)
        {
            time++;
        }
        else
        {
            spawnBlock();
            time = 0;
        }
        seElimina();
        ganar();
    }
}

int menu()
{
    title();
    int select_num = 0;
    std::cin >>  select_num;

    switch(select_num)
    {
    case 1:
    case 2:
    case 3: break;
    default:
        select_num = 0;
        break;
    }
    return select_num;
}

void title()
{
    using namespace std;

    system("cls");
    cout << "#=====================================================#\n";

        cout << "   #    ####### ####### #     #  #####        #\n";
        cout << "  # #   #     # #     # #     #    #         ##\n";
        cout << " #   #  #     # #     # #     #    #        # #\n";
        cout << "####### ####### #     # #     #    #          #\n";
        cout << "#     # # #     #   # # #     #    #          #\n";
        cout << "#     # #   #   #    ## #     #    #          #\n";
        cout << "#     # #     # ####### #######  #####     #######\n";
        cout << "\n\n\n\n";

        cout << "\t<Menu>\n";
        cout << "\t1: Iniciar Juego\n\t2: Salir\n\n";

        cout << "#==================================================#\n";
        cout << "Elegir >> ";
}

void display()
{
    system("cls");

        for (size_t i = 0; i < 17; i++)
        {
            for (size_t j = 0; j < 10; j++)
            {
                switch (field[i][j])
                {
                case 0:
                    std::cout << " " << std::flush;
                    break;
                case 9:
                    std::cout << "*" << std::flush;
                    break;
                default:
                    std::cout << "#" << std::flush;
                    break;
                }
            }
            std::cout << std::endl;
        }
        std::cout << "\n\tA: izquierda\tS: abajo\tD: derecha \t rotar[espacio]\n";
        std::cout << "\n\tPuntaje: " << puntaje << "\n";

            if (gameover)
            {
                system("cls");
                gameOver();
            }
}

void initGame()
{
    for (size_t i = 0; i <= 16; i++)
        {
            for (size_t j = 0; j <= 9; j++)
            {
                if ((j == 0) || (j == 9) || (i == 16))
                {
                    field[i][j] = stage[i][j] = 9;
                }
                else
                {
                    field[i][j] = stage[i][j] = 0;
                }
            }
        }

        crearBlocks();

        display();
}

bool crearBlocks()
{
    x = 4;
    y = 0;

    int tipo = getRandom();

    for (size_t i = 0; i<4;i++){
        for(size_t j = 0; j<4; j++){
            block[i][j]=0;
            block[i][j] = bloques[tipo][i][j];
        }
    }
    for(size_t i= 0;i<4;i++)
    {
        for (size_t j = 0; j < 4; j++)
                {
                    field[i][j + 4] = stage[i][j + 4] + block[i][j];

                    if (field[i][j + 4] > 1)
                    {
                        gameover = true;
                        return true;
                    }
                }
    }
    return false;
}
void moveBlock(int x2, int y2)
{
    //Remover bloque
    for(size_t i = 0; i < 4; i++)
    {
        for(size_t j = 0; j<4; j++)
        {
            field[ y + i ][ x + j ] -= block[i][j];
        }
    }
    //actualizar coordenadas
    x = x2;
    y = y2;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
                field[y + i][x + j] += block[i][j];
        }
    }
    display();
}

void choque()
{
    for(size_t i = 0; i<17; i++)
    {
        for(size_t j = 0; j<10; j++)
        {
            stage[i][j] = field[i][j];
        }
    }
}
bool esChoque(int x2, int y2)
{
    for(size_t i = 0; i < 4; i++)
    {
        for(size_t j = 0; j<4; j++)
        {
            if(block[i][j] && stage[y2 + i][x2 + j] != 0)
            {
                return true;
            }
        }
    }
    return false;
}

void userInput()
{
    char key;
    key = getch();

    switch(key)
    {
    case 'd':
        if(!esChoque(x+1,y))
        {
            moveBlock(x+1,y);
        }
        break;
    case'a':
        if(!esChoque(x-1,y))
        {
            moveBlock(x-1,y);
        }
        break;
    case 's':
        if(!esChoque(x,y+1))
        {
            moveBlock(x,y+1);
        }
        break;
    case 'p':
        pausa();
        break;
    case ' ':
        rotarBloque();
    }
}

bool rotarBloque()
{
    std::vector<std::vector<int>> tmp(4,std::vector<int>(4,0));
    for(size_t i = 0; i<4;i++)
    {
        for(size_t j = 0;j<4;j++)
        {
            tmp[i][j] = block[i][j];
        }
    }
    for(size_t i = 0; i<4;i++)
    {
        for(size_t j = 0;j<4;j++)
        {
            block[i][j] = tmp[3-j][i];
        }
    }
    if(esChoque(x,y))
    {
        for(size_t i = 0; i<4;i++)
        {
            for(size_t j = 0;j<4;j++)
            {
                block[i][j] = tmp[i][j];
            }
        }
        return true;
    }
    for(size_t i = 0; i<4;i++)
    {
        for(size_t j = 0;j<4;j++)
        {
            field[y+i][x+j] -= tmp[i][j];
            field[y+i][x+j] += block[i][j];
        }
    }
    display();

    return false;
}

void spawnBlock()
{
    if(!esChoque(x,y+1))
    {
        moveBlock(x,y+1);
    }
    else
    {
        choque();
        crearBlocks();
        display();
    }
}
void seElimina()
{
    for (size_t i = 0; i < 17; i++)
    {
        size_t j = 1;
        if(lineaLlena(i,j))
        {
            eliminarFila(i);
            puntaje++;
        }

    }
}

void eliminarFila(size_t x)
{
    for (size_t i = x; i > 1; i--)
    {
        for(size_t j = 8; j>0;j--)
        {
            field[i][j]=field[i-1][j];
        }

    }
}
bool lineaLlena(size_t x,size_t y)
{
    if(y == 9)
    {
        return true;
    }
    if(field[x][y]==1)
    {
        return lineaLlena(x,y+1);
    }
    else
    {
        return false;
    }
}
int ganar()
{
    if(puntaje == 10)
    {
        system("cls");
        using namespace std;

        char a;
            cout << " #####     #    #     #    #    #     #    #    ####### ####### #######\n" ;
            cout << "#     #   # #   ##    #   # #   ##    #   # #   #          #    #\n";
            cout << "#        #   #  # #   #  #   #  # #   #  #   #  #          #    #\n";
            cout << "#  #### #     # #  #  # #     # #  #  # #     # #######    #    #####\n";
            cout << "#     # ####### #   # # ####### #   # # #######       #    #    #\n";
            cout << "#     # #     # #    ## #     # #    ## #     #       #    #    #\n";
            cout << " #####  #     # #     # #     # #     # #     # #######    #    #######\n";
            cout << "\n" ;
            cout << "\n" ;
            cout << "\n" ;
            cout << "\nPuntaje: " << puntaje << "\n";
            cout << "\n";
            cout << "\n";
            cout << "\n\nPresione cualquier tecla para continuar seguido de Enter.\n";
            cin >> a;

            y = 0;
            x = 0;
            puntaje = 0;
            gameover = false;


            switch(menu())
            {
            case 1:
                gameLoop();
                break;
            case 2:
                return 0;
            case 0:
                std::cerr<< "Escoger 1 o 2" << std::endl;
                return -1;
            }

            return 0;

    }
    return 0;
}
