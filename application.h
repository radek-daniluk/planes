//application.h
#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include <memory> //std::unique_ptr
#include "common.h"
#include "game.h"
#include "graphics_sdl.h"
#include "controls.h"
#include "exceptions.h"

class Application {
	using GfxPtr = std::unique_ptr<GraphicsSdl> ;
	using CtrlPtr = std::unique_ptr<Controls>;
	using GamePtr = std::unique_ptr<Game>;
	const std::string s_err = "Reinstallation may resolve this problem.";

	AppState state_;
	GamePtr gra;
	GfxPtr gfx;
	CtrlPtr ctrl;
	bool vsync;
	int fps{0};
	int debug{0};

	int loadGame( const std::string & );
	void show_err( const char* );
	void show_err( const std::string & s ) { show_err( s.c_str() ); }


	public:

	Application( int width = 0, int height = 0, int debug = 0, int fps = 0 );
	~Application() {};

	int startMainLoop ( void );
	AppState state() const { return state_; }
	void state( AppState newState ) { state_ = newState; }
	SDL_Window* win() const;

};

#endif
