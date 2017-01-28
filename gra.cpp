#include <iostream>
#include <sstream>

#include "application.h"

using std::cerr;
using std::cout;
using std::endl;

using std::stringstream;

int main(int argc, char** argv) {

	int debug_app = 1;
	int fps = 0;

	if (argc > 1) {
		stringstream s( argv[1] );
		s >> debug_app;
	}
	cout << "debug=" << debug_app << endl;

	if (argc > 2) {
		stringstream s( argv[2] );
		s >> fps;
		if( fps )
			cout << "vsync disabled. fps=" << fps << "µs" << endl;
	}

	Application app( debug_app, fps );
	if ( app.startMainLoop() ) { cerr << "mainLoop() error" << endl; return 3; }

	return 0;
}
