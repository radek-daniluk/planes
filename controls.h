//controls.h
#ifndef CONTROLS_H
#define CONTROLS_H

#include "common.h"

class Controls {

	private:

	const Uint8 * keys;

	public:

	Controls();
	~Controls();

	void eventLoop( Application&, Game& ) const;

};

#endif
