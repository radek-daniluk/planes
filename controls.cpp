//controls.cpp

#include<SDL2/SDL_events.h>
#include<thread>
#include<chrono>
#include "controls.h"
#include "game.h"
#include "application.h"

Controls::Controls() { keys = SDL_GetKeyboardState(NULL); }

Controls::~Controls() {}

void Controls::gameEventLoop( Application & app, Game & game ) {

	while( SDL_PollEvent( event ) ) {
		basic_events( *event, app );
		if( event->type == SDL_KEYDOWN )
			if( event->key.keysym.sym == SDLK_ESCAPE )
				app.state( paused );
	}
	game_controls( game );
}

bool Controls::pauseEventLoop( Application & app, int sleep_time ) {
	std::this_thread::sleep_for( std::chrono::milliseconds( sleep_time ) );

	bool redraw = false;

	while( SDL_PollEvent( event ) ) {
		basic_events( *event, app );
		redraw = pause_events( *event, app );
	}
	return redraw;
}

void Controls::hiddenEventLoop( Application & app, int sleep_time ) {
	std::this_thread::sleep_for( std::chrono::milliseconds( sleep_time ) );

	while( SDL_PollEvent( event ) ) {
		basic_events( *event, app );
		hidden_events( *event, app );
	}
}

void Controls::basic_events( SDL_Event & event, Application & app ) {

	if( event.type == SDL_QUIT )
		app.state( quit );
	// TODO add OS events
}

void Controls::hidden_events( SDL_Event & event, Application & app ) {
	if( event.type == SDL_WINDOWEVENT )
		if( event.window.event == SDL_WINDOWEVENT_SHOWN )
			app.state( paused );
}

bool Controls::pause_events( SDL_Event & event, Application & app ) {
	bool toRedraw = false;
	if( event.type == SDL_WINDOWEVENT ) {
		if( event.window.event == SDL_WINDOWEVENT_HIDDEN ) {
			app.state( hidden ); }
		else if( event.window.event == SDL_WINDOWEVENT_EXPOSED ) {
			toRedraw = true; }
	}
	else if( event.type == SDL_KEYDOWN ) {
		if( event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_n ) {
			app.state( running ); }
		else if( event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_t ||
				event.key.keysym.sym == SDLK_y ) {
			app.state( quit ); }
	}
	return toRedraw;
}

void Controls::game_controls( Game & game ) {
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

