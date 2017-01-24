//controls.cpp

#include<SDL2/SDL_events.h>
#include<thread>
#include<chrono>
#include "controls.h"
#include "game.h"
#include "application.h"

Controls::Controls() { keys = SDL_GetKeyboardState(NULL);}

Controls::~Controls() {}

void Controls::eventLoop( Application & app, Game & game ) {
	basic_events( app );
	game_events( game );
}

void Controls::pauseEventLoop( Application & app ) {
	basic_events( app );
	std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
}

void Controls::basic_events( Application & app ) {

	while( SDL_PollEvent( &event ) ) {
		switch( event.type ) {
			case SDL_KEYDOWN:
				switch( event.key.keysym.sym ) {
					case SDLK_ESCAPE:
						app.state( quit );
						break;
					case SDLK_p: // pause game
						if      ( app.state() == paused )
										app.state( running );
						else if ( app.state() == running )
										app.state( paused );
						break;
					} //swith event.key.keysym.sym
					break; // SDL_KEYDOOWN
			case SDL_QUIT:
				app.state( quit );
				break;
		} // switch event.type
	}//while PollEvent
}

void Controls::game_events( Game & game ) {
	auto & p = game.nonConstPlane();

	// manage x axis movement
	if( keys[ SDL_GetScancodeFromKey( SDLK_LEFT ) ] ) {
		game.accelPlane( -1000, 0 );
	}else if( keys[ SDL_GetScancodeFromKey( SDLK_RIGHT ) ] ) {
		game.accelPlane( 1000, 0 );
	}else { // gradually increase or decrease speed to 0
		if( p.speedX() < -1000 )
			game.accelPlane( 1000, 0 );
		else if( p.speedX() > 1000 )
			game.accelPlane( -1000 ,0 );
		else
			p.stopX();
	}

	// manage y axis movement
	if( keys[ SDL_GetScancodeFromKey( SDLK_UP ) ] ) {
		game.accelPlane( 0, 700 );
	}else if( keys[ SDL_GetScancodeFromKey( SDLK_DOWN ) ] ) {
		game.accelPlane( 0, -500 );
	}

	if( keys[ SDL_GetScancodeFromKey( SDLK_SPACE ) ] )
		game.addBullet();
}

