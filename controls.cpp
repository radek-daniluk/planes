//controls.cpp

#include<SDL2/SDL_events.h>
#include "controls.h"
#include "game.h"
#include "application.h"

Controls::Controls() { keys = SDL_GetKeyboardState(NULL);}

Controls::~Controls() {}

void Controls::eventLoop( Application& app, Game & game ) const {

	SDL_Event event;

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

	//SDL_PumpEvents();

	auto & p = game.nonConstPlane();

	// manage x axis movement
	if( keys[ SDL_GetScancodeFromKey( SDLK_LEFT ) ] ) {
		p.accel(-1,0);
	}else if( keys[ SDL_GetScancodeFromKey( SDLK_RIGHT ) ] ) {
		p.accel(1,0);
	}else { // gradually increase or decrease speed to 0
		if( p.speedX() < 0 )
			p.accel(1,0);
		else if( p.speedX() > 0 )
			p.accel(-1,0);
	}

	// manage y axis movement
	if( keys[ SDL_GetScancodeFromKey( SDLK_UP ) ] ) {
		p.accel(0,-0.5);
	}else if( keys[ SDL_GetScancodeFromKey( SDLK_DOWN ) ] ) {
		p.accel(0,1);
	}else{// gradually increase or decrease speed to 0
		if( p.speedY() < p.maxY() )
			p.accel(0,0.4);
		//else if( p.speedY() > 0 )
			//p.accel(0,-1);
	}

	if( keys[ SDL_GetScancodeFromKey( SDLK_SPACE ) ] )
		game.addBullet();

}

