//sdl_initializer.cpp

#include <string>
#include "sdl_initializer.h"

Sdl_initializer::Sdl_initializer( bool vsync ) {

	if ( SDL_Init( SDL_INIT_VIDEO ) )
		throw "SDL_Init(SDL_INIT_VIDEO) failed: SDL_GetError: " +
			(std::string) SDL_GetError();

	if( SDL_GetDesktopDisplayMode(0, &dm) )
		throw "SDL_GetDesktopDisplayMode(0, &dm) failed: SDL_GetError: " +
			(std::string) SDL_GetError();
	refresh_rate = dm.refresh_rate;

	window = SDL_CreateWindow ( "gierka", 0, 0, 800, dm.h, 0);//SDL_WINDOW_SHOWN );
	if( window == NULL )
		throw "error SDL_CreateWindow; SDL_GetError():" +
			(std::string) SDL_GetError();

	Uint32 flags = 0;
	if (vsync)
		flags = SDL_RENDERER_PRESENTVSYNC;

	renderer = SDL_CreateRenderer ( window, -1, flags );
	if( renderer == NULL )
		throw "error SDL_CreateRenderer; SDL_GetError():" +
			(std::string) SDL_GetError();

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
		throw "SDL_image could not initialize! SDL_image Error: " +
			(std::string) IMG_GetError();
}

Sdl_initializer::~Sdl_initializer() {
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	renderer = NULL;
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}
