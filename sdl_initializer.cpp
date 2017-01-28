//sdl_initializer.cpp

#include <string>
#include "sdl_initializer.h"

Sdl_initializer::Sdl_initializer( bool vsync, int win_width, int win_height ) {

	if ( SDL_Init( SDL_INIT_VIDEO ) )
		throw "SDL_Init(SDL_INIT_VIDEO) failed: SDL_GetError: " +
			(std::string) SDL_GetError();

	// get info about desktop screen resolution and store it in dm
	if( SDL_GetDesktopDisplayMode(0, &dm) )
		throw "SDL_GetDesktopDisplayMode(0, &dm) failed: SDL_GetError: " +
			(std::string) SDL_GetError();

	//defaults for windowed mode
	Uint32 win_flags = SDL_WINDOW_SHOWN;
	int win_pos = SDL_WINDOWPOS_UNDEFINED;

	if( win_width <=0 || win_height <= 0 ) { // if fullscreen mode
		win_flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
		width = dm.w;
		height = dm.h;
		win_pos = 0;
	}else { // if windowed mode
		width = win_width;
		height = win_height;
	}

	window = SDL_CreateWindow ( "gierka", win_pos, win_pos, width, height, win_flags);
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

	//Initialize PNG,JPG... formats loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
		throw "SDL_image could not initialize! SDL_image Error: " +
			(std::string) IMG_GetError();

	SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_MOD );
}

Sdl_initializer::~Sdl_initializer() {
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	renderer = NULL;
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}
