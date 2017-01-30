//sdl_initializer.cpp
#include "sdl_initializer.h"

Sdl_initializer::Sdl_initializer( string title, int win_width, int win_height,
									bool vsync ) :
		Sdl_init( SDL_INIT_VIDEO ),
		Img_init( IMG_INIT_PNG ) //IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF
{
	// get info about desktop screen and store it in dm structure
	if( SDL_GetDesktopDisplayMode(0, &dm) )
		throw SdlExcept( "SDL_GetDesktopDisplayMode(0, &dm) failed: SDL_GetError: "
			+ (std::string) SDL_GetError() );

	// SDL window
	Uint32 flags = SDL_WINDOW_SHOWN; // default flags for windowed mode
	int win_pos = SDL_WINDOWPOS_UNDEFINED; // default position for windowed mode
	if( win_width <=0 || win_height <= 0 ) { // fullscreen mode
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
		width = dm.w;
		height = dm.h;
		win_pos = 0;
	}else { // windowed mode
		width = win_width;
		height = win_height;
	}
	window = SDL_CreateWindow ( title.c_str(), win_pos, win_pos, width, height, flags );
	if( window == NULL ) // on error
		throw SdlExcept( "error SDL_CreateWindow; SDL_GetError():"
			+ (string) SDL_GetError() );

	// SDL renderer
	flags = 0; // default renderer flags for windowed mode
	if (vsync)
		flags = flags | SDL_RENDERER_PRESENTVSYNC;
	rend = SDL_CreateRenderer( window, -1, flags );
	if( rend == NULL ) { // on error
		SDL_DestroyWindow( window ); // revert window creation
		throw SdlExcept( "error SDL_CreateRenderer; SDL_GetError():"
		+ (string) SDL_GetError() );
	}
}

Sdl_initializer::~Sdl_initializer() {
	SDL_DestroyRenderer( rend );
	SDL_DestroyWindow( window );
}
