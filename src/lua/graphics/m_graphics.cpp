#include "libs/luax/luax.h"
#include "render/image.h"
#include "render/canvas.h"
#include "render/jsl.h"
#include "render/graphics.h"
#include "render/window.h"
#include "render/font.h"
#include "../m_types.h"
#include "lua/embed/graphics.lua.h"
#include "libs/GLee/GLee.h"
#include "fs/filesystem.h"
#include <SDL2/SDL.h>

using namespace jin::render;
using namespace jin::fs; 

namespace jin
{
namespace module
{
    
    /**
    * jin.graphics context, storge some module
    * shared variables. 
    */
    static struct
    {
        // current render color 
        color curRenderColor;
        
        // currently used font 
        Font* curFont = 0; 

        // default ingame font 
        Font* defaultFont = 0; 

    } context;

    /**
    * Init video system. 
    * jin.graphics.init(width, height, title) 
    */
    static int l_init(lua_State* L)
    {
        int w = luax_checknumber(L, 1);
        int h = luax_checknumber(L, 2);
        const char* t = luaL_checkstring(L, 3);
        
        // init video subsystem
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            luax_error(L, "could not init video");
            luax_pushboolean(L, false);
            return 1;
        }

        // init window system 
        Window* wnd = Window::get();
        wnd->init(w, h, t);

        // set default blend method 
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        // init success 
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
        // pseudo constructor
        img->init();
        Filesystem* fs = Filesystem::get(); 
        const char* f = luax_checkstring(L, 1);
        if (!fs->exists(f))
        {
            printf("no such image %s\n", f);
            exit(1);
        }
        Buffer b = {};
        fs->read(f, &b); 
        img->loadb((const char*)b.data, b.size); 
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
        if (luax_gettop(L) == 0)
        {
            glClearColor(0, 0, 0, 1); 
        }
        else
        {
            int r = luax_checknumber(L, 1);
            int g = luax_checknumber(L, 2);
            int b = luax_checknumber(L, 3);
            int a = luax_checknumber(L, 4);
            glClearColor(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
        }
        glClear(GL_COLOR_BUFFER_BIT);
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
    
    // jin.graphics.draw(x, y, scalex, scaley, r)
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
        // jin.graphics.color() to set back to default 
        // render color
        if (luax_gettop(L) == 0)
        {
            glColor4f(1, 1, 1, 1);
            return 0;
        }

        context.curRenderColor.r = luax_checknumber(L, 1);
        context.curRenderColor.g = luax_checknumber(L, 2);
        context.curRenderColor.b = luax_checknumber(L, 3);
        context.curRenderColor.a = luax_checknumber(L, 4);

        glColor4f(context.curRenderColor.r / 255.f, 
            context.curRenderColor.g / 255.f, 
            context.curRenderColor.b / 255.f,
            context.curRenderColor.a / 255.f);
        return 0;
    }

    static int l_getColor(lua_State * L)
    {
        luax_pushnumber(L, context.curRenderColor.r);
        luax_pushnumber(L, context.curRenderColor.g);
        luax_pushnumber(L, context.curRenderColor.b);
        luax_pushnumber(L, context.curRenderColor.a);
        return 4; 
    }
    
    static int l_bindCanvas(lua_State* L)
    {
        if (luax_gettop(L) == 0)
        {
            // bind to default canvas
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

    static int l_setBlend(lua_State* L)
    {


        return 0; 
    }

    static RENDER_MODE strtomode(const char* str)
    {
        std::string s = std::string(str);
        if (s == "fill") return FILL;
        else if (s == "line") return LINE;
        else return NONE;
    }

    /**
    * draw pixel to screen 
    * jin.graphics.pixel(x, y) 
    */
    static int l_drawpoint(lua_State* L)
    {
        int x = luax_checknumber(L, 1);
        int y = luax_checknumber(L, 2);
        render::point(x, y);
        
        return 0; 
    }
    
    static int l_drawLine(lua_State* L)
    {
        int x1 = luax_checknumber(L, 1); 
        int y1 = luax_checknumber(L, 2);
        int x2 = luax_checknumber(L, 3);
        int y2 = luax_checknumber(L, 4);
        render::line(x1, y1, x2, y2);
        
        return 0; 
    }

    static int l_drawRect(lua_State* L)
    {
        const char* modestr = luax_checkstring(L, 1);
        RENDER_MODE mode = strtomode(modestr);
        if (mode != NONE)
        {
            int x = luax_checknumber(L, 2);
            int y = luax_checknumber(L, 3);
            int w = luax_checknumber(L, 4);
            int h = luax_checknumber(L, 5);
            render::rect(mode, x, y, w, h);
        }
        else
        {
            luax_typerror(L, 1, "'fill' or 'line'");
            return 1;
        }

        return 0; 
    }

    static int l_drawCircle(lua_State* L)
    {
        const char* modestr = luax_checkstring(L, 1);
        RENDER_MODE mode = strtomode(modestr);
        if (mode != NONE)
        {
            int x = luax_checknumber(L, 2);
            int y = luax_checknumber(L, 3);
            float r = luax_checknumber(L, 4);
            render::circle(mode, x, y, r); 
        }
        else
        {
            luax_typerror(L, 1, "'fill' or 'line'");
            return 1;
        }

        return 0;
    }

    static int l_drawTriangle(lua_State* L)
    {
        const char* modestr = luax_checkstring(L, 1);
        RENDER_MODE mode = strtomode(modestr);
        if (mode != NONE)
        {
            int x = luax_checknumber(L, 2);
            int y = luax_checknumber(L, 3);
        
            int x2 = luax_checknumber(L, 3);
            int y2 = luax_checknumber(L, 4);

            int x3 = luax_checknumber(L, 5);
            int y3 = luax_checknumber(L, 6);

            render::triangle(mode, x, y, x2, y2, x3, y3);
        }
        else
        {
            luax_typerror(L, 1, "'fill' or 'line'");
            return 1;
        }

        return 0;
    }
    
    /**
    * draw polygon. 
    * jin.graphics.polygon(mode, n, {{}, {}, {}...})
    */
    static int l_drawPolygon(lua_State* L)
    {
        const char* modestr = luax_checkstring(L, 1);
        int n = luax_checknumber(L, 2); 
        RENDER_MODE mode = strtomode(modestr); 
        if (mode != NONE)
        {
            if (!luax_istable(L, 3))
            {
                luax_typerror(L, 3, "table");
                return 1; 
            }
            int tn = luax_tableidxlen(L, 3);
            if (tn != n * 2)
            {
                static char emsg[] = 
                "number of polygon vertices doesn't match "
                "provided n, expect %d numbers but get %d";
                luax_error(L, emsg, n * 2, tn);
                return 1;
            }
            float* p = new float[2 * n];
            for (int i = 1; i <= 2 * n; i++)
                p[i - 1] = luax_rawgetnumber(L, 3, i);
            render::polygon(mode, p, n);
            delete[] p; 
        }
        else
        {
            luax_typerror(L, 1, "'fill' or 'line'");
            return 1; 
        }
        
        return 0;
    }

    static int l_newFont(lua_State* L)
    {
        Font* font = (Font*)luax_newinstance(L, TYPE_FONT, sizeof(Font));
        const char* path = luax_checkstring(L, 1);
        Filesystem* fs = Filesystem::get();
        Buffer b = {};
        if (!fs->exists(path))
        {
            printf("no such font %s\n", path);
            exit(1);
        }
        fs->read(path, &b);
        font->loadb((const unsigned char*)b.data);

        return 1;
    }

    /**
    * study font, 0 args for study default font. 
    */
    static int l_study(lua_State* L)
    {
        int n = luax_gettop(L);
        if (n == 0)
        {
            if (context.defaultFont == 0)
            {
                #include "res/font.ttf.h"
                // load default font
                context.defaultFont = new Font();
                context.defaultFont->loadb(font_ttf);
            }
            context.curFont = context.defaultFont;
            return 0;
        }
        Font* font = (Font*)luax_checktype(L, 1, TYPE_FONT);
        context.curFont = font;
        return 0;
    }

    /**
    * draw text with current font(after study). befor write, must
    * study a font. 
    */
    static int l_write(lua_State* L)
    {
        if (context.curFont == 0)
            return 0;

        const char* text = luax_checkstring(L, 1);
        int x = luax_checknumber(L, 2); 
        int y = luax_checknumber(L, 3); 

        int fh = luax_optnumber(L, 4, 15); 
        int spacing = luax_optnumber(L, 5, 1);
        int lh = luax_optnumber(L, 6, 18);

        context.curFont->render(text, x, y, fh, spacing, lh);

        return 0;
    }

    /**
    * get text bound box 
    */
    static int l_box(lua_State* L)
    {
        const char* text = luax_checkstring(L, 1);
        int fontheight = luax_checknumber(L, 2);
        int spacing = luax_checknumber(L, 3); 
        int lineheight = luax_checknumber(L, 4);
        int w, h; 
        context.curFont->box(text, fontheight, spacing, lineheight, &w, &h);
        luax_pushnumber(L, w); 
        luax_pushnumber(L, h);
        return 2; 
    }

    static const luaL_Reg f[] = {
        {"init",     l_init},
        {"size",     l_getSize}, 
        {"Image",    l_newImage},
        {"Shader",   l_newShader},
        {"Canvas",   l_newCanvas},
        {"Font",     l_newFont},
        /**
        * before using box and write
        * must call study to set 
        * current font 
        */ 
        {"box",      l_box},
        {"write",    l_write},
        {"clear",    l_clear},
        {"draw",     l_draw},
        {"color",    l_setColor},
        {"palette",  l_getColor},
        {"present",  l_present},
        //{"blend",    l_setBlend},
        // study font
        {"study",    l_study},
        // bind canvas
        {"bind",     l_bindCanvas},
        // use shader
        //{"use",      l_useShader},
        // draw shapes
        {"point",    l_drawpoint},
        {"line",     l_drawLine}, 
        {"rect",     l_drawRect},
        {"circle",   l_drawCircle},
        {"triangle", l_drawTriangle}, 
        {"polygon",  l_drawPolygon},
        {0, 0}
    };

    extern int luaopen_Image(lua_State* L);
    
    extern int luaopen_Font(lua_State* L);
    
    extern int luaopen_Canvas(lua_State* L);
    
    extern int luaopen_JSL(lua_State* L);
    
    int luaopen_graphics(lua_State* L)
    {
        // register types
        luaopen_Image(L);
        luaopen_Canvas(L);
        luaopen_Font(L);

        // load whole lib 
        luax_newlib(L, f); 
        
        return 1;
    }

}
}