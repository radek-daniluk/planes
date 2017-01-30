//graphics_sdl.cpp

#include <iostream>
#include <string>
#include <SDL2/SDL_image.h>
#include "graphics_sdl.h"
#include "game.h"

using std::cerr;
using std::cout;
using std::endl;

GraphicsSdl::GraphicsSdl( std::string title, int width, int height, bool vsync ) :
		Sdl_initializer( title, width, height, vsync ),
		mig29{ "img/mig29.png", rend },
		mig29_r{ "img/mig29_right.png", rend },
		mig29_l{ "img/mig29_left.png", rend },
		f16{ "img/F-16.png", rend },
		f22{ "img/F-22.png", rend },
		f35{ "img/F-35.png", rend },
		bullet{ "img/bullet.png", rend },
		tree{ "img/tree.png", rend }
{
	for( auto & path : {"img/explosion1.png",
						"img/explosion2.png",
						"img/explosion3.png",
						"img/explosion4.png",
						"img/explosion5.png",
						"img/explosion6.png"} )
		expl.emplace_back( path, rend );

	for( unsigned int i=0; i<expl.size(); ++i ) {
		expl[i].w( expl[i].w()/2 );
		expl[i].h( expl[i].h()/2 );
	}


	wreck = { SDL_Rect{43,45,27,32}, SDL_Rect{0,0,27,32} };
	wreckBig = { SDL_Rect{0,0,42,100}, SDL_Rect{0,0,42,100} };
}

void GraphicsSdl::clear() {
	SDL_SetRenderDrawColor( rend, 0x5C, 0xDF, 0x46, 0xFF );
	SDL_RenderClear( rend );
}

void GraphicsSdl::update( const Application & app, const Game & game ) {

	/*Uint8 alpha;
	if( app.state() == running ) alpha = 0xFF;
	else if( app.state() == paused ) alpha = 0x80;
	else alpha = 0xFF;*/


	int py = game.plane().y();
	int offset = py + height - game.plane().size();

	// fixed blobs
	for( const auto & b : game.fblobs() ) {
		if( b.active() ) {
			tree.x( b.x() - b.radius() );
			tree.y( -b.y() - b.radius() + offset );
			tree.h( tree.w( b.size() ) );
			SDL_RenderCopy( rend, tree.texture() , NULL, tree.rect() );
		}
	}

	// moving blobs
	for( const auto & b : game.blobs() ) {
		f16.x( b.x() - b.radius() );
		f16.y( -b.y() - b.radius() + offset );
		//f16.h( f16.w( b.size() ) );
		SDL_RenderCopy( rend, f16.texture() , NULL, f16.rect() );
	}

	for( const auto & b : game.wreckageBig() ) {

		wreckBig[1].x = b.x() - b.radius();
		wreckBig[1].y = -b.y() - b.radius() + offset;
		wreckBig[1].w = b.radius();
		wreckBig[1].h = b.radius() + 60;

		SDL_RenderCopyEx( rend, f16.texture(),
							&wreckBig[0], &wreckBig[1],
							b.angle(), NULL, SDL_FLIP_NONE);
	}

	for( const auto & b : game.wreckage() ) {

		wreck[1].x = b.x() - b.radius();
		wreck[1].y = -b.y() - b.radius() + offset;
		wreck[1].w = wreck[1].h = b.size();

		SDL_RenderCopyEx( rend, f16.texture(),
							&wreck[0], &wreck[1],
							b.angle(), NULL, SDL_FLIP_NONE);
	}

	for( const auto & b : game.bullets() ) {
		bullet.x( b.x() - b.radius() );
		bullet.y( -b.y() - b.radius() + offset );
		bullet.h( b.size() );
		bullet.w( b.size() / 2 );

		SDL_SetRenderDrawColor( rend, 0xFF, 0x00, 0x00, 0xFF );
		SDL_RenderFillRect( rend , bullet.rect() );
		//SDL_RenderCopy( rend, bullet.texture() , NULL, bullet.rect() );
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
	SDL_RenderCopy( rend, pl, NULL, mig29.rect() );


	//temporary blobs
	for( const auto & b : game.tblobs() ) {

		int spr = expl.size() * ( b.ttlStart() - b.ttl() ) / b.ttlStart();
		if( spr == (int)expl.size() )
			--spr;
		else if( spr < 0 )
			spr = 0;

		//expl[spr].w( expl[spr].texture().h * b.size() );
		//expl[spr].h( expl[spr].h() * b.size() );
		expl[spr].x( b.x() - expl[spr].w()/2 );
		expl[spr].y( -b.y() - expl[spr].h()/2 + offset );

		SDL_RenderCopy( rend, expl[spr].texture(),
				NULL, expl[spr].rect() );
	}

	if( app.state() == paused ) {
		SDL_SetRenderDrawBlendMode( rend, SDL_BLENDMODE_MOD );
		SDL_Rect rect;
		rect.x = width/4;
		rect.y = height/4;
		rect.w = width/2;
		rect.h = height/2;
		SDL_SetRenderDrawColor( rend, 0x40, 0x40, 0x40, 0xFF );
		SDL_RenderFillRect( rend, NULL );
		SDL_RenderFillRect( rend, &rect );
		SDL_SetRenderDrawBlendMode( rend, SDL_BLENDMODE_BLEND );
	}


	SDL_RenderPresent( rend );
}
