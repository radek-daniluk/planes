//graphics_sdl.cpp

#include <iostream>
#include <string>
#include <SDL2/SDL_image.h>
#include "graphics_sdl.h"
#include "game.h"

using std::cerr;
using std::cout;
using std::endl;

GraphicsSdl::GraphicsSdl( bool vsync ) :
		Sdl_initializer( vsync ),
		mig29{ "img/mig29.png", renderer },
		mig29_r{ "img/mig29_right.png", renderer },
		mig29_l{ "img/mig29_left.png", renderer },
		f16{ "img/F-16.png", renderer },
		f22{ "img/F-22.png", renderer },
		f35{ "img/F-35.png", renderer },
		bullet{ "img/bullet.png", renderer },
		tree{ "img/tree.png", renderer }
{
	for( auto & path : {"img/explosion1.png",
						"img/explosion2.png",
						"img/explosion3.png",
						"img/explosion4.png",
						"img/explosion5.png",
						"img/explosion6.png"} )
		explosion.emplace_back( path, renderer );

	for( unsigned int i=0; i<explosion.size(); ++i ) {
		explosion[i].w( explosion[i].w()/2 );
		explosion[i].h( explosion[i].h()/2 );
	}
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

	// fixed blobs
	for( const auto & b : game.fblobs() ) {
		if( b.active() ) {
			tree.x( b.x() - b.radius() );
			tree.y( -b.y() - b.radius() + offset );
			tree.h( tree.w( b.size() ) );
			SDL_RenderCopy( renderer, tree.texture() , NULL, tree.rect() );
		}
	}

	// moving blobs
	for( const auto & b : game.blobs() ) {
		f16.x( b.x() - b.radius() );
		f16.y( -b.y() - b.radius() + offset );
		//f16.h( f16.w( b.size() ) );
		SDL_RenderCopy( renderer, f16.texture() , NULL, f16.rect() );
	}

	for( const auto & b : game.bullets() ) {
		bullet.x( b.x() - b.radius() );
		bullet.y( -b.y() - b.radius() + offset );
		bullet.h( b.size() );
		bullet.w( b.size() / 2 );

		SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
		SDL_RenderFillRect( renderer , bullet.rect() );
		//SDL_RenderCopy( renderer, bullet.texture() , NULL, bullet.rect() );
	}

	//plane
	SDL_Texture* pl;
	if ( game.plane().speedX() == 0 )
		pl = mig29.texture();
	else if( game.plane().speedX() < 0 )
		pl = mig29_l.texture();
	else
		pl = mig29_r.texture();

	mig29.x( game.plane().x() - 34 );//game.plane().radius();
	mig29.y( -game.plane().y() + offset - 50);//game.plane().radius();
	//rect.h = 100;
	//rect.w = 68;
	SDL_RenderCopy( renderer, pl, NULL, mig29.rect() );


	//temporary blobs
	for( const auto & b : game.tblobs() ) {

		int curr_frame = explosion.size() * ( b.ttlStart() - b.ttl() ) / b.ttlStart();
		if( curr_frame == (int)explosion.size() )
			--curr_frame;
		else if( curr_frame < 0 )
			curr_frame = 0;

		explosion[curr_frame].x( b.x() - explosion[curr_frame].w()/2 );
		explosion[curr_frame].y( -b.y() - explosion[curr_frame].h()/2 + offset );

		SDL_RenderCopy( renderer, explosion[curr_frame].texture(),
				NULL, explosion[curr_frame].rect() );
	}

	SDL_RenderPresent( renderer );
}
