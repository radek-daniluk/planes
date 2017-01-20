//game.h
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "common.h"
#include "blob2d.h"
#include "blob2d_temp.h"
#include "blob2d_shoot.h"

typedef double NUM;

class Game {

	private:
	NUM speed_;
	NUM fps_;
	Blob2d_shoot<NUM> plane_{600, 0, 80, 30, 0, 0, 20, -20, 30, 7, 1};
	std::vector< Blob2d_fix<NUM> > fblobs_;
	std::vector< Blob2d<NUM> > blobs_;
	std::vector< Blob2d_temp<NUM> > tblobs_;
	std::vector< Blob2d_temp<NUM> > bullets_;

	public:

	Game( std::istream &, NUM speed = 60, NUM fps = 60 );
	Game( NUM speed = 60, NUM fps = 60 );
	~Game() {};

	void nextStep();
	void updateActive();
	int collisions();


	const std::vector< Blob2d<NUM> > & blobs() const { return blobs_; }
	const std::vector< Blob2d_fix<NUM> > & fblobs() const { return fblobs_; }
	const std::vector< Blob2d_temp<NUM> > & tblobs() const { return tblobs_; }
	const std::vector< Blob2d_temp<NUM> > & bullets() const { return bullets_; }

	void addBullet();

	Blob2d<NUM> & blob( int n ) { return blobs_[n]; }

	const auto & plane() const { return plane_; }
	auto & nonConstPlane() { return plane_; }

	friend istream & operator>>(istream &, Game &);
};

std::ostream & operator<<( std::ostream &, const Game &);

#endif
