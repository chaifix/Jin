#ifndef __JIN_FONT_H
#define __JIN_FONT_H

#include "drawable.h"
#include "libs/stb/stb_truetype.h"
#include "quad.h"

namespace jin
{
namespace render
{  
    /**
    * Usage of stb_truetype.h here might be a little 
    * bit dummy. Implementation of Font is referring 
    * to stb_truetype.h L243~284. I basicly copy it:)
    */
    class Font: public Drawable
    {
    public: 

        Font(); 

        /**
        * load ttf font data from .ttf 
        */
        void loadf(const char* file); 

        /**
        * load ttf font data from memory 
        */
        void loadb(const unsigned char* data);
        
        /**
        * render text to screen 
        */
        void render(
            const char* str,  // rendered text 
            float x, float y, // render position 
            int fheight,      // font size 
            int spacing,      // font spacing 
            int lheight       // line height
        );

        void box(const char* str, int fheight, int spacing, int lheight, int* w, int * h); 

    private: 

        /**
        * ASCII 32(space)..126(~) is 95 glyphs 
        */
        stbtt_bakedchar cdata[96];
        
    };

}
}

#endif