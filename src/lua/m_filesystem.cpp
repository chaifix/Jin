#include "libs/luax/luax.h"
#include "fs/filesystem.h"
#include <string>

using namespace jin::fs;

namespace jin
{
namespace module
{

    static struct
    {
        Filesystem* fs; 
    } context;

    static int l_init(lua_State* L)
    {
        context.fs = Filesystem::get();
        return 0; 
    }

    /**
    * set current game root, like 
    * C:/jin/games/tank/ 
    */
    static int l_mount(lua_State* L)
    {
        const char* path = luax_checkstring(L, 1);
        context.fs->mount(path);
        return 0;
    }

    /**
    * 
    */
    static int l_isDir(lua_State *L)
    {
        const char* path = luax_checkstring(L, 1);
        int r = context.fs->isDir(path);
        luax_pushboolean(L, r); 
        return 1; 
    }

    /**
    * 
    */
    static int l_exist(lua_State * L)
    {
        const char* path = luax_checkstring(L, 1);
        int r = context.fs->exists(path);
        luax_pushboolean(L, r);
        return 1;
    }

    static int l_isdir(lua_State* L)
    {
        const char* path = luax_checkstring(L, 1);
        int r = context.fs->isDir(path);
        luax_pushboolean(L, r);
        return 1;
    }

    // load but dont run it 
    static int loadf(lua_State* L)
    {
        const char* filename = lua_tostring(L, -1);
        Buffer bf; 
        context.fs->read(filename, &bf);
        luax_loadbuffer(L, (const char*)bf.data, bf.size, filename);
        return 1; 
    }

    static int loader(lua_State* L)
    {
        const char * filename = lua_tostring(L, -1);

        std::string tmp(filename);
        tmp += ".lua";

        int size = tmp.size();

        for (int i = 0; i<size - 4; i++)
        {
            if (tmp[i] == '.')
            {
                tmp[i] = '/';
            }
        }

        // Check whether file exists.
        if (context.fs->exists(tmp.c_str()))
        {
            lua_pop(L, 1);
            lua_pushstring(L, tmp.c_str());
            // Ok, load it.
            return loadf(L);
        }

        tmp = filename;
        size = tmp.size();
        for (int i = 0; i<size; i++)
        {
            if (tmp[i] == '.')
            {
                tmp[i] = '/';
            }
        }

        if (context.fs->isDir(tmp.c_str()))
        {
            tmp += "/init.lua";
            if (context.fs->exists(tmp.c_str()))
            {
                lua_pop(L, 1);
                lua_pushstring(L, tmp.c_str());
                // Ok, load it.
                return loadf(L);
            }
        }

        lua_pushfstring(L, "\n\tno file \"%s\" in jin game directories.\n", (tmp + ".lua").c_str());
        return 1;
    }

    static const luaL_Reg f[] = {
        {"init",  l_init},
        {"mount", l_mount},
        {"isdir", l_isDir},
        {"exist", l_exist},
        {0, 0}
    };

    int luaopen_filesystem(lua_State* L)
    {
        luax_newlib(L, f);
        luax_register_searcher(L, loader, 1); 
        return 0;
    }

}
}