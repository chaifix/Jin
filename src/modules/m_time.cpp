#include "libs/luax/luax.h"
#include <SDL2/SDL.h>
namespace jin
{
namespace module
{

    static int l_sec(lua_State* L)
    {
        luax_pushnumber(L, SDL_GetTicks()/1000.f); 
        return 1;
    }

    static int l_sleep(lua_State* L)
    {
        double sec = luax_checknumber(L, 1); 
        SDL_Delay(sec * 1000);
        return 0; 
    }

    static const luaL_Reg f[] = {
        {"second",  l_sec},
        {"sleep",   l_sleep},
        {0, 0},
    };
    
    int luaopen_time(lua_State* L)
    {
        luax_newlib(L, f); 
        return 1; 
    }
}
}