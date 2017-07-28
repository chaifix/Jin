#include "libs/luax/luax.h"
#include "lua/embed/keyboard.lua.h"

namespace jin
{
namespace module
{

    int luaopen_keyboard(lua_State* L)
    {
        luax_newlib(L, 0); 
        return 1;
    }

}
}