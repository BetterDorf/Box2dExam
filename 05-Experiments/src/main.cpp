#include <iostream>
#include "Entity.h"
#include "game.h"

int main()
{
    Game game;

    game.init();

    game.loop();
}
