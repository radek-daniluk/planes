//game.cpp
#include <iterator>
#include "game.h"

Game::Game( std::istream & is, int speed, int fps) {

	speed_ = speed;
	fps_ = fps;
	is >> *this;

	//plane = Blob2d<int>
}

Game::Game(int speed, int fps) {

	speed_ = speed;
	fps_ = fps;
	for(int i=40; i<400; i+=50) {
		blobs_.push_back( Blob2d<int>( i*2, i, 16 ) );
	}
}

void Game::nextStep () {

	for( Blob2d<int> & b : blobs_ )
		b + ( speed_/fps_ );

	for( auto it = tblobs_.begin(); it != tblobs_.end(); ++it )
		if( it->ttl() > 0 )
			--(*it);
		else
			tblobs_.erase( it-- );

	//std::cout << *this << std::endl;
}

int Game::collisions () {

	int collisions = 0;

	for( const Blob2d<int> & b : blobs_ )
		for( const Blob2d_fix<int> & fb: fblobs_)
			if( b.distance(fb) < 0 ) {
				++collisions;
				tblobs_.push_back( Blob2d_temp<int>(b) );
			}

	return collisions;
}

std::ostream & operator<<( std::ostream & os, const Game & g) {

	for (auto b : g.fblobs() )
		os << b.type() << ' ' << b;

	for (auto b : g.blobs() )
		os << b.type() << ' ' << b;

	for (auto b : g.tblobs() )
		os << b.type() << ' ' << b;

	return os;
}

std::istream & operator>>( std::istream & is, Game & g) {

	g.blobs_.clear();
	g.fblobs_.clear();
	g.tblobs_.clear();

	char c = ' ';
	while( is ) {
		is >> c;
		if( ! is.eof() ) {
			if(c == 'f')
				g.fblobs_.push_back( Blob2d_fix<int>( is ) );
			else if(c == 'm')
				g.blobs_.push_back( Blob2d<int>( is ) );
			else if(c == 't')
				g.tblobs_.push_back( Blob2d_temp<int>( is ) );
			else
				throw "operator>>( istream &, Game & ) failed: unknown blob type";
		}
	}

	if( is.eof() )
		std::cout << "Game loaded" << std::endl <<
			"operator>>( istream &, Game & ) OK" << std::endl;
	else
		throw "Game failed to load"; // <<
			//"operator>>( istream &, Game & ) FAILED" << std::endl);

	return is;
}
