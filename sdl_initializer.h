//sdl_initializer.h
//
#ifndef SDL_INITIALIZER_H
#define SDL_INITIALIZER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sdl_initializer {

	protected:
	int width{0};
	int height{0};
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_DisplayMode dm{SDL_PIXELFORMAT_UNKNOWN,0,0,0,0};

	public:
	Sdl_initializer( bool vsync = true, int width = 0, int height = 0 );
	~Sdl_initializer();
	Sdl_initializer( const Sdl_initializer & ) = delete;
	Sdl_initializer & operator=( const Sdl_initializer & ) = delete;

	int w() const { return width; }
	int h() const { return height; }
};
#endif
