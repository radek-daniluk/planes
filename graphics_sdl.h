//graphics_sdl.h
#ifndef GRAPHICS_SDL_H
#define GRAPHICS_SDL_H

#include <SDL2/SDL.h>
#include "common.h"
#include "application.h"

class GraphicsSdl {

	private:

	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_DisplayMode dm;
	SDL_DisplayMode desktopDm;

	float loopDelay;

	public:

	GraphicsSdl();
	~GraphicsSdl();

	//static void sdlDisplayInfo( void );

	void update( const Application &, const Game & );
	float getLoopDelay() const { return loopDelay; };

	//std::string print( void );

};

#endif
