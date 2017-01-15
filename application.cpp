//application.cpp
#include <iostream>
#include <fstream>
#include "application.h"
#include "controls.h"

using std::cerr;
using std::cout;
using std::endl;

Application::Application() {
	state_ = intro;

	try{
		graphics = new GraphicsSdl();
	}
	catch (const char* s) {
		cout << s << endl;
		exit(1);
	}

	controls = new Controls();

}

Application::~Application() {
	//delete gra;
	delete controls;
	delete graphics;
}

int Application::startMainLoop ( void ) {

	if( loadGame("test/2.game") ) {
		std::cout << "Game loading error. Exiting" << std::endl;
		return 2;
	}

	state_ = running;

	while( state_ ) { // state_ != quit
		controls->eventLoop( *this, *gra );
		++(*gra);
		if( gra->collisions() )
			cout << "Bum bum!!!" << std::endl;
			//state_.pause()
		graphics->update( *this, *gra );
		SDL_Delay( graphics->getLoopDelay() );
	}

	delete gra;

	return 0;
}

int Application::loadGame( std::string file_name ) {

	std::ifstream fs( file_name );
	try{
		gra = new Game( fs, 60, 60 );
	}
	catch (const char* s) {
		std::cout << s << " from file:\"" << file_name << "\"" << std::endl;
		fs.close();
		return 1;
	}

	fs.close();
	return 0;
}

