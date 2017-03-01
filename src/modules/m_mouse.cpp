#include "libs/luax/luax.h"
#include "SDL2/SDL.h"
namespace jin
{
namespace module
{
    static int l_pos(lua_State* L)
    {
        int x, y; 
        SDL_GetMouseState(&x, &y);
        luax_pushnumber(L, x); 
        luax_pushnumber(L, y);
        return 2; 
    }

    static const luaL_Reg f[] = {
        {"position", l_pos},
        {0, 0}
    };
    
    int luaopen_mouse(lua_State* L)
    {
        luax_newlib(L, f);
        return 1;
    }
}
}