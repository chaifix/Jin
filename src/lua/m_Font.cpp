#include "libs/luax/luax.h"
#include "m_types.h"
#include "render/font.h"

using namespace jin::render;

namespace jin
{
namespace module
{

    static int l_gc(lua_State* L)
    {
        return 0; 
    }

    static int l_box(lua_State* L)
    {
        Font* font = (Font*)luax_checktype(L, 1, TYPE_FONT);
        const char* text = luax_checkstring(L, 2); 
        int fheight = luax_checknumber(L, 3);
        int spacing = luax_checknumber(L, 4);
        int lheight = luax_checknumber(L, 5);
        int w, h; 
        font->box(text, fheight, lheight, spacing,  &w, &h);
        luax_pushnumber(L, w); 
        luax_pushnumber(L, h);
        return 2; 
    }

    static const luaL_Reg f[] = {
        {"__gc", l_gc},
        {"box",  l_box},
        {0, 0}
    };

    int luaopen_Font(lua_State* L)
    {
        luax_newtype(L, TYPE_FONT, f);

        return 0;
    }

}
}