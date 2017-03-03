/**
* Some color operating here. 
*/
#ifndef __JIN_COLOR_H
#define __JIN_COLOR_H
#include "utils/endian.h"

namespace jin 
{
namespace render
{
    
    class color { 

    public:
        
        inline color(): r(0), g(0), b(0), a(0)
        {
        }

        inline color(int c)
        {
        #if JIN_BYTEORDER == JIN_BIG_ENDIAN
            /* big endian machine, ABGR */
            r = c & 0xff000000 >> 24;
            g = c & 0xff0000 >> 16;
            b = c & 0xff00 >> 8;
            a = c & 0xff;
        #else
            /* little endian machine, RGBA */
            r = c & 0xff;
            g = (c & 0xff00) >> 8;
            b = (c & 0xff0000) >> 16;
            a = (c & 0xff000000) >> 24;
        #endif
        }
        
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;

    };

    /**
    * Translate 8bits(only alpha channel) pixels to 32bits color pixels.
    */
    inline color* a_c(unsigned char* src, int size)
    {
        color* pixels = new color[size]; 
        for (int i = 0; i < size; i++)
        {
            pixels[i].r = 0xff;
            pixels[i].g = 0xff;
            pixels[i].b = 0xff;
            pixels[i].a = src[i];
        }
    }

}
} 

#endif