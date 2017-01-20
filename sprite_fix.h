//sprite_fix.h
// Class represents simple 2D graphical sprite with fixed size and no rotation.

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sprite_fix {

	private:
	SDL_Texture * texture_ {NULL};
	SDL_Rect rect_;
	SDL_Texture * load_texture( std::string, SDL_Renderer * );

	public:
	Sprite_fix( std::string, SDL_Renderer *, int x = 0, int y = 0);
	~Sprite_fix() { SDL_DestroyTexture( texture_ ); }

	SDL_Texture * texture() { return texture_; }
	const SDL_Rect * rect() const { return & rect_; }
	void x( int new_x ) { rect_.x = new_x; }
	void y( int new_y ) { rect_.y = new_y; }
};
