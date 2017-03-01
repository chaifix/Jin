#include "window.h"
#include "libs/GLee/GLee.h"
#include "canvas.h"
namespace jin
{
namespace render
{
    Window* Window::g_wnd = 0; 
    Window* Window::get()
    {
        return (g_wnd ? g_wnd : (g_wnd = new Window()));
    }
    Window::Window(): wnd(0), ctx(0)
    {
    }
    Window::~Window()
    {
    }
    void Window::init(int pw, int ph, const char* t)
    {
        w = pw;
        h = ph;
        if (wnd)
        {
            SDL_DestroyWindow(wnd); 
            SDL_FlushEvent(SDL_WINDOWEVENT);
        }
        if (ctx)
        {
            SDL_GL_DeleteContext(ctx);
        }
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
        int wx = SDL_WINDOWPOS_UNDEFINED,
            wy = SDL_WINDOWPOS_UNDEFINED;

        /* Create window */
        wnd = SDL_CreateWindow(t, wx, wy, w, h, flags);

        /* Create an opengl context */
        ctx = SDL_GL_CreateContext(wnd);
        SDL_GL_MakeCurrent(wnd, ctx);

        /* Default clear color */
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        /* Default render color */
        glColor4f(1, 1, 1, 1);

        /**
		* Set the viewport to top-left corner. 
		* Bind to the default render buffer. 
		*/ 
		Canvas::unbind();
        
        /* Swap window buffer */
        swapBuffers();
    }
    
    SDL_Window* Window::getWnd()
    {
        return wnd; 
    }

    SDL_GLContext Window::getCtx()
    {
        return ctx; 
    }

    int Window::getW()
    {
        return w; 
    }

    int Window::getH()
    {
        return h;
    }

    void Window::swapBuffers()
    {
        if (wnd) 
            SDL_GL_SwapWindow(wnd);
    }
}
}