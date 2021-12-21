#include "game.h"

int main()
{
    Game game;

	game.init();

	game.defineMenu();

    while (game.loop())
    {}
}
