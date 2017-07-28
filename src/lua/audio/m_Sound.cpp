#include "libs/luax/luax.h"

namespace jin
{
namespace module
{

    static int l_play(lua_State* L)
    {

        return 0; 
    }

    static const luaL_Reg f[] = {
        {"play", l_play},
        {0, 0}
    };

    int luaopen_Sound(lua_State* L)
    {

        return 1; 
    }
}
}