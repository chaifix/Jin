#ifndef __JIN_RENDER_WINDOW
#define __JIN_RENDER_WINDOW
#include "SDL2/SDL.h"
namespace jin
{
namespace render
{
    class Window
    {
    public: 
        
        void init(int w, int h, const char* t);
        SDL_Window* getWnd();
        SDL_GLContext getCtx(); 
        static Window* get(); 

        int getW(); 
        int getH();
        
        void swapBuffers();

    private: 

        Window(); 
        ~Window(); 
        static Window* g_wnd; 
        SDL_Window* wnd; 
        SDL_GLContext ctx;
        int w, h;
    };
}
}
#endif