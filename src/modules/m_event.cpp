/**
* Event module 
*/
#include "input/event.h"
#include "libs/luax/luax.h"
#include "SDL2/SDL.h"
#include "input/event.h"
#include "input/mouse.h"
#include "input/keyboard.h"
using namespace jin::input;
namespace jin
{
namespace module
{
    /**
    * Load event poll, return a iterator(a table). 
    */
    static int l_event_poll(lua_State *L)
    {
        // table to store events
        luax_newtable(L); 
        SDL_Event e; 
        int i = 1;
        poll:
        while (SDL_PollEvent(&e))
        {
            // each event is a table 
            luax_newtable(L);
            switch (e.type)
            {
            case SDL_QUIT: 
                luax_setfield_string(L, "type", "quit");
            break;
            case SDL_KEYDOWN: 
                luax_setfield_string(L, "type", "keydown");
                luax_setfield_string(L, "key", SDL_GetKeyName(e.key.keysym.sym));
            break;
            case SDL_KEYUP: 
                luax_setfield_string(L, "type", "keyup");
                luax_setfield_string(L, "key", SDL_GetKeyName(e.key.keysym.sym));
            break; 
            case SDL_MOUSEMOTION: 
                luax_setfield_string(L, "type", "mousemotion");
                luax_setfield_number(L, "x", e.motion.x);
                luax_setfield_number(L, "y", e.motion.y);
            break; 
            case SDL_MOUSEBUTTONDOWN: 
                luax_setfield_string(L, "type", "mousebuttondown");
                luax_setfield_string(L, "button", buttonStr(e.button.button));
                luax_setfield_number(L, "x", e.button.x);
                luax_setfield_number(L, "y", e.button.y);
            break; 
            case SDL_MOUSEBUTTONUP:
                luax_setfield_string(L, "type", "mousebuttonup");
                luax_setfield_string(L, "button", buttonStr(e.button.button));
                luax_setfield_number(L, "x", e.button.x);
                luax_setfield_number(L, "y", e.button.y);
            break;
            case SDL_MOUSEWHEEL: 
                luax_setfield_string(L, "type", "wheel");
                if(e.wheel.x == -1)
                    luax_setfield_string(L, "x", "left");
                else if(e.wheel.x == 1) 
                    luax_setfield_string(L, "x", "right");
                else 
                    luax_setfield_string(L, "x", "none");

                if (e.wheel.y == -1)
                    luax_setfield_string(L, "y", "near");
                else if (e.wheel.y == 1)
                    luax_setfield_string(L, "y", "far");
                else
                    luax_setfield_string(L, "y", "none");
            break;
            default:
                /* ignore other events */ 
                luax_pop(L, 1); // pop table out
                goto poll;
            break;
            }
            luax_rawseti(L, -2, i++);
        }
        return 1;
    }

    static const luaL_Reg f[] = {
        { "poll", l_event_poll },
        { 0 ,0 }
    };

    /**
    * load event module
    */
    int luaopen_event(lua_State* L)
    {
        luax_newlib(L, f);
        return 1; 
    }
}
}