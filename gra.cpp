#include <iostream>

#include "application.h"

using std::cerr;
using std::cout;
using std::endl;

int main(int argc, char** argv) {

	int i;
	cout << "arguments from CLI:" << endl;
	for(i=0; i<argc; i++)
		cout << i << "=" << argv[i] << endl;

	Application app;
	// CLI arguments handling

	//if ( initNewGame() ) { cerr << "initNewGame() error << endl; return 2; }
	if ( app.startMainLoop() ) { cerr << "mainLoop() error" << endl; return 3; }

	return 0;
}
