//graphics_sdl.h
#ifndef GRAPHICS_SDL_H
#define GRAPHICS_SDL_H

#include <SDL2/SDL.h>
#include <vector>
#include "common.h"
#include "application.h"
#include "time_count.h"
#include "sprite.h"
#include "sdl_initializer.h"

class GraphicsSdl : public Sdl_initializer {

	private:

	int scale_factor;

	Sprite mig29;
	Sprite mig29_r;
	Sprite mig29_l;

	Sprite f16;
	Sprite f22;
	Sprite f35;

	Sprite bullet;
	Sprite tree;

	std::vector<Sprite> explosion;

	public:

	GraphicsSdl( bool vsync = true );
	~GraphicsSdl() {}

	void update( const Application &, const Game & );
	void clear();
};

#endif
