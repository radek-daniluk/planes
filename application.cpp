//application.cpp
#include <iostream>
#include <iomanip> // std::setprecision, std::fixed
#include <fstream> // std::ifstream
#include <array>
#include <thread> // std::this_thread::sleep_for
#include <chrono> // std::chrono::microseconds

#include "application.h"
#include "controls.h"
#include "time_count.h"
#include "time_loop.h"

using std::cerr;
using std::cout;
using std::endl;

Application::Application( int width, int height, int debug, int fps ) {
	state_ = intro;
	this->fps = fps;
	vsync = !(bool)(fps);
	this->debug = debug;

	try{
		gfx = GfxPtr(new GraphicsSdl( "no title yet", width, height, vsync ) );
	}
	catch( SdlErr & e ) { show_err( e.what() ); exit(EXIT_FAILURE); }
	catch( SdlImgErr & e ) { show_err( e.what() ); exit(EXIT_FAILURE); }

	ctrl = CtrlPtr( new Controls() );
}

SDL_Window* Application::win() const { return gfx->win(); }

int Application::startMainLoop ( void ) {

	if( loadGame("test/2.game") ) {
		return -1;
	}

	state_ = running;

	string sep = " \t";
	cout << std::setprecision(1) << std::fixed;

	std::array<TimeCount, 6> tc;
	TimeLoop timeL;
	TimeCount tcvsync;

	while( state_ ) { // state_ != quit

		if( !vsync )
			tcvsync.start();

		double interval = timeL.interval();
		if ( debug ){
			if( debug == 1 )
				;//cout << "\b\b\b\b\b\b\b\b\b\b       " << 1.0/interval;
			else if ( debug > 1 )
				cout << "fps=" << 1.0/interval << " \t";
		}

		if( state_ == hidden ){
			timeL.pause();
			while( state_ == hidden )
				ctrl->hiddenEventLoop( *this, 50 );
			timeL.resume();
		}

		if( state_ == paused ){
			timeL.pause();
			while( state_ == paused )
				if( ctrl->pauseEventLoop( *this, 50 ) ) {
					gfx->clear();
					gfx->update( *this, *gra );
				}
			timeL.resume();
		}

		if( state_ == running ) { // update game mechanics while running
			if( debug )
				tc[0].start();
			ctrl->gameEventLoop( *this, *gra );
			if( debug ){
				tc[0].stop();
				if(debug > 1)
					cout << tc[0].last() << sep;}

			if( debug )
				tc[1].start();
			gra->nextStep( interval );
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
			gra->collisions( interval );
			if( debug ){
				tc[3].stop();
				if(debug > 1)
					cout << tc[3].last() << sep;}
		}// if ( state_ == running )

		if( debug && !vsync )
			tc[5].start();
		gfx->clear();
		if( debug && !vsync ) {
			tc[5].stop();
			if(debug > 1)
				cout << tc[5].last() << sep;}

		if( debug )
			tc[4].start();
		gfx->update( *this, *gra );
		if( debug ) {
			tc[4].stop();
			if(debug > 1)
				cout << tc[4].last() << endl;}

		if ( !vsync ) {
			tcvsync.stop();
			int delay = 1000000.0/fps - tcvsync.last();
			std::this_thread::sleep_for( std::chrono::microseconds( delay ) );
		}
	}

	// Display table summarising execution times counted by TimeCount's in tc arr
	if( debug ) {
		cout << "Execution times summary" << endl;
		cout << "  \tctrl\tnextStp\tactive\tcollis\trender\tclear";
		if( vsync )
			cout << "<-clear N/A(vsync)";
		cout << endl;

		std::vector<string> labels{"min","mean","max","sum"};
		std::vector<string> units {"µs", "µs",  "µs", "ms" };
		std::vector<int> divisors { 1,    1,     1,   1000 };
		using T = TimeCount;
		std::vector<double(T::*)()const> func{ &T::min, &T::mean, &T::max, &T::sum };
		float total = 0;

		for( int i=0; i<(int)labels.size(); i++ ) {
			cout << labels[i];
			for( auto & t : tc ) {
				cout << sep << (t.*func[i])()/divisors[i];
				total += t.sum();
			}
			cout << " [" << units[i] << "]" << endl;
		}
		cout << "total " << total/1000000 << "[s]" << endl;
	}
	return 0;
}

int Application::loadGame( const std::string & file_name ) {

	std::ifstream fs( file_name );
	if( !fs.good() ) {
		show_err( "Cannot open file:'" + file_name + "' It is probably missing\n"
			+ s_err );
		return -1;
	}

	try{
		gra = GamePtr( new Game( fs, 1.0 ) );
	}
	catch ( FileErr e ) { show_err( string("File:'") + file_name
		+ "' is probably corrupted;\n" + s_err + "\n" + e.what() ); return -1;
	}
	return 0;
}

void Application::show_err( const char * s) {
	if( SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", s, NULL) )
		cout << s << endl;
}
