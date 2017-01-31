//sdl_initializer.h
//
#ifndef SDL_INITIALIZER_H
#define SDL_INITIALIZER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <sstream>
#include "exceptions.h"
using std::string;

class Sdl_init {
	public:
	explicit Sdl_init( Uint32 flags ) {
		if ( SDL_Init( flags ) ) {
			std::istringstream s;
			s >> flags;
			throw SdlErr( "SDL_Init(" + s.str() + ")@sdl_initializer.h" );
		}
	}
	~Sdl_init() { SDL_Quit(); }
};

class Img_init {
	public:
	explicit Img_init( int flags ) {
		if( !( IMG_Init( flags ) & flags ) ) {
			std::istringstream s;
			s >> flags;
			throw SdlImgErr( "IMG_Init(" + s.str() + ")@sdl_initialize.h" );
		}
	}
	~Img_init() { IMG_Quit(); }
};

class Sdl_initializer : private Sdl_init, private Img_init {
	SDL_Window * window;

	protected:
	int width{0};
	int height{0};
	SDL_DisplayMode dm{SDL_PIXELFORMAT_UNKNOWN,0,0,0,0};
	SDL_Renderer* rend;

	public:
	explicit Sdl_initializer( string title, int w = 0, int h = 0, bool vsync = true);
	~Sdl_initializer();
	Sdl_initializer( const Sdl_initializer & ) = delete;
	Sdl_initializer & operator=( const Sdl_initializer & ) = delete;

	int w() const { return width; }
	int h() const { return height; }
	SDL_Window * win() const { return window; }
};
#endif
