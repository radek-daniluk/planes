//graphics_sdl.cpp

#include <iostream>
#include <string>
#include <SDL2/SDL_image.h>
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

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
		throw "SDL_image could not initialize! SDL_image Error: " +
			(std::string) IMG_GetError();

	// Load images to Textures
	plane = loadTexture ("img/mig29.png");
	plane_r = loadTexture ("img/mig29_right.png");
	plane_l = loadTexture ("img/mig29_left.png");
	tree = loadTexture ("img/tree.bmp");

	loopDelay = 1000.0/(double)dm.refresh_rate; //can be done more precisely
}

GraphicsSdl::~GraphicsSdl() {

	SDL_DestroyTexture( plane );
	SDL_DestroyTexture( plane_r );
	SDL_DestroyTexture( plane_l );
	plane = plane_r = plane_l = NULL;

	SDL_DestroyTexture( tree );

	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	renderer = NULL;
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}

void GraphicsSdl::update( const Application & app, const Game & game ) {

	/*Uint8 alpha;
	if( app.state() == running ) alpha = 0xFF;
	else if( app.state() == paused ) alpha = 0x80;
	else alpha = 0xFF;*/


	int py = game.plane().y();
	int offset = - py + dm.h - game.plane().size();

	SDL_Rect rect;

	//background
	SDL_SetRenderDrawColor( renderer, 0x5C, 0xDF, 0x46, 0xFF );
	SDL_RenderClear( renderer );;

	// fixed blobs
	for( const auto & b : game.fblobs() ) {
		rect.x = b.x() - b.radius();
		rect.y = b.y() - b.radius() + offset;
		rect.h = rect.w = b.size();
		SDL_SetRenderDrawColor( renderer, 0xF7, 0xE4, 0x31, 0xFF );
		SDL_RenderFillRect( renderer , &rect );
	}

	// moving blobs
	for( const auto & b : game.blobs() ) {
		rect.x = b.x() - b.radius();
		rect.y = b.y() - b.radius() + offset;
		rect.h = rect.w = b.size();
		SDL_SetRenderDrawColor( renderer, 0xF7, 0xE4, 0xB8, 0xFF );
		SDL_RenderFillRect( renderer , &rect );
	}

	//plane
	SDL_Texture* pl;
	if ( game.plane().speedX() == 0 )
		pl = plane;
	else if( game.plane().speedX() < 0 )
		pl = plane_l;
	else
		pl = plane_r;

	rect.x = game.plane().x() - 34;//game.plane().radius();
	rect.y = game.plane().y() + offset - 50;//game.plane().radius();
	rect.h = 100;
	rect.w = 68;
	SDL_RenderCopy( renderer, pl, NULL, &rect );


	//temporary blobs
	for( const auto & b : game.tblobs() ) {
		rect.x = b.x() - b.radius();
		rect.y = b.y() - b.radius() + offset;
		rect.h = rect.w = b.size();
		SDL_SetRenderDrawColor( renderer, 0x24, 0xE4, 0xB8, 0xFF );
		SDL_RenderFillRect( renderer , &rect );
	}

	SDL_RenderPresent( renderer );
}

SDL_Texture* GraphicsSdl::loadTexture( std::string path ) {

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ) {

		std::cout << "Unable to load image "<< path <<"! SDL_image Error: "
		<< IMG_GetError() << std::endl;
	} else {

		newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL ) {
			std::cout << "Unable to create texture from "<< path << "! SDL Error: "
			<< SDL_GetError() << std::endl;
		}
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}
