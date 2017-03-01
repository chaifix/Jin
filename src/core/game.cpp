#include "game.h"

namespace jin
{
namespace core
{
    Game* Game::g_game = 0; 
    
    Game::Game() :run(true) {};
    
    Game* Game::get()
    {
        return g_game ? g_game : (g_game = new Game());
    }

    void Game::quit()
    {
        run = false;
    }

    bool Game::running()
    {
        return run;
    }
}
}

