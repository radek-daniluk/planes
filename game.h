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
	NUM speed_{1};
	Blob2d_shoot<NUM> plane_{600, 0, 80, 0.7, 0, 0, 600, -600, 1000, 300, 1};
	VectorF fblobs_;
	VectorB blobs_;
	VectorT tblobs_;
	VectorT bullets_;

	NUM accel_plane_x{0};
	NUM accel_plane_y{0};

	VectorF::iterator to_active_fix { fblobs_.end() };
	VectorF::iterator from_active_fix { fblobs_.end() };

	VectorB::iterator to_active_blob { blobs_.end() };
	VectorB::iterator from_active_blob { blobs_.end() };

	bool check_game_format(); // checks if blobs are in ascending order

	public:

	Game( std::istream &, NUM speed );
	Game( NUM speed );
	~Game() {};

	void nextStep( double interval );
	void updateActive();
	void collisions();

	void accelPlane( NUM x, NUM y ) { accel_plane_x += x, accel_plane_y += y; }


	const std::vector< Blob2d<NUM> > & blobs() const { return blobs_; }
	const std::vector< Blob2d_fix<NUM> > & fblobs() const { return fblobs_; }
	const std::vector< Blob2d_temp<NUM> > & tblobs() const { return tblobs_; }
	const std::vector< Blob2d_temp<NUM> > & bullets() const { return bullets_; }

	void addBullet();

	Blob2d<NUM> & blob( int n ) { return blobs_[n]; }

	const auto & plane() const { return plane_; }
	auto & plane() { return plane_; }
	auto & nonConstPlane() { return plane_; }

	friend istream & operator>>(istream &, Game &);
};

std::ostream & operator<<( std::ostream &, const Game &);

#endif
