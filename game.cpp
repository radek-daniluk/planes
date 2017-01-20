//game.cpp
#include <iterator>
#include "game.h"

Game::Game( std::istream & is, NUM speed, NUM fps) : speed_(speed), fps_(fps) {
	is >> *this;
}

Game::Game(NUM speed, NUM fps) : speed_(speed), fps_(fps) {}

void Game::nextStep () {

	plane_.step( speed_/fps_ );

	for( auto & b : blobs_ )
		b.step( speed_/fps_ );

	for( auto it = tblobs_.begin(); it != tblobs_.end(); ++it )
		if( it->ttl() > 0 ) {
			--*it;
			it->speedX( it->speedX()*0.9 );
			it->speedY( it->speedY()*0.9 );
			it->step( speed_/fps_ );
		}else
			tblobs_.erase( it-- );


	for( auto it = bullets_.begin(); it != bullets_.end(); ++it )
		if( it->ttl() > 0 ) {
			--*it;
			it->step( speed_/fps_ );
		}else
			bullets_.erase( it-- );

	//std::cout << *this << std::endl;
}

void Game::updateActive() {
	NUM y1 = plane_.y() + 600; //
	NUM y2 = plane_.y(); // - 50;

	for( auto & b : fblobs_ )
		( b.y() > y1 || b.y() < y2 ) ? b.active( false ) : b.active( true );
}

int Game::collisions() {

	int collisions = 0;

	for( const auto & b : blobs_ ) {
		if( plane_.distance(b) < 0 ) {
			++collisions;
			tblobs_.push_back( Blob2d_temp<NUM>( (Blob2d<NUM>)plane_ ) );
		}
	}

	for( auto it = bullets_.begin(); it != bullets_.end(); ++it)
		for( const auto & b : blobs_ )
			if( it->distance(b) < 0 ) {
				tblobs_.push_back( Blob2d_temp<NUM>(b) ); // add explosion
				bullets_.erase( it-- ); //remove bullet
			}

	return collisions;
}

void Game::addBullet() {

	if( plane_.reloaded() ) {
		bullets_.push_back( Blob2d_temp<NUM>(
			plane_.x(), plane_.y() + plane_.radius(), // x, y
			4, 36, //size, frames_to_live
			0, plane_.speedY() + 20 ) ); //velocity x, velocity y
		plane_.fire();
	}
}

std::ostream & operator<<( std::ostream & os, const Game & g) {

	//for (auto b : g.fblobs() )	//fixed blobs
		//os << b.type() << ' ' << b;

	for (auto b : g.blobs() )		//movable blobs
		os << b.type() << ' ' << b;

	for (auto b : g.tblobs() )		//temp blobs
		os << b.type() << ' ' << b;
	for (auto b : g.bullets() )  //bullets (temp blobs)
		os << "b  " << b;
	os << "p " << g.plane(); //plane

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
				g.fblobs_.push_back( Blob2d_fix<NUM>( is ) );
			else if(c == 'm')
				g.blobs_.push_back( Blob2d<NUM>( is ) );
			else if(c == 't')
				g.tblobs_.push_back( Blob2d_temp<NUM>( is ) );
			else
				throw "operator>>( istream &, Game & ) failed: unknown blob type";
		}
	}

	if( is.eof() )
		std::cout << "Game loaded" << std::endl;
	else
		throw "Game failed to load";

	return is;
}
