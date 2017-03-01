#include "modules/m_jin.h"
#ifdef _WIN32
#include <SDL2/SDL_Main.h>
#endif

int main(int argc, char* argv[])
{
    /* global lua state */
    lua_State* L = luax_newstate();
    luax_openlibs(L);
    /* open jin module and sub modules */
    jin::module::luaopen_jin(L);
    luax_setglobal(L, MODULE_NAME);
    // 
    if (luaL_loadfile(L, "init.lua") == 0)
        lua_call(L, 0, 0);
    //getchar();
    return 0;
}