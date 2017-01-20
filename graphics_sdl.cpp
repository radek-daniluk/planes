//graphics_sdl.cpp

#include <iostream>
#include <string>
#include <SDL2/SDL_image.h>
#include "graphics_sdl.h"
#include "game.h"

using std::cerr;
using std::cout;
using std::endl;

GraphicsSdl::GraphicsSdl( bool vsync ){//bool fullscreen, int width, int height) {

	if ( SDL_Init( SDL_INIT_VIDEO ) )
		throw "SDL_Init(SDL_INIT_VIDEO) failed: SDL_GetError: " +
			(std::string) SDL_GetError();

	if( SDL_GetDesktopDisplayMode(0, &dm) )
		throw "SDL_GetDesktopDisplayMode(0, &dm) failed: SDL_GetError: " +
			(std::string) SDL_GetError();
	desktopDm = dm;

	window = SDL_CreateWindow ( "gierka", 0, 0, 800, dm.h, 0);//SDL_WINDOW_SHOWN );
	if( window == NULL )
		throw "error SDL_CreateWindow; SDL_GetError():" +
			(std::string) SDL_GetError();

	Uint32 flags = 0;
	if (vsync) flags = SDL_RENDERER_PRESENTVSYNC;

	renderer = SDL_CreateRenderer ( window, -1, flags );
	if( renderer == NULL )
		throw "error SDL_CreateRenderer; SDL_GetError():" +
			(std::string) SDL_GetError();

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
		throw "SDL_image could not initialize! SDL_image Error: " +
			(std::string) IMG_GetError();

	// Load images to Textures
	mig29 = loadTexture( "img/mig29.png" );
	mig29_r = loadTexture( "img/mig29_right.png" );
	mig29_l = loadTexture( "img/mig29_left.png" );
	tree = loadTexture( "img/tree.png" );
	f16 = loadTexture( "img/F-16.png" );
	f35 = loadTexture( "img/F-35.png" );
	f22 = loadTexture( "img/F-22.png" );
	explosion = loadTexture( "img/explosion3.png" );
	bullet = loadTexture( "img/bullet.png" );


	refresh_rate = dm.refresh_rate;
}

GraphicsSdl::~GraphicsSdl() {

	SDL_DestroyTexture( mig29 );
	SDL_DestroyTexture( mig29_r );
	SDL_DestroyTexture( mig29_l );
	mig29 = mig29_r = mig29_l = NULL;

	SDL_DestroyTexture( f16 );
	SDL_DestroyTexture( f22 );
	SDL_DestroyTexture( f35 );
	f16 = f22 = f35 = NULL;

	SDL_DestroyTexture( explosion );
	SDL_DestroyTexture( tree );
	SDL_DestroyTexture( bullet );
	bullet = explosion = tree = NULL;

	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	renderer = NULL;
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}

void GraphicsSdl::clear() {
	SDL_SetRenderDrawColor( renderer, 0x5C, 0xDF, 0x46, 0xFF );
	SDL_RenderClear( renderer );
}

void GraphicsSdl::update( const Application & app, const Game & game ) {

	/*Uint8 alpha;
	if( app.state() == running ) alpha = 0xFF;
	else if( app.state() == paused ) alpha = 0x80;
	else alpha = 0xFF;*/


	int py = game.plane().y();
	int offset = py + dm.h - game.plane().size();

	SDL_Rect rect;

	// fixed blobs
	for( const auto & b : game.fblobs() ) {
		if( b.active() ) {
			rect.x = b.x() - b.radius();
			rect.y = - b.y() - b.radius() + offset;
			rect.h = rect.w = b.size();
			SDL_RenderCopy( renderer, tree, NULL, &rect );
		}
	}

	// moving blobs
	for( const auto & b : game.blobs() ) {
		rect.x = b.x() - b.radius();
		rect.y = - b.y() - b.radius() + offset;
		rect.h = rect.w = b.size();
		//SDL_SetRenderDrawColor( renderer, 0xF7, 0xE4, 0xB8, 0xFF );
		//SDL_RenderFillRect( renderer , &rect );
		SDL_RenderCopy( renderer, f22, NULL, &rect );
	}

	for( const auto & b : game.bullets() ) {
		rect.x = b.x() - b.radius();
		rect.y = - b.y() - b.radius() + offset;
		rect.h = rect.w = b.size();
		//SDL_SetRenderDrawColor( renderer, 0xF7, 0xE4, 0xB8, 0xFF );
		//SDL_RenderFillRect( renderer , &rect );
		SDL_RenderCopy( renderer, bullet, NULL, &rect );
	}

	//plane
	SDL_Texture* pl;
	if ( game.plane().speedX() == 0 )
		pl = mig29;
	else if( game.plane().speedX() < 0 )
		pl = mig29_l;
	else
		pl = mig29_r;

	rect.x = game.plane().x() - 34;//game.plane().radius();
	rect.y = - game.plane().y() + offset - 50;//game.plane().radius();
	rect.h = 100;
	rect.w = 68;
	SDL_RenderCopy( renderer, pl, NULL, &rect );


	//temporary blobs
	for( const auto & b : game.tblobs() ) {
		rect.x = b.x() - b.radius();
		rect.y = - b.y() - b.radius() + offset;
		rect.h = rect.w = b.size();
		//SDL_SetRenderDrawColor( renderer, 0x24, 0xE4, 0xB8, 0xFF );
		//SDL_RenderFillRect( renderer , &rect );
		SDL_RenderCopy( renderer, explosion, NULL, &rect );
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
