#include "libs/luax/luax.h"
#include "m_types.h"
#include "render/canvas.h"
using namespace jin::render;
namespace jin
{
namespace module
{
    static int l_getWidth(lua_State* L)
    {
        Canvas* c = (Canvas*)luax_checktype(L, 1, TYPE_CANVAS);
        luax_pushnumber(L, c->getWidth());
        return 1;
    }

    static int l_getHeight(lua_State* L)
    {
        Canvas* c = (Canvas*)luax_checktype(L, 1, TYPE_CANVAS);
        luax_pushnumber(L, c->getHeight());
        return 1;
    }

    static int l_getSize(lua_State* L)
    {
        Canvas* c = (Canvas*)luax_checktype(L, 1, TYPE_CANVAS);
        luax_pushnumber(L, c->getWidth());
        luax_pushnumber(L, c->getHeight());
        return 2;
    }

    static int l_setAnchor(lua_State* L)
    {
        Canvas* c = (Canvas*)luax_checktype(L, 1, TYPE_CANVAS);
        int x = luax_checknumber(L, 1); 
        int y = luax_checknumber(L, 2);
        c->setAnchor(x, y);
        return 0; 
    }

    static int l_gc(lua_State* L)
    {

        return 0;
    }

    static const luaL_Reg f[] = {
        {"__gc",      l_gc},
        {"getWidth",  l_getWidth},
        {"getHeight", l_getHeight},
        {"getSize",   l_getSize},
        {"setAnchor", l_setAnchor},
        {0, 0 }
    };

    int luaopen_Canvas(lua_State* L)
    {
        luax_newtype(L, TYPE_CANVAS, f);
        return 1;
    }
}
}