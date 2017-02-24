#include "event.h"
#include "SDL2\SDL.h"

namespace jin
{
	void Event::poll()
	{
		SDL_Event* e; 
		while (SDL_PollEvent(e))
		{
			
		}
	}
}