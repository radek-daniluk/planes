//sdl_initializer.h
//
#ifndef SDL_INITIALIZER_H
#define SDL_INITIALIZER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sdl_initializer {

	private:
	int refresh_rate;

	protected:
	SDL_Renderer* renderer{NULL};
	SDL_Window* window{NULL};
	SDL_DisplayMode* dm{NULL};

	public:
	Sdl_initializer( bool vsync = true );
	~Sdl_initializer();
	int refreshRate() const { return refresh_rate; };
};
#endif
