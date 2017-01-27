//controls.h
#ifndef CONTROLS_H
#define CONTROLS_H

#include "common.h"

class Controls {

	private:

	SDL_Event event;
	const Uint8 * keys;

	void basic_events( SDL_Event &, Application & );
	void hidden_events( SDL_Event &, Application & );
	bool pause_events( SDL_Event &, Application & );
	void game_controls( Game & );

	public:

	Controls();
	~Controls();

	void gameEventLoop( Application &, Game & );
	bool pauseEventLoop( Application &, int sleep_time );
	void hiddenEventLoop( Application &, int sleep_time );

};

#endif
