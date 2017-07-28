#ifdef _WIN32
// SDL main entry
#include <SDL2/SDL_Main.h>
// directory 
#include <direct.h>
#endif

// luax 
#include "libs/luax/luax.h"

// load jin module
#include "lua/m_jin.h"
using namespace jin::module;

#include "fs/filesystem.h"

int main(int argc, char* argv[])
{

    // global lua state, all lua values are here 
    lua_State* L = luax_newstate();
    luax_openlibs(L);

    /**
    * open jin module, jin module is on the top 
    * of stack
    */
    luaopen_jin(L);

    // add args to global field
    luax_newtable(L); 
    for (int i = 0; i < argc; i++)
        luax_setraw_string(L, -2, i + 1, argv[i]);
    luax_setfield(L, -2, "_argv");
    
    /**
    * jin._dir is the folder of jin binary executable
    */
    int bsize = 1024;
    char* buffer = new char[bsize];
#ifdef _WIN32
    _getcwd(buffer, bsize);
#elif defined __unix__
#elif defined __APPLE__
#endif
#undef BUFFER_SIZE
    luax_setfield_string(L, "_dir", buffer);
    delete[] buffer;
    
    // boot
    boot(L);

    return 0;
}