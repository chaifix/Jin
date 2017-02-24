#ifndef __JIN_CANVAS_H
#define __JIN_CANVAS_H
#include "drawable.h"
#include "quad.h"
namespace jin
{
class Canvas: public Drawable
{
public: 
    void bind(); 
    void unbind(); 
    void draw(int x = 0, int y = 0, int scale = 1);
    void draw(const Rect& src, const Rect& dst);
private:
    //GLuint fbo; 
    //GLuint img; 
    //static GLuint preCanvas;    // previous canvas to render 
};
}// jin

#endif