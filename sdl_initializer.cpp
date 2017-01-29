//sdl_initializer.cpp

#include <string>
#include "sdl_initializer.h"
#include "exceptions.h"

Sdl_initializer::Sdl_initializer( bool vsync, int win_width, int win_height ) {

	if ( SDL_Init( SDL_INIT_VIDEO ) )
		throw SdlExcept("SDL_Init(SDL_INIT_VIDEO) failed: SDL_GetError: " +
			(std::string) SDL_GetError() );

	// get info about desktop screen resolution and store it in dm
	if( SDL_GetDesktopDisplayMode(0, &dm) ) {
		// on error
		SDL_Quit(); // revert SDL_Init
		throw SdlExcept( "SDL_GetDesktopDisplayMode(0, &dm) failed: SDL_GetError: " +
			(std::string) SDL_GetError() );
	}

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
	if( window == NULL ) { // on error
		SDL_Quit(); // revert SDL_Init
		throw SdlExcept( "error SDL_CreateWindow; SDL_GetError():" +
			(std::string) SDL_GetError() );
	}

	Uint32 flags = 0;
	if (vsync)
		flags = SDL_RENDERER_PRESENTVSYNC;

	renderer = SDL_CreateRenderer ( window, -1, flags );
	if( renderer == NULL ) { // on error
		SDL_DestroyWindow( window ); window = NULL; // revert SDL_CreateWindow
		SDL_Quit();	// revert SDL_Init
		throw SdlExcept( "error SDL_CreateRenderer; SDL_GetError():" +
			(std::string) SDL_GetError() );
	}

	//Initialize PNG format loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
		// on error
		SDL_DestroyRenderer( renderer ); renderer = NULL; // revert SDL_CreateRenderer
		SDL_DestroyWindow( window ); window = NULL; // revert SDL_CreateWindow
		SDL_Quit(); // revert SDL_Init
		throw SdlExcept( "SDL_image could not initialize! SDL_image Error: " +
			(std::string) IMG_GetError() );
	}
}

Sdl_initializer::~Sdl_initializer() {
	SDL_DestroyRenderer( renderer ); renderer = NULL;
	SDL_DestroyWindow( window ); window = NULL;
	IMG_Quit();
	SDL_Quit();
}
