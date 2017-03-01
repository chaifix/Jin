#ifndef __JIN_CANVAS_H
#define __JIN_CANVAS_H
#include "drawable.h"
namespace jin
{
namespace render 
{ 
    class Canvas: public Drawable
    {
    public: 

        Canvas(); 
		~Canvas();
        
        bool init(int w, int h); 
        
        void bind(); 
        
		static void unbind();

        static bool hasbind(GLint fbo); 

    private:

        GLuint fbo; 

		// current binded fbo 
		static GLint cur; 
	};
}
}// jin

#endif