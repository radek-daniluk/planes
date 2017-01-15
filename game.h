//game.h
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "common.h"
#include "blob2d.h"
#include "blob2d_temp.h"

typedef double NUM;

class Game {

	private:
	NUM speed_;
	NUM fps_;
	Blob2d<NUM> plane_{600, 0, 80, 0, 0, 20, -20, -7, -30};
	std::vector< Blob2d_fix<NUM> > fblobs_;
	std::vector< Blob2d<NUM> > blobs_;
	std::vector< Blob2d_temp<NUM> > tblobs_;

	void nextStep();

	public:

	Game( std::istream &, NUM speed = 60, NUM fps = 60 );
	Game( NUM speed = 60, NUM fps = 60 );
	~Game() {};

	void operator++() { nextStep(); }
	int collisions();

	const std::vector< Blob2d<NUM> > & blobs() const { return blobs_; }
	const std::vector< Blob2d_fix<NUM> > & fblobs() const { return fblobs_; }
	const std::vector< Blob2d_temp<NUM> > & tblobs() const { return tblobs_;}

	Blob2d<NUM> & blob( int n ) { return blobs_[n]; }

	const Blob2d<NUM> & plane() const { return plane_; }
	Blob2d<NUM> & nonConstPlane() { return plane_; }

	friend istream & operator>>(istream &, Game &);
};

std::ostream & operator<<( std::ostream &, const Game &);

#endif
