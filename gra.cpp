#include <iostream>
#include <sstream>

#include "application.h"

using std::cerr;
using std::cout;
using std::endl;

using std::stringstream;

int main(int argc, char** argv) {

	int debug_app = 1;

	int i;
	cout << "arguments from CLI:" << endl;
	for(i=0; i<argc; i++)
		cout << i << "=" << argv[i] << endl;

	if (argc > 1) {
		stringstream s( argv[1] );
		s >> debug_app;
	}
	cout << "debug=" << debug_app << endl;

	Application app( debug_app );
	// CLI arguments handling

	//if ( initNewGame() ) { cerr << "initNewGame() error << endl; return 2; }
	if ( app.startMainLoop() ) { cerr << "mainLoop() error" << endl; return 3; }

	return 0;
}
