/**
* Copyright (C) 2017 chai(neonum)
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is furnished
* to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __LUAX_H
#define __LUAX_H

#include "libs/lua51/lua.h"
#include "libs/lua51/lauxlib.h"
#include "libs/lua51/lualib.h"

// only for lua 5.1
#if LUA_VERSION_NUM == 501 

#define LUAX_VERSION "0.1.0"

#define luax_newstate luaL_newstate 
#define luax_openlibs luaL_openlibs
// load chunk but dont run it 
#define luax_loadbuffer luaL_loadbuffer
#define luax_pcall lua_pcall 
#define luax_setglobal lua_setglobal
#define luax_pop lua_pop
#define luax_newtable lua_newtable

/**
* 
*/
#define luax_setglobal_string(L, n, v) (lua_pushstring(L, v), lua_setglobal(L, n))

/**
* Get number of args 
*/
#define luax_gettop lua_gettop

/**
* Check userdata type.
*/
#define luax_checktype luaL_checkudata
#define luax_checknumber luaL_checknumber
#define luax_checkstring luaL_checkstring

/**
* Oprating tables. 
*/
#define luax_rawgetnumber(L, i, k) (lua_rawgeti(L,i, k), lua_tonumber(L, -1))

/**
* 
*/
#define luax_typerror luaL_typerror


/**
* Error checking
*/
#define luax_error luaL_error

/**
* Push value on the top of stack.
*/
#define luax_pushnumber  lua_pushnumber
#define luax_pushstring  lua_pushstring 
#define luax_pushinteger lua_pushinteger
#define luax_pushboolean lua_pushboolean

#define luax_rawseti lua_rawseti

/**
* Set field
*/
#define luax_setfield lua_setfield
#define luax_setfield_(T, L, k, v)\
   do { lua_push##T(L, v); lua_setfield(L, -2, k); } while (0)

#define luax_setfield_number(L, k, v) luax_setfield_(number, L, k, v)
#define luax_setfield_string(L, k, v) luax_setfield_(string, L, k, v)
#define luax_setfield_bool(L, k, v)   luax_setfield_(boolean, L, k, v)
#define luax_setfield_udata(L, k, v)  luax_setfield_(lightuserdata, L, k, v)
#define luax_setfield_cfunc(L, k, v)  luax_setfield_(cfunction, L, k, v)
#define luax_setfield_fstring(L, k, ...)\
   do { lua_pushfstring(L, __VA_ARGS__); lua_setfield(L, -2, k); } while (0)
/**
* Set raw 
*/
#define luax_setraw_(T, L, idx, i, v)\
    (lua_push##T(L, v), lua_rawseti(L, idx, i))

#define luax_setraw_string(L, idx, i, v) luax_setraw_(string, L, idx, i, v)
#define luax_setraw_number(L, idx, i, v) luax_setraw_(number, L, idx, i, v)
#define luax_setraw_bool(L, idx, i, v) luax_setraw_(boolean, L, idx, i, v)

/**
* 
*/
#define luax_optboolean(L, i, x)\
  (!lua_isnoneornil(L, i) ? lua_toboolean(L, i) : (x))
#define luax_optudata(L, i, name, x)\
  (!lua_isnoneornil(L, i) ? luaL_checkudata(L, i, name) : (x))
#define luax_optnumber luaL_optnumber

inline int luax_newlib(lua_State* L, const luaL_Reg* f)
{
    lua_createtable(L, 0, sizeof(f));
    for (; f && f->name; f++)
    {
        lua_pushcfunction(L, f->func);
        lua_setfield(L, -2, f->name);
    }
    return 1; // leave lib table on top of stack
}

/**
* Register a userdefined lua type with given type name.
*/
inline void luax_newtype(lua_State* L, const char* tname, const luaL_Reg* f)
{
    luaL_newmetatable(L, tname);

    // m.__index = m
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    if (f != 0)
        luaL_register(L, 0, f);

    lua_pop(L, 1); // Pops metatable.
}

/**
* Instance of a type.
*/
inline void* luax_newinstance(lua_State* L, const char* tname, int size)
{
    void* p = lua_newuserdata(L, size);

    //u->data = data;
    //u->flags = flags;
    //u->own = own;

    // luaL_getmetatable(L, tname) or 
    luaL_newmetatable(L, tname);
    lua_setmetatable(L, -2);
    
    return p;
}

/**
* require a module
*/
inline int luax_require(lua_State* L, const char* mname, lua_CFunction openf, int glb) 
{
    openf(L); 
    if (glb)
    {
        lua_setglobal(L, mname);
        return 0; 
    }
    return 1;
}

/**
* Return 1 if match. 
*/
inline int luax_istype(lua_State* L, int idx, const char* tname)
{
    if (lua_getmetatable(L, idx))
    {
        /* get metatable called tname */
        lua_getfield(L, LUA_REGISTRYINDEX, tname); 
        if (lua_rawequal(L, -1, -2))
        {
            lua_pop(L, 2); // pop both metatables
            return 1; 
        }
        lua_pop(L, 2);
        return 0; 
    }
    /* value at idx has no metatable */
    return 0;
}

#define luax_is(T, L, i) (lua_is##T(L, i))
#define luax_isnumber(L, i) luax_is(number, L, i)
#define luax_isstring(L, i) luax_is(string, L, i)
#define luax_istable(L, i) luax_is(table, L, i)
/**
* To userdata. 
*/
inline void* luax_toudata(lua_State* L, int idx)
{
    void* p = lua_touserdata(L, idx); 
    if (p == NULL)
        luaL_typerror(L, idx, "userdata"); // if p is not userdata
    return p; 
}

/**
* Get table index size. 
*/
inline int luax_tableidxlen(lua_State* L, int i)
{
    return lua_objlen(L, i);
}

/**
* Get table hash size 
inline int luax_tbalehashlen(lua_State* L, int i)
{

}
*/

/**
* Get table hash and index size 
inline int luax_tablelen(lua_State* L, int i)
{

}
*/

/**
* Set value i in stack a global value called v, and 
* don't pop it. 
*/
#define luax_justglobal(L, i, v) (lua_pushvalue(L, i), lua_setglobal(L, v))

inline int luax_table_insert(lua_State * L, int tindex, int vindex, int pos)
{
    if (tindex < 0)
        tindex = lua_gettop(L) + 1 + tindex;
    if (vindex < 0)
        vindex = lua_gettop(L) + 1 + vindex;
    if (pos == -1)
    {
        lua_pushvalue(L, vindex);
        lua_rawseti(L, tindex, lua_objlen(L, tindex) + 1);
        return 0;
    }
    else if (pos < 0)
        pos = lua_objlen(L, tindex) + 1 + pos;
    for (int i = lua_objlen(L, tindex) + 1; i > pos; i--)
    {
        lua_rawgeti(L, tindex, i - 1);
        lua_rawseti(L, tindex, i);
    }
    lua_pushvalue(L, vindex);
    lua_rawseti(L, tindex, pos);
    return 0;
}

/**
* Add the package loader to the package.loaders table.
*/
inline int luax_register_searcher(lua_State * L, lua_CFunction f, int pos)
{
    lua_getglobal(L, "package");

    if (lua_isnil(L, -1))
        return luaL_error(L, "Can't register searcher: package table does not exist.");

    lua_getfield(L, -1, "loaders");

    if (lua_isnil(L, -1))
        return luaL_error(L, "Can't register searcher: package.loaders table does not exist.");

    lua_pushcfunction(L, f);
    luax_table_insert(L, -2, -1, pos);
    lua_pop(L, 3);
    return 0;
}

#endif
#endif