#include "font.h"

#include <stdio.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include "libs/stb/stb_truetype.h"
#include "color.h"

namespace jin
{
namespace render
{

#define BITMAP_WIDTH  512
#define BITMAP_HEIGHT 512
#define PIXEL_HEIGHT 32

    Font::Font():Drawable()
    {
    }

    // ttf file read buffer 
    static unsigned char ttf_buffer[1 << 20];

    // bitmap for saving font data
    static unsigned char temp_bitmap[BITMAP_WIDTH * BITMAP_HEIGHT];

    void Font::loadf(const char* path)
    {
        fread(ttf_buffer, 1, 1 << 20, fopen(path, "rb"));
        
        loadb(ttf_buffer);
    }

    /**
    * load from memory 
    */
    void Font::loadb(const unsigned char* data)
    {
        stbtt_BakeFontBitmap(data, 0, PIXEL_HEIGHT, temp_bitmap, BITMAP_WIDTH, BITMAP_HEIGHT, 32, 96, cdata); 

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, BITMAP_WIDTH,
            BITMAP_HEIGHT, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    /**
    * get texture quad
    */
    static Quad getCharQuad(const stbtt_bakedchar* chardata, int pw, int ph, int char_index)
    {
        float ipw = 1.0f / pw, iph = 1.0f / ph;
        const stbtt_bakedchar *b = chardata + char_index;
        Quad q;
        q.x = b->x0 * ipw;
        q.y = b->y0 * iph;
        q.w = b->x1 * ipw - b->x0 * ipw;
        q.h = b->y1 * iph - b->y0 * iph;
        return q; 
    }

    /**
    * render function draw mutiple times 
    * in loop 
    */
    void Font::render(
        const char* text, // rendered text 
        float x, float y, // render position 
        int fheight,      // font height
        int spacing,      // font spacing 
        int lheight)      // line height
    {
        float _x = x,
              _y = y; 

        int len = strlen(text);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture); 

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        // for saving clip quad
        stbtt_aligned_quad q;
        
        // render every given character
        int xc = x;
        int yc = y; 

        float factor = fheight / (float)PIXEL_HEIGHT;
        
        for (int i = 0; i < len; i++)
        {
            char c = text[i];
            if (c == '\n')
            {
                xc = x; 
                yc += lheight;
                continue;
            }

            // only support ASCII 
            Quad q = getCharQuad(cdata, 512, 512, c - 32);
            float s0 = q.x,
                s1 = q.x + q.w,
                t0 = q.y,
                t1 = q.y + q.h;

            // texture quad
            float tc[] = {
               s0, t1, 
               s1, t1, 
               s1, t0, 
               s0, t0 
            };

            // character bound box 
            stbtt_bakedchar box = cdata[c - 32];

            float width    = factor * (box.x1 - box.x0);
            float height   = factor * (box.y1 - box.y0);
            float xoffset  = factor * box.xoff;
            // I don't know why add PIXEL_HEIGHT to box.yoff, but
            // it works. 
            float yoffset  = factor * (box.yoff + PIXEL_HEIGHT);
            float xadvance = factor * box.xadvance;

            // render quad
            float vc[] = {
                xc + xoffset,         yc + height + yoffset,
                xc + width + xoffset, yc + height + yoffset,
                xc + width + xoffset, yc + yoffset,
                xc + xoffset,         yc + yoffset
            };

            // forward to next character 
            xc += xadvance + spacing;

            glTexCoordPointer(2, GL_FLOAT, 0, tc);
            glVertexPointer(2, GL_FLOAT, 0, vc);
            glDrawArrays(GL_QUADS, 0, 4);
        }

        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);

        glBindTexture(GL_TEXTURE_2D, 0); 
        glDisable(GL_TEXTURE_2D);
    }

    void Font::box(const char* str, int fheight, int spacing, int lheight, int* w, int * h)
    {
        int len = strlen(str);
        
        float xc = 0;
        int yc = len ? lheight: 0;
        int maxX = 0; 

        float factor = fheight / (float)PIXEL_HEIGHT;
		
         for (int i = 0; i < len; i++)
        {
            char c = str[i]; 
            if (c == '\n')
            {
                yc += lheight; 
                xc = 0;
                continue;
            }
            stbtt_bakedchar box = cdata[c - 32];

            xc += factor * box.xadvance + spacing;
            if (xc > maxX) maxX = xc;
        }

        *w = maxX;
        *h = yc;
    }

}
}