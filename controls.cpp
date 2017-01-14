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

	int VEL = 10;

	if( keys[ SDL_GetScancodeFromKey( SDLK_LEFT ) ] ) {
		game.blob(0).speedX(-VEL);
	}else if( keys[ SDL_GetScancodeFromKey( SDLK_RIGHT ) ] )
		game.blob(0).speedX(VEL);
	else
		game.blob(0).speedX(0);
	if( keys[ SDL_GetScancodeFromKey( SDLK_UP ) ] )
		game.blob(0).speedY(-VEL);
	else if( keys[ SDL_GetScancodeFromKey( SDLK_DOWN ) ] )
		game.blob(0).speedY(VEL);
	else
		game.blob(0).speedY(0);
}

