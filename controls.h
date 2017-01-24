//controls.h
#ifndef CONTROLS_H
#define CONTROLS_H

#include "common.h"

class Controls {

	private:

	SDL_Event event;
	const Uint8 * keys;

	void basic_events( Application & );
	void game_events( Game & );

	public:

	Controls();
	~Controls();

	void eventLoop( Application&, Game& );
	void pauseEventLoop( Application& );

};

#endif
