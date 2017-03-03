#ifndef __JIN_LUA_EMBED_H
#define __JIN_LUA_EMBED_H
#include <cstring>

namespace jin
{
namespace embed
{
    
    /**
    * embed lua script to context.
    */
#define embed(L, script, name) \
    if(luaL_loadbuffer(L, script, strlen(script), name) == 0)\
        lua_call(L, 0, 0);

    /**
    * embed structure. 
    */
    struct jin_Embed
    {
        const char* fname, *source;
    };

    static void boot(lua_State* L)
    {
        // embed scripts 
        #include "graphics.lua.h" // graphics 
        #include "keyboard.lua.h" // keyboard
        #include "mouse.lua.h"    // mouse
        #include "debug.lua.h"    // debug 
        #include "boot.lua.h"     // boot

        // embed scripts 
        const jin_Embed scripts[] = {
        { "graphics.lua", graphics_lua },
        { "keyboard.lua", keyboard_lua },
        { "mouse.lua",    mouse_lua },
        { "debug.lua",    debug_lua},
        { "boot.lua",     boot_lua },
        { 0, 0 }
        };
        
        // load all emebd lua scripts
        for (int i = 0; scripts[i].fname; i++)
            embed(L, scripts[i].source, scripts[i].fname);
    }
}
}

#endif