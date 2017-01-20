//application.cpp
#include <iostream>
#include <iomanip>
#include <fstream>
#include <array>
#include <thread>
#include <chrono>

#include "application.h"
#include "controls.h"
#include "time_count.h"
#include "fps_count.h"

using std::cerr;
using std::cout;
using std::endl;


Application::Application( int debug, int loop_delay ) {
	state_ = intro;
	this->loop_delay = loop_delay;
	vsync = !(bool)(loop_delay);
	this->debug = debug;

	try{
		graphics = new GraphicsSdl( vsync );
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

	string sep = " \t";
	std::array<TimeCount, 6> tc;

	FpsCount fps;

	if( debug )
		cout << "\t\t\t\t\t\t\tfps:          " << std::setprecision(1) << std::fixed;

	while( state_ ) { // state_ != quit

		int interval = fps.interval();
		if ( debug ){
			if( debug == 1 )
				cout << "\b\b\b\b\b\b\b\b\b\b       " << 1000000.0/interval;
			else if ( debug > 1 )
				cout << "fps=" << 1000000.0/interval << " \t";
		}

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
		gra->updateActive();
		if( debug ){
			tc[2].stop();
			if(debug > 1)
				cout << tc[2].last() << sep;}

		if( debug )
			tc[3].start();
		gra->collisions();
		if( debug ){
			tc[3].stop();
			if(debug > 1)
				cout << tc[3].last() << sep;}

		if( debug && !vsync )
			tc[5].start();
		graphics->clear();
		if( debug && !vsync ) {
			tc[5].stop();
			if(debug > 1)
				cout << tc[5].last() << sep;}

		if( debug )
			tc[4].start();
		graphics->update( *this, *gra );
		if( debug ) {
			tc[4].stop();
			if(debug > 1)
				cout << tc[4].last() << endl;}

		if ( !vsync )
			std::this_thread::sleep_for( std::chrono::microseconds( loop_delay ) );

	}

	if( debug ) {
		cout << "Execution times summary" << endl;
		cout << "  \tcontrl\tnextStp\tactive\tcollis\trender\tclear";
		if( vsync )
			cout << "-N/A(vsync)";

		cout << endl << "min";
		for( auto & t : tc )
			cout << sep << t.min();

		cout << " [µs]" << endl << "mean";
		for( auto & t : tc )
			cout << sep << t.mean();

		cout << " [µs]" << endl << "max";
		for( auto & t : tc )
			cout << sep << t.max();

		cout << " [µs]" << endl << "sum";
		for( auto & t : tc )
			cout << sep << t.sum()/1000;

		cout << " [ms]" << endl << "total: ";
		float total = 0;
			for( auto& t : tc )
				total += t.sum();
		cout << total/1000000 << " s" << endl;
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

