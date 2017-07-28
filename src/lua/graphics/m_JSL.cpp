#include "libs/luax/luax.h"
#include "../m_types.h"
namespace jin
{
namespace module
{
    /**
    * Use send function send variables to JSL program. 
    */
    static int l_send(lua_State* L)
    {

        return 1; 
    }

    static const luaL_Reg f[] = {
        {"send",  l_send},
        {0, 0}
    };

    /**
    * JSL program
    */
    int luaopen_JSL(lua_State* L)
    {
        luax_newtype(L, TYPE_JSL, f);
        return 0;
    }
}
}