#include "libs/luax/luax.h"
#include "audio/audio.h"
namespace jin
{
namespace module
{   
    static int l_init(lua_State* L) 
    {
        if (SDL_Init(SDL_INIT_AUDIO) < 0)
        {
            luax_error(L, "could not init audio");
            luax_pushboolean(L, false);
            return 1;
        }



        return 0; 
    }
   
    static int l_newSound(lua_State* L) 
    {
        
        return 0; 
    }
   
    static const luaL_Reg f[] = { 
        {"init",  l_init},
        {"Sound", l_newSound},
        {0, 0}
    };

    int luaopen_audio(lua_State* L)
    {
                
        return 1; 
    }
}
}