//gra.cpp
#include <iostream>
#include <sstream> //std::istringstream
#include "application.h"

using std::cerr;
using std::cout;
using std::endl;
using std::istringstream;

int main(int argc, char** argv) {

	int debug_app = 1;
	int fps = 0;
	int width = 0;
	int height = 0;

	// parse window size in format 800x600
	if (argc > 1) {
		istringstream s( argv[1] );
		string token;
		std::getline(s, token, 'x');
		istringstream tok_s( token );
		tok_s >> width;
		s >> height;
	}// debug level
	if (argc > 2) {
		istringstream s( argv[2] );
		s >> debug_app;
	}
	cout << "debug=" << debug_app << endl;
	// get fps or enable vsync if fps==0
	if (argc > 3) {
		istringstream s( argv[3] );
		s >> fps;
		if( fps )
			cout << "vsync disabled. fps=" << fps << "µs" << endl;
	}

	Application app( width, height, debug_app, fps );
	if ( app.startMainLoop() ) { cerr << "mainLoop() error" << endl; return 3; }

	return 0;
}
