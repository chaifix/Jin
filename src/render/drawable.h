#ifndef __JIN_DRAWABLE
#define __JIN_DRAWABLE
#include "libs/GLee/GLee.h"
namespace jin 
{
namespace render
{
    class Drawable
    {
    public:
       
		Drawable();
        ~Drawable();
        
		/* pseudo constructor*/
        void init(int w = 0, int h = 0);
        
		/* set anchor of texture, (0, 0) by default */ 
        void setAnchor(int x, int y); 
        
		void draw(int x, int y, float sx, float sy, float r);
        
		int getWidth();
        int getHeight();
    
	protected:
#define DRAWABLE_V_SIZE 8
		void setVertices(float* v, float* t);
        
		GLuint texture; 
        
		int width, height;
        
		/* anchor point */ 
        int ancx, ancy;
        
		// render coords
		float* textCoord;
        float* vertCoord;
    };
}
}// jin

#endif