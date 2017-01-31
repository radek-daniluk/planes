//application.h
#ifndef APPLICATION_H
#define APPLICATION_H

#include <exception> //std::exception
#include "common.h"
#include "game.h"
#include "graphics_sdl.h"
#include "controls.h"
#include "exceptions.h"

class Application {

	private:

	AppState state_;
	Game* gra;
	GraphicsSdl* graphics;
	Controls* controls;
	bool vsync;
	int fps{0};
	int debug{0};

	int loadGame( const std::string & );
	void show_err( const std::exception & );


	public:

	Application( int width = 0, int height = 0, int debug = 0, int fps = 0 );
	~Application();

	int startMainLoop ( void );
	AppState state() const { return state_; }
	void state( AppState newState ) { state_ = newState; }

};

#endif
