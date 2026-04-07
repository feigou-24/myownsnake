#include "Food.h"
#include <cstdlib>

Food::Food()
{
    generate();
}

void Food::generate()
{
    posX = rand() % (mapWidth - 2) + 1;
    posY = rand() % (mapHeight - 2) + 1;
}
