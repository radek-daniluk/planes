//sprite.h
// Class represents simple 2D graphical sprite with fixed size and no rotation.
#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sprite {

	private:
	SDL_Texture * texture_ {NULL};
	SDL_Rect rect_;
	SDL_Texture * load_texture( std::string, SDL_Renderer * );

	public:
	Sprite( std::string, SDL_Renderer *, int x = 0, int y = 0);
	Sprite( const Sprite & ) = delete;
	Sprite( Sprite && m_spr) {
		texture_ = m_spr.texture_;
		m_spr.texture_ = NULL;
		rect_ = m_spr.rect_;
	}
	~Sprite() { SDL_DestroyTexture( texture_ ); }

	SDL_Texture * texture() { return texture_; }
	const SDL_Rect * rect() const { return & rect_; }

	int x( int new_x ) { rect_.x = new_x; return new_x; }
	int y( int new_y ) { rect_.y = new_y; return new_y; }
	int w( int new_w ) { rect_.w = new_w; return new_w; }
	int h( int new_h ) { rect_.h = new_h; return new_h; }

	int x() { return rect_.x; }
	int y() { return rect_.y; }
	int w() { return rect_.w; }
	int h() { return rect_.h; }
};
#endif
