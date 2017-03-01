#include "libs/luax/luax.h"
#include "render/image.h"
#include "m_types.h"
#include "utils/endian.h"
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
    #if JIN_BYTEORDER == JIN_BIG_ENDIAN
            /* big endian machine */
        int r = c & 0xff000000 >> 24;
        int g = c & 0xff0000 >> 16;
        int b = c & 0xff00 >> 8;
        int a = c & 0xff;
    #else
            /* little endian machine */
        int r = c & 0xff ; 
        int g = (c & 0xff00) >> 8;  
        int b = (c & 0xff0000) >> 16; 
        int a = (c & 0xff000000) >> 24; 
    #endif
        luax_pushnumber(L, r); 
        luax_pushnumber(L, g);
        luax_pushnumber(L, b);
        luax_pushnumber(L, a);
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