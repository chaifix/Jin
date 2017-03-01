#ifndef __JIN_M_JIN_H
#define __JIN_M_JIN_H
#include "libs/luax/luax.h"

#define MODULE_NAME "jin"
#define VERSION     "0.1.0"
#define AUTHOR      "chai(neonum) \nemail: shu_chai@163.com"

namespace jin
{
namespace module
{

    /**
    * open jin to lua
    */
    int luaopen_jin(lua_State* L);

}
}
#endif