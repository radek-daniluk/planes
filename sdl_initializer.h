//sdl_initializer.h
//
#ifndef SDL_INITIALIZER_H
#define SDL_INITIALIZER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sdl_initializer {
	protected:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_DisplayMode dm;

	int refresh_rate;

	public:
	Sdl_initializer( bool vsync = true );
	~Sdl_initializer();
	int refreshRate() const { return refresh_rate; };
};
#endif
