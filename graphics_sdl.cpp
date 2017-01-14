//graphics_sdl.cpp

#include <iostream>
#include <string>
#include "graphics_sdl.h"
#include "game.h"

using std::cerr;
using std::cout;
using std::endl;

GraphicsSdl::GraphicsSdl(){//bool fullscreen, int width, int height) {

	if ( SDL_Init( SDL_INIT_VIDEO ) )
		throw "SDL_Init(SDL_INIT_VIDEO) failed: SDL_GetError: " +
			(std::string) SDL_GetError();

	if( SDL_GetDesktopDisplayMode(0, &dm) )
		throw "SDL_GetDesktopDisplayMode(0, &dm) failed: SDL_GetError: " +
			(std::string) SDL_GetError();
	desktopDm = dm;

	if( SDL_CreateWindowAndRenderer ( dm.w, dm.h, SDL_WINDOW_FULLSCREEN_DESKTOP,
			&window, &renderer) )
		throw "error SDL_CreateWindowAndRenderer; SDL_GetError():" +
			(std::string) SDL_GetError();

	loopDelay = 1000.0/(double)dm.refresh_rate; //can be done more precisely
}

GraphicsSdl::~GraphicsSdl() {

	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );

	SDL_Quit();
}

void GraphicsSdl::update( const Application & app, const Game & game ) {

	/*Uint8 alpha;
	if( app.state() == running ) alpha = 0xFF;
	else if( app.state() == paused ) alpha = 0x80;
	else alpha = 0xFF;*/

	SDL_Rect rect;
	rect.x = rect.y = 0;
	rect.w = dm.w;
	rect.h = dm.h;
	SDL_SetRenderDrawColor( renderer, 0x5C, 0xDF, 0x46, 0xFF );
	SDL_RenderFillRect( renderer , &rect );

	for( const Blob2d_fix<int> & b : game.fblobs() ) {
		rect.x = b.x() - b.radius();
		rect.y = b.y() - b.radius();
		rect.h = rect.w = b.size();
		SDL_SetRenderDrawColor( renderer, 0xF7, 0xE4, 0x31, 0xFF );
		SDL_RenderFillRect( renderer , &rect );
	}

	for( const Blob2d<int> & b : game.blobs() ) {
		rect.x = b.x() - b.radius();
		rect.y = b.y() - b.radius();
		rect.h = rect.w = b.size();
		SDL_SetRenderDrawColor( renderer, 0xF7, 0xE4, 0xB8, 0xFF );
		SDL_RenderFillRect( renderer , &rect );
	}

	for( const Blob2d_temp<int> & b : game.tblobs() ) {
		rect.x = b.x() - b.radius();
		rect.y = b.y() - b.radius();
		rect.h = rect.w = b.size();
		SDL_SetRenderDrawColor( renderer, 0x24, 0xE4, 0xB8, 0xFF );
		SDL_RenderFillRect( renderer , &rect );
	}

	SDL_RenderPresent( renderer );
}
