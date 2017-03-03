#include "canvas.h" 
#include "window.h"

namespace jin
{
namespace render 
{
    Canvas::Canvas() :Drawable()
    {
    }

    Canvas::~Canvas()
    {
        Drawable::~Drawable();
    }

    // no canvas has binded 
    GLint Canvas::cur = -1; 

    bool Canvas::init(int w, int h)
    {
        Drawable::init(w, h);
        Drawable::setVertices(
            new float [DRAWABLE_V_SIZE] {
                0, 0,
                0, (float)h,
                (float)w, (float)h,
                (float)w, 0,
            },
            new float [DRAWABLE_V_SIZE] {
                0, 1,
                0, 0,
                1, 0,
                1, 1
            }
        );

        GLint current_fbo;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);

        // generate a new render buffer object 
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        // generate texture save target 
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        
        // unbind framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, current_fbo);
        
        if (status != GL_FRAMEBUFFER_COMPLETE_EXT)
            return false;
        return true; 
    }

    bool Canvas::hasbind(GLint fbo)
    {
        return cur == fbo; 
    }

    /**
    * bind to canvas 
    */
    void Canvas::bind()
    {
        if (hasbind(fbo)) return;

        cur = fbo;

        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        glViewport(0, 0, width, height);
        glOrtho(0, width, height, 0, -1, 1);

        // Switch back to modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
    }

    /**
    * bind to default screen render buffer. 
    */
    /*static*/ void Canvas::unbind()
    {
        if (hasbind(0)) return;
        
        cur = 0;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // load back to normal 
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        
        Window* wnd = Window::get(); 
        int ww = wnd->getW(),
            wh = wnd->getH();

        // set viewport matrix 
        glViewport(0, 0, ww, wh);
        glOrtho(0, ww, wh, 0, -1, 1);

        //  switch to model matrix  
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
    }
}
}