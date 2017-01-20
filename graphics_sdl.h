//graphics_sdl.h
#ifndef GRAPHICS_SDL_H
#define GRAPHICS_SDL_H

#include <SDL2/SDL.h>
#include "common.h"
#include "application.h"
#include "time_count.h"
#include "sprite_fix.h"
#include "sdl_initializer.h"

class GraphicsSdl : public Sdl_initializer {

	private:

	/*SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_DisplayMode dm;
	*/

	Sprite_fix mig29;
	Sprite_fix mig29_r;
	Sprite_fix mig29_l;

	Sprite_fix f16;
	Sprite_fix f22;
	Sprite_fix f35;

	Sprite_fix explosion;
	Sprite_fix bullet;
	Sprite_fix tree;

	public:

	GraphicsSdl( bool vsync = true );
	~GraphicsSdl() {}

	void update( const Application &, const Game & );
	void clear();
};

#endif
