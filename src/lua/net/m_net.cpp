/** 
* Notice: the net module is not finished yet. 
*/
#include "libs/luax/luax.h"
#include "libs/tekcos/tekcos.h"

namespace jin
{
namespace module
{

    struct
    {
        tk_TCPsocket* sk; 
    }context;

    /**
    * A table is needed. For example: 
    *   local conf = { 
    *       mode = "server", 
    *       ip = "", 
    *       port = 8000
    *   } 
    */
    static int l_open(lua_State* L)
    {
        // init context.sk 
        context.sk = 0; 
        if (!luax_istable(L, 1))
        {
            luax_typerror(L, 1, "table is needed"); 
            return 0;
        }
        luax_getfield(L, 1, "mode");
        if (luax_isnil(L, -1))
        {// no mode field 
            luax_error(L, "mode field is needed, but get nil");
            return 0;
        }
        const char* mode = luax_checkstring(L, -1);
        if (strcmp(mode, "server") == 0 || strcmp(mode, "client") == 0)
        {
            
            if (strcmp(mode, "server") == 0)
            {// a server, ignore ip field
                
            }
            else
            {

            }
        }
        else
        {
            luax_error(L, "\"server\" or \"client\" is needed, but get %s", mode);
            return 0; 
        }
        return 1;
    }

    static int l_accept(lua_State* L)
    {
        return 1; 
    }

    static int l_send(lua_State* L)
    {
        return 1;
    }

    static int l_recv(lua_State* L)
    {
        return 1;
    }

    static int l_close(lua_State* L)
    {
        return 1;
    }

    static int l_nonblocking(lua_State* L)
    {
        return 1;
    }

    // block mode by default 
    static int l_blocking(lua_State* L)
    {
        return 1;
    }

    static const luaL_Reg f[] = {
        {"open",        l_open},
        {"accept",      l_accept}, 
        {"send",        l_send},
        {"recv",        l_recv},
        {"close",       l_close},
        {"blocking",    l_blocking },
        {"nonblocking", l_nonblocking},
        {0, 0}
    };

    // only tcp
    int luaopen_net(lua_State* L)
    {
        luax_newlib(L, f);

        return 1;
    }
}
}