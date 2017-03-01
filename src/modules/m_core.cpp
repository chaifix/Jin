#include "libs/luax/luax.h"
#include "core/game.h"
using namespace jin::core; 
namespace jin
{
namespace module
{
    static int l_running(lua_State* L)
    {
        bool r = Game::get()->running();
        luax_pushboolean(L, r); 
        return 1; 
    }

    static int l_quit(lua_State* L)
    {
        Game::get()->quit();
        return 0;
    }

    static const luaL_Reg f[] = {
        {"running", l_running}, 
        {"quit",    l_quit}, 
        {0, 0}
    };

    int luaopen_core(lua_State* L)
    {
        luax_newlib(L, f); 

        return 1; 
    }
}
}