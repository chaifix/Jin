#include "libs/luax/luax.h"
#include "render/image.h"
#include "m_types.h"

using namespace jin::render;

namespace jin
{
namespace module
{

    static int l_getWidth(lua_State* L)
    {
        Image* i = (Image*)luax_checktype(L, 1, TYPE_IMAGE);
        luax_pushnumber(L, i->getWidth()); 
        return 1; 
    }

    static int l_getHeight(lua_State *L)
    {
        Image* i = (Image*)luax_checktype(L, 1, TYPE_IMAGE);
        luax_pushnumber(L, i->getHeight());
        return 1;
    }

    static int l_getPixel(lua_State* L)
    {
        Image* i = (Image*)luax_checktype(L, 1, TYPE_IMAGE);
        int x = luax_checknumber(L, 2); 
        int y = luax_checknumber(L, 3);
        color c = i->getPixel(x, y); 
        luax_pushnumber(L, c.r); 
        luax_pushnumber(L, c.g);
        luax_pushnumber(L, c.b);
        luax_pushnumber(L, c.a);
        return 4;
    }

    static int l_setAnchor(lua_State* L)
    {
        Image* i = (Image*)luax_checktype(L, 1, TYPE_IMAGE);
        int x = luax_checknumber(L, 2); 
        int y = luax_checknumber(L, 3); 
        i->setAnchor(x, y);
        return 0; 
    }

    static int l_getSize(lua_State* L)
    {
        Image* i = (Image*)luax_checktype(L, 1, TYPE_IMAGE);
        luax_pushnumber(L, i->getWidth());
        luax_pushnumber(L, i->getHeight());
        return 2;
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
        {"getPixel",  l_getPixel},
        {"setAnchor", l_setAnchor},
        {0, 0 }
    };

    int luaopen_Image(lua_State* L)
    {
        luax_newtype(L, TYPE_IMAGE, f);
        return 0;
    }

}// graphics
}// jin