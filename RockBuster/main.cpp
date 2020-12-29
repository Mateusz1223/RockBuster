#include "Game.h"
#include "common.h"

int main()
{
    initCommon();

    Game game;

    while (game.isWindowOpen())
    {
        game.update();
        game.render();
    }

    return 0;
}