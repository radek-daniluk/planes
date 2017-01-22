//animation.h
// Class represents animation of sprites.

#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "sprite.h"

#include <iostream>

class Animation {

	private:
	std::vector< Sprite > sprites;
	std::vector< Sprite >::iterator active_sprite;

	public:
	Animation( std::vector<std::string> file_paths, SDL_Renderer * renderer) {

		if( file_paths.size() < 2 )
			throw "Too create Animation object at least 2 image files needed.";

		for( auto & path : file_paths )
			sprites.emplace_back( path, renderer );
		active_sprite = sprites.begin();

	if (sprites[0].texture() == NULL )
		std::cout << "NULL" << std::endl;
	int a,b,c;
	a = b = c = -1;
	Uint32 u = 1;
	if( SDL_QueryTexture( sprites[0].texture(), &u, &a, &b, &c ) )
		std::cout << "Zla animatura:" << SDL_GetError() << a << " " << b << " " << c << " " << u
		<< std::endl;
	}

	~Animation() {}

	// change to next elt in sprites' vector and if end of vector set to begin
	void operator++() {
		if( ++active_sprite == sprites.end() )
			active_sprite = sprites.begin();
	}
	Sprite & operator[](int n) { return sprites[n]; }
	void setActive( int n ) { active_sprite = sprites.begin() + n; }

	int size() { return sprites.size(); }

	SDL_Texture * texture() { return active_sprite->texture(); }
	const SDL_Rect * rect() const { return active_sprite->rect(); }

	int x( int new_x ) { active_sprite->x( new_x ); return new_x; }
	int y( int new_y ) { active_sprite->y( new_y ); return new_y; }
	int w( int new_w ) { active_sprite->w( new_w ); return new_w; }
	int h( int new_h ) { active_sprite->h( new_h ); return new_h; }

	int x() { return active_sprite->x(); }
	int y() { return active_sprite->y(); }
	int w() { return active_sprite->w(); }
	int h() { return active_sprite->h(); }

};
#endif
