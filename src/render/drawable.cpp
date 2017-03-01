#include "drawable.h"
#include "utils/matrix.h"
#include <stdlib.h>
namespace jin
{
namespace render
{
    Drawable::Drawable():texture(0), width(0), height(0), ancx(0), ancy(0), textCoord(0), vertCoord(0)
    {
    }

    Drawable::~Drawable()
    {
        glDeleteTextures(1, &texture);
		delete[] vertCoord; 
		delete[] textCoord;
    }

    void Drawable::init(int w, int h)
    {
        texture = 0; 
        width   = w; 
        height  = h; 
        ancx    = 0;
        ancy    = 0; 
        textCoord = 0;
        vertCoord = 0;
    }

    void Drawable::setVertices(float* v, float* t)
    {
		// render area 
		if (vertCoord)
			delete[] vertCoord;
		vertCoord = v;

		// textrue 
        if (textCoord) 
			delete[] textCoord; 
		textCoord = t;
    }

    void Drawable::setAnchor(int x, int y)
    {
        ancx = x; 
        ancy = y;
    }

    int Drawable::getWidth()
    {
        return width;
    }

    int Drawable::getHeight()
    {
        return height;
    }

    void Drawable::draw(int x, int y, float sx, float sy, float r)
    {
        if (! textCoord||! vertCoord) return;
        static jin::util::Matrix t;
        t.setTransformation(x, y, r, sx, sy, ancx, ancy);

        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, texture);
        
		// push modle matrix 
        glPushMatrix();
        glMultMatrixf((const GLfloat*)t.getElements());

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, textCoord);
        glVertexPointer(2, GL_FLOAT, 0, vertCoord);
        glDrawArrays(GL_QUADS, 0, 4);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);

		// pop the model matrix 
        glPopMatrix();

		// bind texture to default screen 
        glBindTexture(GL_TEXTURE_2D, 0);

        glDisable(GL_TEXTURE_2D);
    }
}
}