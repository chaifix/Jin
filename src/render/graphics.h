#ifndef __JIN_GRAPHICS_H
#define __JIN_GRAPHICS_H

#include "color.h"
#include "canvas.h"
#include "image.h"

namespace jin
{
namespace render
{
    typedef enum {
        NONE = 0,
        FILL ,
        LINE
    }RENDER_MODE;

    /**
    * TODO:
    *     drawPixels(int n, points)
    */
    extern void line(int x1, int y1, int x2, int y2);

    extern void rect(RENDER_MODE mode, int x, int y, int w, int h);

    extern void triangle(RENDER_MODE mode, int x1, int y1, int x2, int y2, int x3, int y3);

    extern void circle(RENDER_MODE mode, int x, int y, int r);

    extern void point(int x, int y);

    extern void points(int n, GLshort* p, GLubyte* c);

    extern void polygon(RENDER_MODE mode, float* p, int count);
}
}
#endif