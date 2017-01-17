//application.cpp
#include <iostream>
#include <fstream>

#include "application.h"
#include "controls.h"
#include "time_count.h"

using std::cerr;
using std::cout;
using std::endl;


Application::Application( int debug ) {
	state_ = intro;
	this->debug = debug;

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

	string sep = ",";
	TimeCount tc[4];

	while( state_ ) { // state_ != quit

		if( debug )
			tc[0].start();
		controls->eventLoop( *this, *gra );
		if( debug ){
			tc[0].stop();
			if(debug > 1)
				cout << tc[0].last() << sep;}

		if( debug )
			tc[1].start();
		gra->nextStep();
		if( debug ){
			tc[1].stop();
			if(debug > 1)
				cout << tc[1].last() << sep;}

		if( debug )
			tc[2].start();
		gra->collisions();
		if( debug ){
			tc[2].stop();
			if(debug > 1)
				cout << tc[2].last() << sep;}

		if( debug )
			tc[3].start();
		graphics->update( *this, *gra );
		if( debug ){
			tc[3].stop();
			if(debug > 1)
				cout << tc[3].last() << endl;}

		SDL_Delay( graphics->getLoopDelay() );
	}

	if( debug ) {
		cout << "Execution times summary" << endl;
		cout << "  \tcontrl\tnextStp\tcollis\trender" << endl << "mean\t"
		<< tc[0].mean() << "\t" << tc[1].mean() << "\t"<< tc[2].mean() << "\t"
		<< tc[3].mean() << " [µs]" << endl << "min\t"
		<< tc[0].min() << "\t" << tc[1].min() << "\t" << tc[2].min() << "\t"
		<< tc[3].min() << " [µs]" << endl << "max\t"
		<< tc[0].max() << "\t" << tc[1].max() << "\t" << tc[2].max() << "\t"
		<< tc[3].max() << " [µs]" << endl << "sum\t"
		<< tc[0].sum()/1000 << "\t" << tc[1].sum()/1000 << "\t"
		<< tc[2].sum()/1000 << "\t" << tc[3].sum()/1000 << " [ms] total: "
		<< ( tc[0].sum() + tc[1].sum() + tc[2].sum() + tc[3].sum() )/1000000
		<< "s" << endl;
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

