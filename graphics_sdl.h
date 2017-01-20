//graphics_sdl.h
#ifndef GRAPHICS_SDL_H
#define GRAPHICS_SDL_H

#include <SDL2/SDL.h>
#include "common.h"
#include "application.h"
#include "time_count.h"

class GraphicsSdl {

	private:

	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_DisplayMode dm;
	SDL_DisplayMode desktopDm;

	SDL_Texture* mig29;
	SDL_Texture* mig29_r;
	SDL_Texture* mig29_l;

	SDL_Texture* f16;
	SDL_Texture* f22;
	SDL_Texture* f35;

	SDL_Texture* explosion;
	SDL_Texture* bullet;
	SDL_Texture* tree;

	SDL_Texture* loadTexture( std::string );

	int refresh_rate;

	public:

	GraphicsSdl( bool vsync = true );
	~GraphicsSdl();

	//static void sdlDisplayInfo( void );

	void update( const Application &, const Game & );
	void clear();
	int refreshRate() const { return refresh_rate; };

	//std::string print( void );

};

#endif
