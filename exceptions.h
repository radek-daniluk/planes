//exceptions.h
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <SDL2/SDL.h>	// SDL_GetError()
#include <SDL2/SDL_image.h> // IMG_GetError()
#include <stdexcept> //std::runtime_error
#include <string>

using std::string;
using std::runtime_error;

class SdlErr : public runtime_error {
public:
	SdlErr( const string & s )
	: runtime_error( s + string( "; SDL_GetError:'" ) + string( SDL_GetError() )
	+  string( "'" ) ) {}
};

class SdlImgErr : public runtime_error {
public:
	SdlImgErr( const string & s )
	: runtime_error( s + string( "; IMG_GetError:'" ) + string( IMG_GetError() )
	+  string( "'" ) ) {}
};

class FileErr : public runtime_error {
public:
	string path;
	FileErr( const string & s, const string & p = "unknown" ) :
		runtime_error( s ), path(p) {}
};
#endif
