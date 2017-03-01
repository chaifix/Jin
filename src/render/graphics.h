#ifndef __JIN_GRAPHICS_H
#define __JIN_GRAPHICS_H
#include "color.h"
#include "geometry.h"
#include "canvas.h"
#include "image.h"
namespace jin 
{
namespace render
{
	enum RENDER_MODE{
		FILL = 1, 
		LINE
	};
	/**
	* TODO: 
	*     drawline(int x, int y, int x2, int y2, int border)
	*     drawRect(int x, int y, int w, int h, RENDER_MODE mode) 
	*	  drawCircle(int x, int y, float radius)
	*     drawPixel(int x, int y) 
	*/
	
}
}
#endif