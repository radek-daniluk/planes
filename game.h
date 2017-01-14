//game.h
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "common.h"
#include "blob2d.h"
#include "blob2d_temp.h"

class Game {

	private:
	Blob2d<int> plane_;
	std::vector< Blob2d_fix<int> > fblobs_;
	std::vector< Blob2d<int> > blobs_;
	std::vector< Blob2d_temp<int> > tblobs_;
	int fps_;
	int speed_;
	void nextStep();

	public:
	Game( std::istream &, int speed = 60, int fps = 60 );
	Game( int speed = 60, int fps = 60 );
	~Game() {};

	void operator++() { nextStep(); }
	int collisions();

	const std::vector< Blob2d<int> > & blobs() const { return blobs_; }
	const std::vector< Blob2d_fix<int> > & fblobs() const { return fblobs_; }
	const std::vector< Blob2d_temp<int> > & tblobs() const { return tblobs_;}

	Blob2d<int> & blob( int n ) { return blobs_[n]; }

	friend istream & operator>>(istream &, Game &);
};

std::ostream & operator<<( std::ostream &, const Game &);

#endif
