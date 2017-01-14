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

	int loadGame( std::string );

	public:

	Application();
	~Application();

	int startMainLoop ( void );
	AppState state() const { return state_; }
	void state( AppState newState ) { state_ = newState; }

};

#endif
