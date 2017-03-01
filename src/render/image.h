#ifndef __JIN_IMAGE_H
#define __JIN_IMAGE_H
#include "libs/GLee/GLee.h"
#include "color.h"
#include "drawable.h"
namespace jin 
{ 
namespace render
{
    class Image: public Drawable
    {
    public:
        Image();
        ~Image();

        /* just like Image() */
        void init(); 
        
		/* load from file */
        bool loadf(const char* f); 
        
		/* load from buffer */
        bool loadb(const char* b); 
        
		color getPixel(int x, int y);
    
	private:
    
		color* pixels;
    };
}
}

#endif