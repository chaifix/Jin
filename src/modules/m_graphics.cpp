#include "libs/luax/luax.h"
#include "render/image.h"
#include "render/canvas.h"
#include "render/jsl.h"
#include "render/window.h"
#include "m_types.h"
#include "lua/graphics.lua.h"
#include "libs/GLee/GLee.h"
#include <SDL2/SDL.h>
using namespace jin::render;
namespace jin
{
namespace module
{
    /**
    * Init video system. 
    * jin.graphics.init(width, height, title) 
    */
    static int l_init(lua_State* L)
    {
        int w = luax_checknumber(L, 1);
        int h = luax_checknumber(L, 2);
        const char* t = luaL_checkstring(L, 3);
        /* init video subsystem */
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            luax_error(L, "could not init video");
            luax_pushboolean(L, false);
            return 1;
        }
        /* init window system */
        Window* wnd = Window::get();
        wnd->init(w, h, t); 
        /* bind window fbo by default */
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        /* init success */
        luax_pushboolean(L, true);
        return 1;
    }
    
    /**
    * Get windows size. 
    */
    static int l_getSize(lua_State* L) 
    {
        Window* wnd = Window::get(); 
        luax_pushnumber(L, wnd->getW());
        luax_pushnumber(L, wnd->getH()); 
        return 2; 
    }
    
    /**
    * Create a image userdata and set metatable for it.
    */
    static int l_newImage(lua_State* L)
    {
        Image* img = (Image*)luax_newinstance(L, TYPE_IMAGE, sizeof(Image));
        /* pseudo constructor */
        img->init();
        const char* f = luax_checkstirng(L, 1);
        img->loadf(f);
        return 1;
    }

    /**
    * Create a new JSL program. 
    */
    static int l_newShader(lua_State* L)
    {
        JSLProgram* j = (JSLProgram*)luax_newinstance(L, TYPE_JSL, sizeof(JSLProgram));

        return 1;
    }

    /**
    * Create a new Canvas, don't use it in loop, very slow.
    * jin.graphics.newCanvas(w, h)
    */
    static int l_newCanvas(lua_State* L)
    {
        Canvas* cvs = (Canvas*)luax_newinstance(L, TYPE_CANVAS, sizeof(Canvas));
        int w = luax_checknumber(L, 1); 
        int h = luax_checknumber(L, 2);
        cvs->init(w, h);
        return 1;
    }
    
    static int l_clear(lua_State* L)
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        return 0; 
    }

    /**
    * Swap render buffers, present current buffer to front. 
    */
    static int l_present(lua_State* L)
    {
        SDL_GL_SwapWindow(Window::get()->getWnd());
        return 0;
    }
    
    /* jin.graphics.draw(x, y, scalex, scaley, r) */
    static int l_draw(lua_State* L)
    {
        int x = luax_optnumber(L, 2, 0);
        int y = luax_optnumber(L, 3, 0);
        float sx = luax_optnumber(L, 4, 1);
        float sy = luax_optnumber(L, 5, 1);
        float r  = luax_optnumber(L, 6, 0);
        if (luax_istype(L, 1, TYPE_IMAGE))
        {
            /* is image */
            Image* p = (Image*)luax_toudata(L, 1);
            p->draw(x, y, sx, sy, r);
        }
        else if (luax_istype(L, 1, TYPE_CANVAS))
        {
            /* is canvas */
            Canvas* p = (Canvas*)luax_toudata(L, 1);
            p->draw(x, y, sx, sy, r);
        }
        else
        {
            /* wrong type */
			luax_typerror(L, 1, "image or canvas");
        }
        return 0; 
    }

    static int l_setColor(lua_State* L)
    {
        int r = luax_checknumber(L, 1); 
        int g = luax_checknumber(L, 2);
        int b = luax_checknumber(L, 3);
        int a = luax_checknumber(L, 4);
        glColor4f(r / 255.f, g / 255.f, b / 255.f, a / 255.f); 
        return 0;
    }
    
    static int l_bindCanvas(lua_State* L)
    {
        if (luax_gettop(L) == 0)
        {
            /* bind to default canvas */
            Canvas::unbind(); 
            return 0; 
        }
        Canvas* c = (Canvas*)luax_checktype(L, 1, TYPE_CANVAS);
        c->bind(); 
        return 0;
    }

    static int l_useShader(lua_State* L)
    {

        return 0;
    }
    
    static int l_newFont(lua_State* L)
    {
            
        return 0; 
    }

    static int l_setBlend(lua_State* L)
    {
        return 0; 
    }

	static int l_putPixel(lua_State* L)
	{

		return 0; 
	}

	static int l_drawLine(lua_State* L)
	{

		return 0; 
	}

	static int l_drawRect(lua_State* L)
	{

		return 0; 
	}

	static int l_drawCircle(lua_State* L)
	{

		return 0;
	}

	static int l_drawTriangle(lua_State* L)
	{
		return 0;
	}
    
	static int l_drawPolygon(lua_State* L)
	{
		return 0;
	}
    
    static const luaL_Reg f[] = {
        {"init",     l_init},
        {"getSize",  l_getSize}, 
        {"Image",    l_newImage},
        {"Shader",   l_newShader},
        {"Canvas",   l_newCanvas},
        {"Font",     l_newFont},
        {"clear",    l_clear},
        {"draw",     l_draw},
        {"color",    l_setColor},
        {"present",  l_present},
        {"blend",    l_setBlend},
        // bind canvas
        {"bind",     l_bindCanvas},
        // use shader 
        {"use",      l_useShader},
		// draw shapes
		{"pixel",	 l_putPixel},
		{"line",	 l_drawLine}, 
		{"rect",	 l_drawRect},
		{"circle",	 l_drawCircle},
        {"triangle", l_drawTriangle}, 
		{"polygon",  l_drawPolygon},
        {0, 0}
    };
    
    extern int luaopen_Image(lua_State* L);
    
    extern int luaopen_Canvas(lua_State* L);
    
    extern int luaopen_JSL(lua_State* L);
    
    int luaopen_graphics(lua_State* L)
    {
        luaopen_Image(L);
        luaopen_Canvas(L);
        //luaopen_JSL(L);
        luax_newlib(L, f); 
        // add some extra functions from lua script
        //if (luaL_loadbuffer(L, (const char *)graphics_lua, sizeof(graphics_lua), "graphics.lua") == 0)
        //    lua_call(L, 0, 0);
        return 1; 
    }
}
}