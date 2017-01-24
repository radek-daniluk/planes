//sprite.h
// Class represents simple 2D graphical sprite with fixed size and no rotation
#include <iostream>
#include "sprite.h"

Sprite::Sprite( std::string path_to_file, SDL_Renderer * renderer,
		int x, int y ) {

	texture_ = load_texture( path_to_file, renderer );
	if( texture_ == NULL )
		throw "Sprite failed to init image file:" + 	path_to_file;

	int width, height;
	SDL_QueryTexture( texture_, NULL, NULL, &width, &height );
	rect_.x = x;
	rect_.y = y;
	rect_.w = width;
	rect_.h = height;
}

SDL_Texture * Sprite::load_texture( std::string path, SDL_Renderer * renderer ) {

	SDL_Texture* new_texture = NULL;

	SDL_Surface* loaded_surface = IMG_Load( path.c_str() );
	if( loaded_surface == NULL ) {
		std::cout << "Unable to load image "<< path <<"! SDL_image Error: "
		<< IMG_GetError() << std::endl;
	} else {
		new_texture = SDL_CreateTextureFromSurface( renderer, loaded_surface );
		if( new_texture == NULL ) {
			std::cout << "Unable to create texture from "<< path << "! SDL Error: "
			<< SDL_GetError() << std::endl;
		}
		SDL_FreeSurface( loaded_surface );
	}

	return new_texture;
}