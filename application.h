//application.h
#ifndef APPLICATION_H
#define APPLICATION_H

#include "common.h"
#include "game.h"
#include "graphics_sdl.h"
#include "controls.h"

class Application {

	private:

	AppState state_;
	Game* gra;
	GraphicsSdl* graphics;
	Controls* controls;
	bool vsync;
	int fps{0};
	int debug{0};

	int loadGame( std::string );


	public:

	Application( int debug = 0, int fps = 0 );
	~Application();

	int startMainLoop ( void );
	AppState state() const { return state_; }
	void state( AppState newState ) { state_ = newState; }

};

#endif
