//sdl_initializer.h
//
#ifndef SDL_INITIALIZER_H
#define SDL_INITIALIZER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sdl_initializer {

	private:
	int refresh_rate{0};
	int width{0};
	int height{0};

	protected:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_DisplayMode dm{SDL_PIXELFORMAT_UNKNOWN,0,0,0,0};

	public:
	Sdl_initializer( bool vsync = true, int width = 0, int height = 0 );
	~Sdl_initializer();
	int refreshRate() const { return refresh_rate; };
};
#endif
