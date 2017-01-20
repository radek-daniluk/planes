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

	typedef std::vector< Blob2d_fix<NUM> > VectorF;
	typedef std::vector< Blob2d<NUM> > VectorB;
	typedef std::vector< Blob2d_temp<NUM> > VectorT;

	private:
	NUM speed_;
	NUM fps_;
	Blob2d_shoot<NUM> plane_{600, 0, 80, 30, 0, 0, 20, -20, 30, 7, 1};
	VectorF fblobs_;
	VectorB blobs_;
	VectorT tblobs_;
	VectorT bullets_;

	VectorF::iterator to_active_fix { fblobs_.end() };
	VectorF::iterator from_active_fix { fblobs_.end() };

	VectorB::iterator to_active_blob { blobs_.end() };
	VectorB::iterator from_active_blob { blobs_.end() };

	bool check_game_format(); // checks if blobs are in ascending order

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
