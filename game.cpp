//game.cpp
#include <iterator>
#include <algorithm>
#include "game.h"

Game::Game( std::istream & is, NUM speed ) : speed_(speed) {
	is >> *this;
}

Game::Game( NUM speed ) : speed_(speed) {}

void Game::nextStep ( double interval ) {

	// accelerate speed according to control class instructions and game speed
	double intervalNorm = interval * speed_;
	plane_.accel( accel_plane_x, accel_plane_y, intervalNorm );
	accel_plane_x = accel_plane_y = 0;

	plane_.step( intervalNorm );

	for( auto & b : blobs_ )
		b.step( intervalNorm );

	for( auto it = tblobs_.begin(); it != tblobs_.end(); ++it )
		if( it->ttl() > 0 ) {
			it->speedX( it->speedX()*0.9 );
			it->speedY( it->speedY()*0.9 );
			it->step( intervalNorm );
		}else
			tblobs_.erase( it-- );


	for( auto it = bullets_.begin(); it != bullets_.end(); ++it )
		if( it->ttl() > 0 ) {
			it->step( intervalNorm );
		}else
			bullets_.erase( it-- );

	std::cout << *this << std::endl;
}

void Game::updateActive() {
	NUM y1 = plane_.y() + 600; //
	NUM y2 = plane_.y(); // - 50;

	while( to_active_fix < fblobs_.end() && to_active_fix->y() < y1) {
		to_active_fix->active(true);
		++to_active_fix;
	}
	while( from_active_fix < fblobs_.end() && from_active_fix->y() < y2 ) {
		from_active_fix->active(false);
		++from_active_fix;
	}
}

void Game::collisions() {

	for( const auto & b : blobs_ ) {
		if( plane_.distance(b) < 0 ) {
			tblobs_.push_back( Blob2d_temp<NUM>( (Blob2d<NUM>)plane_, 0.5 ) );
		}
	}

	for( auto it = bullets_.begin(); it != bullets_.end(); ++it)
		for( const auto & b : blobs_ )
			if( it->distance(b) < 0 ) {
				tblobs_.push_back( Blob2d_temp<NUM>(b, 0.5) ); // add explosion
				bullets_.erase( it-- ); //remove bullet
			}
}

void Game::addBullet() {

	if( plane_.reloaded() ) {
		bullets_.push_back( Blob2d_temp<NUM>(
			plane_.x(), plane_.y() + plane_.radius(), // x, y
			12, 0.7, //size, time to live
			0, plane_.speedY() + 1000*speed_ ) ); //velocity x, velocity y
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
		std::cout << "Game data loaded. Checking data..." << std::endl;
	if( g.check_game_format() )
		std::cout << "Game format OK" << std::endl;
	else
		throw "Game failed to load";

	g.to_active_fix = g.from_active_fix = g.fblobs_.begin();
	g.to_active_blob = g.from_active_blob = g.blobs_.begin();

	return is;
}

bool Game::check_game_format() {
	return std::is_sorted( fblobs_.begin(), fblobs_.end() );
}
