#include "m_jin.h"
#include "libs/luax/luax.h"
#include "lua/init.lua.h"
namespace jin
{
namespace module
{
    /**
    * sub modules
    */
    extern int luaopen_core(lua_State* L);
    extern int luaopen_graphics(lua_State* L);
    extern int luaopen_audio(lua_State* L);
    extern int luaopen_net(lua_State* L);
    extern int luaopen_event(lua_State* L);
    extern int luaopen_time(lua_State* L);
    extern int luaopen_mouse(lua_State* L);
    extern int luaopen_keyboard(lua_State* L);
    extern int luaopen_filesystem(lua_State* L); 

    static int l_getversion(lua_State* L)
    {
        luax_pushstring(L, VERSION);
        return 1; 
    }

    static int l_getAuthor(lua_State* L)
    {
        luax_pushstring(L, AUTHOR);
        return 1; 
    }

    static int l_getOS(lua_State* L)
    {
    #ifdef _WIN32 
        luax_pushstring(L, "windows");
    #elif defined __unix__
        luax_pushstring(L, "unix");
    #elif defined __APPLE__
        luax_pushstring(L, "macos");
    #endif
        return 1;
    }

    static const luaL_Reg f[] = {
        {"version", l_getversion},
        {"author",  l_getAuthor},
        {"os",      l_getOS},
        //
        {0, 0}
    };
    
    static const luaL_Reg mods[] = {
        {"core",       luaopen_core},
        {"event",      luaopen_event},
        {"graphics",   luaopen_graphics},
        {"time",       luaopen_time}, 
        {"mouse",      luaopen_mouse},
		{"keyboard",   luaopen_keyboard},
		/*
		{"filesystem", luaopen_filesystem},
        {"net",        luaopen_net},
        {"audio",      luaopen_audio}
        */
		{0, 0}
    };

    int luaopen_jin(lua_State* L)
    {
		luax_newlib(L, f); // jin module is on top of the stack 

		// register submodules
        for (int i = 0; mods[i].name; i++)
        {
            mods[i].func(L); // open submodules
            luax_setfield(L, -2, mods[i].name);
        }

        // run init.lua at the end 
        //if (luaL_loadbuffer(L, (const char *)graphics_lua, sizeof(init_lua), "init.lua") == 0)
        //    lua_call(L, 0, 0);

        return 1;
    }
}
}